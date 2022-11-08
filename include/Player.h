#pragma once
#include "GameObject.h"

class Player : public GameObject
{
public:
    Player(int getDirSpeed)
    {
        dirSpeed = getDirSpeed;
    }
    ~Player();

    void load(float x, float y, int width, int height, std::string textureID);
    void draw(SDL_Renderer* pRenderer);
    void update();
    void clean() {};

    int dirSpeed = 0;
};