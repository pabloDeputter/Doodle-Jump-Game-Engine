#include "Game.h"
#include "src/Utils/Random.h"
#include "src/Utils/Stopwatch.h"
#include <iostream>
#include <memory>
#include <thread>

/* TODO
 * Compile different directories, such Utils should never be compiled again
 * IObserver class should be base class of all entities?
 */

int main(int argc, char* argv[])
{

        Game::Game* a = new Game::Game();
        a->run();
        //        std::cout << Utils::Random::GetRandom(());

        //        std::cout << "Hello world\n";
        return 0;
}