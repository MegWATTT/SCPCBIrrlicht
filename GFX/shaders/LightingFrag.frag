#version 120

varying vec3 TN;
varying vec3 pos;

varying vec4 distFromCenter;

uniform sampler2D baseMap;
uniform sampler2D diffuseLight;
uniform sampler2D specularLight;
uniform sampler2D fogTexture;

uniform float fogNear;
uniform float fogFar;

uniform float renderSpecularFactor;

void main(void)
{
	vec4 finalImage = vec4(texture2D( baseMap, gl_TexCoord[0].xy ).xyz,1.0);
	finalImage*=vec4(texture2D(diffuseLight,gl_FragCoord.xy/vec2(1280.0,720.0)).xyz,1.0);
	finalImage+=vec4(texture2D(specularLight,gl_FragCoord.xy/vec2(1280.0,720.0)).xyz,1.0);
	
	float fog = (sqrt(distFromCenter.x*distFromCenter.x+distFromCenter.y*distFromCenter.y+distFromCenter.z*distFromCenter.z)-fogNear);
	fog /= fogFar-fogNear;
	fog = clamp(1.0-fog,0.0,1.0);
	fog*=fog;
	
	finalImage=(finalImage*vec4(vec3(fog),1.0))+(texture2D(fogTexture,gl_FragCoord.xy/vec2(1280.0,720.0))*vec4(vec3(1.0-fog),1.0));
	
	gl_FragData[0] = (finalImage*vec4(1.0-renderSpecularFactor))+vec4(renderSpecularFactor*0.3);
	gl_FragData[1] = vec4(normalize(TN),1.0);
	gl_FragData[2] = vec4(pos,1.0);
}
