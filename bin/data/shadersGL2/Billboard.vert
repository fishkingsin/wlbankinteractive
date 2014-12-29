attribute float divAtt;
attribute float offsetXAtt;
attribute float offsetYAtt;

varying float div;
varying float offsetX;
varying float offsetY;
attribute float angle;
varying float rotAngle;

attribute float alphaAtt;
varying float alpha;

void main() {
    offsetX = offsetXAtt;
    offsetY = offsetYAtt;
    div = divAtt;
    rotAngle = angle;
    alpha = alphaAtt;

    
    gl_TexCoord[0] = gl_MultiTexCoord0;
    vec4 eyeCoord  = gl_ModelViewMatrix * gl_Vertex;
    gl_Position    = gl_ProjectionMatrix * eyeCoord;
    float dist     = sqrt(eyeCoord.x*eyeCoord.x + eyeCoord.y*eyeCoord.y + eyeCoord.z*eyeCoord.z);
    float att	   = 600.0 / dist;
    gl_PointSize = gl_Normal.x * att;
    gl_FrontColor  = gl_Color;
}





