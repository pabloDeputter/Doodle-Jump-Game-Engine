#include "Game.h"
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

        for (int i = 0; i < 100; i++) {
                auto a = Utils::Stopwatch::Delta();
                std::cout << a << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        //        std::cout << "Hello world\n";
        return 0;
}