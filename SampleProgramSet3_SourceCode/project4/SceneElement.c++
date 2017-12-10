// SceneElement.c++

#include "SceneElement.h"
#include "ImageReader.h"

float SceneElement::lightPos[4*MAX_NUM_LIGHTS] =
	{
		25.0, 15.0, 10.0, 1.0,
		25.0, 15.0, 30.0, 1.0,
		0.0, 1.0, 1.0, 0.0
	};

// Are coordinates in "lightPos" stored in MC or EC?
bool SceneElement::posInModelCoordinates[MAX_NUM_LIGHTS] =
	{ true, true, false };
// The following is the buffer actually sent to GLSL. It will contain a copy of
// the (x,y,z,w) for light sources defined in EC; it will contain the coordinates
// after transformation to EC if the position was originally specified in MC.
float posToGLSL[4*MAX_NUM_LIGHTS];

float SceneElement::lightStrength[3*MAX_NUM_LIGHTS] =
	{
		0.55, 0.55, 0.45, //0.65 0.65 0.45
		0.55, 0.55, 0.45,
		0.35, 0.35, 0.4 //0.25 0.25 0.3
	};

float SceneElement::globalAmbient[] = { 0.2, 0.2, 0.2 };

SceneElement::SceneElement(ShaderIF* sIF, const PhongMaterial& matlIn) :
	shaderIF(sIF), matl(matlIn), texID(0), colorGenerationMode(-1),
	textureSource(-1)
{
}

SceneElement::~SceneElement()
{
}

GLuint SceneElement::defineTexture(const char* texImageSource)
{
	if (texImageSource == NULL)
		return 0;
	ImageReader* texImage = ImageReader::create(texImageSource);
	if (texImage == NULL)
		return 0;

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	GLuint locID[1];
	glGenTextures(1, locID);
	glBindTexture(GL_TEXTURE_2D, locID[0]);
	//float borderColor[] = { bcRed, bcGreen, bcBlue, bcAlpha };
	float borderColor[] = { 1,1,1,0 };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);

	GLint mipmapLevel = 0;
	int pw = texImage->getWidth();
	int ph = texImage->getHeight();

	GLint iFormat = texImage->getInternalFormat();
	GLenum format = texImage->getFormat();
	GLenum type = texImage->getType();
	const GLint border = 0; // must be zero (only present for backwards compatibility)
	const void* pixelData = texImage->getTexture();
	glTexImage2D(GL_TEXTURE_2D, mipmapLevel, iFormat, pw, ph, border, format, type, pixelData);

	delete texImage; // all relevant information has been copied to OpenGL

	return locID[0];
}

void SceneElement::establishLightingEnvironment()
{
	// This should set:
	// "actualNumLights", "ecLightPosition", "lightStrength", "globalAmbient"
	float ecLightPosition[4*MAX_NUM_LIGHTS];
	float temp[4];
	float temp2[4];
	cryph::Matrix4x4 mc_ec, ec_lds;
	getMatrices(mc_ec, ec_lds);

	for (int i = 0; i < MAX_NUM_LIGHTS; i++)
	{
		temp[0] = lightPos[4*i];
		temp[1] = lightPos[4*i+1];
		temp[2] = lightPos[4*i+2];
		temp[3] = lightPos[4*i+3];

		if (posInModelCoordinates[i] == true)
		{
			mc_ec.multiply(temp, temp2, 4);

			ecLightPosition[4*i] = temp2[0];
			ecLightPosition[4*i+1] = temp2[1];
			ecLightPosition[4*i+2] = temp2[2];
			ecLightPosition[4*i+3] = temp[3];
		}
		else
		{
			ecLightPosition[4*i] = temp[0];
			ecLightPosition[4*i+1] = temp[1];
			ecLightPosition[4*i+2] = temp[2];
			ecLightPosition[4*i+3] = temp[3];
		}
	}

	int actualNumLights = 3;

	glUniform4fv(shaderIF->ppuLoc("p_ecLightPos"), actualNumLights, ecLightPosition);
  glUniform3fv(shaderIF->ppuLoc("lightStrength"), actualNumLights, lightStrength);
	glUniform1i(shaderIF->ppuLoc("actualNumLights"), actualNumLights);
	glUniform3fv(shaderIF->ppuLoc("globalAmbient"), 1, globalAmbient);
}

