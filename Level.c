#include "Level.h"
#include "GamePlayer.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "includes/graphics_lib.h"

// initialising variables
int markerLocationX = -1;
int projectileVelX;
int projectileVelY;
int attempts;
int cubePosX;
int cubeSize;
int cubePosY;
int cubeMovementDirection;
BITMAP backgroundImage;

int currentAttempt;
int player_attempts_values[10];
int totalThrowDistance , bestThrow, worstThrow;
int distance;
bool canRestartOrQuit;

void InitLevel()
{   //assigning values to the variables
    for(int i = 0; i < 10; i++) {
        player_attempts_values[i] = 0;
    }
    attempts = -1; //starting attempts at an impossible value
    markerLocationX = -1;
    totalThrowDistance = 0;
    bestThrow = 0;
    worstThrow = 0;
    distance = 0;
    projectileVelX = -1;
    projectileVelY = -1;
    levelInfo.floorY = 490;
//  AttemptSelection();
    canRestartOrQuit = false;
    currentAttempt = 0;
    cubePosX = 500;
    cubePosY = 200; //random
    cubeSize = 30; //random
    cubeMovementDirection = 4;
}

void LoadBitmaps() // loads the bank related background image
{
    backgroundImage = GFX_LoadBitmap("res/bank_image.bmp");
}

void DeInitLevel() // unloads the background image when closing the level
{
    GFX_FreeBitmap(backgroundImage);
}

void RenderLevel(int screenWidth)
{
    //draw background here
    if(backgroundImage) GFX_DrawBitmap(backgroundImage, 640, 360);
    GFX_DrawLine(0, levelInfo.floorY, screenWidth, levelInfo.floorY, 2);
    if(attempts <= 0) {
        //write your attemps
        GFX_DrawText(50, 50, "Select your amounts of attempts (hit 0 - 9)");
        return;
    } else if(currentAttempt + 1 <= attempts) {
        char text[255];
        sprintf(text, "Current Attempts %i/%i", currentAttempt + 1, attempts);
        GFX_DrawText(50, 50, text);
    } else {
        //display stats
        int calculated_mean = totalThrowDistance / attempts;
        int average_sqaured = 0;
        int deviation = 0;
        for(int i = 0; i < attempts; i++) {
            if(player_attempts_values[i] == -1) break;
            deviation = player_attempts_values[i] - calculated_mean; //subtract mean
            deviation *= deviation; //square itself
            average_sqaured += deviation; //add to total
        }
        average_sqaured = average_sqaured / attempts; //get average
        // draws text on screen at selected coordinates
        char string[512];
        sprintf(string, "Standard Deviation: %d, Mean Distance: %d, Best Throw: %d, Worst Throw: %d", (int) sqrt(average_sqaured), (totalThrowDistance / attempts), bestThrow, worstThrow);
        GFX_DrawText(50, 50, string);
        GFX_DrawText(50, 70, "Press Escape to quit or Space to restart.");
        canRestartOrQuit = true;
    }
    if(markerLocationX > 0) { //draws the marker
        GFX_DrawLine(markerLocationX, playerInformation.playerModel.floorY, markerLocationX, playerInformation.playerModel.floorY + 40, 2);
    }
    // draws the obstruction
    GFX_DrawLine(cubePosX, cubePosY, cubePosX, cubePosY + cubeSize, 2);
}

void UpdateLevel()
{
    if(markerLocationX < 0) { //checks when to draw the marker
        CreateMarker();
    }
    if(cubePosY <= 50) cubeMovementDirection = 4; // varies the obstructions location
    else if(cubePosY+cubeSize >= 450) cubeMovementDirection = -4;
    cubePosY += cubeMovementDirection;
}

void CreateMarker()
{
    if(markerLocationX < 300 && attempts > 0) {
        //create the marker
        time_t dd; //seed the random so its kinda random
        srand((unsigned) time(&dd) + clock());
        markerLocationX = GFX_RandNumber(300, 1000);
        cubePosX = GFX_RandNumber(300, markerLocationX - 50);
        cubeSize = GFX_RandNumber(30, 100);
    }
}

void CreateProjectile(int velocityX, int velocityY)
{
    if(markerLocationX > 0 && currentAttempt + 1 <= attempts) { //defines when the projectile should be drawn
        currentAttempt++;
        projectileVelX = velocityX;
        projectileVelY = velocityY;
        DrawProjectile();
    }
}


void DrawProjectile()
{
    int initial_posX = playerInformation.playerModel.rarm[2];
    int initial_posY = playerInformation.playerModel.rarm[3];
    int posX = initial_posX;
    int posY = initial_posY;
    float gravity = 9.81;
    GFX_MoveTo(initial_posX, initial_posY);
    int landX = 0;
    bool hitFloor = false;
    bool hitBox = false;
    int lines = 0;
    int velX = posX;
    while(!hitFloor) {
        //projectile calculations
        float time = (velX - playerInformation.playerModel.rarm[2]) / (float)projectileVelX;
        if (posY < 490) { //if its smaller than floor
            if(posX == cubePosX) { // checks if touching the obstruction
                if(posY < cubePosY + cubeSize && posY > cubePosY) hitBox = true;
            }
            posY = initial_posY - ((float)projectileVelY * time) + (gravity * time * time)/2;
            //posY +=1;
            if(hitBox) {
                posX -= 1;
            } else {
                posX += 1;
            }
            velX += 1;
            landX = posX;
            lines++;
        } else if(posY >= 490) { // checks if the marker is at floor level
            hitFloor = true;
        }
        GFX_DrawLineTo(posX, posY, 2);
        GFX_UpdateDisplay();
    }
    DidHitMarker(landX);
}

void DidHitMarker(int landX) { //checks if the projectile reached the marker
    Mathematics(landX);
    sleep(3);
}

//void AttemptSelection() {
//}

void SetAttempts(int key) { //checks which key is pressed
    if(attempts > 0) return;
    switch(key) {
        case 28:
            attempts = 1;
            break;
        case 29:
            attempts = 2;
            break;
        case 30:
            attempts = 3;
            break;
        case 31:
            attempts = 4;
            break;
        case 32:
            attempts = 5;
            break;
        case 33:
            attempts = 6;
            break;
        case 34:
            attempts = 7;
            break;
        case 35:
            attempts = 8;
            break;
        case 36:
            attempts = 9;
            break;
        default:
            attempts = 3;

    }
}

void Mathematics(int landX) {
    distance = (int) abs(markerLocationX - landX);
    player_attempts_values[currentAttempt - 1] = distance;

    if(distance <= 10 || distance >= -10) markerLocationX = -1;

    if(bestThrow > distance || currentAttempt == 1) { //calculates best throw
        bestThrow = distance;
    }
    if(worstThrow < distance || currentAttempt == 1) { //calculates worst throw
        worstThrow = distance;
    }

    totalThrowDistance += distance;
}

void TryQuitGame() {
    if(canRestartOrQuit) {
        QuitGame();
    }
}

void TryRestartGame() {
    if(canRestartOrQuit) {
        InitLevel();
    }
}
