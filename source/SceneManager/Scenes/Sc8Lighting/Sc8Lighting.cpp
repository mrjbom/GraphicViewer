#include "Sc8Lighting.h"
#include "../../globalvars.h"
#include <QGLWidget> //for convertation to gl format

Sc8Lighting::Sc8Lighting(QOpenGLContext* openGLContext)
{
    glFunctions = openGLContext->versionFunctions<QOpenGLFunctions_4_5_Core>();
}

Sc8Lighting::~Sc8Lighting()
{
}

//0 = 0.5, 0.5, -0.5
//1 = -0.5, 0.5, -0.5
//2 = -0.5, 0.5, 0.5
//3 = 0.5, 0.5, 0.5
//4 = 0.5, -0.5, -0.5
//5 = -0.5, -0.5, -0.5
//6 = -0.5, -0.5, 0.5
//7 = 0.5, -0.5, 0.5

//I specifically set all the variables manually, because this is a test code.
float cube_vertexes_coords_normalized[] =
                     { //top side
                       0.5, 0.5, -0.5,
                       -0.5, 0.5, -0.5,
                       0.5, 0.5, 0.5,
                       -0.5, 0.5, -0.5,
                       -0.5, 0.5, 0.5,
                       0.5, 0.5, 0.5,
                       //bottom side
                       0.5, -0.5, 0.5,
                       -0.5, -0.5, 0.5,
                       0.5, -0.5, -0.5,
                       -0.5, -0.5, 0.5,
                       -0.5, -0.5, -0.5,
                       0.5, -0.5, -0.5,
                       //near side
                       0.5, 0.5, 0.5,
                       -0.5, 0.5, 0.5,
                       0.5, -0.5, 0.5,
                       -0.5, 0.5, 0.5,
                       -0.5, -0.5, 0.5,
                       0.5, -0.5, 0.5,
                       //far side
                       -0.5, 0.5, -0.5,
                       0.5, 0.5, -0.5,
                       -0.5, -0.5, -0.5,
                       0.5, 0.5, -0.5,
                       0.5, -0.5, -0.5,
                       -0.5, -0.5, -0.5,
                       //right side
                       0.5, 0.5, -0.5,
                       0.5, 0.5, 0.5,
                       0.5, -0.5, -0.5,
                       0.5, 0.5, 0.5,
                       0.5, -0.5, 0.5,
                       0.5, -0.5, -0.5,
                       //left side
                       -0.5, 0.5, 0.5,
                       -0.5, 0.5, -0.5,
                       -0.5, -0.5, 0.5,
                       -0.5, 0.5, -0.5,
                       -0.5, -0.5, -0.5,
                       -0.5, -0.5, 0.5
                     };

float cube_vertexes_normals[] =
                     {
                        //top side
                        0.0, 1.0, 0.0,
                        0.0, 1.0, 0.0,
                        0.0, 1.0, 0.0,
                        0.0, 1.0, 0.0,
                        0.0, 1.0, 0.0,
                        0.0, 1.0, 0.0,
                        //bottom side
                        0.0, -1.0, 0.0,
                        0.0, -1.0, 0.0,
                        0.0, -1.0, 0.0,
                        0.0, -1.0, 0.0,
                        0.0, -1.0, 0.0,
                        0.0, -1.0, 0.0,
                        //near side
                        0.0, 0.0, 1.0,
                        0.0, 0.0, 1.0,
                        0.0, 0.0, 1.0,
                        0.0, 0.0, 1.0,
                        0.0, 0.0, 1.0,
                        0.0, 0.0, 1.0,
                        //far side
                        0.0, 0.0, -1.0,
                        0.0, 0.0, -1.0,
                        0.0, 0.0, -1.0,
                        0.0, 0.0, -1.0,
                        0.0, 0.0, -1.0,
                        0.0, 0.0, -1.0,
                        //right side
                        1.0, 0.0, 0.0,
                        1.0, 0.0, 0.0,
                        1.0, 0.0, 0.0,
                        1.0, 0.0, 0.0,
                        1.0, 0.0, 0.0,
                        1.0, 0.0, 0.0,
                        //left side
                        -1.0, 0.0, 0.0,
                        -1.0, 0.0, 0.0,
                        -1.0, 0.0, 0.0,
                        -1.0, 0.0, 0.0,
                        -1.0, 0.0, 0.0,
                        -1.0, 0.0, 0.0
                     };

