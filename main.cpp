#include <string>
#include <raylib.h>
#include <raymath.h>

// Global Declare
#define MAX_OBS 10
#define SCREEN_H 800.0f
#define SCREEN_W 1000.0f
#define OBSTACLE_SPACING 350

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
void GameStartMenue();


int main() {
    InitWindow(SCREEN_W, SCREEN_H, "Floppy Bird");
    GameStartMenue();
    InitGame();
    SetTargetFPS(90);

    // Cannot Place these in IitGame()
    Player.score = 0;
    Player.life =3;

    while(!WindowShouldClose()) { UpdateDraw(); }
    UnloadGame();
    CloseWindow();    
    return 0;
}


void InitGame() {
    // Init Game Variables
    pause = false;

    // Init Player Variables
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
        Obstackle[i].Obstackle.x = 600 + (i * OBSTACLE_SPACING); // Space them out
        Obstackle[i].Obstackle.y = SCREEN_H - 200;   // Bottom obstacles
        Obstackle[i].speed = 5;
        Obstackle[i].color = GREEN;
    }
    // Init Obstackle Variables for Top
    for(int i=MAX_OBS/2; i<MAX_OBS; i++) {
        Obstackle[i].height = 200;
        Obstackle[i].width = 50;
        Obstackle[i].Obstackle.height = Obstackle[i].height;
        Obstackle[i].Obstackle.width = Obstackle[i].width;
        Obstackle[i].Obstackle.x = 600 + ((i - MAX_OBS/2) * OBSTACLE_SPACING); // Space them out
        Obstackle[i].Obstackle.y = 0;               // Top obstacles
        Obstackle[i].speed = 5;
        Obstackle[i].color = GREEN;
    }
    
}

void Update() {
        MovePlayer();
        MoveObstackles();
        CollisionTest();
}

void Draw() {
    BeginDrawing();
    // Beautiful sky gradient background
    ClearBackground((Color){135, 206, 235, 255}); // Sky blue
    
    // Add some ground
    DrawRectangle(0, SCREEN_H - 100, SCREEN_W, 100, (Color){34, 139, 34, 255}); // Forest green ground
    DrawRectangle(0, SCREEN_H - 20, SCREEN_W, 20, (Color){139, 69, 19, 255}); // Saddle brown dirt
    
    // Enhanced player with shadow
    DrawRectangleRec((Rectangle){Player.Player.x + 2, Player.Player.y + 2, Player.Player.width, Player.Player.height}, Fade(BLACK, 0.3f)); // Shadow
    DrawRectangleRec(Player.Player, (Color){255, 215, 0, 255}); // Gold player
    DrawRectangleLines(Player.Player.x, Player.Player.y, Player.Player.width, Player.Player.height, (Color){255, 140, 0, 255}); // Dark orange border
    
    // Enhanced obstacles with gradients
    for(int i = 0; i < MAX_OBS; i++) {
        // Shadow
        DrawRectangleRec((Rectangle){Obstackle[i].Obstackle.x + 3, Obstackle[i].Obstackle.y + 3, Obstackle[i].Obstackle.width, Obstackle[i].Obstackle.height}, Fade(BLACK, 0.2f));
        // Main obstacle
        DrawRectangleRec(Obstackle[i].Obstackle, (Color){34, 139, 34, 255}); // Forest green
        // Highlight
        DrawRectangle(Obstackle[i].Obstackle.x, Obstackle[i].Obstackle.y, 8, Obstackle[i].Obstackle.height, (Color){50, 205, 50, 255}); // Lime green highlight
        // Border
        DrawRectangleLines(Obstackle[i].Obstackle.x, Obstackle[i].Obstackle.y, Obstackle[i].Obstackle.width, Obstackle[i].Obstackle.height, (Color){0, 100, 0, 255});
    }
    
    // Enhanced score display
    std::string scoreText = "Score: " + std::to_string(Player.score);
    DrawText(scoreText.c_str(), 22, 22, 50, BLACK); // Shadow
    DrawText(scoreText.c_str(), 20, 20, 50, (Color){255, 215, 0, 255}); // Gold text
    
    // Lives display
    for(int i = 0; i < Player.life; i++) {
        DrawCircle(SCREEN_W - 50 - (i * 40), 40, 15, (Color){220, 20, 60, 255}); // Red hearts
        DrawText("♥", SCREEN_W - 60 - (i * 40), 25, 30, WHITE);
    }

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
        Obstackle[i].Obstackle.x -= Obstackle[i].speed;
        if(Obstackle[i].Obstackle.x <= -Obstackle[i].width) {
            // Reset based on obstacle index to maintain original spacing pattern
            if (i < MAX_OBS/2) {
                // Bottom obstacles - find last bottom obstacle and add spacing
                float lastBottomX = SCREEN_W;
                for(int j = 0; j < MAX_OBS/2; j++) {
                    if(j != i && Obstackle[j].Obstackle.x > lastBottomX) {
                        lastBottomX = Obstackle[j].Obstackle.x;
                    }
                }
                Obstackle[i].Obstackle.x = lastBottomX + OBSTACLE_SPACING;
            } else {
                // Top obstacles - match corresponding bottom obstacle
                int bottomIndex = i - MAX_OBS/2;
                Obstackle[i].Obstackle.x = Obstackle[bottomIndex].Obstackle.x;
            }
            
            if(i < MAX_OBS/2) Player.score += 10; // Only count score once per pair
            RandomiseObsDim(i);
        }
    }
}

