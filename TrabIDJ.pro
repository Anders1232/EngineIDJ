TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += src/main.cpp \
	src/Game.cpp \
	src/Sprite.cpp \
	src/StageState.cpp \
	src/Gameobject.cpp \
	src/Vec2.cpp \
	src/Tileset.cpp \
	src/TileMap.cpp \
	src/Resources.cpp \
	src/InputManager.cpp \
	src/Camera.cpp \
	src/Alien.cpp \
	src/Minion.cpp \
	src/Rect.cpp \
	src/Bullet.cpp \
	src/Penguins.cpp \
	src/Timer.cpp \
	src/Animation.cpp \
	src/State.cpp \
	src/TitleState.cpp \
	src/Music.cpp \
	src/Sound.cpp \
	src/Text.cpp \
	src/EndState.cpp \
	src/StateData.cpp

TARGET = JOGO

QMAKE_CXXFLAGS += -Wall -pedantic -std=c++11 -g
QMAKE_CFLAGS += -Wall -pedantic -std=c99 -g

QMAKE_CXXFLAGS_DEBUG += -g
QMAKE_CFLAGS_DEBUG += -g

QMAKE_CFLAGS_RELEASE += -O3
QMAKE_CXXFLAGS_RELEASE += -O3

include(deployment.pri)
qtcAddDeployment()

INCLUDEPATH += include/

HEADERS += \
	include/Game.h \
	include/Error.h \
	include/Sprite.h \
	include/StageState.h \
	include/Gameobject.h \
	include/Vec2.h \
	include/Tileset.h \
	include/TileMap.h \
	include/Resources.h \
	include/InputManager.h \
	include/Camera.h \
	include/Alien.h \
	include/Minion.h \
	include/Rect.h \
	include/Bullet.h \
	include/Penguins.h\
	include/Collision.h \
	include/Timer.h \
	include/Animation.h \
	include/State.h \
	include/TitleState.h \
	include/Music.h \
	include/Sound.h \
	include/Text.h \
	include/EndState.h \
	include/StateData.h

LIBS += -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

