SET(SRC
        src/model/Entity.cpp
        src/model/Player.cpp
        src/model/Platform.cpp
        src/model/Bonus.cpp
        src/util/Collision.cpp
        src/util/Random.cpp
        src/util/Stopwatch.cpp
        src/util/Transform.cpp
        src/util/Camera.cpp
        src/controller/IController.cpp
        src/controller/PlatformController.cpp
        src/controller/PlayerController.cpp
        src/AbstractFactory.cpp
        src/Observer.cpp
        src/Subject.cpp
        src/World.cpp
        )

ADD_LIBRARY(engine SHARED ${SRC})

TARGET_INCLUDE_DIRECTORIES(engine PUBLIC include)