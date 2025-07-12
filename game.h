#pragma once
#include <string>
#include <raylib.h>
#include <raymath.h>

// Global Declare
#define MAX_OBS 10
#define SCREEN_H 800.0f
#define SCREEN_W 1000.0f
#define OBSTACLE_SPACING 350

// Game Variables
extern bool pause;
extern Sound PlayerMoveS;
extern Sound Hit;
extern Image Background;
extern Texture BackTexture;

// Class
class PlayerClass { public:
    int score;
    int life;
    float height;
    float width;
    Rectangle Player;
    float speed;
    Color color;

    
};
extern PlayerClass Player;

class ObstackleClass { public:
    float height;
    float width;
    Rectangle Obstackle;
    float speed;
    Color color;

};
extern ObstackleClass Obstackle[MAX_OBS];

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
void LoadGame();