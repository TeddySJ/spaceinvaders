#include "game.h"
#include <iostream>
#include "CustomExceptions.h"

int main(void)
{    
    try
    {
        Game().Run();
        return EXIT_SUCCESS;
    }
    catch (const HighscoreSaveException& e)
    {
        std::cout << e.what();
    }
    catch (const RaylibWindowCreationError& e)
    {
        std::cout << e.what();
    }
    catch (const RaylibTextureCreationError& e)
    {
        std::cout << "Exited due to texture loading error. Texture path: " << e.what();
    }
    catch (...)
    {
        std::cout << "Exited due to unspecified error";
    }


    return EXIT_FAILURE;
}