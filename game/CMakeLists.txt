SET(SRC
        src/view/IView.cpp
        src/view/PlatformView.cpp
        src/view/PlayerView.cpp
        src/view/BackgroundView.cpp
        src/ConcreteFactory.cpp
        src/Game.cpp
        src/view/BonusView.cpp
        src/view/ScoreView.cpp
        src/state/MenuState.cpp
        src/state/PlayState.cpp
        src/state/EnterScoreState.cpp
        )

ADD_LIBRARY(game SHARED ${SRC})

TARGET_LINK_LIBRARIES(game ${SFML_LIBRARIES})
TARGET_LINK_LIBRARIES(game engine)

TARGET_INCLUDE_DIRECTORIES(game PUBLIC include)