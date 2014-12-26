uniform sampler2D tex;
varying float div;
varying float offsetX;
varying float offsetY;

void main (void) {
    
    float d = div;
    float x = offsetX;
    float y = offsetY;
    
	gl_FragColor = texture2D(tex,gl_TexCoord[0].st*d+vec2(x,y)) * gl_Color;
}
