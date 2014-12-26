uniform sampler2D tex;

varying vec2 texcoord0;
varying float texScale;
varying float offsetX;
varying float offsetY;

void main (void) {
	gl_FragColor = texture2D(tex,texcoord0) * gl_Color;
}
