#include "ShaderProgram.h"
#include "ShaderPrintf.h"
#include <QDebug>

// _useShaderPrintf
ShaderProgram::ShaderProgram(QOpenGLFunctions_4_5_Core* _glFunctions, const QString _vertexShaderSourceFilePath, const QString _fragmentShaderSourceFilePath, bool _useShaderPrintf)
{
    glFunctions = _glFunctions;
    vertexShaderSourceFilePath = _vertexShaderSourceFilePath;
    fragmentShaderSourceFilePath = _fragmentShaderSourceFilePath;
    useShaderPrintf = _useShaderPrintf;
}

ShaderProgram::~ShaderProgram()
{
    if(!makeSuccessful)
        return;

    glFunctions->glDeleteProgram(compiledShaderProgram);
}

bool ShaderProgram::compile()
{
    const size_t errorMessageBufferSize = 512;

    if(!glFunctions) {
        qDebug("[ERROR] makeShaderProgram: glFunctions not valid!");
        return false;
    }

    //Open files containing the vertex and fragment shader source code
    QFile vertexShaderSourceFile(vertexShaderSourceFilePath);
    if (!vertexShaderSourceFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug("[ERROR] makeShaderProgram: open vertex shader source code file failed!");
        return false;
    }

    QFile fragmentShaderSourceFile(fragmentShaderSourceFilePath);
    if (!fragmentShaderSourceFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug("[ERROR] makeShaderProgram: open fragment shader source code file failed!");
        return false;
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
    int vertexShader = glFunctions->glCreateShader(GL_VERTEX_SHADER);
    if(useShaderPrintf) {
        glShaderSourcePrint(glFunctions, vertexShader, 1, &vertexShaderSourceCodeString, NULL);
    }
    else {
        glFunctions->glShaderSource(vertexShader, 1, &vertexShaderSourceCodeString, NULL);
    }
    glFunctions->glCompileShader(vertexShader);

    //Check vertex compile result
    int vertexShaderCompileStatus = 0;
    glFunctions->glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertexShaderCompileStatus);
    if (!vertexShaderCompileStatus) {
        char infoLog[errorMessageBufferSize];
        glFunctions->glGetShaderInfoLog(vertexShader, sizeof(infoLog), NULL, infoLog);
        qDebug() << "[ERROR] makeShaderProgram: vertex shader compilation failed!\n" << infoLog;
        return false;
    }

    //Compile fragment shader
    int fragmentShader = glFunctions->glCreateShader(GL_FRAGMENT_SHADER);
    if(useShaderPrintf) {
        glShaderSourcePrint(glFunctions, fragmentShader, 1, &fragmentShaderSourceCodeString, NULL);
    }
    else {
        glFunctions->glShaderSource(fragmentShader, 1, &fragmentShaderSourceCodeString, NULL);
    }
    glFunctions->glCompileShader(fragmentShader);

    //Check fragment compile result
    int fragmentShaderCompileStatus = 0;
    glFunctions->glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragmentShaderCompileStatus);
    if (!fragmentShaderCompileStatus) {
        char infoLog[errorMessageBufferSize];
        glFunctions->glGetShaderInfoLog(fragmentShader, sizeof(infoLog), NULL, infoLog);
        qDebug() << "[ERROR] makeShaderProgram: fragment shader compilation failed!\n" << infoLog;
        return false;
    }

    //Link shader program
    unsigned int shaderProgram = 0;
    shaderProgram = glFunctions->glCreateProgram();
    glFunctions->glAttachShader(shaderProgram, vertexShader);
    glFunctions->glAttachShader(shaderProgram, fragmentShader);
    glFunctions->glLinkProgram(shaderProgram);

    //Check link program result
    int shaderProgramLinkStatus = 0;
    glFunctions->glGetProgramiv(shaderProgram, GL_LINK_STATUS, &shaderProgramLinkStatus);
    if (!shaderProgramLinkStatus) {
        char infoLog[errorMessageBufferSize];
        glFunctions->glGetProgramInfoLog(shaderProgram, sizeof(infoLog), NULL, infoLog);
        qDebug() << "[ERROR] makeShaderProgram: shader program link failed!\n" << infoLog;
        return false;
    }

    glFunctions->glDeleteShader(vertexShader);
    glFunctions->glDeleteShader(fragmentShader);

    compiledShaderProgram = shaderProgram;
    makeSuccessful = true;
    return true;
}

void ShaderProgram::enable()
{
    glFunctions->glUseProgram(compiledShaderProgram);
}

void ShaderProgram::disable()
{
    glFunctions->glUseProgram(0);
}

void ShaderProgram::setUniform3f(const GLchar* name, float x, float y, float z)
{
    GLint location = glFunctions->glGetUniformLocation(compiledShaderProgram, name);
    glFunctions->glUniform3f(location, x, y, z);
}

void ShaderProgram::setUniform1i(const GLchar* name, int num)
{
    GLint location = glFunctions->glGetUniformLocation(compiledShaderProgram, name);
    glFunctions->glUniform1i(location, num);
}

void ShaderProgram::setUniform1f(const GLchar* name, float num)
{
    GLint location = glFunctions->glGetUniformLocation(compiledShaderProgram, name);
    glFunctions->glUniform1f(location, num);
}

void ShaderProgram::printfPrepare()
{
    if(!useShaderPrintf)
        return;

    //Create a buffer to hold the printf results
    gShaderPrintfBuffer = createPrintBuffer(glFunctions);
    //Bind it to the program
    bindPrintBuffer(glFunctions, compiledShaderProgram, gShaderPrintfBuffer);
}

void ShaderProgram::printfTerminate()
{
    if(!useShaderPrintf)
        return;

    //Clean up
    deletePrintBuffer(glFunctions, gShaderPrintfBuffer);
}

std::string ShaderProgram::printfGetData()
{
    //Convert to string
    return getPrintBufferString(glFunctions, gShaderPrintfBuffer).c_str();
}
