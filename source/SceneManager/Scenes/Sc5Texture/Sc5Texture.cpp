#include "Sc5Texture.h"
#include <QGLWidget> //for convertation to gl format
#include "../../globalvars.h"

Sc5Texture::Sc5Texture(QOpenGLContext* openGLContext)
{
    glFunctions = openGLContext->versionFunctions<QOpenGLFunctions_4_5_Core>();
}

Sc5Texture::~Sc5Texture()
{
}

void Sc5Texture::initScene(int start_window_width, int start_window_height)
{
    (void)start_window_width;
    (void)start_window_height;

    //for RGBA texture
    glFunctions->glEnable(GL_BLEND);
    glFunctions->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    float vertexes_coords_normalized[] =
                         { 0.5, 0.5, 0,
                           -0.5, 0.5, 0,
                           -0.5, -0.5, 0,
                           0.5, -0.5, 0 };

    unsigned int vertexes_coords_indexes[] =
                         { 0, 1, 3, //first triangle
                           1, 2, 3  //second trianle
                         };

    float vertexes_wall_texture_coords2d[] =
                         { 1.0, 1.0,
                           0.0, 1.0,
                           0.0, 0.0,
                           1.0, 0.0 };

    float vertexes_cat_texture_coords2d[] =
                         { 1.0, 1.0,
                           0.0, 1.0,
                           0.0, 0.0,
                           1.0, 0.0 };
    /*
   texcoords always
     in this range
       /------\1,1
       |      |
       |      |
       |      |
    0,0\------/
    */

    //Create shader program object
    gShaderProgram = new ShaderProgram(glFunctions, ":Scenes/Sc5Texture/shaders/vertshader.vert", ":/Scenes/Sc5Texture/shaders/fragshader.frag");

    //Compile shader program
    if(!gShaderProgram->compile()) {
        qDebug("[ERROR] initializeGL: makeShaderProgram failed!");
        return;
    }

    //Load texture image
    QImage imgWallTexture(":Scenes/Sc5Texture/textures/wall512x512.png");
    if(imgWallTexture.isNull()) {
        qInfo("[ERROR] initScene: image texture load failed!");
        return;
    }
    imgWallTexture = QGLWidget::convertToGLFormat(imgWallTexture);
    //You must use the "Premultiplied alpha" format, otherwise artifacts appear
    imgWallTexture = imgWallTexture.convertToFormat(QImage::Format_ARGB32_Premultiplied);


    //Load texture image
    QImage imgCatTexture(":Scenes/Sc5Texture/textures/cat512x512.png");
    if(imgCatTexture.isNull()) {
        qInfo("[ERROR] initScene: image texture load failed!");
        return;
    }
    imgCatTexture = QGLWidget::convertToGLFormat(imgCatTexture);
    //You must use the "Premultiplied alpha" format, otherwise artifacts appear
    imgCatTexture = imgCatTexture.convertToFormat(QImage::Format_ARGB32_Premultiplied);

    //Texture ID(name)
    unsigned int wallTexture = 0;
    unsigned int catTexture = 0;
    //Allocate 1 buffer for textures
    glFunctions->glGenTextures(1, &wallTexture);
    glFunctions->glGenTextures(1, &catTexture);
    //Select wall texture
    glFunctions->glBindTexture(GL_TEXTURE_2D, wallTexture);
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

    //Select cat texture
    glFunctions->glBindTexture(GL_TEXTURE_2D, catTexture);



    //Select cat texture
    glFunctions->glBindTexture(GL_TEXTURE_2D, catTexture);
    //Load data to texture
    glFunctions->glTexImage2D(GL_TEXTURE_2D, //selected texture type
                 0, //mipmap level(we generate him using OpenGL)
                 GL_RGBA, //texture data format
                 imgCatTexture.width(),
                 imgCatTexture.height(),
                 0, //always zero
                 GL_RGBA, //image format
                 GL_UNSIGNED_BYTE, //image data format
                 imgCatTexture.bits() //image data
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
    unsigned int VBOvertexes = 0;
    //Texture coordinats indexes buffer object ID(name)
    unsigned int EBOindexes = 0;
    //Texture coordinats buffer object ID(name)
    unsigned int VBOWallTexcoords = 0;
    //Vertex arrays object ID(name)
    unsigned int VBOCatTexcoords = 0;
    //Vertex arrays object ID(name)
    unsigned int VAO = 0;

    //Allocate 1 buffer for VBO (Vertex Buffer Object)
    glFunctions->glGenBuffers(1, &VBOvertexes);
    //Allocate 1 buffer for EBO (Element Buffer Object)
    glFunctions->glGenBuffers(1, &EBOindexes);
    //Allocate 1 buffer for VBO (Vertex Buffer Object)
    glFunctions->glGenBuffers(1, &VBOWallTexcoords);
    //Allocate 1 buffer for VBO (Vertex Buffer Object)
    glFunctions->glGenBuffers(1, &VBOCatTexcoords);
    //Allocate 1 buffer for VAO (Vertex Arrays Object)
    glFunctions->glGenVertexArrays(1, &VAO);

    //Select VAO
    glFunctions->glBindVertexArray(VAO);

    //Use buffer object to an OpenGL buffer
    glFunctions->glBindBuffer(GL_ARRAY_BUFFER, VBOvertexes);
    //Copying vertex data from the array to VBO
    glFunctions->glBufferData(GL_ARRAY_BUFFER, sizeof(vertexes_coords_normalized), vertexes_coords_normalized, GL_STATIC_DRAW);
    //Configuring the interpretation of the vertex buffer data
    glFunctions->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    //Use buffer object to an OpenGL buffer
    glFunctions->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOindexes);
    //Copying vertex data from the array to EBO
    glFunctions->glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertexes_coords_indexes), vertexes_coords_indexes, GL_STATIC_DRAW);
    //Unselect EBO
    glFunctions->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    //Use buffer object to an OpenGL buffer
    glFunctions->glBindBuffer(GL_ARRAY_BUFFER, VBOWallTexcoords);
    //Copying vertex texcoords data from the array to VBO
    glFunctions->glBufferData(GL_ARRAY_BUFFER, sizeof(vertexes_wall_texture_coords2d), vertexes_wall_texture_coords2d, GL_STATIC_DRAW);
    //Configuring the interpretation of the vertex texcoords buffer data
    glFunctions->glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

    //Use buffer object to an OpenGL buffer
    glFunctions->glBindBuffer(GL_ARRAY_BUFFER, VBOCatTexcoords);
    //Copying vertex texcoords data from the array to VBO
    glFunctions->glBufferData(GL_ARRAY_BUFFER, sizeof(vertexes_cat_texture_coords2d), vertexes_cat_texture_coords2d, GL_STATIC_DRAW);
    //Configuring the interpretation of the vertex texcoords buffer data
    glFunctions->glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

    //Unselect VBO(so that other calls(glBufferData for example) don't change it)
    glFunctions->glBindBuffer(GL_ARRAY_BUFFER, 0);

    //Unselect VAO(so that other calls don't change it)
    glFunctions->glBindVertexArray(0);

    g_VAO = VAO;
    g_VBO_vertexes = VBOvertexes;
    g_EBO_indexes = EBOindexes;
    g_VBO_wall_texcoords = VBOWallTexcoords;
    g_VBO_cat_texcoords = VBOCatTexcoords;
    g_wall_texture = wallTexture;
    g_cat_texture = catTexture;
}

