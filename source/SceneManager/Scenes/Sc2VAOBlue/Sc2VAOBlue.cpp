#include "Sc2VAOBlue.h"
#include <iostream>

Sc2VAOBlue::Sc2VAOBlue(QOpenGLContext* openGLContext)
{
    glFunctions = openGLContext->versionFunctions<QOpenGLFunctions_3_3_Core>();
}

Sc2VAOBlue::~Sc2VAOBlue()
{
}

void Sc2VAOBlue::initScene()
{
    float vertexes_coords_normalized[] =
                         { 0, 0.5, 0,
                           -0.5, -0.5, 0,
                           0.5, -0.5, 0 };

    HelpfulOpenGLFunctions helpfulOpenGLFunctions(glFunctions);

    //Compile shader program
    unsigned int shaderProgram = helpfulOpenGLFunctions.makeShaderProgram(":Scenes/Sc2VAOBlue/shaders/vertshader.vert", ":/Scenes/Sc2VAOBlue/shaders/fragshader.frag");
    if(!shaderProgram) {
        qDebug("[ERROR] initializeGL: makeShaderProgram failed!");
        return;
    }
    gShaderProgram = shaderProgram;

    //Vertex buffer object ID(name)
    unsigned int VBO = 0;
    //Vertex arrays object ID(name)
    unsigned int VAO = 0;
    //Allocate 1 buffer for VBO (Vertex Buffer Object)
    glFunctions->glGenBuffers(1, &VBO);
    //Allocate 1 buffer for VAO (Vertex Arrays Object)
    glFunctions->glGenVertexArrays(1, &VAO);
    //Select VAO
    glFunctions->glBindVertexArray(VAO);
    //Linking a buffer object to an OpenGL buffer
    glFunctions->glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //Copying vertex data from the array to VBO
    glFunctions->glBufferData(GL_ARRAY_BUFFER, sizeof(vertexes_coords_normalized), vertexes_coords_normalized, GL_STATIC_DRAW);

    //Configuring the interpretation of the vertex buffer data
    glFunctions->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    //Using the vertex attribute
    glFunctions->glEnableVertexAttribArray(0);

    //Unselect VBO(so that other calls(glBufferData for example) don't change it)
    glFunctions->glBindBuffer(GL_ARRAY_BUFFER, 0);

    //Unselect VAO(so that other calls don't change it)
    glFunctions->glBindVertexArray(0);

    gVAO = VAO;
    gVBO = VBO;
}

void Sc2VAOBlue::drawScene()
{
    glFunctions->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    //Select shader program
    glFunctions->glUseProgram(gShaderProgram);
    //Select VAO
    glFunctions->glBindVertexArray(gVAO);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //Draw triangle
    glFunctions->glDrawArrays(GL_TRIANGLES, 0, 3);
    //Unselect VAO
    glFunctions->glBindVertexArray(0);
    //Unselect shader program
    glFunctions->glUseProgram(0);
}
void Sc2VAOBlue::finishScene()
{
    glFunctions->glDeleteBuffers(1, &gVBO);
    glFunctions->glDeleteVertexArrays(1, &gVAO);
}
