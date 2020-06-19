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
    GUI/add.cpp \
    GUI/details.cpp \
    GUI/index.cpp \
    GUI/listino.cpp \
    GUI/model.cpp \
    GUI/myCSV.cpp \
    GUI/myXml.cpp \
    GUI/search.cpp \
    container/container.cpp \
    container/deepPtr.cpp \
        main.cpp \
        mainwindow.cpp \
    model/accessory.cpp \
    model/aperture.cpp \
    model/exception/exception.cpp \
    model/length.cpp \
    model/lens.cpp \
    model/product.cpp \
    model/reflex.cpp \
    model/zoom.cpp

HEADERS += \
    GUI/add.h \
    GUI/details.h \
    GUI/index.h \
    GUI/listino.h \
    GUI/model.h \
    GUI/myCSV.h \
    GUI/myXml.h \
    GUI/search.h \
    container/container.h \
    container/deepPtr.h \
        mainwindow.h \
    model/accessory.h \
    model/aperture.h \
    model/exception/exception.h \
    model/length.h \
    model/lens.h \
    model/product.h \
    model/reflex.h \
    model/zoom.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    GUI/style.qss \
    icon/icon.png \
    images/accessory.png \
    images/camera.png \
    images/image.png \
    images/lens.png \
    images/title.png

RESOURCES += \
    source.qrc