float cube_vertexes_wall_texture_coords2d[] =
                     { //top side
                       1.0, 1.0,
                       0.0, 1.0,
                       1.0, 0.0,
                       0.0, 1.0,
                       0.0, 0.0,
                       1.0, 0.0,
                       //bottom side
                       1.0, 1.0,
                       0.0, 1.0,
                       1.0, 0.0,
                       0.0, 1.0,
                       0.0, 0.0,
                       1.0, 0.0,
                       //near side
                       1.0, 1.0,
                       0.0, 1.0,
                       1.0, 0.0,
                       0.0, 1.0,
                       0.0, 0.0,
                       1.0, 0.0,
                       //far side
                       1.0, 1.0,
                       0.0, 1.0,
                       1.0, 0.0,
                       0.0, 1.0,
                       0.0, 0.0,
                       1.0, 0.0,
                       //right side
                       1.0, 1.0,
                       0.0, 1.0,
                       1.0, 0.0,
                       0.0, 1.0,
                       0.0, 0.0,
                       1.0, 0.0,
                       //left side
                       1.0, 1.0,
                       0.0, 1.0,
                       1.0, 0.0,
                       0.0, 1.0,
                       0.0, 0.0,
                       1.0, 0.0
                     };

//Pyramide
//1 = 0.0, 1.0, 0.0
//2 = 0.5, 0.0, -0.5
//3 = -0.5, 0.0, -0.5
//4 = -0.5, 0.0, 0.5
//5 = 0.5, 0.0, 0.5
float pyramide_vertexes_coords_normalized[] =
                     { //bottom side
                       0.5, 0.0, -0.5,
                       -0.5, 0.0, -0.5,
                       0.5, 0.0, 0.5,
                       -0.5, 0.0, -0.5,
                       -0.5, 0.0, 0.5,
                       0.5, 0.0, 0.5,
                       //near side
                       0.0, 1.0, 0.0,
                       -0.5, 0.0, 0.5,
                       0.5, 0.0, 0.5,
                       //far side
                       0.0, 1.0, 0.0,
                       0.5, 0.0, -0.5,
                       -0.5, 0.0, -0.5,
                       //right side
                       0.0, 1.0, 0.0,
                       0.5, 0.0, 0.5,
                       0.5, 0.0, -0.5,
                       //left side
                       0.0, 1.0, 0.0,
                       -0.5, 0.0, -0.5,
                       -0.5, 0.0, 0.5
                     };

float pyramide_vertexes_normals[] =
                     {
                        //bottom side
                        0.0, -1.0, 0.0,
                        0.0, -1.0, 0.0,
                        0.0, -1.0, 0.0,
                        0.0, -1.0, 0.0,
                        0.0, -1.0, 0.0,
                        0.0, -1.0, 0.0,
                        //near side
                        0.0, 0.447214, 0.894427,
                        0.0, 0.447214, 0.894427,
                        0.0, 0.447214, 0.894427,
                        //far side
                        0.0, 0.447214, -0.894427,
                        0.0, 0.447214, -0.894427,
                        0.0, 0.447214, -0.894427,
                        //right side
                        0.894427, 0.447214, 0,
                        0.894427, 0.447214, 0,
                        0.894427, 0.447214, 0,
                        //left side
                        -0.894427, 0.447214, 0,
                        -0.894427, 0.447214, 0,
                        -0.894427, 0.447214, 0,
                     };

