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

void Sc8Lighting::initScene(int start_window_width, int start_window_height)
{
    window_width = start_window_width;
    window_height = start_window_height;

    //for RGBA texture
    glFunctions->glEnable(GL_BLEND);
    glFunctions->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    //0 = 0.5, 0.5, -0.5
    //1 = -0.5, 0.5, -0.5
    //2 = -0.5, 0.5, 0.5
    //3 = 0.5, 0.5, 0.5
    //4 = 0.5, -0.5, -0.5
    //5 = -0.5, -0.5, -0.5
    //6 = -0.5, -0.5, 0.5
    //7 = 0.5, -0.5, 0.5

    //I specifically set all the variables manually, because this is a test code.
    float box_vertexes_coords_normalized[] =
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

    float box_vertexes_normals[] =
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

    float box_vertexes_wall_texture_coords2d[] =
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

    cam = new Camera(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, -1.0f));
    cam->setPitch(0.0f);
    cam->setYaw(0.0f);
    cam->setRoll(0.0f);
    cam->setMoveSpeed(0.06f);
    cam->setMouseSensitivity(0.15f);

    //Create shader program object
    gBoxShaderProgram = new ShaderProgram(glFunctions, ":Scenes/Sc8Lighting/shaders/box/vertshader.vert", ":/Scenes/Sc8Lighting/shaders/box/fragshader.frag");

    //Compile shader program
    if(!gBoxShaderProgram->compile()) {
        qDebug("[ERROR] initializeGL: compile box shader program failed!");
        return;
    }

    //Create shader program object
    gLightShaderProgram = new ShaderProgram(glFunctions, ":Scenes/Sc8Lighting/shaders/light/vertshader.vert", ":/Scenes/Sc8Lighting/shaders/light/fragshader.frag");

    //Compile shader program
    if(!gLightShaderProgram->compile()) {
        qDebug("[ERROR] initializeGL: compile light shader program failed!");
        return;
    }

    //Load texture image
    QImage imgBoxWallTexture(":Scenes/Sc8Lighting/textures/BoxWall512x512.png");
    if(imgBoxWallTexture.isNull()) {
        qInfo("[ERROR] initScene: image texture load failed!");
        return;
    }
    imgBoxWallTexture = QGLWidget::convertToGLFormat(imgBoxWallTexture);
    //You must use the "Premultiplied alpha" format, otherwise artifacts appear
    imgBoxWallTexture = imgBoxWallTexture.convertToFormat(QImage::Format_ARGB32_Premultiplied);

    //Texture ID(name)
    unsigned int textureBoxWall = 0;
    //Allocate 1 buffer for textures
    glFunctions->glGenTextures(1, &textureBoxWall);
    //Select wall texture
    glFunctions->glBindTexture(GL_TEXTURE_2D, textureBoxWall);
    //Load data to texture
    glFunctions->glTexImage2D(GL_TEXTURE_2D, //selected texture type
                 0, //mipmap level(we generate him using OpenGL)
                 GL_RGBA, //texture data format
                 imgBoxWallTexture.width(),
                 imgBoxWallTexture.height(),
                 0, //always zero
                 GL_RGBA, //image format
                 GL_UNSIGNED_BYTE, //image data format
                 imgBoxWallTexture.bits() //image data
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
    glFunctions->glBufferData(GL_ARRAY_BUFFER, sizeof(box_vertexes_coords_normalized), box_vertexes_coords_normalized, GL_STATIC_DRAW);
    //Configuring the interpretation of the vertex buffer data
    glFunctions->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    //Use buffer object to an OpenGL buffer
    glFunctions->glBindBuffer(GL_ARRAY_BUFFER, VBOBoxNormals);
    //Copying vertex data from the array to VBO
    glFunctions->glBufferData(GL_ARRAY_BUFFER, sizeof(box_vertexes_normals), box_vertexes_normals, GL_STATIC_DRAW);
    //Configuring the interpretation of the vertex buffer data
    glFunctions->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    //Use buffer object to an OpenGL buffer
    glFunctions->glBindBuffer(GL_ARRAY_BUFFER, VBOBoxWallTexcoords);
    //Copying vertex texcoords data from the array to VBO
    glFunctions->glBufferData(GL_ARRAY_BUFFER, sizeof(box_vertexes_wall_texture_coords2d), box_vertexes_wall_texture_coords2d, GL_STATIC_DRAW);
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

    g_VAO_box = VAOBox;
    g_VBO_box_vertexes = VBOBoxVertexes;
    g_VBO_box_normals = VBOBoxNormals;
    g_VBO_box_wall_texcoords = VBOBoxWallTexcoords;
    g_texture_box_wall = textureBoxWall;
    g_VAO_light = VAOlight;
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

    model_matrix = glm::rotate(model_matrix, glm::radians(light_rotation_around_box_degress), glm::vec3(0, 1, 0));
    model_matrix = glm::translate(model_matrix, g_light_to_box_distance);
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
    g_light_position = glm::vec3(0.0f, 0.0f, 0.0f) + g_light_to_box_distance;
    g_light_position = glm::vec4(g_light_position, 0.0f) * glm::rotate(glm::mat4(1.0f), glm::radians(light_rotation_around_box_degress), glm::vec3(0, 1, 0));
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
    glFunctions->glBindVertexArray(g_VAO_box);
    //Select shader program
    gBoxShaderProgram->enable();
    //use matrix
    //create model matrix
    model_matrix = glm::mat4(1.0f);
    view_matrix = cam->getViewMatrix();
    gBoxShaderProgram->setUniformMatrix4fv("projectionMatrix", 1, GL_FALSE, glm::value_ptr(projection_matrix));
    gBoxShaderProgram->setUniformMatrix4fv("viewMatrix", 1, GL_FALSE, glm::value_ptr(view_matrix));
    gBoxShaderProgram->setUniformMatrix4fv("modelMatrix", 1, GL_FALSE, glm::value_ptr(model_matrix));
    gBoxShaderProgram->setUniform3f("objectColor", 1.0f, 0.0f, 0.0f);
    gBoxShaderProgram->setUniform3f("ambientLightColor", 1.0f, 1.0f, 1.0f);
    gBoxShaderProgram->setUniform1f("ambientLightCoef", 0.3f);
    gBoxShaderProgram->setUniform3f("deffuseLightPosition", g_light_position);
    gBoxShaderProgram->setUniform3f("deffuseLightColor", g_light_color);

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


    glFunctions->glDisable(GL_DEPTH_TEST);
}

