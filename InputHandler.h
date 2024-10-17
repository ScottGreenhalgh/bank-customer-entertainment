#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <stdbool.h>

void InitInputHandler();
void SetKeyPressed(int key);
void SetKeyReleased(int key);
bool GetKeyPressed(int key);
void SetMousePosition(int x, int y);
int GetMouseX();
int GetMouseY() ;

#endif // INPUTHANDLER_H