void Sc8Lighting::initScene(int start_window_width, int start_window_height)
{
    window_width = start_window_width;
    window_height = start_window_height;

    //for RGBA texture
    glFunctions->glEnable(GL_BLEND);
    glFunctions->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    cam = new Camera(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, -1.0f));
    cam->setPitch(0.0f);
    cam->setYaw(0.0f);
    cam->setRoll(0.0f);
    cam->setMoveSpeed(0.06f);
    cam->setMouseSensitivity(0.15f);

    arrowPainter = new ArrowPainter(glFunctions);

    //Create shader program object
    gBoxShaderProgram = new ShaderProgram(glFunctions, ":Scenes/Sc8Lighting/shaders/box/vertshader.vert", ":/Scenes/Sc8Lighting/shaders/box/fragshader.frag");

    //Compile shader program
    if(!gBoxShaderProgram->compile()) {
        qDebug("[ERROR] initializeGL: compile cube shader program failed!");
        return;
    }

    //Create shader program object
    gLightShaderProgram = new ShaderProgram(glFunctions, ":Scenes/Sc8Lighting/shaders/light/vertshader.vert", ":/Scenes/Sc8Lighting/shaders/light/fragshader.frag");

    //Compile shader program
    if(!gLightShaderProgram->compile()) {
        qDebug("[ERROR] initializeGL: compile light shader program failed!");
        return;
    }

    //Create shader program object
    gPyramideShaderProgram = new ShaderProgram(glFunctions, ":Scenes/Sc8Lighting/shaders/pyramide/vertshader.vert", ":/Scenes/Sc8Lighting/shaders/pyramide/fragshader.frag");

    //Compile shader program
    if(!gPyramideShaderProgram->compile()) {
        qDebug("[ERROR] initializeGL: compile light shader program failed!");
        return;
    }

    //Vertex buffer object ID(name)
    unsigned int VBOBoxVertexes = 0;
    //Normals buffer object
    unsigned int VBOBoxNormals = 0;
    //Texture coordinats buffer object ID(name)
    unsigned int VBOBoxWallTexcoords = 0;
    //Vertex arrays object ID(name)
    unsigned int VAOBox = 0;

    //Allocate 1 buffer for VBO (Vertex Buffer Object)
    glFunctions->glGenBuffers(1, &VBOBoxVertexes);
    //Allocate 1 buffer for VBO (Vertex Buffer Object)
    glFunctions->glGenBuffers(1, &VBOBoxNormals);
    //Allocate 1 buffer for VBO (Vertex Buffer Object)
    glFunctions->glGenBuffers(1, &VBOBoxWallTexcoords);
    //Allocate 1 buffer for VAO (Vertex Arrays Object)
    glFunctions->glGenVertexArrays(1, &VAOBox);

    //Select VAO
    glFunctions->glBindVertexArray(VAOBox);

    //Use buffer object to an OpenGL buffer
    glFunctions->glBindBuffer(GL_ARRAY_BUFFER, VBOBoxVertexes);
    //Copying vertex data from the array to VBO
    glFunctions->glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertexes_coords_normalized), cube_vertexes_coords_normalized, GL_STATIC_DRAW);
    //Configuring the interpretation of the vertex buffer data
    glFunctions->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    //Use buffer object to an OpenGL buffer
    glFunctions->glBindBuffer(GL_ARRAY_BUFFER, VBOBoxNormals);
    //Copying vertex data from the array to VBO
    glFunctions->glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertexes_normals), cube_vertexes_normals, GL_STATIC_DRAW);
    //Configuring the interpretation of the vertex buffer data
    glFunctions->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    //Use buffer object to an OpenGL buffer
    glFunctions->glBindBuffer(GL_ARRAY_BUFFER, VBOBoxWallTexcoords);
    //Copying vertex texcoords data from the array to VBO
    glFunctions->glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertexes_wall_texture_coords2d), cube_vertexes_wall_texture_coords2d, GL_STATIC_DRAW);
    //Configuring the interpretation of the vertex texcoords buffer data
    glFunctions->glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

    glFunctions->glBindBuffer(GL_ARRAY_BUFFER, 0);


    //Light
    unsigned int VAOlight = 0;
    glFunctions->glGenVertexArrays(1, &VAOlight);
    glFunctions->glBindVertexArray(VAOlight);

    glFunctions->glBindBuffer(GL_ARRAY_BUFFER, VBOBoxVertexes);
    glFunctions->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glFunctions->glBindBuffer(GL_ARRAY_BUFFER, 0);

    //Unselect VAO(so that other calls don't change it)
    glFunctions->glBindVertexArray(0);

    //Pyramide
    //Vertex buffer object ID(name)
    unsigned int VBOPyramideVertexes = 0;
    //Normals buffer object
    unsigned int VBOPyramideNormals = 0;
    //Vertex arrays object ID(name)
    unsigned int VAOPyramide = 0;

    //Allocate 1 buffer for VBO (Vertex Buffer Object)
    glFunctions->glGenBuffers(1, &VBOPyramideVertexes);
    //Allocate 1 buffer for VBO (Vertex Buffer Object)
    glFunctions->glGenBuffers(1, &VBOPyramideNormals);
    //Allocate 1 buffer for VAO (Vertex Arrays Object)
    glFunctions->glGenVertexArrays(1, &VAOPyramide);

    //Select VAO
    glFunctions->glBindVertexArray(VAOPyramide);

    //Use buffer object to an OpenGL buffer
    glFunctions->glBindBuffer(GL_ARRAY_BUFFER, VBOPyramideVertexes);
    //Copying vertex data from the array to VBO
    glFunctions->glBufferData(GL_ARRAY_BUFFER, sizeof(pyramide_vertexes_coords_normalized), pyramide_vertexes_coords_normalized, GL_STATIC_DRAW);
    //Configuring the interpretation of the vertex buffer data
    glFunctions->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    //Use buffer object to an OpenGL buffer
    glFunctions->glBindBuffer(GL_ARRAY_BUFFER, VBOPyramideNormals);
    //Copying vertex data from the array to VBO
    glFunctions->glBufferData(GL_ARRAY_BUFFER, sizeof(pyramide_vertexes_normals), pyramide_vertexes_normals, GL_STATIC_DRAW);
    //Configuring the interpretation of the vertex buffer data
    glFunctions->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glFunctions->glBindBuffer(GL_ARRAY_BUFFER, 0);

    g_VAO_cube = VAOBox;
    g_VBO_cube_vertexes = VBOBoxVertexes;
    g_VBO_cube_normals = VBOBoxNormals;
    g_VBO_cube_wall_texcoords = VBOBoxWallTexcoords;
    g_VAO_light = VAOlight;
    g_VAO_pyramide = VAOPyramide;
    g_VBO_pyramide_vertexes = VBOPyramideVertexes;
    g_VBO_pyramide_normals = VBOPyramideNormals;
}

