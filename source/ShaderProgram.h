#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <QFile>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLFunctions_4_5_Core>

class ShaderProgram
{
private:
    QOpenGLFunctions_4_5_Core* glFunctions = nullptr;
    QString vertexShaderSourceFilePath;
    QString fragmentShaderSourceFilePath;

    bool useShaderPrintf;
    GLuint compiledShaderProgram = 0;
    GLuint gShaderPrintfBuffer = 0;

    bool makeSuccessful = false;
public:
    ShaderProgram(QOpenGLFunctions_4_5_Core* _glFunctions, const QString _vertexShaderSourceFilePath, const QString _fragmentShaderSourceFilePath, bool _useShaderPrintf = false);
    ~ShaderProgram();
    bool compile();
    void enable();
    void disable();
    void setUniform3f(const GLchar* name, float x, float y, float z);

    void printfPrepare();
    void printfTerminate();
    std::string printfGetData();
};

#endif // SHADERPROGRAM_H
