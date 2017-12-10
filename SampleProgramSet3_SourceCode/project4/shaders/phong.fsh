#version 410 core

// phong.fsh - a fragment shader that implements a Phong Lighting model.

in PVA
{
	vec3 ecPosition;
	vec3 ecUnitNormal;
	vec2 texCoords;
} pvaIn;

out vec4 fragmentColor;

uniform sampler2D textureMap;
uniform int texUse = 0;

const int MAX_NUM_LIGHTS = 3;

uniform vec3 kd = vec3(0.8, 0.0, 0.0); // default: darkish red
uniform vec3 ka = vec3(0.8, 0.0, 0.0);
uniform vec3 ks = vec3(0.8, 0.0, 0.0);
uniform vec3 globalAmbient = vec3(0.2, 0.2, 0.2);
uniform vec3 lightStrength[MAX_NUM_LIGHTS];
uniform vec4 p_ecLightPos[MAX_NUM_LIGHTS];
uniform int actualNumLights;
uniform float shininess;
uniform mat4 ec_lds;
uniform float alpha;

uniform int sceneHasTranslucentObjects = 0;
uniform int drawingOpaqueObjects = 1;


float atten(vec3 i, vec3 q)
{
	return (1/(distance(i, q)/2));
}

vec4 evaluateLightingModel()
{
	vec3 vHat;
	float m = shininess;
	vec3 final = vec3(0.0, 0.0, 0.0);
	final += ka*globalAmbient;

	if (ec_lds[2][3] != 0)
	{
		vHat = normalize(-pvaIn.ecPosition);
	}
	else
	{
		vec3 o = vec3(((-ec_lds[2][0])/ec_lds[0][0]), ((-ec_lds[2][1])/ec_lds[1][1]), 1);
		vHat = normalize(o);
	}

	vec3 norm = pvaIn.ecUnitNormal;
	if (dot(vHat, norm) < 0)
	{
		norm = -norm;
	}

	vec3 q = pvaIn.ecPosition;
	vec3 riHat;
	vec3 liHat;
	vec3 liStrength;
	float att = 1.0;
	vec3 totalDiffuse;
	vec3 totalSpecular;
	for (int i = 0; i < actualNumLights; i++)
	{
		vec4 liPosition = vec4(p_ecLightPos[i]);
		liStrength = vec3(lightStrength[i]);

		if (liPosition.w == 1)
		{
			liHat = normalize(liPosition.xyz - q);
			att = atten(liPosition.xyz, q)*5;
		}
		else
		{
			liHat = normalize(liPosition.xyz);
		}

		riHat = normalize(-reflect(liHat, norm));

		if (dot(liHat, norm) > 0)
		{
			if (liPosition.w == 1)
			{
				final += att*kd*liStrength*dot(liHat, norm);
			}
			else
			{
				final += kd*liStrength*dot(liHat, norm);
			}
		}

		if (dot(riHat, vHat) > 0)
		{
			if (liPosition.w == 1)
			{
				final += att*ks*liStrength*pow(dot(riHat, vHat), m);
			}
			else
			{
				final += ks*liStrength*pow(dot(riHat, vHat), m);
			}
		}
	}

	return vec4(final, alpha);
}

void main ()
{
		vec4 textureColor;
		vec4 color = evaluateLightingModel();



		if(texUse == 1)
		{
			textureColor = texture(textureMap, pvaIn.texCoords);
		}
		else
		{
			textureColor = vec4(1,1,1,1);
		}

		color = textureColor * color;


    if (sceneHasTranslucentObjects == 1)
    {
        if (drawingOpaqueObjects == 1)
            if (color.w < 1.0)
                discard;
            else
                fragmentColor = color;

        else if (color.w < 1)
            fragmentColor = color;

        else
            discard;
    }
    else
        fragmentColor = color;


}
