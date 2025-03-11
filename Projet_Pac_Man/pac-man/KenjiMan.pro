TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
include(MinGL2_IUT_AIX-master/mingl.pri)
SOURCES += \
        code/GameLogic.cpp \
        code/globals.cpp \
        main.cpp \
        code/params.cpp \
        code/rendu.cpp
DISTFILES += \
   fichiers_config/config.yaml

HEADERS += \
     enTetes/GameLogic.h \
     enTetes/Type.h \
     enTetes/globals.h \
     enTetes/params.h \
     enTetes/rendu.h
