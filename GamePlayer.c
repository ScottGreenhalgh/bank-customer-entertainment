#include "GamePlayer.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void InitPlayer()
{
    playerInformation.gameStatus = GAMESTATUS_PLAYING;
    playerInformation.playerModel.head[0] = 160;
    playerInformation.playerModel.head[1] = 400;
    playerInformation.playerModel.head[2] = 10;
    updateBody();
    playerInformation.playerModel.floorY = 490; //todo get this information from the level, shouldn't be on player
}

void UpdatePlayer()
{
    playerInformation.playerModel.head[0] = 160 + playerInformation.playerX;
    updateBody();

    if(GetKeyPressed(1)) { //check if A key is pressed
        playerInformation.playerX = playerInformation.playerX - 4;
        if(160 + playerInformation.playerX < 20) playerInformation.playerX = 20 - 160;
    }
    if(GetKeyPressed(4)) { //check if D key is pressed
        playerInformation.playerX = playerInformation.playerX + 4;
        if(160 + playerInformation.playerX > 250) playerInformation.playerX = 250 - 160;
    }
    if(GetKeyPressed(59)) { //check if Esc key is pressed
        TryQuitGame();
    }
    if(GetKeyPressed(75)) { // check if Space key is pressed
        TryRestartGame();
    }
}
void MouseButtonPressed(int button)
{
    if(button == 1) { //check if mouse button 1 is pressed
        int xVel = GetMouseX() - 160 + playerInformation.playerX;
        if(xVel < 20) xVel = 20;
        if(xVel > 50) xVel = 50;
        int yVel = (490 - GetMouseY()) / 4;
        if(yVel < 0) yVel = 20;
        if(yVel > 75) yVel = 75;
        CreateProjectile(xVel, yVel);
    }
}

void updateBody()
{   //player array
    playerInformation.playerModel.leye[0] = playerInformation.playerModel.head[0] - 3;
    playerInformation.playerModel.leye[1] = playerInformation.playerModel.head[1] - 5;
    playerInformation.playerModel.leye[2] = playerInformation.playerModel.head[0] - 3;
    playerInformation.playerModel.leye[3] = playerInformation.playerModel.head[1] - 1;
    playerInformation.playerModel.reye[0] = playerInformation.playerModel.head[0] + 3;
    playerInformation.playerModel.reye[1] = playerInformation.playerModel.head[1] - 5;
    playerInformation.playerModel.reye[2] = playerInformation.playerModel.head[0] + 3;
    playerInformation.playerModel.reye[3] = playerInformation.playerModel.head[1] - 1;
    //playerInformation.playerModel.mouth[0] = playerInformation.playerModel.head[0];
    //playerInformation.playerModel.mouth[1] = playerInformation.playerModel.head[1];
    //playerInformation.playerModel.mouth[2] = 5;
    //playerInformation.playerModel.mouth[3] = 0;
    //playerInformation.playerModel.mouth[4] = 180;
    playerInformation.playerModel.body[0] = playerInformation.playerModel.head[0];
    playerInformation.playerModel.body[1] = playerInformation.playerModel.head[1] + 10;
    playerInformation.playerModel.body[2] = playerInformation.playerModel.head[0];
    playerInformation.playerModel.body[3] = playerInformation.playerModel.head[1] + 60;
    playerInformation.playerModel.larm[0] = playerInformation.playerModel.body[0];
    playerInformation.playerModel.larm[1] = playerInformation.playerModel.body[1];
    playerInformation.playerModel.larm[2] = playerInformation.playerModel.body[0] - 30;
    playerInformation.playerModel.larm[3] = playerInformation.playerModel.body[1] + 30;
    playerInformation.playerModel.rarm[0] = playerInformation.playerModel.body[0];
    playerInformation.playerModel.rarm[1] = playerInformation.playerModel.body[1];
    playerInformation.playerModel.rarm[2] = playerInformation.playerModel.body[0] + 30;
    playerInformation.playerModel.rarm[3] = playerInformation.playerModel.body[1] + 30;
    playerInformation.playerModel.lleg[0] = playerInformation.playerModel.body[2];
    playerInformation.playerModel.lleg[1] = playerInformation.playerModel.body[3];
    playerInformation.playerModel.lleg[2] = playerInformation.playerModel.body[2] + 30;
    playerInformation.playerModel.lleg[3] = playerInformation.playerModel.body[3] + 30;
    playerInformation.playerModel.rleg[0] = playerInformation.playerModel.body[2];
    playerInformation.playerModel.rleg[1] = playerInformation.playerModel.body[3];
    playerInformation.playerModel.rleg[2] = playerInformation.playerModel.body[2] - 30;
    playerInformation.playerModel.rleg[3] = playerInformation.playerModel.body[3] + 30;
}

void RenderPlayer()
{   // draws player
    updateBody();
    GFX_DrawCircle(playerInformation.playerModel.head[0], playerInformation.playerModel.head[1], playerInformation.playerModel.head[2], 2);
    GFX_DrawLine(playerInformation.playerModel.body[0], playerInformation.playerModel.body[1], playerInformation.playerModel.body[2], playerInformation.playerModel.body[3], 2);
    GFX_DrawLine(playerInformation.playerModel.larm[0], playerInformation.playerModel.larm[1], playerInformation.playerModel.larm[2], playerInformation.playerModel.larm[3], 2);
    GFX_DrawLine(playerInformation.playerModel.rarm[0], playerInformation.playerModel.rarm[1], playerInformation.playerModel.rarm[2], playerInformation.playerModel.rarm[3], 2);
    GFX_DrawLine(playerInformation.playerModel.lleg[0], playerInformation.playerModel.lleg[1], playerInformation.playerModel.lleg[2], playerInformation.playerModel.lleg[3], 2);
    GFX_DrawLine(playerInformation.playerModel.rleg[0], playerInformation.playerModel.rleg[1], playerInformation.playerModel.rleg[2], playerInformation.playerModel.rleg[3], 2);
    GFX_DrawLine(playerInformation.playerModel.reye[0], playerInformation.playerModel.reye[1], playerInformation.playerModel.reye[2], playerInformation.playerModel.reye[3], 2);
    GFX_DrawLine(playerInformation.playerModel.leye[0], playerInformation.playerModel.leye[1], playerInformation.playerModel.leye[2], playerInformation.playerModel.leye[3], 2);
    //GFX_DrawArc(playerInformation.playerModel.mouth[0], playerInformation.playerModel.mouth[1], playerInformation.playerModel.mouth[2], playerInformation.playerModel.mouth[3], playerInformation.playerModel.mouth[4], 2);
}

// returnType <name>(parameterType parameter ...)

structPlayer_t* GetPlayerInfo()
{
    return &playerInformation;
}

void QuitGame()
{
    playerInformation.gameStatus = GAMESTATUS_QUIT;
}
