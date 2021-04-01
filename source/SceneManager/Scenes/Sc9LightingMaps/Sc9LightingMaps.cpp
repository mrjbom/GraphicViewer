#include "Sc9LightingMaps.h"
#include "../../globalvars.h"
#include <QGLWidget> //for convertation to gl format

Sc9LightingMaps::Sc9LightingMaps(QOpenGLContext* openGLContext)
{
    glFunctions = openGLContext->versionFunctions<QOpenGLFunctions_4_5_Core>();
}

Sc9LightingMaps::~Sc9LightingMaps()
{
}

void Sc9LightingMaps::initScene(int start_window_width, int start_window_height)
{
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
                            -0.894427, 0.447214, 0
                         };

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
    gBoxShaderProgram = new ShaderProgram(glFunctions, ":Scenes/Sc9LightingMaps/shaders/box/vertshader.vert", ":/Scenes/Sc9LightingMaps/shaders/box/fragshader.frag");

    gBoxShaderProgram->createNamedStringFromFile(":Scenes/Sc9LightingMaps/shaders/box/light_type.glsl", "/light_type.glsl");
    //Compile shader program
    if(!gBoxShaderProgram->compile()) {
        qDebug("[ERROR] initializeGL: compile cube shader program failed!");
        return;
    }

    //Create shader program object
    gLightShaderProgram = new ShaderProgram(glFunctions, ":Scenes/Sc9LightingMaps/shaders/light/vertshader.vert", ":/Scenes/Sc9LightingMaps/shaders/light/fragshader.frag");

    //Compile shader program
    if(!gLightShaderProgram->compile()) {
        qDebug("[ERROR] initializeGL: compile light shader program failed!");
        return;
    }

    //Load texture image
    QImage imgWallTexture(":Scenes/Sc9LightingMaps/textures/metalbox_deffusemap512x512.png");
    if(imgWallTexture.isNull()) {
        qInfo("[ERROR] initScene: image texture load failed!");
        return;
    }
    imgWallTexture = QGLWidget::convertToGLFormat(imgWallTexture);
    //You must use the "Premultiplied alpha" format, otherwise artifacts appear
    imgWallTexture = imgWallTexture.convertToFormat(QImage::Format_ARGB32_Premultiplied);

    //Load texture image
    QImage imgWallTexture2(":Scenes/Sc9LightingMaps/textures/metalbox_specularmap512x512.png");
    if(imgWallTexture2.isNull()) {
        qInfo("[ERROR] initScene: image texture load failed!");
        return;
    }
    imgWallTexture2 = QGLWidget::convertToGLFormat(imgWallTexture2);
    //You must use the "Premultiplied alpha" format, otherwise artifacts appear
    imgWallTexture2 = imgWallTexture2.convertToFormat(QImage::Format_ARGB32_Premultiplied);

    //Texture ID(name)
    unsigned int metalbox_deffusemap_texture = 0;
    unsigned int metalbox_specularmap_texture = 0;
    //Allocate 1 buffer for textures
    glFunctions->glGenTextures(1, &metalbox_deffusemap_texture);
    glFunctions->glGenTextures(1, &metalbox_specularmap_texture);
    //Select wall texture
    glFunctions->glBindTexture(GL_TEXTURE_2D, metalbox_deffusemap_texture);
    //Load data to texture
    glFunctions->glTexImage2D(GL_TEXTURE_2D, //selected texture type
                 0, //mipmap level(we generate him using OpenGL)
                 GL_RGBA, //texture data format
                 imgWallTexture.width(),
                 imgWallTexture.height(),
                 0, //always zero
                 GL_RGBA, //image format
                 GL_UNSIGNED_BYTE, //image data format
                 imgWallTexture.bits() //image data
                );

    if(glFunctions->glGetError() != GL_NO_ERROR) {
        qInfo("[ERROR] initScene: glTexImage2D failed!");
        return;
    }

    //Generate mipmap for texture
    glFunctions->glGenerateMipmap(GL_TEXTURE_2D);

    //Setting up texture
    //Texture draw
    glFunctions->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glFunctions->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //Texture filtration
    glFunctions->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glFunctions->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //Select wall texture
    glFunctions->glBindTexture(GL_TEXTURE_2D, metalbox_specularmap_texture);
    //Load data to texture
    glFunctions->glTexImage2D(GL_TEXTURE_2D, //selected texture type
                 0, //mipmap level(we generate him using OpenGL)
                 GL_RGBA, //texture data format
                 imgWallTexture2.width(),
                 imgWallTexture2.height(),
                 0, //always zero
                 GL_RGBA, //image format
                 GL_UNSIGNED_BYTE, //image data format
                 imgWallTexture2.bits() //image data
                );

    if(glFunctions->glGetError() != GL_NO_ERROR) {
        qInfo("[ERROR] initScene: glTexImage2D failed!");
        return;
    }

    //Generate mipmap for texture
    glFunctions->glGenerateMipmap(GL_TEXTURE_2D);

    //Setting up texture
    //Texture draw
    glFunctions->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glFunctions->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //Texture filtration
    glFunctions->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glFunctions->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //Unselect texture
    glFunctions->glBindTexture(GL_TEXTURE_2D, 0);

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
    g_VBO_cube_metalbox_deffusemap_texcoords = VBOBoxWallTexcoords;
    g_metalbox_deffusemap_texture = metalbox_deffusemap_texture;
    g_metalbox_specularmap_texture = metalbox_specularmap_texture;
    g_VAO_light = VAOlight;
}

