////////\\\\\\\\\\
    //      A       \\
    //    Simple    \\
    //  FloppyBird  \\
    ////////\\\\\\\\\\

#include <raylib.h>
#include <raymath.h>

// Global Declare
#define MAX_OBS 10
#define SCREEN_H 800.0f
#define SCREEN_W 1000.0f

// Game Variables
bool pause;

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
void MovePlayer();
void MoveObstackles();
void CollisionTest();
void RandomiseObsDim(int ith_obs);


int main() {
    InitWindow(SCREEN_W, SCREEN_H, "Floppy Bird");
    InitGame();
    SetTargetFPS(90);

    while(!WindowShouldClose()) { UpdateDraw(); }
    UnloadGame();
    CloseWindow();    
    return 0;
}


void InitGame() {w
    // Init Game Variables
    pause = false;

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

    // Init Obstackle Variables for Bottom
    for(int i=0; i<MAX_OBS/2; i++) {
        Obstackle[i].height = 200;
        Obstackle[i].width = 50;
        Obstackle[i].Obstackle.height = Obstackle[i].height;
        Obstackle[i].Obstackle.width = Obstackle[i].width;
        Obstackle[i].Obstackle.x = 600 + (i * 200); // Space them out
        Obstackle[i].Obstackle.y = SCREEN_H - 200;   // Bottom obstacles
        Obstackle[i].speed = 5;
        Obstackle[i].color = MAROON;
    }
    // Init Obstackle Variables for Top
    for(int i=MAX_OBS/2; i<MAX_OBS; i++) {
        Obstackle[i].height = 200;
        Obstackle[i].width = 50;
        Obstackle[i].Obstackle.height = Obstackle[i].height;
        Obstackle[i].Obstackle.width = Obstackle[i].width;
        Obstackle[i].Obstackle.x = 600 + ((i - MAX_OBS/2) * 200); // Space them out
        Obstackle[i].Obstackle.y = 0;               // Top obstacles
        Obstackle[i].speed = 5;
        Obstackle[i].color = MAROON;
    }
    
}

void Update() {
        MovePlayer();
        MoveObstackles();
        CollisionTest();
}

void Draw() {
    BeginDrawing();
    ClearBackground(RAYWHITE);

        // Draw Players
        DrawRectangleRec(Player.Player, Player.color);
        // Draw all obstacles
        for(int i = 0; i < MAX_OBS; i++) DrawRectangleRec(Obstackle[i].Obstackle, Obstackle[i].color);

    EndDrawing();
}

void MovePlayer() {
    if(IsKeyDown(KEY_W)) Player.Player.y -= Player.speed;
    if(IsKeyDown(KEY_S)) Player.Player.y += Player.speed;
    else Player.Player.y += 0.5*Player.speed;
    Player.Player.y = Clamp(Player.Player.y, 0.0f, SCREEN_H - Player.height);
}

void MoveObstackles() {
    for(int i=0; i<MAX_OBS; i++) {
        Obstackle[i].Obstackle.x -= Obstackle->speed;
        if(Obstackle[i].Obstackle.x <=0) {
            Obstackle[i].Obstackle.x = SCREEN_W - 50;
            Player.score+=10;
            RandomiseObsDim(i);
        }
    }
}

void CollisionTest() {
    for(int i=0; i<MAX_OBS; i++) {
        if(CheckCollisionRecs(Player.Player, Obstackle[i].Obstackle)) {
            Player.life--;
            Obstackle[i].color = RED;
        }
    }
}

void RandomiseObsDim(int ith_obs) {
    float h1, h2;

    h1 = GetRandomValue(100, 300);
    h2 = GetRandomValue(100, 300);

    Obstackle[ith_obs].Obstackle.height = h1;
    Obstackle[ith_obs + 5].Obstackle.height = h2;
}

void GameOverMenue() {
    bool restart = false;
    bool escape = false;
    while(!restart and !escape) {
        restart = IsKeyPressed(KEY_R);
        escape = IsKeyPressed(KEY_ESCAPE);
        BeginDrawing();
        ClearBackground(RAYWHITE);
            DrawRectangleRec(Player.Player, Player.color);
            for(int i = 0; i < MAX_OBS; i++) DrawRectangleRec(Obstackle[i].Obstackle, Obstackle[i].color);

            DrawRectangle(0, 0, SCREEN_W, SCREEN_H, Fade(BLACK, 0.7f));
            Rectangle rect = { SCREEN_W/2 - 100, SCREEN_H/2 - 50, 200, 100 };
            DrawRectangleRounded(rect, 0.3f, 10, PURPLE);
            DrawText("Press 'R' to restart and 'esc' to close the game", SCREEN_W/2-100, SCREEN_H/2-50, 10, RED);


        EndDrawing();
    }
    if(restart) InitGame();
    // if(escape) CloseWindow();
}

void UnloadGame() {
    
}

void UpdateDraw() {
    if (IsKeyPressed(KEY_P)) pause = !pause;
    
    if(!pause) {
        Update();
        Draw();
        if (Player.life == 0) GameOverMenue();
    }
    else {
        // Just draw the current state
        BeginDrawing();
        ClearBackground(RAYWHITE);
            // Draw game elements (frozen)
            DrawRectangleRec(Player.Player, Player.color);
            for(int i = 0; i < MAX_OBS; i++) DrawRectangleRec(Obstackle[i].Obstackle, Obstackle[i].color);
            
            // Draw pause indicator
            DrawText("PAUSED - Press P to Resume", 10, 10, 20, BLACK);
        EndDrawing();
    }
}