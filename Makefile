#############################################################################
# Makefile for building: groove
# Generated by qmake (2.01a) (Qt 4.6.2) on: Fri Jun 25 06:09:19 2010
# Project:  Groove.pro
# Template: app
# Command: /usr/bin/qmake -unix -o Makefile Groove.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_GL_NO_SCISSOR_TEST -DQT_DEFAULT_TEXTURE_GLYPH_CACHE_WIDTH=1024 -DQT_NO_DEBUG -DQT_PHONON_LIB -DQT_GUI_LIB -DQT_NETWORK_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -O3 -fno-omit-frame-pointer -fno-optimize-sibling-calls -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -O3 -fno-omit-frame-pointer -fno-optimize-sibling-calls -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/linux-g++-maemo5 -I. -I/targets/FREMANTLE_ARMEL/usr/include/QtCore -I/targets/FREMANTLE_ARMEL/usr/include/QtNetwork -I/targets/FREMANTLE_ARMEL/usr/include/QtGui -I/targets/FREMANTLE_ARMEL/usr/include/phonon -I/targets/FREMANTLE_ARMEL/usr/include -I. -I../qjson/src -I/usr/include/phonon_compat -I.
LINK          = g++
LFLAGS        = -Wl,-rpath-link,/usr/lib -Wl,-O1 -Wl,--hash-style=gnu -Wl,-rpath,/usr/lib
LIBS          = $(SUBLIBS)  -L/usr/lib -L~/NokiaQtSDK/Maemo/4.6.2/sysroots/fremantle-arm-sysroot-1014-slim/usr/lib -lqjson -lphonon -L/usr/lib -L/usr/X11R6/lib -lQtGui -lQtNetwork -lQtDBus -lQtXml -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = main.cpp \
		groove.cpp \
		gscom.cpp \
		splayer.cpp \
		streamio.cpp \
		playlist.cpp \
		downloadmanager.cpp \
		grooveprogressbar.cpp \
		qmaemo5rotator.cpp moc_groove.cpp \
		moc_gscom.cpp \
		moc_splayer.cpp \
		moc_streamio.cpp \
		moc_playlist.cpp \
		moc_downloadmanager.cpp \
		moc_grooveprogressbar.cpp \
		moc_qmaemo5rotator.cpp \
		qrc_reasource.cpp
OBJECTS       = main.o \
		groove.o \
		gscom.o \
		splayer.o \
		streamio.o \
		playlist.o \
		downloadmanager.o \
		grooveprogressbar.o \
		qmaemo5rotator.o \
		moc_groove.o \
		moc_gscom.o \
		moc_splayer.o \
		moc_streamio.o \
		moc_playlist.o \
		moc_downloadmanager.o \
		moc_grooveprogressbar.o \
		moc_qmaemo5rotator.o \
		qrc_reasource.o
DIST          = /targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/common/unix.conf \
		/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/common/linux.conf \
		/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/qconfig.pri \
		/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/qt_config.prf \
		/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/default_pre.prf \
		/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/release.prf \
		/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/default_post.prf \
		/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/warn_on.prf \
		/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/qt.prf \
		/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/moc.prf \
		/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/resources.prf \
		/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/uic.prf \
		/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/yacc.prf \
		/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/lex.prf \
		/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		Groove.pro
QMAKE_TARGET  = groove
DESTDIR       = 
TARGET        = groove

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET):  $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: Groove.pro  /targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/linux-g++-maemo5/qmake.conf /targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/common/unix.conf \
		/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/common/linux.conf \
		/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/qconfig.pri \
		/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/qt_config.prf \
		/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/default_pre.prf \
		/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/release.prf \
		/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/default_post.prf \
		/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/warn_on.prf \
		/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/qt.prf \
		/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/moc.prf \
		/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/resources.prf \
		/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/uic.prf \
		/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/yacc.prf \
		/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/lex.prf \
		/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		/usr/lib/libphonon.prl \
		/usr/lib/libQtDBus.prl \
		/usr/lib/libQtXml.prl \
		/usr/lib/libQtCore.prl \
		/usr/lib/libQtGui.prl \
		/usr/lib/libQtNetwork.prl
	$(QMAKE) -unix -o Makefile Groove.pro
