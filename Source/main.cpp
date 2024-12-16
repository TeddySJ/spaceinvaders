#include "raylib.h"
#include "game.h"

int main(void)
{    
    // TODO: Exception handling
    
    // TODO: Move all these game-related things into the game-class, and have a Run function for the basic loop

    const int screenWidth = 1920;
    const int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "SPACE INVADERS");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    Game game = { State::STARTSCREEN }; // TODO: Aggregate initialization should not be used for a large, complex class
    Resources resources;
    game.resources = resources;
    game.Launch();

    
    InitAudioDevice();

    auto sound = LoadSound("./hitHurt.ogg");

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        game.Update();
      
        // TODO: Move surrounding render-code into Render()
        BeginDrawing();

        ClearBackground(BLACK); 

        game.Render();

        EndDrawing();
    }

    CloseAudioDevice();
    
    CloseWindow();        // Close window and OpenGL context

    std::string filename = "level.txt";  

    return 0;
}