TEMPLATE = subdirs

DISTFILES += \
    Doxyfile \

SUBDIRS += \
        CourseLib \
        Game \
        UnitTests

CourseLib.subdir = Course/CourseLib
Game.depends = CourseLib
