//
//  CommonAssets.cpp
//  wlbankinteractive
//
//  Created by Kong king sin on 29/12/14.
//
//

#include "CommonAssets.h"
struct token_name {
    GLuint count;
    GLenum token;
    const char *name;
};


void
print_extension_list(char *ext)
{
    const char *indentString = "    ";
    const int indent = 4;
    const int max = 79;
    int width, i, j;
    
    if (!ext || !ext[0])
        return;
    
    width = indent;
    printf("%s", indentString);
    i = j = 0;
    while (1) {
        if (ext[j] == ' ' || ext[j] == 0) {
            /* found end of an extension name */
            const int len = j - i;
            if (width + len > max) {
                /* start a new line */
                printf("\n");
                width = indent;
                printf("%s", indentString);
            }
            /* print the extension name between ext[i] and ext[j] */
            while (i < j) {
                printf("%c", ext[i]);
                i++;
            }
            /* either we're all done, or we'll continue with next extension */
            width += len + 1;
            if (ext[j] == 0) {
                break;
            }
            else {
                i++;
                j++;
                if (ext[j] == 0)
                    break;
                printf(", ");
                width += 2;
            }
        }
        j++;
    }
    printf("\n");
}

static void
print_limits(void)
{
    
    static const struct token_name openglLimits[] = {
        { 1, GL_MAX_ATTRIB_STACK_DEPTH, "GL_MAX_ATTRIB_STACK_DEPTH" },
        { 1, GL_MAX_CLIENT_ATTRIB_STACK_DEPTH, "GL_MAX_CLIENT_ATTRIB_STACK_DEPTH" },
        { 1, GL_MAX_CLIP_PLANES, "GL_MAX_CLIP_PLANES" },
        { 1, GL_MAX_COLOR_MATRIX_STACK_DEPTH, "GL_MAX_COLOR_MATRIX_STACK_DEPTH" },
        { 1, GL_MAX_ELEMENTS_VERTICES, "GL_MAX_ELEMENTS_VERTICES" },
        { 1, GL_MAX_ELEMENTS_INDICES, "GL_MAX_ELEMENTS_INDICES" },
        { 1, GL_MAX_EVAL_ORDER, "GL_MAX_EVAL_ORDER" },
        { 1, GL_MAX_LIGHTS, "GL_MAX_LIGHTS" },
        { 1, GL_MAX_LIST_NESTING, "GL_MAX_LIST_NESTING" },
        { 1, GL_MAX_MODELVIEW_STACK_DEPTH, "GL_MAX_MODELVIEW_STACK_DEPTH" },
        { 1, GL_MAX_NAME_STACK_DEPTH, "GL_MAX_NAME_STACK_DEPTH" },
        { 1, GL_MAX_PIXEL_MAP_TABLE, "GL_MAX_PIXEL_MAP_TABLE" },
        { 1, GL_MAX_PROJECTION_STACK_DEPTH, "GL_MAX_PROJECTION_STACK_DEPTH" },
        { 1, GL_MAX_TEXTURE_STACK_DEPTH, "GL_MAX_TEXTURE_STACK_DEPTH" },
        { 1, GL_MAX_TEXTURE_SIZE, "GL_MAX_TEXTURE_SIZE" },
        { 1, GL_MAX_3D_TEXTURE_SIZE, "GL_MAX_3D_TEXTURE_SIZE" },
        { 1, GL_MAX_CUBE_MAP_TEXTURE_SIZE_ARB, "GL_MAX_CUBE_MAP_TEXTURE_SIZE_ARB" },
        { 1, GL_MAX_RECTANGLE_TEXTURE_SIZE_NV, "GL_MAX_RECTANGLE_TEXTURE_SIZE_NV" },
        { 1, GL_NUM_COMPRESSED_TEXTURE_FORMATS_ARB, "GL_NUM_COMPRESSED_TEXTURE_FORMATS_ARB" },
        { 1, GL_MAX_TEXTURE_UNITS_ARB, "GL_MAX_TEXTURE_UNITS_ARB" },
        { 1, GL_MAX_TEXTURE_LOD_BIAS_EXT, "GL_MAX_TEXTURE_LOD_BIAS_EXT" },
        { 1, GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, "GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT" },
        { 2, GL_MAX_VIEWPORT_DIMS, "GL_MAX_VIEWPORT_DIMS" },
        { 2, GL_ALIASED_LINE_WIDTH_RANGE, "GL_ALIASED_LINE_WIDTH_RANGE" },
        { 2, GL_SMOOTH_LINE_WIDTH_RANGE, "GL_SMOOTH_LINE_WIDTH_RANGE" },
        { 2, GL_ALIASED_POINT_SIZE_RANGE, "GL_ALIASED_POINT_SIZE_RANGE" },
        { 2, GL_SMOOTH_POINT_SIZE_RANGE, "GL_SMOOTH_POINT_SIZE_RANGE" },
        { 0, (GLenum) 0, NULL }
    };
    GLint i, max[2];
    printf("OpenGL limits:\n");
    for (i = 0; openglLimits[i].count; i++) {
        glGetIntegerv(openglLimits[i].token, max);
        if (glGetError() == GL_NONE) {
            if (openglLimits[i].count == 1)
                printf("    %s = %d\n", openglLimits[i].name, max[0]);
            else /* XXX fix if we ever query something with more than 2 values */
                printf("    %s = %d, %d\n", openglLimits[i].name, max[0], max[1]);
        }
    }
}

