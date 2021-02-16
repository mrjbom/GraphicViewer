#include "Sc7Box3DCam.h"
#include "../../globalvars.h"
#include <QGLWidget> //for convertation to gl format

Sc7Box3DCam::Sc7Box3DCam(QOpenGLContext* openGLContext)
{
    glFunctions = openGLContext->versionFunctions<QOpenGLFunctions_4_5_Core>();
}

Sc7Box3DCam::~Sc7Box3DCam()
{
}

void Sc7Box3DCam::initScene(int start_window_width, int start_window_height)
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
                           0.5, -0.5, -0.5,
                           -0.5, -0.5, -0.5,
                           0.5, -0.5, 0.5,
                           -0.5, -0.5, -0.5,
                           -0.5, -0.5, 0.5,
                           0.5, -0.5, 0.5,
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
    gShaderProgram = new ShaderProgram(glFunctions, ":Scenes/Sc7Box3DCam/shaders/vertshader.vert", ":/Scenes/Sc7Box3DCam/shaders/fragshader.frag");

    //Compile shader program
    if(!gShaderProgram->compile()) {
        qDebug("[ERROR] initializeGL: makeShaderProgram failed!");
        return;
    }

    //Load texture image
    QImage imgBoxWallTexture(":Scenes/Sc6Box3DPerspective/textures/BoxWall512x512.png");
    if(imgBoxWallTexture.isNull()) {
        qInfo("[ERROR] initScene: image texture load failed!");
        return;
    }
    imgBoxWallTexture = QGLWidget::convertToGLFormat(imgBoxWallTexture);
    //You must use the "Premultiplied alpha" format, otherwise artifacts appear
    imgBoxWallTexture = imgBoxWallTexture.convertToFormat(QImage::Format_ARGB32_Premultiplied);

    //Texture ID(name)
    unsigned int textureBoxWall = 0;
    unsigned int textureBoxWall2 = 0;
    //Allocate 1 buffer for textures
    glFunctions->glGenTextures(1, &textureBoxWall);
    glFunctions->glGenTextures(1, &textureBoxWall2);
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

    //Select second texture
    glFunctions->glBindTexture(GL_TEXTURE_2D, textureBoxWall2);

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
    unsigned int VBOBoxVertexes2 = 0;
    //Texture coordinats buffer object ID(name)
    unsigned int VBOBoxWallTexcoords = 0;
    unsigned int VBOBoxWallTexcoords2 = 0;
    //Vertex arrays object ID(name)
    unsigned int VAOBox = 0;
    unsigned int VAOBox2 = 0;

    //Allocate 1 buffer for VBO (Vertex Buffer Object)
    glFunctions->glGenBuffers(1, &VBOBoxVertexes);
    glFunctions->glGenBuffers(1, &VBOBoxVertexes2);
    //Allocate 1 buffer for VBO (Vertex Buffer Object)
    glFunctions->glGenBuffers(1, &VBOBoxWallTexcoords);
    glFunctions->glGenBuffers(1, &VBOBoxWallTexcoords2);
    //Allocate 1 buffer for VAO (Vertex Arrays Object)
    glFunctions->glGenVertexArrays(1, &VAOBox);
    glFunctions->glGenVertexArrays(1, &VAOBox2);

    //Select VAO
    glFunctions->glBindVertexArray(VAOBox);

    //Use buffer object to an OpenGL buffer
    glFunctions->glBindBuffer(GL_ARRAY_BUFFER, VBOBoxVertexes);
    //Copying vertex data from the array to VBO
    glFunctions->glBufferData(GL_ARRAY_BUFFER, sizeof(box_vertexes_coords_normalized), box_vertexes_coords_normalized, GL_STATIC_DRAW);
    //Configuring the interpretation of the vertex buffer data
    glFunctions->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    //Use buffer object to an OpenGL buffer
    glFunctions->glBindBuffer(GL_ARRAY_BUFFER, VBOBoxWallTexcoords);
    //Copying vertex texcoords data from the array to VBO
    glFunctions->glBufferData(GL_ARRAY_BUFFER, sizeof(box_vertexes_wall_texture_coords2d), box_vertexes_wall_texture_coords2d, GL_STATIC_DRAW);
    //Configuring the interpretation of the vertex texcoords buffer data
    glFunctions->glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

    //Unselect VBO(so that other calls(glBufferData for example) don't change it)
    glFunctions->glBindBuffer(GL_ARRAY_BUFFER, 0);

    //Select second VAO
    glFunctions->glBindVertexArray(VAOBox2);

    //Use buffer object to an OpenGL buffer
    glFunctions->glBindBuffer(GL_ARRAY_BUFFER, VBOBoxVertexes);
    //Copying vertex data from the array to VBO
    glFunctions->glBufferData(GL_ARRAY_BUFFER, sizeof(box_vertexes_coords_normalized), box_vertexes_coords_normalized, GL_STATIC_DRAW);
    //Configuring the interpretation of the vertex buffer data
    glFunctions->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    //Use buffer object to an OpenGL buffer
    glFunctions->glBindBuffer(GL_ARRAY_BUFFER, VBOBoxWallTexcoords);
    //Copying vertex texcoords data from the array to VBO
    glFunctions->glBufferData(GL_ARRAY_BUFFER, sizeof(box_vertexes_wall_texture_coords2d), box_vertexes_wall_texture_coords2d, GL_STATIC_DRAW);
    //Configuring the interpretation of the vertex texcoords buffer data
    glFunctions->glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

    //Unselect VBO(so that other calls(glBufferData for example) don't change it)
    glFunctions->glBindBuffer(GL_ARRAY_BUFFER, 0);

    //Unselect VAO(so that other calls don't change it)
    glFunctions->glBindVertexArray(0);

    g_VAO_box = VAOBox;
    g_VAO_box2 = VAOBox2;
    g_VBO_box_vertexes = VBOBoxVertexes;
    g_VBO_box_vertexes2 = VBOBoxVertexes2;
    g_VBO_box_wall_texcoords = VBOBoxWallTexcoords;
    g_VBO_box_wall_texcoords2 = VBOBoxWallTexcoords2;
    g_texture_box_wall = textureBoxWall;
    g_texture_box_wall2 = textureBoxWall2;
}

