#pragma once
#include "GameObject.h"

class Monster : public GameObject //과제2. 다형성을 이용하여 Monster 객체 생성하기 
{
public:
    void load(float x, float y, int width, int height, std::string textureID);
    void draw(SDL_Renderer* pRenderer);
    void update() {  }
    void clean() {};

private:
    int count = 0;

    void MungMungSlide();
    void MungMungSwim();
    void MungMungWave();
    //void (Monster::* move)() = &Monster::moveDiagonal;
};