void printShaderLimits(){
    
    static const struct token_name lll[] = {
        { 1, GL_MAX_VERTEX_ATTRIBS, "GL_MAX_VERTEX_ATTRIBS" },
        { 1, GL_MAX_VERTEX_UNIFORM_COMPONENTS, "GL_MAX_VERTEX_UNIFORM_COMPONENTS" },
        { 1, GL_MAX_VARYING_FLOATS, "GL_MAX_VARYING_FLOATS" },
        { 1, GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, "GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS" },
        { 1, GL_MAX_TEXTURE_IMAGE_UNITS, "GL_MAX_TEXTURE_IMAGE_UNITS" },
        { 0, (GLenum) 0, NULL }
    };
    
    GLint i, max[2];
    printf("Shader limits:\n");
    for (i = 0; lll[i].count; i++) {
        glGetIntegerv(lll[i].token, max);
        if (glGetError() == GL_NONE) {
            if (lll[i].count == 1)
                printf("    %s = %d\n", lll[i].name, max[0]);
            else /* XXX fix if we ever query something with more than 2 values */
                printf("    %s = %d, %d\n", lll[i].name, max[0], max[1]);
        }
    }
}


void printGLInfo(){
    
    char *version = NULL;
    char *vendor = NULL;
    char *renderer = NULL;
    //    char *extensions = NULL;
    //    int   glutVersion;
    
    //glutVersion = glutGet(0x01FC);
    version =     (char*)glGetString(GL_VERSION);
    vendor =      (char*)glGetString(GL_VENDOR);
    renderer =    (char*)glGetString(GL_RENDERER);
    
    printf("version=%s\nvendor=%s\nrenderer=%s\n",
           version,vendor,renderer);
    
}
void CommonAssets::loadImage(string filePath , int col , int row ,int  nParticle)
{
    
    texture.loadImage(filePath);
    
    texW = texture.getWidth();
    texH = texture.getHeight();
    
    cellRows  = col;
    cellColls = row;
    kParticles = nParticle *1024;
}
void CommonAssets::setup()
{
    bgDir.listDir("backgrounds/");
    logoDir.listDir("logos/");
    billboards.setUsage( GL_DYNAMIC_DRAW );
    billboards.setMode(OF_PRIMITIVE_POINTS);
    
    
    billboardShader.setGeometryInputType(GL_POINT);
    billboardShader.setGeometryOutputType(GL_TRIANGLE_STRIP);
    billboardShader.setGeometryOutputCount(4);
    if(ofGetGLProgrammableRenderer()){
        ofLogVerbose()<< "load shadersGL3";
        billboardShader.load("shadersGL3/Billboard");
    }else{
        ofLogVerbose()<< "load shadersGL2";
        billboardShader.load("shadersGL2/Billboard");
    }
    
    divAtt.resize(kParticles,0);
    moffsetXAtt.resize(kParticles,0);
    moffsetYAtt.resize(kParticles,0);
    angle.resize(kParticles,0);
//    alpha.resize(kParticles,0);
    billboards.getVertices().resize(kParticles,ofVec3f::zero());
    billboards.getColors().resize(kParticles,ofColor::white);
    billboards.getNormals().resize(kParticles,ofVec3f(0));
    billboards.getTexCoords().resize(kParticles,ofVec2f(0));
    int n = kParticles;

    billboardShader.begin();
    int moffsetXAttLoc = billboardShader.getAttributeLocation("moffsetXAtt");
    billboards.getVbo().setAttributeData(moffsetXAttLoc, &moffsetXAtt[0], 1, n, GL_DYNAMIC_DRAW);
    int moffsetYAttLoc = billboardShader.getAttributeLocation("moffsetYAtt");
    billboards.getVbo().setAttributeData(moffsetYAttLoc, &moffsetYAtt[0], 1, n, GL_DYNAMIC_DRAW);

    int divAttLoc = billboardShader.getAttributeLocation("divAtt");
    billboards.getVbo().setAttributeData(divAttLoc,  &divAtt[0], 1, n,  GL_DYNAMIC_DRAW);
    int angleAttLoc = billboardShader.getAttributeLocation("angleAtt");
    billboards.getVbo().setAttributeData(angleAttLoc, &angle[0], 1, n, GL_DYNAMIC_DRAW);

//    int alphaAttLoc = billboardShader.getAttributeLocation("alphaAtt");
//    billboards.getVbo().setAttributeData(alphaAttLoc, &alpha[0], 1, n, GL_DYNAMIC_DRAW);

    
    billboardShader.end();
    
    updateAttribtuteData();

}
void CommonAssets::updateAttribtuteData()
{
    int n = kParticles;
    billboardShader.begin();
    int moffsetXAttLoc = billboardShader.getAttributeLocation("moffsetXAtt");
    billboards.getVbo().updateAttributeData(moffsetXAttLoc, &moffsetXAtt[0], n);
    int moffsetYAttLoc = billboardShader.getAttributeLocation("moffsetYAtt");
    billboards.getVbo().updateAttributeData(moffsetYAttLoc, &moffsetYAtt[0], n);

    int divAttLoc = billboardShader.getAttributeLocation("divAtt");
    billboards.getVbo().updateAttributeData(divAttLoc,  &divAtt[0], n);
    int angleAttLoc = billboardShader.getAttributeLocation("angleAtt");
    billboards.getVbo().updateAttributeData(angleAttLoc, &angle[0], n);
//    int alphaAttLoc = billboardShader.getAttributeLocation("alphaAtt");
//    billboards.getVbo().updateAttributeData(alphaAttLoc, &alpha[0], n);
    
    billboardShader.end();
}