/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/common/unix.conf:
/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/common/linux.conf:
/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/qconfig.pri:
/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/qt_functions.prf:
/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/qt_config.prf:
/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/default_pre.prf:
/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/release.prf:
/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/default_post.prf:
/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/warn_on.prf:
/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/qt.prf:
/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/unix/thread.prf:
/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/moc.prf:
/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/resources.prf:
/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/uic.prf:
/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/yacc.prf:
/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/lex.prf:
/targets/FREMANTLE_ARMEL/usr/share/qt4/mkspecs/features/include_source_dir.prf:
/usr/lib/libphonon.prl:
/usr/lib/libQtDBus.prl:
/usr/lib/libQtXml.prl:
/usr/lib/libQtCore.prl:
/usr/lib/libQtGui.prl:
/usr/lib/libQtNetwork.prl:
qmake:  FORCE
	@$(QMAKE) -unix -o Makefile Groove.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/groove1.0.0 || $(MKDIR) .tmp/groove1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/groove1.0.0/ && $(COPY_FILE) --parents groove.h gscom.h splayer.h streamio.h playlist.h downloadmanager.h grooveprogressbar.h qmaemo5rotator.h .tmp/groove1.0.0/ && $(COPY_FILE) --parents reasource.qrc .tmp/groove1.0.0/ && $(COPY_FILE) --parents main.cpp groove.cpp gscom.cpp splayer.cpp streamio.cpp playlist.cpp downloadmanager.cpp grooveprogressbar.cpp qmaemo5rotator.cpp .tmp/groove1.0.0/ && (cd `dirname .tmp/groove1.0.0` && $(TAR) groove1.0.0.tar groove1.0.0 && $(COMPRESS) groove1.0.0.tar) && $(MOVE) `dirname .tmp/groove1.0.0`/groove1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/groove1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_groove.cpp moc_gscom.cpp moc_splayer.cpp moc_streamio.cpp moc_playlist.cpp moc_downloadmanager.cpp moc_grooveprogressbar.cpp moc_qmaemo5rotator.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_groove.cpp moc_gscom.cpp moc_splayer.cpp moc_streamio.cpp moc_playlist.cpp moc_downloadmanager.cpp moc_grooveprogressbar.cpp moc_qmaemo5rotator.cpp
moc_groove.cpp: gscom.h \
		splayer.h \
		streamio.h \
		grooveprogressbar.h \
		qmaemo5rotator.h \
		playlist.h \
		groove.h
	/usr/bin/moc $(DEFINES) $(INCPATH) groove.h -o moc_groove.cpp

moc_gscom.cpp: gscom.h
	/usr/bin/moc $(DEFINES) $(INCPATH) gscom.h -o moc_gscom.cpp

moc_splayer.cpp: streamio.h \
		splayer.h \
		grooveprogressbar.h \
		qmaemo5rotator.h \
		playlist.h \
		gscom.h \
		splayer.h
	/usr/bin/moc $(DEFINES) $(INCPATH) splayer.h -o moc_splayer.cpp

moc_streamio.cpp: splayer.h \
		streamio.h \
		grooveprogressbar.h \
		qmaemo5rotator.h \
		playlist.h \
		gscom.h \
		streamio.h
	/usr/bin/moc $(DEFINES) $(INCPATH) streamio.h -o moc_streamio.cpp

moc_playlist.cpp: gscom.h \
		playlist.h
	/usr/bin/moc $(DEFINES) $(INCPATH) playlist.h -o moc_playlist.cpp

moc_downloadmanager.cpp: downloadmanager.h
	/usr/bin/moc $(DEFINES) $(INCPATH) downloadmanager.h -o moc_downloadmanager.cpp

