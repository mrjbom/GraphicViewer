#include "ShaderProgram.h"
#include "ShaderPrintf.h"
#include <QDebug>

// _useShaderPrintf
ShaderProgram::ShaderProgram(QOpenGLFunctions_4_5_Core* targetGlFunctions, const QString vertex_shader_source_file_path, const QString fragment_shader_source_file_path, bool use_shader_printf)
{
    this->glFunctions = targetGlFunctions;
    this->vertex_shader_source_file_path = vertex_shader_source_file_path;
    this->fragment_shader_source_file_path = fragment_shader_source_file_path;
    this->use_shader_printf = use_shader_printf;
}

ShaderProgram::~ShaderProgram()
{
    if(!make_successful)
        return;
    glFunctions->glDeleteProgram(compiled_shader_program);
}

bool ShaderProgram::compile()
{
    const size_t errorMessageBufferSize = 512;

    if(!glFunctions) {
        qDebug("[ERROR] makeShaderProgram: glFunctions not valid!");
        return false;
    }

    //Open files containing the vertex and fragment shader source code
    QFile vertexShaderSourceFile(vertex_shader_source_file_path);
    if (!vertexShaderSourceFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug("[ERROR] compile: open vertex shader source code file failed!");
        return false;
    }

    QFile fragmentShaderSourceFile(fragment_shader_source_file_path);
    if (!fragmentShaderSourceFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug("[ERROR] compile: open fragment shader source code file failed!");
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
    if(use_shader_printf) {
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
        qDebug() << "[ERROR] compile: vertex shader compilation failed!\n" << infoLog;
        return false;
    }

    //Compile fragment shader
    int fragmentShader = glFunctions->glCreateShader(GL_FRAGMENT_SHADER);
    if(use_shader_printf) {
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
        qDebug() << "[ERROR] compile: fragment shader compilation failed!\n" << infoLog;
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
        qDebug() << "[ERROR] compile: shader program link failed!\n" << infoLog;
        return false;
    }

    glFunctions->glDeleteShader(vertexShader);
    glFunctions->glDeleteShader(fragmentShader);

    compiled_shader_program = shaderProgram;
    make_successful = true;
    return true;
}

void ShaderProgram::enable()
{
    glFunctions->glUseProgram(compiled_shader_program);
}

void ShaderProgram::disable()
{
    glFunctions->glUseProgram(0);
}

void ShaderProgram::setUniform3f(const GLchar* name, float x, float y, float z)
{
    GLint location = glFunctions->glGetUniformLocation(compiled_shader_program, name);
    if(location < 0) {
        qInfo() << "[ERROR] ShaderProgram::setUniform3f: name:" << name;
        return;
    }
    glFunctions->glUniform3f(location, x, y, z);
}

void ShaderProgram::setUniform3f(const GLchar* name, glm::vec3 vec)
{
    GLint location = glFunctions->glGetUniformLocation(compiled_shader_program, name);
    if(location < 0) {
        qInfo() << "[ERROR] ShaderProgram::setUniform3f: name:" << name;
        return;
    }
    glFunctions->glUniform3f(location, vec.x, vec.y, vec.z);
}

void ShaderProgram::setUniform1i(const GLchar* name, int num)
{
    GLint location = glFunctions->glGetUniformLocation(compiled_shader_program, name);
    if(location < 0) {
        qInfo() << "[ERROR] ShaderProgram::setUniform1i: name:" << name;
        return;
    }
    glFunctions->glUniform1i(location, num);
}

void ShaderProgram::setUniform1f(const GLchar* name, float num)
{
    GLint location = glFunctions->glGetUniformLocation(compiled_shader_program, name);
    if(location < 0) {
        qInfo() << "[ERROR] ShaderProgram::setUniform1f: name:" << name;
        return;
    }
    glFunctions->glUniform1f(location, num);
}

void ShaderProgram::setUniformMatrix4fv(const GLchar* name, GLsizei count, GLboolean transpose, const GLfloat* value)
{
    GLint location = glFunctions->glGetUniformLocation(compiled_shader_program, name);
    if(location < 0) {
        qInfo() << "[ERROR] ShaderProgram::setUniformMatrix4fv: name:" << name;
        return;
    }
    glFunctions->glUniformMatrix4fv(location, count, transpose, value);
}

void ShaderProgram::setUniformBool(const GLchar* name, bool value)
{
    GLint location = glFunctions->glGetUniformLocation(compiled_shader_program, name);
    if(location < 0) {
        qInfo() << "[ERROR] ShaderProgram::setUniformBool: name:" << name;
        return;
    }
    glFunctions->glUniform1i(location, (int)value);
}

void ShaderProgram::printfPrepare()
{
    if(!use_shader_printf)
        return;

    //Create a buffer to hold the printf results
    g_shader_printf_buffer = createPrintBuffer(glFunctions);
    //Bind it to the program
    bindPrintBuffer(glFunctions, compiled_shader_program, g_shader_printf_buffer);
}

void ShaderProgram::printfTerminate()
{
    if(!use_shader_printf)
        return;

    //Clean up
    deletePrintBuffer(glFunctions, g_shader_printf_buffer);
}

std::string ShaderProgram::printfGetData()
{
    if(!use_shader_printf)
        return "This shader program does not use ShaderPrintf, enable it using the parameters of the shader program compilation function";
    //Convert to string
    return getPrintBufferString(glFunctions, g_shader_printf_buffer).c_str();
}