void Sc8Lighting::drawScene()
{
    glFunctions->glEnable(GL_DEPTH_TEST);
    glFunctions->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    gLightShaderProgram->enable();
    //use matrix
    //create model matrix
    model_matrix = glm::mat4(1.0f);
    //create view matrix
    view_matrix = glm::mat4(1.0f);
    //create projection matrix
    projection_matrix = glm::mat4(1.0f);

    //setting up projection
    projection_matrix = glm::perspective(45.0f, (float)window_width / (float)window_height, 0.1f, 100.0f);
    cam->update();
    view_matrix = cam->getViewMatrix();

    model_matrix = glm::rotate(model_matrix, glm::radians(light_rotation_around_degress), glm::vec3(0, 1, 0));
    model_matrix = glm::translate(model_matrix, g_light_to_cube_distance);
    model_matrix = glm::scale(model_matrix, glm::vec3(0.5, 0.5, 0.5));

    gLightShaderProgram->setUniformMatrix4fv("projectionMatrix", 1, GL_FALSE, glm::value_ptr(projection_matrix));
    gLightShaderProgram->setUniformMatrix4fv("viewMatrix", 1, GL_FALSE, glm::value_ptr(view_matrix));
    gLightShaderProgram->setUniformMatrix4fv("modelMatrix", 1, GL_FALSE, glm::value_ptr(model_matrix));
    gLightShaderProgram->setUniform3f("lightColor", g_light_color * g_light_color_coef);

    //Select VAO
    glFunctions->glBindVertexArray(g_VAO_light);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //Enable the vertex attribute(the rest attributes remain off for optimization)
    glFunctions->glEnableVertexAttribArray(0);

    //calculating light position
    //                             box position
    g_light_position = glm::vec3(0.0f, 0.0f, 0.0f) + g_light_to_cube_distance;
    g_light_position = glm::vec4(g_light_position, 0.0f) * glm::rotate(glm::mat4(1.0f), glm::radians(light_rotation_around_degress), glm::vec3(0, 1, 0));
    g_light_position.z = -g_light_position.z;
    //qInfo() << g_light_position.x << g_light_position.y << g_light_position.z;

    gLightShaderProgram->printfPrepare();

    //Draw box using triangles
    glFunctions->glDrawArrays(GL_TRIANGLES, 0, 36);

    //Debug output from
    //qInfo() << QString::fromStdString(gShaderProgram->printfGetData());
    gLightShaderProgram->printfTerminate();
    gLightShaderProgram->disable();



    //Select VAO
    glFunctions->glBindVertexArray(g_VAO_cube);
    //Select shader program
    gBoxShaderProgram->enable();
    //use matrix
    //create model matrix
    model_matrix = glm::mat4(1.0f);

    glm::mat4 rm_x = glm::rotate(glm::mat4(1.0f),
        glm::radians(y_rotation_speed_in_degrees), glm::vec3(0, 1, 0));
    glm::mat4 rm_y = glm::rotate(glm::mat4(1.0f),
        glm::radians(x_rotation_speed_in_degrees), glm::vec3(1, 0, 0));
    rotation_matrix = rm_x * rm_y * rotation_matrix;

    model_matrix = rotation_matrix * glm::scale(model_matrix, glm::vec3(x_size_scale, y_size_scale, 1.0f));
    glm::mat4 normal_matrix = glm::transpose(glm::inverse(model_matrix));

    view_matrix = cam->getViewMatrix();
    gBoxShaderProgram->setUniformMatrix4fv("projectionMatrix", 1, GL_FALSE, glm::value_ptr(projection_matrix));
    gBoxShaderProgram->setUniformMatrix4fv("viewMatrix", 1, GL_FALSE, glm::value_ptr(view_matrix));
    gBoxShaderProgram->setUniformMatrix4fv("modelMatrix", 1, GL_FALSE, glm::value_ptr(model_matrix));
    gBoxShaderProgram->setUniformMatrix4fv("normalMatrix", 1, GL_FALSE, glm::value_ptr(normal_matrix));
    gBoxShaderProgram->setUniform3f("cameraPosition", cam->getPosition());
    gBoxShaderProgram->setUniform3f("objectColor", 1.0f, 0.0f, 0.0f);
    gBoxShaderProgram->setUniform3f("ambientLightColor", g_light_color * g_light_color_coef);
    gBoxShaderProgram->setUniform1f("ambientLightCoef", g_light_ambient_coef);
    gBoxShaderProgram->setUniform3f("deffuseLightPosition", g_light_position);
    gBoxShaderProgram->setUniform3f("deffuseLightColor", g_light_color * g_light_color_coef);
    gBoxShaderProgram->setUniform3f("specularLightColor", g_light_color * g_light_color_coef);
    gBoxShaderProgram->setUniform1f("specularLightCoef", g_light_specular_coef);
    gBoxShaderProgram->setUniform1f("specularLightShineCoef", g_light_specular_shine_coef);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //Enable the vertex attribute(the rest attributes remain off for optimization)
    glFunctions->glEnableVertexAttribArray(0);
    glFunctions->glEnableVertexAttribArray(1);

    gBoxShaderProgram->printfPrepare();

    //Draw box using triangles
    glFunctions->glDrawArrays(GL_TRIANGLES, 0, 36);

    //Debug output from
    //qInfo() << QString::fromStdString(gBoxShaderProgram->printfGetData());
    gBoxShaderProgram->printfTerminate();

    glFunctions->glDisableVertexAttribArray(0);
    glFunctions->glDisableVertexAttribArray(1);
    //Unselect VAO
    glFunctions->glBindVertexArray(0);
    //Unselect shader program
    gBoxShaderProgram->disable();
    //Unselect VAO
    glFunctions->glBindVertexArray(0);

    ////Select VAO
    //glFunctions->glBindVertexArray(g_VAO_pyramide);
    ////Select shader program
    //gPyramideShaderProgram->enable();
    ////use matrix
    ////create model matrix
    //model_matrix = glm::mat4(1.0f);
    //
    //glm::mat4 rm_x = glm::rotate(glm::mat4(1.0f),
    //    glm::radians(y_rotation_speed_in_degrees), glm::vec3(0, 1, 0));
    //glm::mat4 rm_y = glm::rotate(glm::mat4(1.0f),
    //    glm::radians(x_rotation_speed_in_degrees), glm::vec3(1, 0, 0));
    //rotation_matrix = rm_x * rm_y * rotation_matrix;
    //
    //model_matrix = rotation_matrix * glm::scale(model_matrix, glm::vec3(x_size_scale, y_size_scale, 1.0f));
    //model_matrix = glm::translate(model_matrix, glm::vec3(0.0f, -0.25f, 0.0f));
    //glm::mat4 normal_matrix = glm::transpose(glm::inverse(model_matrix));
    //
    //view_matrix = cam->getViewMatrix();
    //gPyramideShaderProgram->setUniformMatrix4fv("projectionMatrix", 1, GL_FALSE, glm::value_ptr(projection_matrix));
    //gPyramideShaderProgram->setUniformMatrix4fv("viewMatrix", 1, GL_FALSE, glm::value_ptr(view_matrix));
    //gPyramideShaderProgram->setUniformMatrix4fv("modelMatrix", 1, GL_FALSE, glm::value_ptr(model_matrix));
    //gPyramideShaderProgram->setUniformMatrix4fv("normalMatrix", 1, GL_FALSE, glm::value_ptr(normal_matrix));
    //gPyramideShaderProgram->setUniform3f("cameraPosition", cam->getPosition());
    //gPyramideShaderProgram->setUniform3f("objectColor", 1.0f, 0.0f, 0.0f);
    //gPyramideShaderProgram->setUniform3f("ambientLightColor", 1.0f, 1.0f, 1.0f);
    //gPyramideShaderProgram->setUniform1f("ambientLightCoef", 0.3f);
    //gPyramideShaderProgram->setUniform3f("deffuseLightPosition", g_light_position);
    //gPyramideShaderProgram->setUniform3f("deffuseLightColor", g_light_color);
    //gPyramideShaderProgram->setUniform3f("specularLightColor", g_light_color);
    //gPyramideShaderProgram->setUniform1f("specularLightCoef", 0.5);
    //gPyramideShaderProgram->setUniform1f("specularLightShineCoef", 32);
    //
    ////glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    ////Enable the vertex attribute(the rest attributes remain off for optimization)
    //glFunctions->glEnableVertexAttribArray(0);
    //glFunctions->glEnableVertexAttribArray(1);
    //
    //gPyramideShaderProgram->printfPrepare();
    //
    ////Draw pyramide using triangles
    //glFunctions->glDrawArrays(GL_TRIANGLES, 0, 18);
    //
    ////Debug output from
    ////qInfo() << QString::fromStdString(gPyramideShaderProgram->printfGetData());
    //gPyramideShaderProgram->printfTerminate();
    //
    //glFunctions->glDisableVertexAttribArray(0);
    //glFunctions->glDisableVertexAttribArray(1);
    ////Unselect VAO
    //glFunctions->glBindVertexArray(0);
    ////Unselect shader program
    //gPyramideShaderProgram->disable();
    ////Unselect VAO
    //glFunctions->glBindVertexArray(0);
}

