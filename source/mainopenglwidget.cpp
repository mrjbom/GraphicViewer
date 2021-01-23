#include "mainopenglwidget.h"
#include <QFile>

MainOpenGLWidget::MainOpenGLWidget(QWidget* parent)
{

}

MainOpenGLWidget::~MainOpenGLWidget()
{

}

GLuint MainOpenGLWidget::makeShaderProgram(const QString vertexShaderSourceFilePath, const QString fragmentShaderSourceFilePath)
{
    const size_t errorMessageBufferSize = 512;

    //Open files containing the vertex and fragment shader source code
    QFile vertexShaderSourceFile(vertexShaderSourceFilePath);
    if (!vertexShaderSourceFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug("[ERROR] makeShadersProgram: open vertex shader source code file failed!");
        return 0;
    }

    QFile fragmentShaderSourceFile(fragmentShaderSourceFilePath);
    if (!fragmentShaderSourceFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug("[ERROR] makeShadersProgram: open fragment shader source code file failed!");
        return 0;
    };

    //Reading the vertex and fragment shader source code
    QByteArray vertexShaderSourceCodeByteArray;
    const char* vertexShaderSourceCodeString;
    while (!vertexShaderSourceFile.atEnd()) {
        vertexShaderSourceCodeByteArray.append(vertexShaderSourceFile.readLine());
    }
    vertexShaderSourceFile.close();
    vertexShaderSourceCodeString = vertexShaderSourceCodeByteArray.data();

    QByteArray fragmentShaderSourceCodeByteArray;
    const char* fragmentShaderSourceCodeString;
    while (!fragmentShaderSourceFile.atEnd()) {
        fragmentShaderSourceCodeByteArray.append(fragmentShaderSourceFile.readLine());
    }
    fragmentShaderSourceFile.close();
    fragmentShaderSourceCodeString = fragmentShaderSourceCodeByteArray.data();

    //Compile vertex shader
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSourceCodeString, NULL);
    glCompileShader(vertexShader);

    //Check vertex compile result
    int vertexShaderCompileStatus = 0;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertexShaderCompileStatus);
    if (!vertexShaderCompileStatus) {
        char infoLog[errorMessageBufferSize];
        glGetShaderInfoLog(vertexShader, sizeof(infoLog), NULL, infoLog);
        qDebug() << "[ERROR] makeShadersProgram: vertex shader compilation failed!\n" << infoLog;
        return 0;
    }

    //Compile fragment shader
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSourceCodeString, NULL);
    glCompileShader(fragmentShader);

    //Check fragment compile result
    int fragmentShaderCompileStatus = 0;
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragmentShaderCompileStatus);
    if (!fragmentShaderCompileStatus) {
        char infoLog[errorMessageBufferSize];
        glGetShaderInfoLog(fragmentShader, sizeof(infoLog), NULL, infoLog);
        qDebug() << "[ERROR] makeShadersProgram: fragment shader compilation failed!\n" << infoLog;
        return 0;
    }

    //Link shader program
    unsigned int shaderProgram = 0;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    //Check link program result
    int shaderProgramLinkStatus = 0;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &shaderProgramLinkStatus);
    if (!shaderProgramLinkStatus) {
        char infoLog[errorMessageBufferSize];
        glGetProgramInfoLog(shaderProgram, sizeof(infoLog), NULL, infoLog);
        qDebug() << "[ERROR] makeShadersProgram: shader program link failed!\n" << infoLog;
        return 0;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

float vertexes_normalized[12] =
                     {-0.5, 0.5, 0,
                       0.5, 0.5, 0,
                       0.5, -0.5, 0,
                      -0.5, -0.5, 0};

float vertexes[12] = {-100, 100, 0,
                       100, 100, 0,
                       100, -100, 0,
                      -100, -100, 0};

unsigned int gVBO = 0;
unsigned int gShaderProgram = 0;

void MainOpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    openglVersionString = (char*)glGetString(GL_VERSION);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-this->width() / 2, this->width() / 2, -this->height() / 2, this->height() / 2);
    glViewport(0, 0, this->width(), this->height());

    //Compile shader program
    unsigned int shaderProgram = makeShaderProgram(":/glshaders/vertshader.vert", ":/glshaders/fragshader.frag");
    if(!shaderProgram) {
        qDebug("[ERROR]initializeGL: makeShaderProgram failed!");
        return;
    }
    gShaderProgram = shaderProgram;

    //объект вершинного буфера
    unsigned int VBO = 0;
    //выделяем 1 буффер
    glGenBuffers(1, &VBO);
    //связываем буферный объект с буфером OpenGL
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //копируем данные о вершинах из массива в VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexes_normalized), vertexes_normalized, GL_STATIC_DRAW);
    gVBO = VBO;

    //настраиваем интерпретацию данных вершинного буфера
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glUseProgram(shaderProgram);
}

void MainOpenGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

int i = 0;

void MainOpenGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    glRotatef(i++, 0, 0, -1);
    glDrawArrays(GL_POLYGON, 0, 4);

    glPopMatrix();

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