void Sc9LightingMaps::drawScene()
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
    model_matrix = glm::translate(model_matrix, g_light_direction);
    model_matrix = glm::scale(model_matrix, glm::vec3(0.5, 0.5, 0.5));

    gLightShaderProgram->setUniformMatrix4fv("projectionMatrix", 1, GL_FALSE, glm::value_ptr(projection_matrix));
    gLightShaderProgram->setUniformMatrix4fv("viewMatrix", 1, GL_FALSE, glm::value_ptr(view_matrix));
    gLightShaderProgram->setUniformMatrix4fv("modelMatrix", 1, GL_FALSE, glm::value_ptr(model_matrix));
    gLightShaderProgram->setUniform3f("lightColor", g_light_color);

    //Select VAO
    glFunctions->glBindVertexArray(g_VAO_light);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //Enable the vertex attribute(the rest attributes remain off for optimization)
    glFunctions->glEnableVertexAttribArray(0);

    //calculating light position
    //                             box position
    g_light_position = g_light_direction;
    g_light_position = glm::vec4(g_light_position, 1.0f) * glm::rotate(glm::mat4(1.0f), glm::radians(light_rotation_around_degress), glm::vec3(0, 1, 0));
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
    //Select texture
    glFunctions->glActiveTexture(GL_TEXTURE0);
    glFunctions->glBindTexture(GL_TEXTURE_2D, g_metalbox_deffusemap_texture);
    glFunctions->glActiveTexture(GL_TEXTURE1);
    glFunctions->glBindTexture(GL_TEXTURE_2D, g_metalbox_specularmap_texture);
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
    gBoxShaderProgram->setUniform1i("material.diffuse", 0);
    gBoxShaderProgram->setUniform1i("material.specular", 1);
    gBoxShaderProgram->setUniform1f("material.shininess", 32.0f);
    gBoxShaderProgram->setUniform3f("light.position", g_light_position);
    gBoxShaderProgram->setUniform3f("light.ambient", 0.4f, 0.4f, 0.4f);
    gBoxShaderProgram->setUniform3f("light.diffuse", 0.7f, 0.7f, 0.7f);
    gBoxShaderProgram->setUniform3f("light.specular", 1.0f, 1.0f, 1.0f);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //Enable the vertex attribute(the rest attributes remain off for optimization)
    glFunctions->glEnableVertexAttribArray(0);
    glFunctions->glEnableVertexAttribArray(1);
    glFunctions->glEnableVertexAttribArray(2);

    gBoxShaderProgram->printfPrepare();

    //Draw box using triangles
    glFunctions->glDrawArrays(GL_TRIANGLES, 0, 36);

    //Debug output from
    //qInfo() << QString::fromStdString(gBoxShaderProgram->printfGetData());
    gBoxShaderProgram->printfTerminate();

    glFunctions->glDisableVertexAttribArray(0);
    glFunctions->glDisableVertexAttribArray(1);
    glFunctions->glDisableVertexAttribArray(2);
    //Unselect VAO
    glFunctions->glBindVertexArray(0);
    //Unselect shader program
    gBoxShaderProgram->disable();
    //Unselect texture
    glFunctions->glBindTexture(GL_TEXTURE_2D, 0);
    //Unselect VAO
    glFunctions->glBindVertexArray(0);
}

void Sc9LightingMaps::finishScene()
{
    glFunctions->glDeleteBuffers(1, &g_VBO_cube_vertexes);
    glFunctions->glDeleteBuffers(1, &g_VBO_cube_normals);
    glFunctions->glDeleteBuffers(1, &g_VBO_cube_metalbox_deffusemap_texcoords);
    glFunctions->glDeleteVertexArrays(1, &g_VAO_cube);
    glFunctions->glDeleteVertexArrays(1, &g_VAO_light);

    glFunctions->glDisable(GL_BLEND);

    rotation_matrix = glm::mat4(1.0f);
    x_rot = 0;
    y_rot = 0;
    x_rotation_speed_in_degrees = 0;
    y_rotation_speed_in_degrees = 0;
    x_size_scale = 1;
    y_size_scale = 1;
    light_rotation_around_degress = 0;
    g_light_direction = glm::vec3(2.5f, 0.0f, 0.0f);
    g_light_color = glm::vec3(1.0f, 1.0f, 1.0f);

    delete gBoxShaderProgram;
    delete gLightShaderProgram;
    delete cam;
    delete arrowPainter;
}

