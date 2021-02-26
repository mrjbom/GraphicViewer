#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <QFile>
#include <QOpenGLFunctions_4_5_Core>
#include "glm/glm.hpp"

class ShaderProgram
{
private:
    QOpenGLFunctions_4_5_Core* glFunctions = nullptr;
    QString vertexShaderSourceFilePath;
    QString fragmentShaderSourceFilePath;

    GLuint compiledShaderProgram = 0;
    GLuint gShaderPrintfBuffer = 0;
    bool makeSuccessful = false;
    bool useShaderPrintf = false;
public:
    //Setting the _useShaderPrintf parameter and using the functions associated with printing data from the shader leads to a huge memory overhead!
    ShaderProgram(QOpenGLFunctions_4_5_Core* _glFunctions, const QString _vertexShaderSourceFilePath, const QString _fragmentShaderSourceFilePath, bool _useShaderPrintf = false);
    ~ShaderProgram();
    bool compile();
    void enable();
    void disable();
    void setUniform3f(const GLchar* name, float x, float y, float z);
    void setUniform3f(const GLchar* name, glm::vec3 vec);
    void setUniform1i(const GLchar* name, int num);
    void setUniform1f(const GLchar* name, float num);
    void setUniformMatrix4fv(const GLchar* name, GLsizei count, GLboolean transpose, const GLfloat* value);
    void setUniformBool(const GLchar* name, bool value);

    //Using these functions if useShaderPrintf enabled results in a huge memory overhead!
    void printfPrepare();
    void printfTerminate();
    std::string printfGetData();
};

#endif // SHADERPROGRAM_H
