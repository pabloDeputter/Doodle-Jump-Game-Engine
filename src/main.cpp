#include "Game.h"

//#include "model/Player.h"
//#include "model/Spring.h"

using namespace std;

int main(int argc, char* argv[])
{

        Game game = Game(800, 1440);
        game.run();
        return 0;
}