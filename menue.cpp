#include "game.h"

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
            UnloadGame();
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
        DrawText("FLAPPY BIRD", BackGr.x + 60, BackGr.y + 30, 36, (Color){255, 69, 0, 255}); // Orange red
        DrawText("FLAPPY BIRD", BackGr.x + 62, BackGr.y + 32, 36, (Color){255, 140, 0, 255}); // Dark orange (shadow effect)
        
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
        if(quitHover && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) { UnloadGame(), exit(0);}
        EndDrawing();
    }
}
