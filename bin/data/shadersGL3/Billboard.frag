#version 150

uniform sampler2D tex;

in vec4 colorVarying;

out vec4 fragColor;

in float div;
in float offsetX;
in float offsetY;
in  float		rotAngle;

void main (void) {
    float d = div;
    float x = offsetX;
    float y = offsetY;
	fragColor = texture(tex, gl_PointCoord*d+vec2(x,y)) * colorVarying;
}