void Sc8Lighting::finishScene()
{
    glFunctions->glDeleteBuffers(1, &g_VBO_cube_vertexes);
    glFunctions->glDeleteBuffers(1, &g_VBO_cube_normals);
    glFunctions->glDeleteBuffers(1, &g_VBO_cube_wall_texcoords);
    glFunctions->glDeleteBuffers(1, &g_VBO_pyramide_vertexes);
    glFunctions->glDeleteBuffers(1, &g_VBO_pyramide_normals);
    glFunctions->glDeleteVertexArrays(1, &g_VAO_cube);
    glFunctions->glDeleteVertexArrays(1, &g_VAO_light);
    glFunctions->glDeleteVertexArrays(1, &g_VAO_pyramide);

    glFunctions->glDisable(GL_BLEND);

    rotation_matrix = glm::mat4(1.0f);
    x_rot = 0;
    y_rot = 0;
    x_rotation_speed_in_degrees = 0;
    y_rotation_speed_in_degrees = 0;
    x_size_scale = 1;
    y_size_scale = 1;
    light_rotation_around_degress = 0;

    delete gBoxShaderProgram;
    delete gLightShaderProgram;
    delete gPyramideShaderProgram;
    delete cam;
    delete arrowPainter;
}

void Sc8Lighting::resizeSceneWindow(int w, int h)
{
    window_width = w;
    window_height = h;
}

