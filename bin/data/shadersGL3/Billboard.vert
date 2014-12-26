#version 150

uniform mat4 orientationMatrix;
uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 textureMatrix;
uniform mat4 modelViewProjectionMatrix;

in vec4  position;
in vec4  color;
in vec3  normal;

out vec4 colorVarying;


in float divAtt;
in float offsetXAtt;
in float offsetYAtt;
in float angle;

out float div;
out float offsetX;
out float offsetY;
out float rotAngle;

void main() {
    
    offsetX = offsetXAtt;
    offsetY = offsetYAtt;
    div = divAtt;
    rotAngle = angle;
    
	vec4 eyeCoord = modelViewMatrix * position;
	gl_Position = projectionMatrix * eyeCoord; // to be accurate this should premultiply by orientationMatrix
	
	float dist = sqrt(eyeCoord.x*eyeCoord.x + eyeCoord.y*eyeCoord.y + eyeCoord.z*eyeCoord.z);
	float att	 = 600.0 / dist;
	
	gl_PointSize = normal.x * att;
	colorVarying = color;
}





