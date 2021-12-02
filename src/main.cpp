#include "Game.h"
#include <exception>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
        //        try {
        //                // stuff to try
        //                try {
        //                        // other stuff to try
        //                } catch (std::exception &e) {
        //                        // solve problem
        //                } catch (...) {
        //                        // solve another problem
        //                }
        //        } catch (...) {
        //                // whatever
        //        }
        //        cout << "Just kidding, carry on!" << endl;

        Game game = Game();
        game.run();
        return 0;
}