void Sc9LightingMaps::resizeSceneWindow(int w, int h)
{
    window_width = w;
    window_height = h;
}

void Sc9LightingMaps::mousePressEventHandler(QMouseEvent event)
{
    if(event.button() != Qt::LeftButton)
        return;

    mouse_last_xpos = event.pos().x();
    mouse_last_ypos = event.pos().y();
    mouse_left_button_pressed = true;
}

void Sc9LightingMaps::mouseReleaseEventHandler(QMouseEvent event)
{
    if(event.button() != Qt::LeftButton)
        return;
    mouse_left_button_pressed = false;
}

void Sc9LightingMaps::mouseMoveEventHandler(QMouseEvent event)
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

void Sc9LightingMaps::keyPressEventHandler(QKeyEvent* event)
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

void Sc9LightingMaps::keyReleaseEventHandler(QKeyEvent* event)
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

void Sc9LightingMaps::createUiOptionsWidget()
{
    uiOptionsForm = new Ui::Sc9LightingMapsOptionsForm;
    optionsFormWidget = new QWidget;
    uiOptionsForm->setupUi(optionsFormWidget);
    globalMainWindowFormUI->sceneOptionsStackedWidget->addWidget(optionsFormWidget);

    QObject::connect(uiOptionsForm->xRotationSlider, &QSlider::valueChanged, this, &Sc9LightingMaps::setXRotSpeedValueFromSlider);
    QObject::connect(uiOptionsForm->yRotationSlider, &QSlider::valueChanged, this, &Sc9LightingMaps::setYRotSpeedValueFromSlider);
    QObject::connect(uiOptionsForm->xSizeSlider, &QSlider::valueChanged, this, &Sc9LightingMaps::setXSizeValueFromSlider);
    QObject::connect(uiOptionsForm->ySizeSlider, &QSlider::valueChanged, this, &Sc9LightingMaps::setYSizeValueFromSlider);
    QObject::connect(uiOptionsForm->resetRotationsPushButton, &QPushButton::clicked, this, &Sc9LightingMaps::resetRotationsButtonClicked);
    QObject::connect(uiOptionsForm->lightRotationSlider, &QSlider::valueChanged, this, &Sc9LightingMaps::setLightRotValueFromSlider);
    uiOptionsForm->lightDistinationDoubleSpinBoxX->setValue(g_light_direction.x);
    QObject::connect(uiOptionsForm->lightDistinationDoubleSpinBoxX, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &Sc9LightingMaps::setXLightDistValueFromSlider);
    uiOptionsForm->lightDistinationDoubleSpinBoxY->setValue(g_light_direction.y);
    QObject::connect(uiOptionsForm->lightDistinationDoubleSpinBoxY, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &Sc9LightingMaps::setYLightDistValueFromSlider);
    uiOptionsForm->lightDistinationDoubleSpinBoxZ->setValue(g_light_direction.z);
    QObject::connect(uiOptionsForm->lightDistinationDoubleSpinBoxZ, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &Sc9LightingMaps::setZLightDistValueFromSlider);
}

void Sc9LightingMaps::deleteUiOptionsWidget()
{
    globalMainWindowFormUI->sceneOptionsStackedWidget->removeWidget(optionsFormWidget);
    delete optionsFormWidget;
    delete uiOptionsForm;
}

void Sc9LightingMaps::setXRotSpeedValueFromSlider(int new_value)
{
    x_rotation_speed_in_degrees = (1.0f / 100) * new_value;
}

void Sc9LightingMaps::setYRotSpeedValueFromSlider(int new_value)
{
    y_rotation_speed_in_degrees = (1.0f / 100) * new_value;
}

void Sc9LightingMaps::setXSizeValueFromSlider(int new_value)
{
    x_size_scale = (1.0f / 100) * new_value;
}

void Sc9LightingMaps::setYSizeValueFromSlider(int new_value)
{
    y_size_scale = (1.0f / 100) * new_value;
}

void Sc9LightingMaps::resetRotationsButtonClicked()
{
    rotation_matrix = glm::mat4(1.0f);
    x_rot = 0;
    y_rot = 0;
}

void Sc9LightingMaps::setLightRotValueFromSlider(int new_value)
{
    light_rotation_around_degress = new_value;
}

void Sc9LightingMaps::setXLightDistValueFromSlider(double new_value)
{
    g_light_direction.x = new_value;
}

void Sc9LightingMaps::setYLightDistValueFromSlider(double new_value)
{
    g_light_direction.y = new_value;
}

void Sc9LightingMaps::setZLightDistValueFromSlider(double new_value)
{
    g_light_direction.z = new_value;
}
