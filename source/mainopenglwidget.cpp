#include "mainopenglwidget.h"
#include <QFile>

MainOpenGLWidget::MainOpenGLWidget(QWidget* parent) : QOpenGLWidget(parent)
{
    sceneManager = new SceneManager;
}

MainOpenGLWidget::~MainOpenGLWidget()
{
    sceneManager->final();
    delete sceneManager;
}

//The vertices are specified in counter-clockwise order
// A
// |\
// | \
// |  \
// B---C
// A->B->C
//float vertexes_coords_normalized[] =
//                     { 0, 0.5, 0,
//                       -0.5, -0.5, 0,
//                       0.5, -0.5, 0 };

unsigned int gVAO = 0;
unsigned int gShaderProgram = 0;

void MainOpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    openglVersionString = (char*)glGetString(GL_VERSION);
    sceneManager->init(this->context());
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-this->width() / 2, this->width() / 2, -this->height() / 2, this->height() / 2);
    glViewport(0, 0, this->width(), this->height());

    ////Compile shader program
    //unsigned int shaderProgram = makeShaderProgram(":/glshaders/vertshader.vert", ":/glshaders/fragshader.frag");
    //if(!shaderProgram) {
    //    qDebug("[ERROR] initializeGL: makeShaderProgram failed!");
    //    return;
    //}
    //gShaderProgram = shaderProgram;
    //
    ////Vertex buffer object ID(name)
    //unsigned int VBO = 0;
    ////Vertex arrays object ID(name)
    //unsigned int VAO = 0;
    ////Allocate 1 buffer for VBO (Vertex Buffer Object)
    //glGenBuffers(1, &VBO);
    ////Allocate 1 buffer for VAO (Vertex Arrays Object)
    //glGenVertexArrays(1, &VAO);
    ////Select VAO
    //glBindVertexArray(VAO);
    ////Linking a buffer object to an OpenGL buffer
    //glBindBuffer(GL_ARRAY_BUFFER, VBO);
    ////Copying vertex data from the array to VBO
    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertexes_coords_normalized), vertexes_coords_normalized, GL_STATIC_DRAW);
    //
    ////Configuring the interpretation of the vertex buffer data
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    //glEnableVertexAttribArray(0);
    //
    ////Unselect VBO(so that other calls(glBufferData for example) don't change it)
    //glBindBuffer(GL_ARRAY_BUFFER, 0);
    //
    ////Unselect VAO(so that other calls don't change it)
    //glBindVertexArray(0);
    //
    //gVAO = VAO;

}

void MainOpenGLWidget::resizeGL(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-w / 2, w / 2, -h / 2, h / 2);
    glViewport(0, 0, w, h);
}

int i = 0;

void MainOpenGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    ////Select shader program
    //glUseProgram(gShaderProgram);
    ////Select VAO
    //glBindVertexArray(gVAO);
    ////glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    ////Draw triangle
    //glDrawArrays(GL_TRIANGLES, 0, 3);
    ////Unselect VAO
    //glBindVertexArray(0);
    ////Unselect shader program
    //glUseProgram(0);
    sceneManager->callInitScene();
    sceneManager->callDrawScene();


    //glColor3f(1, 1, 1);
    //glPushMatrix();
    //glRotatef(i++, 0, 0, -1);
    //qInfo() << i;
    //glBegin(GL_POLYGON);
    //glVertex3f(-100, 100, 0);
    //glVertex3f(100, 100, 0);
    //glVertex3f(100, -100, 0);
    //glVertex3f(-100, -100, 0);
    //glEnd();
    //glPopMatrix();

    update();
}
