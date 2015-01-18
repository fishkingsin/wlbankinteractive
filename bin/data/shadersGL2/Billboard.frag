uniform sampler2D tex;
varying float mDiv;
varying float mOffsetX;
varying float mOffsetY;
//varying float alpha;
varying float angle;
void main (void) {
    float d = mDiv;
    float x = mOffsetX;
    float y = mOffsetY;
//    float a = alpha;
    float ang = angle;
    vec2 offset		= vec2(.5, .5);
    vec2 v2 = gl_TexCoord[0].st;//vec2(gl_TexCoord[0].st*d+vec2(x,y));
    float cosX, sinX;
    float cosY, sinY;
    sinX = sin(ang);
    cosX = cos(ang);
    sinY = sin(ang);
    cosY = cos(ang);
    
    mat2 rotationMatrix = mat2( cosX, -sinX,
                               sinY, cosX);
    
    vec2 newcoords = ((v2-offset) * (rotationMatrix));
    newcoords += offset;

    vec2 texCoor = newcoords;
    vec4 c = texture2D(tex, texCoor*d+vec2(x,y));
    vec4 result =  mix(c, gl_Color, c.a);//vec4(1.0,1.0,1.0,1.0);
//    if (c.r < 0.5 || c.r < 0.5 || c.r < 0.5) {
//        result = 2.0 * c * gl_Color;
//    } else {
//        result = vec4(1.0) - 2.0 * (vec4(1.0) - gl_Color) * (vec4(1.0) - c);
//    }
//    if (c.g < 0.5) {
//        result = 2.0 * c * gl_Color;
//    } else {
//        result = vec4(1.0) - 2.0 * (vec4(1.0) - gl_Color) * (vec4(1.0) - c);
//    }
//    if (c.b < 0.5) {
//        result = 2.0 * c * gl_Color;
//    } else {
//        result = vec4(1.0) - 2.0 * (vec4(1.0) - gl_Color) * (vec4(1.0) - c);
//    }
//    result.a = c.a*gl_Color.a;

//    gl_FragColor = result;
    gl_FragColor = c*gl_Color;
	 
}
