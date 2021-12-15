SET(SRC
        src/model/Player.cpp
        src/model/Bonus.cpp
        src/model/Background.cpp
        src/util/Utilities.cpp
        src/util/Random.cpp
        src/util/Stopwatch.cpp
        src/util/Camera.cpp
        src/controller/PlatformController.cpp
        src/controller/PlayerController.cpp
        src/World.cpp
        src/model/HorizontalPlatform.cpp
        src/model/VerticalPlatform.cpp
        src/model/Jetpack.cpp
        src/model/Spring.cpp
        src/controller/BonusController.cpp
        src/model/Score.cpp
        include/Settings.h
        src/HighScore.cpp
        )

ADD_LIBRARY(engine SHARED ${SRC})

TARGET_INCLUDE_DIRECTORIES(engine PUBLIC include)