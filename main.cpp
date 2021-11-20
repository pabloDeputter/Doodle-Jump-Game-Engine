#include "src/Game.h"
#include <exception>
#include <iostream>
#include <memory>
#include <thread>

/* TODO
 * Compile different directories, such Utils should never be compiled again
 * Observer class should be base class of all entities?
 */

/* TODO
 * Check collision between player and entity --> check entity --> platform --> check if mVelocity.y > 0;
 *
 */

int main(int argc, char* argv[])
{

        try {
                Game* a = new Game();
                a->run();
        } catch (...) {
                std::cout << "runtime error\n;";
        }

        //        std::cout << "Hello world\n";
        return 0;
}