void CollisionTest() {
    for(int i=0; i<MAX_OBS; i++) {
        if(CheckCollisionRecs(Player.Player, Obstackle[i].Obstackle)) {
            Player.life--;
            
            if(Player.life <= 0) {
                GameOverMenue();
                return;
            }
            else {
                // Reset player position to safe area
                Player.Player.x = 30;
                Player.Player.y = SCREEN_H/2;
                
                // Optional: Move obstacles away temporarily
                for(int j = 0; j < MAX_OBS; j++) {
                    if(Obstackle[j].Obstackle.x < 200) {
                        Obstackle[j].Obstackle.x = 200;
                    }
                }
                break;
            }
        }
    }
}

void RandomiseObsDim(int ith_obs) {
    // Only randomize when bottom obstacles reset (indices 0-4)
    if (ith_obs < MAX_OBS/2) {
        float gapSize = 150;
        float bottomHeight = GetRandomValue(100, 350);
        float topHeight = SCREEN_H - bottomHeight - gapSize;
        
        // Bottom obstacle
        Obstackle[ith_obs].Obstackle.height = bottomHeight;
        Obstackle[ith_obs].Obstackle.y = SCREEN_H - bottomHeight;
        
        // Corresponding top obstacle
        int topIndex = ith_obs + 5;
        Obstackle[topIndex].Obstackle.height = topHeight;
        Obstackle[topIndex].Obstackle.y = 0;
    }
}

void GameOverMenue() {
    while(true) {
        Rectangle restartBtn = { SCREEN_W/2 - 80, SCREEN_H/2 + 20, 160, 50 };
        Rectangle quitBtn = { SCREEN_W/2 - 70, SCREEN_H/2 + 80, 140, 50 };
        
        Vector2 mousePos = GetMousePosition();
        bool restartHover = CheckCollisionPointRec(mousePos, restartBtn);
        bool quitHover = CheckCollisionPointRec(mousePos, quitBtn);
        
        if((restartHover && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) || IsKeyPressed(KEY_R)) {
            // Properly reset everything
            Player.life = 3;
            Player.score = 0; // Reset score too
            InitGame();
            return; // Exit the game over menu
        }
        if((quitHover && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) || IsKeyPressed(KEY_ESCAPE)) {
            exit(0);
        }
        
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        // Draw frozen game state
        DrawRectangleRec(Player.Player, Player.color);
        for(int i = 0; i < MAX_OBS; i++) DrawRectangleRec(Obstackle[i].Obstackle, Obstackle[i].color);

        // Dark overlay
        DrawRectangle(0, 0, SCREEN_W, SCREEN_H, Fade(BLACK, 0.8f));
        
        // Main panel
        Rectangle panel = { SCREEN_W/2 - 200, SCREEN_H/2 - 120, 400, 280 };
        DrawRectangleRounded((Rectangle){panel.x + 5, panel.y + 5, panel.width, panel.height}, 0.3f, 10, Fade(BLACK, 0.5f));
        DrawRectangleRounded(panel, 0.3f, 10, (Color){255, 248, 220, 255});
        DrawRectangleRoundedLines(panel, 0.3f, 10, (Color){184, 134, 11, 255});
        
        // Game Over text
        DrawText("GAME OVER", panel.x + 80, panel.y + 30, 42, (Color){220, 20, 60, 255});
        DrawText("GAME OVER", panel.x + 82, panel.y + 32, 42, (Color){139, 0, 0, 255});
        
        // Score display
        DrawText(TextFormat("Final Score: %d", Player.score), panel.x + 120, panel.y + 90, 24, (Color){25, 25, 112, 255});
        
        // Restart button
        Color restartColor = restartHover ? (Color){34, 139, 34, 255} : (Color){50, 205, 50, 255};
        DrawRectangleRounded(restartBtn, 0.4f, 8, restartColor);
        DrawText("RESTART (R)", restartBtn.x + 15, restartBtn.y + 15, 20, WHITE);
        
        // Quit button
        Color quitColor = quitHover ? (Color){178, 34, 34, 255} : (Color){220, 20, 60, 255};
        DrawRectangleRounded(quitBtn, 0.4f, 8, quitColor);
        DrawText("QUIT (ESC)", quitBtn.x + 10, quitBtn.y + 15, 20, WHITE);

        EndDrawing();
    }
}

