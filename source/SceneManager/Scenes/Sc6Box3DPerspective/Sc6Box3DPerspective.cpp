#include "Sc6Box3DPerspective.h"
#include "../../globalvars.h"
#include <QGLWidget> //for convertation to gl format

Sc6Box3DPerspective::Sc6Box3DPerspective(QOpenGLContext* openGLContext)
{
    glFunctions = openGLContext->versionFunctions<QOpenGLFunctions_4_5_Core>();
}

Sc6Box3DPerspective::~Sc6Box3DPerspective()
{
}

void Sc6Box3DPerspective::initScene(int start_window_width, int start_window_height)
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

    //Create shader program object
    gShaderProgram = new ShaderProgram(glFunctions, ":Scenes/Sc6Box3DPerspective/shaders/vertshader.vert", ":/Scenes/Sc6Box3DPerspective/shaders/fragshader.frag");

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

    //Unselect texture
    glFunctions->glBindTexture(GL_TEXTURE_2D, 0);

    //Vertex buffer object ID(name)
    unsigned int VBOBoxVertexes = 0;
    //Texture coordinats buffer object ID(name)
    unsigned int VBOBoxWallTexcoords = 0;
    //Vertex arrays object ID(name)
    unsigned int VAOBox = 0;

    //Allocate 1 buffer for VBO (Vertex Buffer Object)
    glFunctions->glGenBuffers(1, &VBOBoxVertexes);
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
    g_VBO_box_vertexes = VBOBoxVertexes;
    g_VBO_box_wall_texcoords = VBOBoxWallTexcoords;
    g_texture_box_wall = textureBoxWall;
}

void Sc6Box3DPerspective::drawScene()
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

    //setting up model
    //model_matrix = glm::translate(model_matrix, glm::vec3(0, 0, -2.5));
    //y_rot += y_rotation_speed_in_degrees / 2;
    //x_rot += x_rotation_speed_in_degrees / 2;
    //model_matrix = glm::rotate(model_matrix, glm::radians(y_rot), glm::vec3(0, 1, 0));
    //model_matrix = glm::rotate(model_matrix, glm::radians(x_rot), glm::vec3(1, 0, 0));

    glm::mat4 rm_x = glm::rotate(glm::mat4(1.0f),
        glm::radians(y_rotation_speed_in_degrees), glm::vec3(0, 1, 0));
    glm::mat4 rm_y = glm::rotate(glm::mat4(1.0f),
        glm::radians(x_rotation_speed_in_degrees), glm::vec3(1, 0, 0));
    rotation_matrix = rm_x * rm_y * rotation_matrix;

    model_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -2.5)) * rotation_matrix;
    model_matrix = glm::scale(model_matrix, glm::vec3(0.75, 0.75, 0.75));

    //setting up projection
    projection_matrix = glm::perspective(45.0f, (float)window_width / (float)window_height, 0.1f, 100.0f);

    replication_matrix = projection_matrix * view_matrix * model_matrix;

    gShaderProgram->setUniformMatrix4fv("replication_matrix", 1, GL_FALSE, glm::value_ptr(replication_matrix));

    gShaderProgram->printfPrepare();

    //Draw box using triangles
    glFunctions->glDrawArrays(GL_TRIANGLES, 0, 36);

    //Debug output from
    //qInfo() << QString::fromStdString(gShaderProgram->printfGetData());
    gShaderProgram->printfTerminate();

    glFunctions->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    //Disable the vertex attribute(for optimization)
    glFunctions->glDisableVertexAttribArray(0);
    glFunctions->glDisableVertexAttribArray(1);

    //Unselect texture
    glBindTexture(GL_TEXTURE_2D, 0);
    //Unselect VAO
    glFunctions->glBindVertexArray(0);
    //Unselect shader program
    gShaderProgram->disable();

    glDisable(GL_DEPTH_TEST);
}

void Sc6Box3DPerspective::finishScene()
{
    glFunctions->glDeleteTextures(1, &g_texture_box_wall);
    glFunctions->glDeleteBuffers(1, &g_VBO_box_vertexes);
    glFunctions->glDeleteBuffers(1, &g_VBO_box_wall_texcoords);
    glFunctions->glDeleteVertexArrays(1, &g_VAO_box);

    glFunctions->glDisable(GL_BLEND);

    rotation_matrix = glm::mat4(1.0f);
    x_rot = 0;
    y_rot = 0;
    x_rotation_speed_in_degrees = 0;
    y_rotation_speed_in_degrees = 0;

    delete gShaderProgram;
}

void Sc6Box3DPerspective::resizeSceneWindow(int w, int h)
{
    window_width = w;
    window_height = h;
}