void CommonAssets::draw()
{
    ofSetColor(255);
    billboardShader.begin();

    ofEnablePointSprites(); // not needed for GL3/4
    texture.getTextureReference().bind();
    billboards.draw();
    texture.getTextureReference().unbind();
    ofDisablePointSprites(); // not needed for GL3/4

    billboardShader.end();
}

void CommonAssets::setParticleColor(int i, ofColor c)
{
    if(i < 0)                               i = 0;
    if(i > kParticles)   i = kParticles;
    billboards.setColor(i, c);
//    alpha[i] = c.a/255.0f;
}
void CommonAssets::setParticleVertex(int i, ofVec3f v)
{
    if(i < 0)                               i = 0;
    if(i > kParticles)   i = kParticles;
    billboards.getVertices()[i] = v;
}

void CommonAssets::setParticleNormal(int i, ofVec3f v)
{
    if(i < 0)                               i = 0;
    if(i > kParticles)   i = kParticles;
    ofVec3f v2 = v*ofRandom(3,6);
//    ofVec3f v3 = billboards.getVertices()[i] + (v2);
     billboards.setNormal(i,v2);
//    billboards.setVertex(i, v3);
}

void CommonAssets::setParticleTexCoords(int i, float columnID, float rowID)
{
    
    if(i < 0)                               i = 0;
    if(i > kParticles)   i = kParticles;
    
    if(columnID > cellColls) columnID = cellColls;
    if(rowID    > cellRows)  rowID    = cellRows;
    
    if(columnID < 0) columnID = 0;
    if(rowID < 0)    rowID    = 0;
    
    
    
    // get the cell image width
    float cellWidth  = texW / cellRows;
    float cellHeight = texH / cellColls;
    
    float row = rowID;
    float col = columnID;
    moffsetXAtt[i] = (cellWidth * row) / texW;
    moffsetYAtt[i] = (cellHeight * col) / texH;
    billboards.getTexCoords()[i].set((cellWidth * row) / texW,
                                     moffsetYAtt[i] = (cellHeight * col) / texH);
//        ofLogVerbose(__PRETTY_FUNCTION__) << "moffsetXAtt :" << moffsetXAtt[i] <<  " moffsetYAtt :" << moffsetYAtt[i];
    // P1
    //    billboards.getTexCoords()[(i*4)+0].set( (cellWidth * row) / texW,(cellHeight * col) / texH);
    //    ofLogVerbose(ofToString(i)) << billboards.getTexCoords()[(i*4)+0];
    
    // P2
    //    billboards.getTexCoords()[(i*4)+1].x = ((cellWidth * row)  +   cellWidth)    / texW;
    //    billboards.getTexCoords()[(i*4)+1].y = (cellHeight * col)        / texH;
    //
    //    // P2
    //    billboards.getTexCoords()[(i*4)+2].x = ((cellWidth * row) + cellWidth)           / texW;
    //    billboards.getTexCoords()[(i*4)+2].y = ((cellHeight * col) + cellHeight) / texH;
    //
    //    // P2
    //    billboards.getTexCoords()[(i*4)+3].x = (cellWidth * row)         / texW;
    //    billboards.getTexCoords()[(i*4)+3].y = ((cellHeight * col)+cellHeight)   / texH;
    
    
    
}
void CommonAssets::setParticleAngle(int i, float _angle)
{
    if(i < 0)                               i = 0;
    if(i > kParticles)   i = kParticles;
    angle[i] = _angle;
}
void CommonAssets::reset()
{
    for(int i = 0 ; i < kParticles ; i++)
    {
        setParticleVertex(i,ofVec3f::zero());
    }
}
string CommonAssets::getBGPath()
{
    if(bgDir.getFiles().size()>0)
    {
        imageIndex = (int)ofRandom(0,bgDir.getFiles().size());
        return bgDir.getPath(imageIndex);
    }
    else
    {
        ofLogError() << "could not load image";
        return "";
    }
}

string CommonAssets::getLogoPath()
{
    if(imageIndex < logoDir.size())
    {
//        imageIndex = (int)ofRandom(0,logoDir.getFiles().size());
        return logoDir.getPath(imageIndex);
    }
    else
    {
        ofLogError() << "could not load image";
        return "";
    }
}

void CommonAssets::nextImage()
{
    bg.loadImage(getBGPath());
    logo.loadImage(getLogoPath());
}