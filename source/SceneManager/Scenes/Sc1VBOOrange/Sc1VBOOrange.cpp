#include "Sc1VBOOrange.h"

Sc1VBOOrange::Sc1VBOOrange(QOpenGLContext* openGLContext)
{
    glFunctions = openGLContext->versionFunctions<QOpenGLFunctions_4_5_Core>();
}

Sc1VBOOrange::~Sc1VBOOrange()
{
}

void Sc1VBOOrange::initScene(int start_window_width, int start_window_height)
{
    (void)start_window_width;
    (void)start_window_height;

    float vertexes_coords_normalized[] =
                         { 0, 0.5, 0,
                           -0.5, -0.5, 0,
                           0.5, -0.5, 0 };

    //Create shader program object
    gShaderProgram = new ShaderProgram(glFunctions, ":Scenes/Sc1VBOOrange/shaders/vertshader.vert", ":/Scenes/Sc1VBOOrange/shaders/fragshader.frag");

    //Compile shader program
    if(!gShaderProgram->compile()) {
        qDebug("[ERROR] initializeGL: makeShaderProgram failed!");
        return;
    }

    //Vertex buffer object ID(name)
    unsigned int VBO = 0;
    //Allocate 1 buffer for VBO (Vertex Buffer Object)
    glFunctions->glGenBuffers(1, &VBO);
    //Use buffer object to an OpenGL buffer
    glFunctions->glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //Copying vertex data from the array to VBO
    glFunctions->glBufferData(GL_ARRAY_BUFFER, sizeof(vertexes_coords_normalized), vertexes_coords_normalized, GL_STATIC_DRAW);

    //Configuring the interpretation of the vertex buffer data
    glVertexPointer(3, GL_FLOAT, 0, (void*)0);

    //Unselect VBO(so that other calls(glBufferData for example) don't change it)
    glFunctions->glBindBuffer(GL_ARRAY_BUFFER, 0);

    g_VBO = VBO;
}

void Sc1VBOOrange::drawScene()
{
    glFunctions->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //Select shader program
    gShaderProgram->enable();
    //Select VBO
    glEnableClientState(GL_VERTEX_ARRAY);
    glFunctions->glBindBuffer(GL_ARRAY_BUFFER, g_VBO);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


    gShaderProgram->printfPrepare();

    //Draw triangle
    glFunctions->glDrawArrays(GL_TRIANGLES , 0, 3);

    //qInfo() << QString::fromStdString(gShaderProgram->printfGetData());
    gShaderProgram->printfTerminate();


    //Unselect VBO
    glFunctions->glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDisableClientState(GL_VERTEX_ARRAY);
    //Unselect shader program
    gShaderProgram->disable();
}

void Sc1VBOOrange::finishScene()
{
    glFunctions->glDeleteBuffers(1, &g_VBO);
    delete gShaderProgram;
}
