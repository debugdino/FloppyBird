#include "game.h"

// Global variable definitions
bool pause;
PlayerClass Player;
ObstackleClass Obstackle[MAX_OBS];

int main() {
    InitWindow(SCREEN_W, SCREEN_H, "Flappy Bird");
    InitAudioDevice();

    InitGame();
    GameStartMenue();
    SetTargetFPS(90);

    // Cannot Place these in InitGame()
    Player.score = 0;
    Player.life =3;

    while(!WindowShouldClose()) { UpdateDraw(); }

    UnloadGame();
    CloseWindow();    
    return 0;
}
