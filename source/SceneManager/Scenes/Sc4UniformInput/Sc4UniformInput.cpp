#include "Sc4UniformInput.h"

Sc4UniformInput::Sc4UniformInput(QOpenGLContext* openGLContext)
{
    glFunctions = openGLContext->versionFunctions<QOpenGLFunctions_4_5_Core>();
}

Sc4UniformInput::~Sc4UniformInput()
{
}

void Sc4UniformInput::initScene()
{
    float vertexes_coords_normalized[] =
                         { 0, 0.5, 0,
                           -0.5, -0.5, 0,
                           0.5, -0.5, 0 };

    //Create shader program object
    gShaderProgram = new ShaderProgram(glFunctions, ":Scenes/Sc4UniformInput/shaders/vertshader.vert", ":/Scenes/Sc4UniformInput/shaders/fragshader.frag");

    //Compile shader program
    if(!gShaderProgram->compile()) {
        qDebug("[ERROR] initializeGL: makeShaderProgram failed!");
        return;
    }

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

    //Unselect VBO(so that other calls(glBufferData for example) don't change it)
    glFunctions->glBindBuffer(GL_ARRAY_BUFFER, 0);

    //Unselect VAO(so that other calls don't change it)
    glFunctions->glBindVertexArray(0);

    gVAO = VAO;
    gVBO = VBO;
}

void Sc4UniformInput::drawScene()
{
    glFunctions->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Select shader program
    gShaderProgram->enable();

    //Generate color
    static float color = 0;
    if(color + 0.01f <= 1.0f)
        color += 0.01f;
    else
        color = 0;

    //Set uniform variable
    gShaderProgram->setUniform3f("inputColor", color, 0, color);

    //Select VAO
    glFunctions->glBindVertexArray(gVAO);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //Enable the vertex attribute(the rest attributes remain off for optimization)
    glFunctions->glEnableVertexAttribArray(0);
    //Draw triangle
    glFunctions->glDrawArrays(GL_TRIANGLES, 0, 3);
    //Disable the vertex attribute(for optimization)
    glFunctions->glDisableVertexAttribArray(0);
    //Unselect VAO
    glFunctions->glBindVertexArray(0);
    //Unselect shader program
    gShaderProgram->disable();
}
void Sc4UniformInput::finishScene()
{
    glFunctions->glDeleteBuffers(1, &gVBO);
    glFunctions->glDeleteVertexArrays(1, &gVAO);
    delete gShaderProgram;
}
