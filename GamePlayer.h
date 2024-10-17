#ifndef GAMEPLAYER_H
#define GAMEPLAYER_H

typedef enum EnumGameStatus {
    GAMESTATUS_MENU,
    GAMESTATUS_PLAYING,
    GAMESTATUS_QUIT
} enumGameStatus_t;

typedef struct PlayerModel {
    int head[3];
    int leye[4];
    int reye[4];
    int mouth[5];
    int body[4];
    int larm[4];
    int rarm[4];
    int lleg[4];
    int rleg[4];
    int floorY;
} playerModel_s;

typedef struct StructPlayer {
    enumGameStatus_t gameStatus;
    int playerX;
    playerModel_s playerModel;
} structPlayer_t;

struct StructPlayer playerInformation;

void InitPlayer();
void UpdatePlayer();
void updateBody();
void RenderPlayer();
void QuitGame();
void MouseButtonPressed(int button);
structPlayer_t* GetPlayerInfo();

#endif // GAMEPLAYER_H
