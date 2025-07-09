#include <raylib.h>

// Global Declare
#define MAX_OBS 5
#define SCREEN_H 800.0f
#define SCREEN_W 1000.0f

// Class
class Player { public:
    static int score;
    bool gameover;

    
};

class Obstackle { public:
    bool touch;

};

// PreDefine
void InitGame();
void UpdateDraw();
void UnloadGame();


int main() {
    InitWindow(SCREEN_W, SCREEN_H, "Floppy Bird");
    InitGame();
    SetTargetFPS(90);

    while(!WindowShouldClose()) { UpdateDraw(); }
    UnloadGame();
    CloseWindow();    
    return 0;
}