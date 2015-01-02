uniform sampler2D tex;
varying float mDiv;
varying float mOffsetX;
varying float mOffsetY;
void main (void) {
    float d = mDiv;
    float x = mOffsetX;
    float y = mOffsetY;
	gl_FragColor = texture2D(tex, vec2(gl_TexCoord[0].st*d+vec2(x,y))) * gl_Color;
}