void SceneElement::establishMaterial()
{
	glUniform3fv(shaderIF->ppuLoc("kd"), 1, matl.kd);
	glUniform3fv(shaderIF->ppuLoc("ka"), 1, matl.ka);
	glUniform3fv(shaderIF->ppuLoc("ks"), 1, matl.ks);
	glUniform1f(shaderIF->ppuLoc("shininess"), matl.shininess);
	glUniform1f(shaderIF->ppuLoc("alpha"), matl.alpha);
}

void SceneElement::establishTexture()
{
	// Unless you are texture-mapping onto faces of BasicShape instances,
	// this method should be called from your render method, and it should
	// set texture-related parameters like:
	// "colorGenerationMode", "textureSource", "textureMap"
	// It should also do the appropriate call to glBindTexture.
	// (If you are texture-mapping onto faces of BasicShape instances,
	// you use the "prepareForFace" callback which may or may not be
	// implemented by calling this method.)

	int activeTexture = 0; // We will study this under "advanced texture mapping"
	glActiveTexture(GL_TEXTURE0 + activeTexture);

	// Set the textureMap uniform variable in the fragment shader so
	// that it will use the current "texture unit" we just specified above.
	glUniform1i(shaderIF->ppuLoc("textureMap"), activeTexture);
	glUniform1i(shaderIF->ppuLoc("texUse"), 1);

	// glBindTexture reestablishes the current texture along with its settings.
	glBindTexture(GL_TEXTURE_2D, texID);

	// If any texture parameters need to be set (or if ones set when the texture
	// was defined have changed), we set them here with their current values.
	// For example:
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
}

void SceneElement::establishView()
{
	// Line of sight, dynamic view controls, 3D-2D projection, & mapping to LDS:
	cryph::Matrix4x4 mc_ec, ec_lds;
	ModelView::getMatrices(mc_ec, ec_lds);
	float m[16];
	glUniformMatrix4fv(shaderIF->ppuLoc("mc_ec"), 1, false, mc_ec.extractColMajor(m));
	glUniformMatrix4fv(shaderIF->ppuLoc("ec_lds"), 1, false, ec_lds.extractColMajor(m));
}

bool SceneElement::handleCommand(unsigned char anASCIIChar, double ldsX, double ldsY)
{
	if (anASCIIChar == 'O')
		ModelView::setProjection(ORTHOGONAL);
	else if (anASCIIChar == 'P')
		ModelView::setProjection(PERSPECTIVE);
	else if (anASCIIChar == 'Q')
		ModelView::setProjection(OBLIQUE);
	else
		return ModelView::handleCommand(anASCIIChar, ldsX, ldsY);
	Controller::getCurrentController()->redraw();
	return true;
}

void SceneElement::setColorGenerationMode(int mode, int onFace)
{
	colorGenerationMode = mode;
}

void SceneElement::setTextureImage(const std::string& imgFileName, int onFace)
{
	ImageReader* ir = ImageReader::create(imgFileName.c_str());
	if (ir == nullptr)
	{
		std::cerr << "Could not open '" << imgFileName << "' for texture map.\n";
		return;
	}
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);
	float white[] = { 1.0, 1.0, 1.0, 1.0 };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, white);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); //GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); //GL_CLAMP_TO_BORDER);
	GLint level = 0;
	int pw = ir->getWidth(), ph = ir->getHeight();
	GLint iFormat = ir->getInternalFormat();
	GLenum format = ir->getFormat();
	GLenum type = ir->getType();
	const GLint border = 0; // must be zero (only present for backwards compatibility)
	const void* pixelData = ir->getTexture();
	glTexImage2D(GL_TEXTURE_2D, level, iFormat, pw, ph, border, format, type, pixelData);
	delete ir;
}

void SceneElement::setTextureSource(int source, int onFace)
{
	textureSource = source;
}
