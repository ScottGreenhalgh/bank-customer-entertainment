#include "InputHandler.h"

int* keyStates; //there is 133 keys total in allegro (added one since im not sure if the first key starts at 0 or 1)
int mouseX;
int mouseY;

void InitInputHandler()
{
    keyStates = malloc(sizeof(int) * 134);
}

void SetKeyPressed(int key)
{
    if(key >= 28 && key <= 37) {
        SetAttempts(key);
    }
    keyStates[key] = 1;
}

void SetKeyReleased(int key)
{
    keyStates[key] = 0;
}

bool GetKeyPressed(int key)
{
    return (bool)keyStates[key];
}

void SetMousePosition(int x, int y) {
    mouseX = x;
    mouseY = y;
}

int GetMouseX() { return mouseX; }
int GetMouseY() { return mouseY; }
