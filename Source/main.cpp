#include "game.h"
#include <iostream>

int main(void)
{    
    // TODO: Complete exception handling
    try
    {
        Game().Run();
        return EXIT_SUCCESS;
    }
    catch (...)
    {
        std::cout << "Exited due to unknown error";
    }


    return EXIT_FAILURE;
}