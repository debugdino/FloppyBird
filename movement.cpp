#include "game.h"
bool keyHeld = false;

void MovePlayer() {
    if(IsKeyDown(KEY_W)) {
        if(!keyHeld) {
            PlaySound(PlayerMoveS);
            keyHeld = true;
        }
        Player.Player.y -= Player.speed;
    }else keyHeld = false;
    
    if(IsKeyDown(KEY_S)) {
        if(!keyHeld) {
            PlaySound(PlayerMoveS);
            keyHeld = true;
        }   
        Player.Player.y += Player.speed;
    }
    else {
        keyHeld = false;
        Player.Player.y += 0.5*Player.speed;
    }
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