void Sc8Lighting::mousePressEventHandler(QMouseEvent event)
{
    if(event.button() != Qt::LeftButton)
        return;

    mouse_last_xpos = event.pos().x();
    mouse_last_ypos = event.pos().y();
    mouse_left_button_pressed = true;
}

void Sc8Lighting::mouseReleaseEventHandler(QMouseEvent event)
{
    if(event.button() != Qt::LeftButton)
        return;
    mouse_left_button_pressed = false;
}

void Sc8Lighting::mouseMoveEventHandler(QMouseEvent event)
{
    //"Note that the returned value(QMouseEvent::button()) is always Qt::NoButton for mouse move events."

    if(mouse_left_button_pressed) {
        float xpos = event.pos().x();
        float ypos = event.pos().y();

        float xoffset = xpos - mouse_last_xpos;
        float yoffset = mouse_last_ypos - ypos;

        mouse_last_xpos = xpos;
        mouse_last_ypos = ypos;

        cam->processMouseOffsets(xoffset, yoffset);
    }
}

void Sc8Lighting::keyPressEventHandler(QKeyEvent* event)
{
    //Exclude repeated calls when the button is pressed
    if(event->isAutoRepeat())
        return;
    //language-and case-insensitive button native code
    Qt::Key nativeKey = (Qt::Key)event->nativeVirtualKey();
    switch(nativeKey) {
    case Qt::Key_W:
        cam->setMoveDirectionFlagStatus(CameraMoveDirections::MOVE_FORWARD, true);
        break;
    case Qt::Key_S:
        cam->setMoveDirectionFlagStatus(CameraMoveDirections::MOVE_BACK, true);
        break;
    case Qt::Key_D:
        cam->setMoveDirectionFlagStatus(CameraMoveDirections::MOVE_RIGHT, true);
        break;
    case Qt::Key_A:
        cam->setMoveDirectionFlagStatus(CameraMoveDirections::MOVE_LEFT, true);
        break;
    case Qt::Key_Up:
        cam->setMoveDirectionFlagStatus(CameraMoveDirections::MOVE_UP, true);
        break;
    case Qt::Key_Down:
        cam->setMoveDirectionFlagStatus(CameraMoveDirections::MOVE_DOWN, true);
        break;
    default:
        break;
    }
}

