#pragma once
#include "GameObject.h"

class EnergyNote : public GameObject  //, public INoteType
{
public:
    void load(int x, int y, int width, int height, int currentRow, int currentFrame, std::string textureID);
    void draw(SDL_Renderer* pRenderer);
    void update();
    void clean();

    //void move() override;
    //void crashEvent() override;
};