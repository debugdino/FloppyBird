#include "game.h"
#include <thread>
#include <chrono>
Sound PlayerMoveS;
Sound Hit;

Image Background;
Texture BackTexture;

void InitGame() {
    // Init Audio
    LoadGame();

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

void Update() {
        MovePlayer();
        MoveObstackles();
        CollisionTest();
}

void CollisionTest() {
    for(int i=0; i<MAX_OBS; i++) {
        if(CheckCollisionRecs(Player.Player, Obstackle[i].Obstackle)) {
            PlaySound(Hit);
            Player.life--;
            
            if(Player.life <= 0) {
                GameOverMenue();
                return;
            }
            else {
                // Reset player position to safe area
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                InitGame();
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

void UnloadGame() {
    // Audio
    UnloadSound(PlayerMoveS);
    UnloadSound(Hit);

    // Image
    UnloadImage(Background);
    UnloadTexture(BackTexture);
}

void LoadGame() {
    // Audio
    PlayerMoveS = LoadSound("assets/sound/player_movement.mp3");
    Hit = LoadSound("assets/sound/hit-by-a-wood.mp3");

    //Image
    Background = LoadImage("assets/pictures/copied_test.jpeg"); BackTexture = LoadTextureFromImage(Background);
}