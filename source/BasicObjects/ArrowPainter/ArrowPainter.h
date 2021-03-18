#ifndef ARROWPAINTER_H
#define ARROWPAINTER_H

#include <QDebug>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_5_Core>

#include "../../ShaderProgram.h"

#include "../../glm/glm.hpp"
#include "../../glm/gtc/matrix_transform.hpp"
#include "../../glm/gtc/type_ptr.hpp"

class ArrowPainter
{
private:
    QOpenGLFunctions_4_5_Core* glFunctions = nullptr;
    ShaderProgram* shaderProgram = nullptr;
    unsigned int VAO_line = 0;
    unsigned int VBO_vertexes = 0;
    glm::vec3 start_point = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 end_point = glm::vec3(1.0f, 0.0f, 0.0f);
    glm::vec3 color = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::mat4 mvp_matrix = glm::mat4(1.0f);
public:
    ArrowPainter(QOpenGLFunctions_4_5_Core* _glFunctions);
    void updatePoints(glm::vec3 start_p, glm::vec3 end_p);
    void setColor(glm::vec3 new_color);
    void setMVP(glm::mat4 mvp_mat);
    void Draw();
    ~ArrowPainter();
};

#endif // ARROWPAINTER_H
