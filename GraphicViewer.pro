QT += core gui opengl
LIBS += -lglu32 -lopengl32

#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    source/BasicObjects/ArrowPainter/ArrowPainter.cpp \
    source/Camera/Camera.cpp \
    source/SceneManager/Scenes/Sc0Test/Sc0Test.cpp \
    source/SceneManager/Scenes/Sc9LightingMaps/Sc9LightingMaps.cpp \
    source/SceneManager/Scenes/Sc10ManyCubesLM/Sc10ManyCubesLM.cpp \
    source/SceneManager/Scenes/Sc1VBOOrange/Sc1VBOOrange.cpp \
    source/SceneManager/Scenes/Sc2VAOBlue/Sc2VAOBlue.cpp \
    source/SceneManager/Scenes/Sc3EBOGreen/Sc3EBOGreen.cpp \
    source/SceneManager/Scenes/Sc4UniformInput/Sc4UniformInput.cpp \
    source/SceneManager/Scenes/Sc5Texture/Sc5Texture.cpp \
    source/SceneManager/SceneManager.cpp \
    source/SceneManager/Scenes/Sc6Box3DPerspective/Sc6Box3DPerspective.cpp \
    source/SceneManager/Scenes/Sc7Box3DCam/Sc7Box3DCam.cpp \
    source/SceneManager/Scenes/Sc8Lighting/Sc8Lighting.cpp \
    source/ShaderProgram.cpp \
    source/globalvars.cpp \
    source/main.cpp \
    source/MainOpenGLWidget.cpp \
    source/MainWindow.cpp

HEADERS += \
    source/BasicObjects/ArrowPainter/ArrowPainter.h \
    source/Camera/Camera.h \
    source/SceneManager/Scenes/Sc0Test/Sc0Test.h \
    source/SceneManager/Scenes/Sc9LightingMaps/Sc9LightingMaps.h \
    source/SceneManager/Scenes/Sc10ManyCubesLM/Sc10ManyCubesLM.h \
    source/SceneManager/Scenes/Sc1VBOOrange/Sc1VBOOrange.h \
    source/SceneManager/Scenes/Sc2VAOBlue/Sc2VAOBlue.h \
    source/SceneManager/Scenes/Sc3EBOGreen/Sc3EBOGreen.h \
    source/SceneManager/Scenes/Sc4UniformInput/Sc4UniformInput.h \
    source/SceneManager/Scenes/Sc5Texture/Sc5Texture.h \
    source/SceneManager/SceneManager.h \
    source/SceneManager/Scenes/Sc6Box3DPerspective/Sc6Box3DPerspective.h \
    source/SceneManager/Scenes/Sc7Box3DCam/Sc7Box3DCam.h \
    source/SceneManager/Scenes/Sc8Lighting/Sc8Lighting.h \
    source/ShaderProgram.h \
    source/globalvars.h \
    source/MainOpenGLWidget.h \
    source/MainWindow.h \
    source/ShaderPrintf.h

FORMS += \
    MainWindowForm.ui \
    source/SceneManager/Scenes/Sc0Test/ui/Sc0TestOptionsForm.ui \
    source/SceneManager/Scenes/Sc9LightingMaps/ui/Sc9LightingMapsOptionsForm.ui \
    source/SceneManager/Scenes/Sc10ManyCubesLM/ui/Sc10ManyCubesLMOptionsForm.ui \
    source/SceneManager/Scenes/Sc1VBOOrange/ui/Sc1VBOOrangeOptionsForm.ui \
    source/SceneManager/Scenes/Sc2VAOBlue/ui/Sc2VAOBlueOptionsForm.ui \
    source/SceneManager/Scenes/Sc3EBOGreen/ui/Sc3EBOGreenOptionsForm.ui \
    source/SceneManager/Scenes/Sc4UniformInput/ui/Sc4UniformInputOptionsForm.ui \
    source/SceneManager/Scenes/Sc5Texture/ui/Sc5TextureOptionsForm.ui \
    source/SceneManager/Scenes/Sc6Box3DPerspective/ui/Sc6Box3DPerspectiveOptionsForm.ui \
    source/SceneManager/Scenes/Sc7Box3DCam/ui/Sc7Box3DCamOptionsForm.ui \
    source/SceneManager/Scenes/Sc8Lighting/ui/Sc8LightingOptionsForm.ui \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#ASSIMP
#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/source/assimp-5.0.1/build/code/release/ -lassimp-vc142-mtd
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/source/assimp-5.0.1/build/code/debug/ -lassimp-vc142-mtd

INCLUDEPATH += $$PWD/source/assimp-5.0.1/myinclude
DEPENDPATH += $$PWD/source/assimp-5.0.1/myinclude

RESOURCES += \
    resourcesBasicObjects.qrc \
    resourcesScenes.qrc