void Sc5Texture::drawScene()
{
    glFunctions->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //Select shader program
    gShaderProgram->enable();

    gShaderProgram->setUniform1f("mix_value", g_mix_value);

    //Select texture unit
    glFunctions->glActiveTexture(GL_TEXTURE0);
    //Select texture
    glFunctions->glBindTexture(GL_TEXTURE_2D, g_wall_texture);
    gShaderProgram->setUniform1i("wallTexture", 0);

    //Select texture unit
    glFunctions->glActiveTexture(GL_TEXTURE1);
    //Select texture
    glFunctions->glBindTexture(GL_TEXTURE_2D, g_cat_texture);
    gShaderProgram->setUniform1i("catTexture", 1);

    //Select default texture unit
    glFunctions->glActiveTexture(GL_TEXTURE0);
    //Select VAO
    glFunctions->glBindVertexArray(g_VAO);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //Enable the vertex attribute(the rest attributes remain off for optimization)
    glFunctions->glEnableVertexAttribArray(0);
    glFunctions->glEnableVertexAttribArray(1);
    glFunctions->glEnableVertexAttribArray(2);

    glFunctions->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_EBO_indexes);

    gShaderProgram->printfPrepare();

    //Draw square
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

    //Debug output from
    //qInfo() << QString::fromStdString(gShaderProgram->printfGetData());
    gShaderProgram->printfTerminate();

    glFunctions->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    //Disable the vertex attribute(for optimization)
    glFunctions->glDisableVertexAttribArray(0);
    glFunctions->glDisableVertexAttribArray(1);
    glFunctions->glDisableVertexAttribArray(2);

    //Unselect texture
    glBindTexture(GL_TEXTURE_2D, 0);
    //Unselect VAO
    glFunctions->glBindVertexArray(0);
    //Unselect shader program
    gShaderProgram->disable();
}
void Sc5Texture::finishScene()
{
    glFunctions->glDeleteTextures(1, &g_wall_texture);
    glFunctions->glDeleteTextures(1, &g_cat_texture);
    glFunctions->glDeleteBuffers(1, &g_VBO_vertexes);
    glFunctions->glDeleteBuffers(1, &g_EBO_indexes);
    glFunctions->glDeleteBuffers(1, &g_VBO_wall_texcoords);
    glFunctions->glDeleteBuffers(1, &g_VBO_cat_texcoords);
    glFunctions->glDeleteVertexArrays(1, &g_VAO);

    glFunctions->glDisable(GL_BLEND);

    delete gShaderProgram;
}

void Sc5Texture::createUiOptionsWidgets()
{
    gMixValueTextLabel = new QLabel();
    gMixValueTextLabel->setText("Mix Value: " + QString::number(g_mix_value));
    globalMainWindowFormUI->sceneOptionsGridLayout->addWidget(gMixValueTextLabel);

    gMixValueSlider = new QSlider(Qt::Orientation::Horizontal);
    gMixValueSlider->setMinimum(0);
    gMixValueSlider->setMaximum(100);
    QObject::connect(gMixValueSlider, &QSlider::valueChanged, this, &Sc5Texture::setNewMixValueFromSlider);
    globalMainWindowFormUI->sceneOptionsGridLayout->addWidget(gMixValueSlider);
}

void Sc5Texture::deleteUiOptionsWidgets()
{
    globalMainWindowFormUI->sceneOptionsGridLayout->removeWidget(gMixValueTextLabel);
    delete gMixValueTextLabel;
    globalMainWindowFormUI->sceneOptionsGridLayout->removeWidget(gMixValueSlider);
    delete gMixValueSlider;
    g_mix_value = 0;
}

void Sc5Texture::setNewMixValueFromSlider(int new_value)
{
    //Convert range 0...100 to 0.0...1.0
    g_mix_value = (1.0f / 100) * new_value;
    gMixValueTextLabel->setText("Mix Value: " + QString::number(g_mix_value));
}
