######################################################################
# Automatically generated by qmake (2.01a) Tue May 11 00:18:10 2010
######################################################################

TEMPLATE = app
TARGET = groove
#target = groove
#target.path = /usr/bin
#//target.path = /usr/local/
#INSTALLS += target
#CONFIG += build_all
DEPENDPATH += .
INCLUDEPATH += .
INCLUDEPATH += /usr/include/qjson /usr/include
#INCLUDEPATH += ../qjson/src/
#INCLUDEPATH += ./src/
#LIBS += -L/usr/lib -lqjson ##Desktop Target
LIBS += -L/usr/local/lib -lqjson ##Armel Target
#LIBS += -L~/NokiaQtSDK/Maemo/4.6.2/sysroots/fremantle-arm-sysroot-1014-slim/usr/lib -lqjson ##Armel Target SDK
#LIBS += -L../qjson/lib -lqjson ##X86 maemo
QT += network
QT += phonon

# Input
SOURCES += main.cpp \
    groove.cpp \
    gscom.cpp \
    splayer.cpp \
    streamio.cpp \
    playlist.cpp \
    downloadmanager.cpp \
    grooveprogressbar.cpp \
    topbar.cpp \
    bottombar.cpp \
    vkb.cpp \
    searchresults.cpp \
    pwin.cpp
##  mpgplayer.cpp

HEADERS += \
    groove.h \
    gscom.h \
    splayer.h \
    streamio.h \
    playlist.h \
    downloadmanager.h \
    grooveprogressbar.h \
    topbar.h \
    bottombar.h \
    vkb.h \
    searchresults.h \
    pwin.h
##    mpgplayer.h

maemo5 {
SOURCES += qmaemo5rotator.cpp
HEADERS += qmaemo5rotator.h
QT += dbus
}
OTHER_FILES += \
    icon.svg \
    groove.png \
    general_fullsize.png \
    general_search.png \
    wmTaskSwitcherIconPressed.png \
    wmTaskSwitcherIconHighlight.png \
    wmTaskSwitcherIcon.png \
    general_forward.png \
    general_foldertree.png \
    general_close.png \
    general_back.png \
    general_add.png \
    camera_video_stop.png \
    camera_video_pause.png \
    camera_camera_setting.png \
    wmTaskModified.png
unix {
  PREFIX = /usr
  BINDIR = $$PREFIX/bin
  DATADIR =$$PREFIX/share

  DEFINES += DATADIR=\"$$DATADIR\" PKGDATADIR=\"$$PKGDATADIR\"

  #MAKE INSTALL

  INSTALLS += target desktop icon64

  target.path =$$BINDIR

  desktop.path = $$DATADIR/applications/hildon
  desktop.files += groove.desktop

  icon64.path = $$DATADIR/icons/hicolor/64x64/apps
  icon64.files += groove.png
}

RESOURCES += \
    res.qrc

FORMS += \
    topbar.ui \
    bottombar.ui \
    vkb.ui \
    searchresults.ui \
    pwin.ui
