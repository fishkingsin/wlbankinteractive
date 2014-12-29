uniform sampler2D tex;
varying float div;
varying float offsetX;
varying float offsetY;
varying  float		rotAngle;
varying float alpha;
void main (void) {
    
    float d = div;
    float x = offsetX;
    float y = offsetY;
    float a = alpha;
    
    float angle		= rotAngle;
    vec2 offset		= vec2(.5, .5)*d;
    vec2 v2 = gl_TexCoord[0].st*d+vec2(x,y);
    
    // not sure this is right
    // I just search on how to rotate
    // a texture...
    float cosX, sinX;
    float cosY, sinY;
    sinX = sin(angle);
    cosX = cos(angle);
    sinY = sin(angle);
    cosY = cos(angle);
    
    mat2 rotationMatrix = mat2( cosX, -sinX,
                               sinY, cosX);
    
    vec2 newcoords = ((v2-offset) * (rotationMatrix));
    newcoords += offset;
    vec4 col = texture2D(tex,v2);
    col.a *= a;
	gl_FragColor = col * gl_Color ;
}
