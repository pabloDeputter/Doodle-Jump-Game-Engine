SET(SRC
        src/view/IView.cpp
        src/view/PlatformView.cpp
        src/view/PlayerView.cpp
        src/view/BackgroundView.cpp
        src/ConcreteFactory.cpp
        src/Game.cpp
        src/util/Resourcemanager.cpp
        src/view/BonusView.cpp include/view/BonusView.h)

ADD_LIBRARY(game SHARED ${SRC})

TARGET_LINK_LIBRARIES(game ${SFML_LIBRARIES})
TARGET_LINK_LIBRARIES(game engine)

TARGET_INCLUDE_DIRECTORIES(game PUBLIC include)