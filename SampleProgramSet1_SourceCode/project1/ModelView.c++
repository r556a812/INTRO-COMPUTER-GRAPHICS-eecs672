// ModelView.c++ - a basic combined Model and View for OpenGL

#include <iostream>

#include "ModelView.h"
#include "Controller.h"
#include "ShaderIF.h"

double ModelView::mcRegionOfInterest[6] = { -1.0, 1.0, -1.0, 1.0, -1.0, 1.0 };
bool ModelView::aspectRatioPreservationEnabled = true;
int ModelView::numInstances = 0;

// NOTE: You will likely want to modify the ModelView constructor to
//       take additional parameters.
ModelView::ModelView(ShaderIF* sIF, float pointsArray[]) : shaderIF(sIF),serialNumber(numInstances++)
{
	// TODO: define and call method(s) to initialize your model and send data to GPU
	numPoints = pointsArray[10];
	vec2 vertices[numPoints];
	createArray(pointsArray, vertices);
	initModelGeometry(vertices);
}

ModelView::~ModelView()
{
	// TODO: delete the vertex array objects and buffers here
	glDeleteBuffers(1, vbo);
	glDeleteVertexArrays(1, vao);
	vao[0] = vbo[0] = 0;
}

void ModelView::createArray(float pointsArray[], vec2* vertices)
{
	//Declare variables
	int numPoints = pointsArray[10];
	float tmin = pointsArray[8];
	float tmax = pointsArray[9];
	float dt = (tmax - tmin)/(numPoints-1);
	float t = tmin;
	float xt, yt = 0.0;

	//Calculate all the other points and insert into vertices
	for (int i = 0; i < numPoints; i++)
	{
		xt = pointsArray[0] + (pointsArray[1] * t) + (pointsArray[2] * (t*t))
		 			+ (pointsArray[3] * (t*t*t));
		yt = pointsArray[4] + (pointsArray[5] * t) + (pointsArray[6] * (t*t))
					+ (pointsArray[7] * (t*t*t));
		vertices[i][0] = xt;
		vertices[i][1] = yt;

		t += dt;
	}
}

