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
        qDebug() << vertex_shader_source_file_path << "\n" << fragment_shader_source_file_path;
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
        qDebug() << fragment_shader_source_file_path;
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
        qDebug() << vertex_shader_source_file_path << "\n" << fragment_shader_source_file_path;
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

bool ShaderProgram::extAvailable(const GLchar *name)
{
    std::string extentions_list((char*)glGetString(GL_EXTENSIONS));
    if(extentions_list.find(name) == std::string::npos) {
        return false;
    } else {
        return true;
    }
}

void ShaderProgram::defineNamedStringFromFile(const QString named_string_file_path, const char* pathname)
{
    if(!extAvailable("GL_ARB_shading_language_include")) {
        qDebug("[ERROR] defineNamedStringARBFromFile: extention GL_ARB_shading_language_include not available!");
        return;
    }

    //Find functions
    //void glNamedStringARB(enum type, int namelen, const char *name, int stringlen, const char *string);
    PFNGLNAMEDSTRINGARBPROC glNamedStringARB;
    glNamedStringARB = (PFNGLNAMEDSTRINGARBPROC)wglGetProcAddress("glNamedStringARB");
    if(glNamedStringARB == NULL) {
        qDebug("[ERROR] defineNamedStringARBFromFile: can't find glNamedStringARB pointer!");
        return;
    }
    //void glDeleteNamedStringARB(int namelen, const char *name);
    PFNGLDELETENAMEDSTRINGARBPROC glDeleteNamedStringARB;
    glDeleteNamedStringARB = (PFNGLDELETENAMEDSTRINGARBPROC)wglGetProcAddress("glDeleteNamedStringARB");
    if(glDeleteNamedStringARB == NULL) {
        qDebug("[ERROR] defineNamedStringARBFromFile: can't find glDeleteNamedStringARB pointer!");
        return;
    }
    //void glCompileShaderIncludeARB(uint shader, sizei count, const char *const *path, const int *length);
    PFNGLCOMPILESHADERINCLUDEARBPROC glCompileShaderIncludeARB;
    glCompileShaderIncludeARB = (PFNGLCOMPILESHADERINCLUDEARBPROC)wglGetProcAddress("glCompileShaderIncludeARB");
    if(glCompileShaderIncludeARB == NULL) {
        qDebug("[ERROR] defineNamedStringARBFromFile: can't find glCompileShaderIncludeARB pointer!");
        return;
    }
    //boolean glIsNamedStringARB(int namelen, const char *name);
    PFNGLISNAMEDSTRINGARBPROC glIsNamedStringARB;
    glIsNamedStringARB = (PFNGLISNAMEDSTRINGARBPROC)wglGetProcAddress("glIsNamedStringARB");
    if(glIsNamedStringARB == NULL) {
        qDebug("[ERROR] defineNamedStringARBFromFile: can't find glIsNamedStringARB pointer!");
        return;
    }
    //void glGetNamedStringARB(int namelen, const char *name, sizei bufSize, int *stringlen, char *string);
    PFNGLGETNAMEDSTRINGARBPROC glGetNamedStringARB;
    glGetNamedStringARB = (PFNGLGETNAMEDSTRINGARBPROC)wglGetProcAddress("glGetNamedStringARB");
    if(glGetNamedStringARB == NULL) {
        qDebug("[ERROR] defineNamedStringARBFromFile: can't find glGetNamedStringARB pointer!");
        return;
    }
    //void GetNamedStringivARB(int namelen, const char *name, enum pname, int *params);
    PFNGLGETNAMEDSTRINGIVARBPROC glGetNamedStringivARB;
    glGetNamedStringivARB = (PFNGLGETNAMEDSTRINGIVARBPROC)wglGetProcAddress("glGetNamedStringivARB");
    if(glGetNamedStringivARB == NULL) {
        qDebug("[ERROR] defineNamedStringARBFromFile: can't find glGetNamedStringivARB pointer!");
        return;
    }


    QFile namedStringSourceFile(named_string_file_path);
    if (!namedStringSourceFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug("[ERROR] defineNamedStringARBFromFile: open named string source file failed!");
        return;
    }

    QByteArray namedStringSourceByteArray;
    while (!namedStringSourceFile.atEnd()) {
        namedStringSourceByteArray.append(namedStringSourceFile.readLine());
    }
    namedStringSourceFile.close();

    //Define named string
    glNamedStringARB(GL_SHADER_INCLUDE_ARB, strlen(pathname), pathname, namedStringSourceByteArray.length(), namedStringSourceByteArray.data());
}

void ShaderProgram::deleteNamedString(const char* pathname)
{
    //void glDeleteNamedStringARB(int namelen, const char *name);
    PFNGLDELETENAMEDSTRINGARBPROC glDeleteNamedStringARB;
    glDeleteNamedStringARB = (PFNGLDELETENAMEDSTRINGARBPROC)wglGetProcAddress("glDeleteNamedStringARB");
    if(glDeleteNamedStringARB == NULL) {
        qDebug("[ERROR] defineNamedStringARBFromFile: can't find glDeleteNamedStringARB pointer!");
        return;
    }
    glDeleteNamedStringARB(strlen(pathname), pathname);
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