void Sc7Box3DCam::drawScene()
{
    glEnable(GL_DEPTH_TEST);

    glFunctions->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //Select shader program
    gShaderProgram->enable();
    //Select texture unit
    glFunctions->glActiveTexture(GL_TEXTURE0);
    //Select texture
    glFunctions->glBindTexture(GL_TEXTURE_2D, g_texture_box_wall);
    gShaderProgram->setUniform1i("boxWallTexture", 0);

    //Select VAO
    glFunctions->glBindVertexArray(g_VAO_box);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //Enable the vertex attribute(the rest attributes remain off for optimization)
    glFunctions->glEnableVertexAttribArray(0);
    glFunctions->glEnableVertexAttribArray(1);

    //use matrix
    //create model matrix
    model_matrix = glm::mat4(1.0f);
    //create view matrix
    view_matrix = glm::mat4(1.0f);
    //create projection matrix
    projection_matrix = glm::mat4(1.0f);

    cam->update();
    view_matrix = cam->getViewMatrix();

    //setting up projection
    projection_matrix = glm::perspective(45.0f, (float)window_width / (float)window_height, 0.1f, 100.0f);

    model_matrix = glm::translate(model_matrix, glm::vec3(-1, 0, 0));
    x_rot += x_rotation_speed_in_degrees;
    y_rot += y_rotation_speed_in_degrees;
    model_matrix = glm::rotate(model_matrix, glm::radians(x_rot), glm::vec3(1, 0, 0));
    model_matrix = glm::rotate(model_matrix, glm::radians(y_rot), glm::vec3(0, 1, 0));

    replication_matrix = projection_matrix * view_matrix * model_matrix;

    gShaderProgram->setUniformMatrix4fv("replication_matrix", 1, GL_FALSE, glm::value_ptr(replication_matrix));

    gShaderProgram->printfPrepare();

    //Draw box using triangles
    glFunctions->glDrawArrays(GL_TRIANGLES, 0, 36);

    //Debug output from
    //qInfo() << QString::fromStdString(gShaderProgram->printfGetData());
    gShaderProgram->printfTerminate();

    //Select VAO
    glFunctions->glBindVertexArray(g_VAO_box2);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //Enable the vertex attribute(the rest attributes remain off for optimization)
    glFunctions->glEnableVertexAttribArray(0);
    glFunctions->glEnableVertexAttribArray(1);

    //use matrix
    //create model matrix
    model_matrix = glm::mat4(1.0f);

    //setting up projection

    model_matrix = glm::translate(model_matrix, glm::vec3(1, 0, 0));
    x_rot += x_rotation_speed_in_degrees;
    y_rot += y_rotation_speed_in_degrees;
    model_matrix = glm::rotate(model_matrix, glm::radians(-x_rot), glm::vec3(1, 0, 0));
    model_matrix = glm::rotate(model_matrix, glm::radians(-y_rot), glm::vec3(0, 1, 0));

    replication_matrix = projection_matrix * view_matrix * model_matrix;

    gShaderProgram->setUniformMatrix4fv("replication_matrix", 1, GL_FALSE, glm::value_ptr(replication_matrix));

    gShaderProgram->printfPrepare();

    //Draw box using triangles
    glFunctions->glDrawArrays(GL_TRIANGLES, 0, 36);

    //Debug output from
    //qInfo() << QString::fromStdString(gShaderProgram->printfGetData());
    gShaderProgram->printfTerminate();

    glFunctions->glDisableVertexAttribArray(0);
    glFunctions->glDisableVertexAttribArray(1);
    //Unselect VAO
    glFunctions->glBindVertexArray(0);
    //Unselect shader program
    gShaderProgram->disable();

    glDisable(GL_DEPTH_TEST);
}