void Sc8Lighting::finishScene()
{
    glFunctions->glDeleteTextures(1, &g_texture_box_wall);
    glFunctions->glDeleteBuffers(1, &g_VBO_box_vertexes);
    glFunctions->glDeleteBuffers(1, &g_VBO_box_normals);
    glFunctions->glDeleteBuffers(1, &g_VBO_box_wall_texcoords);
    glFunctions->glDeleteVertexArrays(1, &g_VAO_box);
    glFunctions->glDeleteVertexArrays(1, &g_VAO_light);

    glFunctions->glDisable(GL_BLEND);

    delete gBoxShaderProgram;
    delete gLightShaderProgram;
    delete cam;
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

void Sc8Lighting::createUiOptionsWidgets()
{
    lightRotationSpeedSlider = new QSlider(Qt::Orientation::Horizontal);
    lightRotationSpeedSlider->setMinimum(0);
    lightRotationSpeedSlider->setMaximum(359);
    QObject::connect(lightRotationSpeedSlider, &QSlider::valueChanged, this, &Sc8Lighting::setLightRotSpeedValueFromSlider);
    globalMainWindowFormUI->sceneOptionsGridLayout->addWidget(lightRotationSpeedSlider);
}

void Sc8Lighting::deleteUiOptionsWidgets()
{
    globalMainWindowFormUI->sceneOptionsGridLayout->removeWidget(lightRotationSpeedSlider);
    delete lightRotationSpeedSlider;
    light_rotation_around_box_degress = 0;
}

void Sc8Lighting::setLightRotSpeedValueFromSlider(int new_value)
{
    light_rotation_around_box_degress = new_value;
}

