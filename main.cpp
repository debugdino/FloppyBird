    ////////\\\\\\\\\\
    //      A       \\
    //    Simple    \\
    //  FloppyBird  \\
    ////////\\\\\\\\\\

#include <raylib.h>

// Global Declare
#define MAX_OBS 10
#define SCREEN_H 800.0f
#define SCREEN_W 1000.0f

// Game Variables
bool pause;
bool touch;

// Class
class Player { public:
    int score;
    int life;
    float height;
    float width;
    Rectangle Player;
    float speed;
    Color color;

    
}Player;

class Obstackle { public:
    float height;
    float width;
    Rectangle Obstackle;
    float speed;
    Color color;

}Obstackle[MAX_OBS];

// PreDefine
void InitGame();
void UpdateDraw();
void Update();
void Draw();
void UnloadGame();
void GameOverMenue();


int main() {
    InitWindow(SCREEN_W, SCREEN_H, "Floppy Bird");
    InitGame();
    SetTargetFPS(90);

    while(!WindowShouldClose()) { UpdateDraw(); }
    UnloadGame();
    CloseWindow();    
    return 0;
}


void InitGame() {
    // Init Game Variables
    pause = false;
    touch = false;

    // Init Player Variables
    Player.score = 0;
    Player.life =3;
    Player.height = 50;
    Player.width = 50;
    Player.Player.height = Player.height;
    Player.Player.width = Player.width;
    Player.Player.x = 30;
    Player.Player.y = SCREEN_H/2;
    Player.speed = 10;
    Player.color = GRAY;

    // Init Obstackle Variables
    for(int i=0; i<MAX_OBS; i++) {
        Obstackle->height = 200;
        Obstackle->width = 50;
        Obstackle->Obstackle.height = Obstackle->height;
        Obstackle->Obstackle.width = Obstackle->width;
        Obstackle->Obstackle.x = 600;
        Obstackle->Obstackle.y = 600;
        Obstackle->speed = 10;
        Obstackle->color = MAROON;
    }

}

void Update() {
    if (Player.life > 0) {
        if (IsKeyPressed(KEY_P)) pause = !pause;
        if (!pause) {
            if (touch) Player.life --;
            
        }
    }
}

void Draw() {
    BeginDrawing();
    ClearBackground(RAYWHITE);

        DrawRectangleRec(Player.Player, Player.color);
        DrawRectangleRec(Obstackle->Obstackle, Obstackle->color);

    EndDrawing();
}

void GameOverMenue() {

}

void UpdateDraw() {
    Update();
    Draw();
    if (Player.life == 0) GameOverMenue();
}

void UnloadGame() {

}