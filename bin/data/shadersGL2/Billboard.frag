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
    vec4 base = texture2D(tex, texCoor*d+vec2(x,y));
//    gl_FragColor = base*gl_Color;
    if (!(gl_Color.r == 1.0 && gl_Color.g == 1.0  && gl_Color.b == 1.0) )
    {
        vec4 result =  mix(base, gl_Color, gl_Color.a);//vec4(1.0,1.0,1.0,1.0);
        result.a  = base.a * gl_Color.a;
//        gl_FragColor = base;
        gl_FragColor = result;
    }
    else
    {
        vec4 result =  mix(base, gl_Color,base.a);//vec4(1.0,1.0,1.0,1.0);
        result.a = gl_Color.a*base.a;
        gl_FragColor = result;
    }

	 
}
