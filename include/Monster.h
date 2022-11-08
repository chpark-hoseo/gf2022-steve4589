#pragma once
#include "GameObject.h"

enum State
{
    Slide = 0,
    Swimming,
    Wave
};

class Monster : public GameObject //����2. �������� �̿��Ͽ� Monster ��ü �����ϱ� 
{
public:
    void load(float x, float y, int width, int height, std::string textureID);
    void draw(SDL_Renderer* pRenderer);
    void update() { State(); }
    void clean() {};

    void GoSwim() { state = Swimming; }
    void GoWave() { state = Wave; }

private:
    State state = Slide;
    int count = 0;

    void State()
    {
        switch (state)
        {
        default:
            break;
        case Slide :
            MungMungSlide();
            break;
        case Swimming:
            MungMungSwim();
            break;
        case Wave:
            MungMungWave();
            break;
        }
    }
    void MungMungSlide();
    void MungMungSwim();
    void MungMungWave();
    //void (Monster::* move)() = &Monster::moveDiagonal;
};