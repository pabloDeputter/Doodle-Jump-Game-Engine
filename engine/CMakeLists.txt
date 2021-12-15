SET(SRC
        src/model/Entity.cpp
        src/model/Player.cpp
        src/model/Bonus.cpp
        src/model/Background.cpp
        src/util/Utilities.cpp
        src/util/Random.cpp
        src/util/Stopwatch.cpp
        src/util/Camera.cpp
        src/controller/IController.cpp
        src/controller/PlatformController.cpp
        src/controller/PlayerController.cpp
        src/AbstractFactory.cpp
        src/Observer.cpp
        src/Subject.cpp
        src/World.cpp
        src/model/StaticPlatform.cpp
        src/model/HorizontalPlatform.cpp
        src/model/VerticalPlatform.cpp
        src/model/TemporaryPlatform.cpp
        src/model/Jetpack.cpp
        src/model/Spring.cpp
        src/controller/BonusController.cpp
        src/IVisitor.cpp
        src/Score.cpp
        src/util/Exception.cpp
        include/Settings.h
        src/HighScore.cpp
        ../game/include/State.h)

ADD_LIBRARY(engine SHARED ${SRC})

TARGET_INCLUDE_DIRECTORIES(engine PUBLIC include)