void Sc7Box3DCam::finishScene()
{
    glFunctions->glDeleteTextures(1, &g_texture_box_wall);
    glFunctions->glDeleteBuffers(1, &g_VBO_box_vertexes);
    glFunctions->glDeleteBuffers(1, &g_VBO_box_wall_texcoords);
    glFunctions->glDeleteVertexArrays(1, &g_VAO_box);

    glFunctions->glDeleteTextures(1, &g_texture_box_wall2);
    glFunctions->glDeleteBuffers(1, &g_VBO_box_vertexes2);
    glFunctions->glDeleteBuffers(1, &g_VBO_box_wall_texcoords2);
    glFunctions->glDeleteVertexArrays(1, &g_VAO_box2);

    glFunctions->glDisable(GL_BLEND);

    x_rot = 0;
    y_rot = 0;

    delete gShaderProgram;
    delete cam;
}

void Sc7Box3DCam::resizeSceneWindow(int w, int h)
{
    window_width = w;
    window_height = h;
}

void Sc7Box3DCam::mousePressEventHandler(QMouseEvent *event)
{
    if(event->button() != Qt::LeftButton)
        return;

    mouse_last_xpos = event->pos().x();
    mouse_last_ypos = event->pos().y();
    mouse_left_button_pressed = true;
}

void Sc7Box3DCam::mouseReleaseEventHandler(QMouseEvent *event)
{
    if(event->button() != Qt::LeftButton)
        return;
    mouse_left_button_pressed = false;
}

void Sc7Box3DCam::mouseMoveEventHandler(QMouseEvent *event)
{
    //"Note that the returned value(QMouseEvent::button()) is always Qt::NoButton for mouse move events."

    if(mouse_left_button_pressed) {
        float xpos = event->pos().x();
        float ypos = event->pos().y();

        float xoffset = xpos - mouse_last_xpos;
        float yoffset = mouse_last_ypos - ypos;

        mouse_last_xpos = xpos;
        mouse_last_ypos = ypos;

        cam->processMouseOffsets(xoffset, yoffset);
    }
}

void Sc7Box3DCam::keyPressEventHandler(QKeyEvent* event)
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

void Sc7Box3DCam::keyReleaseEventHandler(QKeyEvent* event)
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

void Sc7Box3DCam::createUiOptionsWidgets()
{
    xRotationSpeedSlider = new QSlider(Qt::Orientation::Horizontal);
    xRotationSpeedSlider->setMinimum(0);
    xRotationSpeedSlider->setMaximum(200);
    QObject::connect(xRotationSpeedSlider, &QSlider::valueChanged, this, &Sc7Box3DCam::setXRotSpeedValueFromSlider);
    globalMainWindowFormUI->sceneOptionsGridLayout->addWidget(xRotationSpeedSlider);

    yRotationSpeedSlider = new QSlider(Qt::Orientation::Horizontal);
    yRotationSpeedSlider->setMinimum(0);
    yRotationSpeedSlider->setMaximum(200);
    QObject::connect(yRotationSpeedSlider, &QSlider::valueChanged, this, &Sc7Box3DCam::setYRotSpeedValueFromSlider);
    globalMainWindowFormUI->sceneOptionsGridLayout->addWidget(yRotationSpeedSlider);

    rotationsResetButton = new QPushButton("Reset rotations");
    QObject::connect(rotationsResetButton, &QPushButton::clicked, this, &Sc7Box3DCam::resetRotationsButtonClicked);
    globalMainWindowFormUI->sceneOptionsGridLayout->addWidget(rotationsResetButton);
}

void Sc7Box3DCam::deleteUiOptionsWidgets()
{
    globalMainWindowFormUI->sceneOptionsGridLayout->removeWidget(xRotationSpeedSlider);
    delete xRotationSpeedSlider;
    x_rotation_speed_in_degrees = 0;

    globalMainWindowFormUI->sceneOptionsGridLayout->removeWidget(yRotationSpeedSlider);
    delete yRotationSpeedSlider;
    x_rotation_speed_in_degrees = 0;

    globalMainWindowFormUI->sceneOptionsGridLayout->removeWidget(rotationsResetButton);
    delete rotationsResetButton;
}

void Sc7Box3DCam::setXRotSpeedValueFromSlider(int new_value)
{
    x_rotation_speed_in_degrees = (1.0f / 100) * new_value;
}

void Sc7Box3DCam::setYRotSpeedValueFromSlider(int new_value)
{
    y_rotation_speed_in_degrees = (1.0f / 100) * new_value;
}

void Sc7Box3DCam::resetRotationsButtonClicked()
{
    x_rot = 0;
    y_rot = 0;
}

