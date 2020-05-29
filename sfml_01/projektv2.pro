TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        0_main.cpp \
        1_AnimationOperator.cpp \
        1_GameOperator.cpp \
        1_MapOperator.cpp \
        1_PlayerOperator.cpp \
        2_EnemiesOperator.cpp \
        2_Zombie.cpp \
        3_DamageObjects.cpp \
        3_PlayerBullet.cpp \
        GUIOperator.cpp \
        LevelOperator.cpp

INCLUDEPATH += "C:/SFML-2.5.1/include"

LIBS += -L"C:/SFML-2.5.1/lib"
CONFIG(debug, debug|release){
    LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-system-d -lsfml-window-d
} else {
    LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window
}

HEADERS += \
    1_AnimationOperator.h \
    1_GameOperator.h \
    1_MapOperator.h \
    1_PlayerOperator.h \
    2_EnemiesOperator.h \
    2_Zombie.h \
    3_DamageObjects.h \
    3_PlayerBullet.h \
    GUIOperator.h \
    LevelOperator.h
