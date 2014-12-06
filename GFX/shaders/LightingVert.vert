#version 110

uniform vec3 lightPos1;
uniform vec3 lightPos2;
uniform vec3 lightPos3;
uniform vec3 lightPos4;

uniform vec4 lightColor1;
uniform vec4 lightColor2;
uniform vec4 lightColor3;
uniform vec4 lightColor4;

//light radius ^ 2, because that way GPU does less math
uniform float lightRadius1;
uniform float lightRadius2;
uniform float lightRadius3;
uniform float lightRadius4;

varying vec3 TN;
varying vec3 v;

//light positions for specular mapping
varying vec3 olightPos1;
varying vec3 olightPos2;
varying vec3 olightPos3;
varying vec3 olightPos4;

varying vec4 oLightColor1;
varying vec4 oLightColor2;
varying vec4 oLightColor3;
varying vec4 oLightColor4;

varying mat3 oNormalMatrix;

float getLengthSQR (vec3 vec) {
	return(vec.x*vec.x+vec.y*vec.y+vec.z*vec.z);
} 

void main(void)
{
	
	v = vec3(gl_ModelViewMatrix * gl_Vertex);       
	vec3 N = gl_Normal;
	
	TN = gl_NormalMatrix*N;
	TN = normalize(TN);
	
	oNormalMatrix = gl_NormalMatrix;
	
	olightPos1 = lightPos1 - v;
	olightPos2 = lightPos2 - v;
	olightPos3 = lightPos3 - v;
	olightPos4 = lightPos4 - v;
	
	oLightColor1 = lightColor1;
	oLightColor2 = lightColor2;
	oLightColor3 = lightColor3;
	oLightColor4 = lightColor4;
	
	oLightColor1 *= vec4(vec3(max(1.0/(getLengthSQR(olightPos1)/lightRadius1),0.0)*0.8),1.0);
	oLightColor2 *= vec4(vec3(max(1.0/(getLengthSQR(olightPos2)/lightRadius2),0.0)*0.8),1.0);
	oLightColor3 *= vec4(vec3(max(1.0/(getLengthSQR(olightPos3)/lightRadius3),0.0)*0.8),1.0);
	oLightColor4 *= vec4(vec3(max(1.0/(getLengthSQR(olightPos4)/lightRadius4),0.0)*0.8),1.0);
	
	olightPos1 = normalize(olightPos1);
	olightPos2 = normalize(olightPos2);
	olightPos3 = normalize(olightPos3);
	olightPos4 = normalize(olightPos4);
	
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	
	v = normalize(-v);
	
	gl_TexCoord[0] = gl_MultiTexCoord0;
	
}