void ModelView::initModelGeometry(vec2* vertices)
{
	if (serialNumber%5 == 4)
	{
		colorScheme[0] = 1.0; colorScheme[1] = 0.0; colorScheme[2] = 0.0;
	}
	else if (serialNumber%5 == 3)
	{
		colorScheme[0] = 0.0; colorScheme[1] = 1.0; colorScheme[2] = 0.0;
	}
	else if (serialNumber%5 == 2)
	{
		colorScheme[0] = 0.0; colorScheme[1] = 0.0; colorScheme[2] = 1.0;
	}
	else if (serialNumber%5 == 1)
	{
		colorScheme[0] = 1.0; colorScheme[1] = 1.0; colorScheme[2] = 0.0;
	}
	else
	{
		colorScheme[0] = 1.0; colorScheme[1] = 0.0; colorScheme[2] = 1.0;
	}

	//Create the VAO and VBO
	glGenVertexArrays(1, vao);
	glGenBuffers(1, vbo);

	//Initialize VAO and VBO
	glBindVertexArray(vao[0]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

	//Allocate spaace on GPU and send the data
	int numBytes = numPoints * sizeof(vec2) * sizeof(float);
	glBufferData(GL_ARRAY_BUFFER, numBytes, vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(shaderIF->pvaLoc("mcPosition"), 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(shaderIF->pvaLoc("mcPosition"));

	//Find the x min and max and the y min and max
	xmin = xmax = vertices[0][0];
	ymin = ymax = vertices[0][1];
	for (int i = 1; i < numPoints; i++)
	{
		if (vertices[i][0] > xmax)
		{
			xmax = vertices[i][0];
		}
		else if (vertices[i][0] < xmin)
		{
			xmin = vertices[i][0];
		}

		if (vertices[i][1] > ymax)
		{
			ymax = vertices[i][1];
		}
		else if (vertices[i][1] < ymin)
		{
			ymin = vertices[i][1];
		}
	}
}

void ModelView::compute2DScaleTrans(float* scaleTransF) // CLASS METHOD
{
	// TODO: This code can be used as is, BUT be absolutely certain you
	//       understand everything about how it works.

	double xmin = mcRegionOfInterest[0];
	double xmax = mcRegionOfInterest[1];
	double ymin = mcRegionOfInterest[2];
	double ymax = mcRegionOfInterest[3];

	if (aspectRatioPreservationEnabled)
	{
		// preserve aspect ratio. Make "region of interest" wider or taller to
		// match the Controller's viewport aspect ratio.
		double vAR = Controller::getCurrentController()->getViewportAspectRatio();
		matchAspectRatio(xmin, xmax, ymin, ymax, vAR);
	}

    // We are only concerned with the xy extents for now, hence we will
    // ignore mcRegionOfInterest[4] and mcRegionOfInterest[5].
    // Map the overall limits to the -1..+1 range expected by the OpenGL engine:
	double scaleTrans[4];
	linearMap(xmin, xmax, -1.0, 1.0, scaleTrans[0], scaleTrans[1]);
	linearMap(ymin, ymax, -1.0, 1.0, scaleTrans[2], scaleTrans[3]);
	for (int i=0 ; i<4 ; i++)
		scaleTransF[i] = static_cast<float>(scaleTrans[i]);
}

// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
void ModelView::getMCBoundingBox(double* xyzLimits) const
{
	// TODO:
	// Put this ModelView instance's min and max x, y, and z extents
	// into xyzLimits[0..5]. (-1 .. +1 is OK for z direction for 2D models)
	xyzLimits[0] = xmin;
	xyzLimits[1] = xmax;
	xyzLimits[2] = ymin;
	xyzLimits[3] = ymax;
	xyzLimits[4] = -1;
	xyzLimits[5] = 1;
}

bool ModelView::handleCommand(unsigned char anASCIIChar, double ldsX, double ldsY)
{
	return true;
}

// linearMap determines the scale and translate parameters needed in
// order to map a value, f (fromMin <= f <= fromMax) to its corresponding
// value, t (toMin <= t <= toMax). Specifically: t = scale*f + trans.
void ModelView::linearMap(double fromMin, double fromMax, double toMin, double toMax,
					  double& scale, double& trans) // CLASS METHOD
{
	scale = (toMax - toMin) / (fromMax - fromMin);
	trans = toMin - scale*fromMin;
}

void ModelView::matchAspectRatio(double& xmin, double& xmax,
        double& ymin, double& ymax, double vAR)
{
	// TODO: This code can be used as is, BUT be absolutely certain you
	//       understand everything about how it works.

	double wHeight = ymax - ymin;
	double wWidth = xmax - xmin;
	double wAR = wHeight / wWidth;
	if (wAR > vAR)
	{
		// make window wider
		wWidth = wHeight / vAR;
		double xmid = 0.5 * (xmin + xmax);
		xmin = xmid - 0.5*wWidth;
		xmax = xmid + 0.5*wWidth;
	}
	else
	{
		// make window taller
		wHeight = wWidth * vAR;
		double ymid = 0.5 * (ymin + ymax);
		ymin = ymid - 0.5*wHeight;
		ymax = ymid + 0.5*wHeight;
	}
}

void ModelView::render() const
{
	// save the current GLSL program in use
	GLint pgm;
	glGetIntegerv(GL_CURRENT_PROGRAM, &pgm);

	// draw the triangles using our vertex and fragment shaders
	glUseProgram(shaderIF->getShaderPgmID());

	// TODO: set scaleTrans (and all other needed) uniform(s)
	float scaleTrans[4];
	compute2DScaleTrans(scaleTrans);
	glUniform4fv(shaderIF->ppuLoc("scaleTrans"), 1, scaleTrans);
	// TODO: make require primitive call(s)
	glUniform3fv(shaderIF->ppuLoc("color"), 1, colorScheme);
	glBindVertexArray(vao[0]);
	glDrawArrays(GL_LINE_STRIP, 0, numPoints);
	// restore the previous program
	glUseProgram(pgm);
}

void ModelView::setMCRegionOfInterest(double xyz[6])
{
	for (int i=0 ; i<6 ; i++)
		mcRegionOfInterest[i] = xyz[i];
}
