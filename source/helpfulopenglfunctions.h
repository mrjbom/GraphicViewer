#ifndef HELPFULOPENGLFUNCTIONS_H
#define HELPFULOPENGLFUNCTIONS_H

#include <QFile>
#include <QDebug>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <GL/GLU.h>
#include "SceneManager/SceneManager.h"

class HelpfulOpenGLFunctions
{
public:
    HelpfulOpenGLFunctions(QOpenGLFunctions_3_3_Core* _glFunctions);
    //Compiles a vertical and fragment shader, creates a shader program from them, and returns a shader program
    GLuint makeShaderProgram(const QString vertexShaderSourceFilePath, const QString fragmentShaderSourceFilePath);
private:
    QOpenGLFunctions_3_3_Core* glFunctions = nullptr;
};

#endif // HELPFULOPENGLFUNCTIONS_H
