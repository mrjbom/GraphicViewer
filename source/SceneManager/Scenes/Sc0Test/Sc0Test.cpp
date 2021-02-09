#include "Sc0Test.h"

Sc0Test::Sc0Test(QOpenGLContext* openGLContext)
{
    glFunctions = openGLContext->versionFunctions<QOpenGLFunctions_4_5_Core>();
}

Sc0Test::~Sc0Test()
{
}

void Sc0Test::initScene()
{
    float vertexes_coords_normalized[] =
                         { 0, 0.5, 0,
                           -0.5, -0.5, 0,
                           0.5, -0.5, 0 };

    float vertexes_colors[] =
                         { 1, 0, 0,
                           0, 1, 0,
                           0, 0, 1 };

    //Create shader program object
    gShaderProgram = new ShaderProgram(glFunctions, ":Scenes/Sc0Test/shaders/vertshader.vert", ":/Scenes/Sc0Test/shaders/fragshader.frag", false);

    //Compile shader program
    if(!gShaderProgram->compile()) {
        qDebug("[ERROR] initializeGL: makeShaderProgram failed!");
        return;
    }

    //Vertex buffer object ID(name)
    unsigned int VBO = 0;
    unsigned int colorsVBO;
    //Vertex arrays object ID(name)
    unsigned int VAO = 0;
    //Allocate 1 buffer for VBO (Vertex Buffer Object)
    glFunctions->glGenBuffers(1, &VBO);
    glFunctions->glGenBuffers(1, &colorsVBO);
    //Allocate 1 buffer for VAO (Vertex Arrays Object)
    glFunctions->glGenVertexArrays(1, &VAO);
    //Select VAO
    glFunctions->glBindVertexArray(VAO);
    //Use buffer object to an OpenGL buffer
    glFunctions->glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //Copying vertex data from the array to VBO
    glFunctions->glBufferData(GL_ARRAY_BUFFER, sizeof(vertexes_coords_normalized), vertexes_coords_normalized, GL_STATIC_DRAW);
    //Configuring the interpretation of the vertex buffer data
    glFunctions->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    //Use buffer object to an OpenGL buffer
    glFunctions->glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
    //Copying vertex data from the array to VBO
    glFunctions->glBufferData(GL_ARRAY_BUFFER, sizeof(vertexes_colors), vertexes_colors, GL_STATIC_DRAW);
    //Configuring the interpretation of the vertex buffer data
    glFunctions->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    //Unselect VBO(so that other calls(glBufferData for example) don't change it)
    glFunctions->glBindBuffer(GL_ARRAY_BUFFER, 0);

    //Unselect VAO(so that other calls don't change it)
    glFunctions->glBindVertexArray(0);

    gVAO = VAO;
    gVBO = VBO;
    gColorsVBO = colorsVBO;
}

void Sc0Test::drawScene()
{
    glFunctions->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //Select shader program
    gShaderProgram->enable();
    //Select VAO
    glFunctions->glBindVertexArray(gVAO);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //Enable the vertex attribute(the rest attributes remain off for optimization)
    glFunctions->glEnableVertexAttribArray(0);
    glFunctions->glEnableVertexAttribArray(1);

    gShaderProgram->printfPrepare();

    //Draw triangle
    glFunctions->glDrawArrays(GL_TRIANGLES, 0, 3);

    //Debug output from
    //qInfo() << QString::fromStdString(gShaderProgram->printfGetData());
    gShaderProgram->printfTerminate();

    //Disable the vertex attribute(for optimization)
    glFunctions->glDisableVertexAttribArray(0);
    glFunctions->glDisableVertexAttribArray(1);
    //Unselect VAO
    glFunctions->glBindVertexArray(0);
    //Unselect shader program
    gShaderProgram->disable();
}
void Sc0Test::finishScene()
{
    glFunctions->glDeleteBuffers(1, &gVBO);
    glFunctions->glDeleteBuffers(1, &gColorsVBO);
    glFunctions->glDeleteVertexArrays(1, &gVAO);
    delete gShaderProgram;
}

void Sc0Test::createUiOptionsWidgets()
{
    //QPushButton* btn = new QPushButton(globalMainWindowFormUI->sceneOptionsFrame);
    //btn->setGeometry(0, 0, 100, 30);
    //btn->setText("Button for Test Scene");
    //globalMainWindowFormUI->sceneOptionsGridLayout->addWidget(btn);
    //gBtn = btn;
}

void Sc0Test::deleteUiOptionsWidgets()
{
    //globalMainWindowFormUI->sceneOptionsGridLayout->removeWidget(gBtn);
    //delete gBtn;
}
