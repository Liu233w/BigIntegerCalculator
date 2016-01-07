#-------------------------------------------------
#
# Project created by QtCreator 2015-12-02T22:46:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BigIntegerCalculator
TEMPLATE = app
CONFIG += c++11

SOURCES += main.cpp \
    mainwindow.cpp \
    about_dialog.cpp \
    biginteger.cpp \
    state.cpp


HEADERS  += \
    mainwindow.h \
    about_dialog.h \
    biginteger.h \
    state.h


FORMS    += mainwindow.ui \
    about_dialog.ui

RESOURCES += \
    material.qrc

RC_FILE += logo.rc

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