moc_grooveprogressbar.cpp: qmaemo5rotator.h \
		grooveprogressbar.h
	/usr/bin/moc $(DEFINES) $(INCPATH) grooveprogressbar.h -o moc_grooveprogressbar.cpp

moc_qmaemo5rotator.cpp: qmaemo5rotator.h
	/usr/bin/moc $(DEFINES) $(INCPATH) qmaemo5rotator.h -o moc_qmaemo5rotator.cpp

compiler_rcc_make_all: qrc_reasource.cpp
compiler_rcc_clean:
	-$(DEL_FILE) qrc_reasource.cpp
qrc_reasource.cpp: reasource.qrc \
		icon.svg
	/usr/bin/rcc -name reasource reasource.qrc -o qrc_reasource.cpp

compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_rcc_clean 

####### Compile

main.o: main.cpp groove.h \
		gscom.h \
		splayer.h \
		streamio.h \
		grooveprogressbar.h \
		qmaemo5rotator.h \
		playlist.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

groove.o: groove.cpp groove.h \
		gscom.h \
		splayer.h \
		streamio.h \
		grooveprogressbar.h \
		qmaemo5rotator.h \
		playlist.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o groove.o groove.cpp

gscom.o: gscom.cpp gscom.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o gscom.o gscom.cpp

splayer.o: splayer.cpp splayer.h \
		streamio.h \
		grooveprogressbar.h \
		qmaemo5rotator.h \
		playlist.h \
		gscom.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o splayer.o splayer.cpp

streamio.o: streamio.cpp streamio.h \
		splayer.h \
		grooveprogressbar.h \
		qmaemo5rotator.h \
		playlist.h \
		gscom.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o streamio.o streamio.cpp

playlist.o: playlist.cpp playlist.h \
		gscom.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o playlist.o playlist.cpp

downloadmanager.o: downloadmanager.cpp downloadmanager.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o downloadmanager.o downloadmanager.cpp

grooveprogressbar.o: grooveprogressbar.cpp grooveprogressbar.h \
		qmaemo5rotator.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o grooveprogressbar.o grooveprogressbar.cpp

qmaemo5rotator.o: qmaemo5rotator.cpp qmaemo5rotator.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o qmaemo5rotator.o qmaemo5rotator.cpp

moc_groove.o: moc_groove.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_groove.o moc_groove.cpp

moc_gscom.o: moc_gscom.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_gscom.o moc_gscom.cpp

moc_splayer.o: moc_splayer.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_splayer.o moc_splayer.cpp

moc_streamio.o: moc_streamio.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_streamio.o moc_streamio.cpp

moc_playlist.o: moc_playlist.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_playlist.o moc_playlist.cpp

moc_downloadmanager.o: moc_downloadmanager.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_downloadmanager.o moc_downloadmanager.cpp

moc_grooveprogressbar.o: moc_grooveprogressbar.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_grooveprogressbar.o moc_grooveprogressbar.cpp

moc_qmaemo5rotator.o: moc_qmaemo5rotator.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_qmaemo5rotator.o moc_qmaemo5rotator.cpp

qrc_reasource.o: qrc_reasource.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o qrc_reasource.o qrc_reasource.cpp

####### Install

install_target: first FORCE
	@$(CHK_DIR_EXISTS) $(INSTALL_ROOT)/usr/bin/ || $(MKDIR) $(INSTALL_ROOT)/usr/bin/ 
	-$(INSTALL_PROGRAM) "$(QMAKE_TARGET)" "$(INSTALL_ROOT)/usr/bin/$(QMAKE_TARGET)"
	-$(STRIP) "$(INSTALL_ROOT)/usr/bin/$(QMAKE_TARGET)"

uninstall_target:  FORCE
	-$(DEL_FILE) "$(INSTALL_ROOT)/usr/bin/$(QMAKE_TARGET)"
	-$(DEL_DIR) $(INSTALL_ROOT)/usr/bin/ 


install:  install_target  FORCE

uninstall: uninstall_target   FORCE

FORCE:

