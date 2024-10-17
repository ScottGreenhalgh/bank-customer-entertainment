#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graphics_lib.h"
#include "GamePlayer.h"
#include "Level.h"

int main()
{
    //initialse game stuff
    InitInputHandler();
    InitPlayer();
    InitLevel();
    time_t start, end;

    //create window
    int windowDimensions[2] = {1280, 720};
	GFX_InitWindow(windowDimensions[0], windowDimensions[1]);

	//initialise input methods and design features
	GFX_InitBitmap();
	GFX_InitFont();
	GFX_InitMouse();
	GFX_InitKeyboard();

	//create event contexts
	GFX_CreateEventQueue();
	GFX_RegisterDisplayEvents();
	GFX_RegisterMouseEvents();
	GFX_RegisterKeyboardEvents();

    //set colours
	GFX_SetColour(CYAN);
	GFX_SetBackgroundColour(BROWN);

	LoadBitmaps();

    while(GetPlayerInfo()->gameStatus != GAMESTATUS_QUIT) {
        start = time(NULL);
        // Input
        while(GFX_IsEventWaiting()) {
            GFX_WaitForEvent();

            if(GFX_IsEventCloseDisplay()) {
                QuitGame(); // kill the loop
            } else if(GFX_IsEventKeyDown()) {
                int key;
                GFX_GetKeyPress(&key);
                SetKeyPressed(key);
            } else if(GFX_IsEventKeyUp()) {
                int key;
                GFX_GetKeyPress(&key);
                SetKeyReleased(key);
            } else if(GFX_IsEventMouseButton()) {
                int key;
                GFX_GetMouseButton(&key);
                MouseButtonPressed(key);
            } else if(GFX_IsEventMouseMoved()) {
                int mx, my;
                GFX_GetMouseCoordinates(&mx, &my);
                SetMousePosition(mx, my);
            }
        }

        if(GetPlayerInfo()->gameStatus == GAMESTATUS_MENU) {
            //menu updating
        } else {
            // Update
            UpdateLevel();
            UpdatePlayer();
        }

        // Rendering
        GFX_ClearWindow();
        //do rendering
        if(GetPlayerInfo()->gameStatus == GAMESTATUS_MENU) {
            //menu rendering
        } else {
            RenderLevel(windowDimensions[0]);
            RenderPlayer();
        }

        GFX_UpdateDisplay();

        end = time(NULL);
        double elapsed = difftime(end, start);
        double allowedTPS = (float)1 / (float)30;
        if(elapsed < allowedTPS) {
            usleep((allowedTPS - elapsed) * 1000000);
        }
    }
    //main loop
    //  input
    //  update
    //  render

    DeInitLevel();

    //cleanup
    GFX_CloseKeyboard();
    GFX_CloseMouse();
    GFX_CloseWindow();

    return 0;
}
