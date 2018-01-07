#-------------------------------------------------
#
# Project created by QtCreator 2018-01-04T01:53:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HIKVersion_V2_0
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp \
        mainwindow.cpp \
    ipc.cpp \
    logindialog.cpp \
    featuretracker.cpp
HEADERS += \
    includeCn/HCNetSDK.h \
    includeCn/LinuxPlayM4.h \
    includeCn/PlayM4.h \
    ipc.h \
    logindialog.h \
    mainwindow.h \
    featuretracker.h

FORMS += \
    logindialog.ui \
    mainwindow.ui

DISTFILES += \
    lib/HCNetSDKCom/libanalyzedata.so \
    lib/HCNetSDKCom/libHCAlarm.so \
    lib/HCNetSDKCom/libHCCoreDevCfg.so \
    lib/HCNetSDKCom/libHCDisplay.so \
    lib/HCNetSDKCom/libHCGeneralCfgMgr.so \
    lib/HCNetSDKCom/libHCIndustry.so \
    lib/HCNetSDKCom/libHCPlayBack.so \
    lib/HCNetSDKCom/libHCPreview.so \
    lib/HCNetSDKCom/libHCVoiceTalk.so \
    lib/HCNetSDKCom/libiconv2.so \
    lib/HCNetSDKCom/libStreamTransClient.so \
    lib/HCNetSDKCom/libSystemTransform.so \
    lib/libAudioRender.so \
    lib/libHCCore.so \
    lib/libhcnetsdk.so \
    lib/libhpr.so \
    lib/libPlayCtrl.so \
    lib/libSuperRender.so

unix:!macx: LIBS += -L$$PWD/lib/ -lhcnetsdk

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

unix:!macx: LIBS += -L$$PWD/lib/HCNetSDKCom/ -lHCDisplay

INCLUDEPATH += $$PWD/includeCn
DEPENDPATH += $$PWD/lib/HCNetSDKCom

unix:!macx: LIBS += -L$$PWD/lib/ -lHCCore

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += opencv

unix:!macx: LIBS += -L$$PWD/lib/ -lPlayCtrl

INCLUDEPATH += $$PWD/includeCn
DEPENDPATH += $$PWD/includeCn

unix:!macx: LIBS += -L$$PWD/lib/ -lAudioRender

INCLUDEPATH += $$PWD/includeCn
DEPENDPATH += $$PWD/includeCn

unix:!macx: LIBS += -L$$PWD/lib/ -lSuperRender

INCLUDEPATH += $$PWD/includeCn
DEPENDPATH += $$PWD/includeCn
