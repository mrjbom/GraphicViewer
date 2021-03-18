#include "ArrowPainter.h"

ArrowPainter::ArrowPainter(QOpenGLFunctions_4_5_Core* _glFunctions)
{
    glFunctions = _glFunctions;
    color = glm::vec3(1.0f, 1.0f, 1.0f);

    //Create shader program object
    shaderProgram = new ShaderProgram(glFunctions, ":/BasicObjects/ArrowPainter/shaders/vertshader.vert", ":/BasicObjects/ArrowPainter/shaders/fragshader.frag");

    //Compile shader program
    if(!shaderProgram->compile()) {
        qDebug("[ERROR] Arrow: compile arrow shader program failed!");
        return;
    }

    glFunctions->glGenVertexArrays(1, &VAO_line);
    glFunctions->glGenBuffers(1, &VBO_vertexes);
    glFunctions->glBindVertexArray(VAO_line);

    glFunctions->glBindBuffer(GL_ARRAY_BUFFER, VBO_vertexes);
    glFunctions->glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6, NULL, GL_DYNAMIC_DRAW);

    glFunctions->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glFunctions->glEnableVertexAttribArray(0);

    glFunctions->glBindBuffer(GL_ARRAY_BUFFER, 0);
    glFunctions->glBindVertexArray(0);
}

void ArrowPainter::updatePoints(glm::vec3 start_p, glm::vec3 end_p)
{
    //contain data
    start_point = start_p;
    end_point = end_p;

    float vertexes[] = {
        start_point.x, start_point.y, start_point.z,
        end_point.x, end_point.y, end_point.z
    };

    glFunctions->glBindBuffer(GL_ARRAY_BUFFER, VBO_vertexes);
    if(VBO_vertexes != 0) {
        glFunctions->glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertexes), vertexes);
    }
    glFunctions->glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ArrowPainter::setColor(glm::vec3 new_color)
{
    color = new_color;
}

void ArrowPainter::setMVP(glm::mat4 mvp_mat)
{
    mvp_matrix = mvp_mat;
}

void ArrowPainter::Draw()
{
    if(start_point == end_point)
        return;

    shaderProgram->enable();
    shaderProgram->setUniformMatrix4fv("mvpMatrix", 1, GL_FALSE, glm::value_ptr(mvp_matrix));
    shaderProgram->setUniform3f("lineColor", color);

    glFunctions->glBindVertexArray(VAO_line);
    glFunctions->glDrawArrays(GL_LINES, 0, 2);
    glFunctions->glPointSize(8);
    glFunctions->glEnable(GL_POINT_SMOOTH);
    glFunctions->glDrawArrays(GL_POINTS, 1, 1);
    glFunctions->glDisable(GL_POINT_SMOOTH);
    glFunctions->glPointSize(1);
    glFunctions->glBindVertexArray(0);
    shaderProgram->disable();
}

ArrowPainter::~ArrowPainter()
{
    delete shaderProgram;
    glFunctions->glDeleteVertexArrays(1, &VAO_line);
    glFunctions->glDeleteBuffers(1, &VBO_vertexes);
}