void GameStartMenue() {
    Rectangle BackGr = { SCREEN_W/2 - 175, SCREEN_H/2 - 120, 350, 240 };
    Rectangle Start = { SCREEN_W/2 - 70, SCREEN_H/2 - 50, 140, 50 };
    Rectangle Quit = { SCREEN_W/2 - 60, SCREEN_H/2 + 20, 120, 50 };


    while(true) {
        Vector2 mousePos = GetMousePosition();
        bool startHover = CheckCollisionPointRec(mousePos, Start);
        bool quitHover = CheckCollisionPointRec(mousePos, Quit);
        
        BeginDrawing();
        // Beautiful gradient-like background
        ClearBackground((Color){135, 206, 235, 255}); // Sky blue
        
        // Animated clouds effect
        DrawCircle(100, 100, 60, Fade(WHITE, 0.7f));
        DrawCircle(200, 150, 40, Fade(WHITE, 0.5f));
        DrawCircle(800, 80, 50, Fade(WHITE, 0.6f));
        DrawCircle(900, 200, 35, Fade(WHITE, 0.4f));
        
        // Main panel with shadow effect
        DrawRectangleRounded((Rectangle){BackGr.x + 5, BackGr.y + 5, BackGr.width, BackGr.height}, 0.3f, 10, Fade(BLACK, 0.3f)); // Shadow
        DrawRectangleRounded(BackGr, 0.3f, 10, (Color){255, 255, 255, 250}); // White with slight transparency
        DrawRectangleRoundedLines(BackGr, 0.3f, 10, (Color){70, 130, 180, 255}); // Steel blue border
        
        // Game title
        DrawText("FLOPPY BIRD", BackGr.x + 60, BackGr.y + 30, 36, (Color){255, 69, 0, 255}); // Orange red
        DrawText("FLOPPY BIRD", BackGr.x + 62, BackGr.y + 32, 36, (Color){255, 140, 0, 255}); // Dark orange (shadow effect)
        
        // Start button with hover effect
        Color startColor = startHover ? (Color){34, 139, 34, 255} : (Color){50, 205, 50, 255}; // Forest green / Lime green
        DrawRectangleRounded(Start, 0.4f, 8, startColor);
        DrawRectangleRoundedLines(Start, 0.4f, 8, (Color){0, 100, 0, 255}); // Dark green border
        DrawText("START", Start.x + 35, Start.y + 12, 28, WHITE);
        
        // Quit button with hover effect  
        Color quitColor = quitHover ? (Color){178, 34, 34, 255} : (Color){220, 20, 60, 255}; // Fire brick / Crimson
        DrawRectangleRounded(Quit, 0.4f, 8, quitColor);
        DrawRectangleRoundedLines(Quit, 0.4f, 8, (Color){139, 0, 0, 255}); // Dark red border
        DrawText("QUIT", Quit.x + 30, Quit.y + 12, 28, WHITE);
        
        if(startHover && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) break;
        if(quitHover && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) exit(0);
        EndDrawing();
    }
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