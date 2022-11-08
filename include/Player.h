#pragma once
#include "GameObject.h"

enum PlayerState
{
    Slide = 0,
    Swimming,
    Wave
};

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
    void update() { State(); }
    void clean() {};

    void GoSwim() { state = Swimming; }
    void GoWave() { state = Wave; }

    int dirSpeed = 0;
 
private:
    PlayerState state = Swimming;
    int count;

    void State()
    {
        switch (state)
        {
        default:
            break;
        case Swimming:
            MungMungSwim();
            break;
        case Wave:
            MungMungWave();
            break;
        }
    }
    void MungMungSwim()
    {
        m_y += sin((float)(3.141592f * 2 / 240) * count);
        m_x += cos((float)(3.141592f * 2 / 240) * count);
       
        count++;
    }
    void MungMungWave()
    {
        m_y += sin((float)(3.141592f * 2 / 240) * count);
        m_x += 1;

        count++;
    }
};