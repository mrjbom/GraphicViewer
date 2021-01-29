#include "Sc1VBOOrange.h"
#include <iostream>

Sc1VBOOrange::Sc1VBOOrange(QOpenGLContext* openGLContext)
{
    glFunctions = openGLContext->versionFunctions<QOpenGLFunctions_3_3_Core>();
}

Sc1VBOOrange::~Sc1VBOOrange()
{
}

void Sc1VBOOrange::initScene()
{
    float vertexes_coords_normalized[] =
                         { 0, 0.5, 0,
                           -0.5, -0.5, 0,
                           0.5, -0.5, 0 };

    HelpfulOpenGLFunctions helpfulOpenGLFunctions(glFunctions);

    //Compile shader program
    unsigned int shaderProgram = helpfulOpenGLFunctions.makeShaderProgram(":/Scenes/Sc1VBOOrange/shaders/vertshader.vert", ":/Scenes/Sc1VBOOrange/shaders/fragshader.frag");
    if(!shaderProgram) {
        qDebug("[ERROR] initializeGL: makeShaderProgram failed!");
        return;
    }
    gShaderProgram = shaderProgram;

    //Vertex buffer object ID(name)
    unsigned int VBO = 0;
    //Allocate 1 buffer for VBO (Vertex Buffer Object)
    glFunctions->glGenBuffers(1, &VBO);
    //Linking a buffer object to an OpenGL buffer
    glFunctions->glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //Copying vertex data from the array to VBO
    glFunctions->glBufferData(GL_ARRAY_BUFFER, sizeof(vertexes_coords_normalized), vertexes_coords_normalized, GL_STATIC_DRAW);

    //Configuring the interpretation of the vertex buffer data
    glVertexPointer(3, GL_FLOAT, 0, (void*)0);

    //Unselect VBO(so that other calls(glBufferData for example) don't change it)
    glFunctions->glBindBuffer(GL_ARRAY_BUFFER, 0);

    gVBO = VBO;
}

void Sc1VBOOrange::drawScene()
{
    glFunctions->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //Select shader program
    glFunctions->glUseProgram(gShaderProgram);
    glEnableClientState(GL_VERTEX_ARRAY);
    //Select VBO
    glFunctions->glBindBuffer(GL_ARRAY_BUFFER, gVBO);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //Draw triangle
    glFunctions->glDrawArrays(GL_TRIANGLES , 0, 3);
    //Unselect VBO
    glFunctions->glBindBuffer(GL_ARRAY_BUFFER, 0);
    //Unselect shader program
    glDisableClientState(GL_VERTEX_ARRAY);
    glFunctions->glUseProgram(0);
}
void Sc1VBOOrange::finishScene()
{
    glFunctions->glDeleteBuffers(1, &gVBO);
}
