attribute float		divAtt;
attribute float		moffsetXAtt;
attribute float		moffsetYAtt;
attribute float     angleAtt;
//attribute float     alphaAtt;
varying float       mDiv;
varying float       mOffsetX;
varying float       mOffsetY;
//varying float alpha;
varying float angle;

void main() {
    mOffsetX = moffsetXAtt;
    mOffsetY = moffsetYAtt;
    mDiv=divAtt;
//    alpha = alphaAtt;
    angle = angleAtt;
//    float a = gl_Normal.x;
    
	gl_TexCoord[0] = gl_MultiTexCoord0;

	vec4 eyeCoord = gl_ModelViewMatrix * gl_Vertex;
	gl_Position = gl_ProjectionMatrix * eyeCoord;
	float dist = sqrt(eyeCoord.x*eyeCoord.x + eyeCoord.y*eyeCoord.y + eyeCoord.z*eyeCoord.z);
	float att	 = 600.0 / dist;
	
	gl_PointSize = gl_Normal.x ;
	gl_FrontColor =  gl_Color;
}