void Sc8Lighting::keyReleaseEventHandler(QKeyEvent* event)
{
    //Exclude repeated calls when the button is pressed
    if(event->isAutoRepeat())
        return;
    //language-and case-insensitive button native code
    Qt::Key nativeKey = (Qt::Key)event->nativeVirtualKey();
    switch(nativeKey) {
    case Qt::Key_W:
        cam->setMoveDirectionFlagStatus(CameraMoveDirections::MOVE_FORWARD, false);
        break;
    case Qt::Key_S:
        cam->setMoveDirectionFlagStatus(CameraMoveDirections::MOVE_BACK, false);
        break;
    case Qt::Key_D:
        cam->setMoveDirectionFlagStatus(CameraMoveDirections::MOVE_RIGHT, false);
        break;
    case Qt::Key_A:
        cam->setMoveDirectionFlagStatus(CameraMoveDirections::MOVE_LEFT, false);
        break;
    case Qt::Key_Up:
        cam->setMoveDirectionFlagStatus(CameraMoveDirections::MOVE_UP, false);
        break;
    case Qt::Key_Down:
        cam->setMoveDirectionFlagStatus(CameraMoveDirections::MOVE_DOWN, false);
        break;
    default:
        break;
    }
}

void Sc8Lighting::createUiOptionsWidget()
{
    uiOptionsForm = new Ui::Sc8LightingOptionsForm;
    optionsFormWidget = new QWidget;
    uiOptionsForm->setupUi(optionsFormWidget);
    globalMainWindowFormUI->sceneOptionsStackedWidget->addWidget(optionsFormWidget);

    QObject::connect(uiOptionsForm->xRotationSlider, &QSlider::valueChanged, this, &Sc8Lighting::setXRotSpeedValueFromSlider);
    QObject::connect(uiOptionsForm->yRotationSlider, &QSlider::valueChanged, this, &Sc8Lighting::setYRotSpeedValueFromSlider);
    QObject::connect(uiOptionsForm->xSizeSlider, &QSlider::valueChanged, this, &Sc8Lighting::setXSizeValueFromSlider);
    QObject::connect(uiOptionsForm->ySizeSlider, &QSlider::valueChanged, this, &Sc8Lighting::setYSizeValueFromSlider);
    QObject::connect(uiOptionsForm->resetRotationsPushButton, &QPushButton::clicked, this, &Sc8Lighting::resetRotationsButtonClicked);

    QObject::connect(uiOptionsForm->lightRotationSlider, &QSlider::valueChanged, this, &Sc8Lighting::setLightRotValueFromSlider);

    uiOptionsForm->lightColorCoefSlider->setValue(g_light_color_coef * 100);
    uiOptionsForm->lightColorCoefValueLabel->setText(QString::number(g_light_color_coef));
    QObject::connect(uiOptionsForm->lightColorCoefSlider, &QSlider::valueChanged, this, &Sc8Lighting::setLightColorCoefValueFromSlider);

    uiOptionsForm->lightAmbientCoefSlider->setValue(g_light_ambient_coef * 100);
    uiOptionsForm->lightAmbientCoefValueLabel->setText(QString::number(g_light_ambient_coef));
    QObject::connect(uiOptionsForm->lightAmbientCoefSlider, &QSlider::valueChanged, this, &Sc8Lighting::setLightAmbientCoefValueFromSlider);

    uiOptionsForm->lightSpecularCoefSlider->setValue(g_light_specular_coef * 100);
    uiOptionsForm->lightSpecularCoefValueLabel->setText(QString::number(g_light_specular_coef));
    QObject::connect(uiOptionsForm->lightSpecularCoefSlider, &QSlider::valueChanged, this, &Sc8Lighting::setLightSpecularCoefValueFromSlider);

    uiOptionsForm->lightSpecularShineCoefSlider->setValue(g_light_specular_shine_coef);
    uiOptionsForm->lightSpecularShineCoefValueLabel->setText(QString::number(g_light_specular_shine_coef));
    QObject::connect(uiOptionsForm->lightSpecularShineCoefSlider, &QSlider::valueChanged, this, &Sc8Lighting::setLightSpecularShineCoefValueFromSlider);
}

