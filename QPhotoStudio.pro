#-------------------------------------------------
#
# Project created by QtCreator 2020-03-29T17:00:43
#
#-------------------------------------------------

QT       += core gui
QT       += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QPhotoStudio
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.


# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    GUI/Details.cpp \
    GUI/Listino.cpp \
    GUI/MyCSV.cpp \
    GUI/Search.cpp \
        model/Product.cpp \
        model/Reflex.cpp \
        model/Accessory.cpp \
        model/Lens.cpp \
        model/Length.cpp \
        model/Aperture.cpp \
        model/Zoom.cpp \
        container/DeepPtr.cpp \
        container/Container.cpp \
        GUI/Add.cpp \
        GUI/Index.cpp \
        GUI/Model.cpp \
        GUI/MyXml.cpp \
        main.cpp \
        mainwindow.cpp \
    model/exception/Exception.cpp

HEADERS += \
    GUI/Details.h \
    GUI/Listino.h \
    GUI/MyCSV.h \
    GUI/Search.h \
        model/Product.h \
        model/Reflex.h \
        model/Accessory.h \
        model/Lens.h \
        model/Length.h \
        model/Aperture.h \
        model/Zoom.h \
        container/DeepPtr.h \
        container/Container.h \
        GUI/Add.h \
        GUI/Index.h \
        GUI/Model.h \
        GUI/MyXml.h \
        mainwindow.h \
    model/exception/Exception.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    GUI/font.ttf \
    GUI/style.qss \
    icon/icon.png \
    images/accessory.png \
    images/camera.png \
    images/image.png \
    images/lens.png \
    images/title.png

RESOURCES += \
    source.qrc
