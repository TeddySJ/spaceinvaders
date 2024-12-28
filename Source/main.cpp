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
    catch (HighscoreSaveException& e)
    {
        std::cout << e.what();
    }
    catch (RaylibWindowCreationError& e)
    {
        std::cout << e.what();
    }
    catch (RaylibTextureCreationError& e)
    {
        std::cout << "Exited due to texture loading error. Texture path: " << e.what();
    }
    catch (...)
    {
        std::cout << "Exited due to unspecified error";
    }


    return EXIT_FAILURE;
}