void Sc8Lighting::deleteUiOptionsWidget()
{
    globalMainWindowFormUI->sceneOptionsStackedWidget->removeWidget(optionsFormWidget);
    delete optionsFormWidget;
    delete uiOptionsForm;
}

void Sc8Lighting::setXRotSpeedValueFromSlider(int new_value)
{
    x_rotation_speed_in_degrees = (1.0f / 100) * new_value;
}

void Sc8Lighting::setYRotSpeedValueFromSlider(int new_value)
{
    y_rotation_speed_in_degrees = (1.0f / 100) * new_value;
}

void Sc8Lighting::setXSizeValueFromSlider(int new_value)
{
    x_size_scale = (1.0f / 100) * new_value;
}

void Sc8Lighting::setYSizeValueFromSlider(int new_value)
{
    y_size_scale = (1.0f / 100) * new_value;
}

void Sc8Lighting::resetRotationsButtonClicked()
{
    rotation_matrix = glm::mat4(1.0f);
    x_rot = 0;
    y_rot = 0;
}

void Sc8Lighting::setLightRotValueFromSlider(int new_value)
{
    light_rotation_around_degress = new_value;
}

void Sc8Lighting::setLightColorCoefValueFromSlider(int new_value)
{
    g_light_color_coef = (1.0f / 100) * new_value;
    uiOptionsForm->lightColorCoefValueLabel->setText(QString::number(g_light_color_coef));
}

void Sc8Lighting::setLightAmbientCoefValueFromSlider(int new_value)
{
    g_light_ambient_coef = (1.0f / 100) * new_value;
    uiOptionsForm->lightAmbientCoefValueLabel->setText(QString::number(g_light_ambient_coef));
}

void Sc8Lighting::setLightSpecularCoefValueFromSlider(int new_value)
{
    g_light_specular_coef = (1.0f / 100) * new_value;
    uiOptionsForm->lightSpecularCoefValueLabel->setText(QString::number(g_light_specular_coef));
}

void Sc8Lighting::setLightSpecularShineCoefValueFromSlider(int new_value)
{
    g_light_specular_shine_coef = new_value;
    uiOptionsForm->lightSpecularShineCoefValueLabel->setText(QString::number(g_light_specular_shine_coef));
}
