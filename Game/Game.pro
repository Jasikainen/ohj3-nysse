TEMPLATE = app
TARGET = NYSSE

QT += core gui widgets network multimedia

CONFIG += c++14

SOURCES += \
    city.cc \
    creategame.cc \
    digitalclock.cc \
    gameengine.cpp \
    gamemainwindow.cpp \
    highscoredialog.cpp \
    main.cc \
    nysseactoritem.cpp \
    player.cpp \
    playeractoritem.cpp \
    projectileitem.cpp \
    radaritem.cpp \
    startdialog.cpp \
    statistics.cpp

win32:CONFIG(release, debug|release): LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/release/ -lCourseLib
else:win32:CONFIG(debug, debug|release): LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/debug/ -lCourseLib
else:unix: LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/ -lCourseLib

INCLUDEPATH += \
    $$PWD/../Course/CourseLib

DEPENDPATH += \
    $$PWD/../Course/CourseLib

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/release/libCourseLib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/debug/libCourseLib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/release/CourseLib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/debug/CourseLib.lib
else:unix: PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/libCourseLib.a

HEADERS += \
    city.hh \
    config.hh \
    digitalclock.hh \
    gameengine.hh \
    gamemainwindow.hh \
    highscoredialog.hh \
    nysseactoritem.hh \
    player.hh \
    playeractoritem.hh \
    projectileitem.hh \
    radaritem.hh \
    startdialog.hh \
    statistics.hh

FORMS += \
    gamemainwindow.ui \
    highscoredialog.ui \
    startdialog.ui

RESOURCES += \
    data.qrc
