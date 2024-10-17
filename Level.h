#ifndef LEVEL_H
#define LEVEL_H

typedef struct StructLevel {
    int floorY;
    int attempts;
} structLevel_s;

struct StructLevel levelInfo;

void InitLevel();
void LoadBitmaps();
void DeInitLevel();
void UpdateLevel();
void CreateProjectile(int velocityX, int velocityY);
void CreateMarker();
void RenderLevel(int screenWidth);
void DrawProjectile();
void DidHitMarker(int landX);
void ThrowingAttempt();
void AttempSelection();
void SetAttempts(int key);
structLevel_s* GetLevelInfo();
void Mathematics(int landX);

#endif // LEVEL_H
