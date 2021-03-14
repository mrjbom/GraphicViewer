#include "Sc3EBOGreen.h"

Sc3EBOGreen::Sc3EBOGreen(QOpenGLContext* openGLContext)
{
    glFunctions = openGLContext->versionFunctions<QOpenGLFunctions_4_5_Core>();
}

Sc3EBOGreen::~Sc3EBOGreen()
{
}

void Sc3EBOGreen::initScene(int start_window_width, int start_window_height)
{
    (void)start_window_width;
    (void)start_window_height;

    float vertexes_coords_normalized[] =
                         { 0, 0.5, 0,
                           -0.5, -0.5, 0,
                           0.5, -0.5, 0,
                           0.0, -0.75, 0 };

    unsigned int indexes_of_coords[] =
                         { 0, 1, 2, //first triangle
                           1, 2, 3  //second triangle
                                   };

    //Create shader program object
    gShaderProgram = new ShaderProgram(glFunctions, ":Scenes/Sc3EBOGreen/shaders/vertshader.vert", ":/Scenes/Sc3EBOGreen/shaders/fragshader.frag");

    //Compile shader program
    if(!gShaderProgram->compile()) {
        qDebug("[ERROR] initializeGL: makeShaderProgram failed!");
        return;
    }

    //Vertex buffer object ID(name)
    unsigned int VBO = 0;
    //Element buffer object ID(name)
    unsigned int EBO = 0;
    //Allocate 1 buffer for VBO (Vertex Buffer Object)
    glFunctions->glGenBuffers(1, &VBO);
    //Allocate 1 buffer for EBO (Element Buffer Object)
    glFunctions->glGenBuffers(1, &EBO);
    //Use buffer object to an OpenGL buffer
    glFunctions->glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //Copying element data from the array to VBO
    glFunctions->glBufferData(GL_ARRAY_BUFFER, sizeof(vertexes_coords_normalized), vertexes_coords_normalized, GL_STATIC_DRAW);
    //Configuring the interpretation of the vertex buffer data
    glVertexPointer(3, GL_FLOAT, 0, (void*)0);
    //Use buffer object to an OpenGL buffer
    glFunctions->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //Copying vertex data from the array to EBO
    glFunctions->glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes_of_coords), indexes_of_coords, GL_STATIC_DRAW);

    //Unselect VBO(so that other calls(glBufferData for example) don't change it)
    glFunctions->glBindBuffer(GL_ARRAY_BUFFER, 0);
    //Unselect EBO(so that other calls(glBufferData for example) don't change it)
    glFunctions->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    g_VBO = VBO;
    g_EBO = EBO;
}

void Sc3EBOGreen::drawScene()
{
    glFunctions->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //Select shader program
    gShaderProgram->enable();
    glEnableClientState(GL_VERTEX_ARRAY);
    //Select VBO
    glFunctions->glBindBuffer(GL_ARRAY_BUFFER, g_VBO);
    //Select EBO
    glFunctions->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_EBO);
    //Draw and polygons lines
    if(g_show_polygon_lines) {
        glFunctions->glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    //Draw triangle
    glFunctions->glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    if(g_show_polygon_lines) {
        glFunctions->glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    //Unselect VBO
    glFunctions->glBindBuffer(GL_ARRAY_BUFFER, 0);
    //Unselect EBO
    glFunctions->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    //Unselect shader program
    gShaderProgram->disable();
    glDisableClientState(GL_VERTEX_ARRAY);
}
void Sc3EBOGreen::finishScene()
{
    glFunctions->glDeleteBuffers(1, &g_VBO);
    glFunctions->glDeleteBuffers(1, &g_EBO);
    delete gShaderProgram;
}
