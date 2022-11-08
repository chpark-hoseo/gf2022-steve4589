#pragma once
#include "GameObject.h"

class Monster : public GameObject //����2. �������� �̿��Ͽ� Monster ��ü �����ϱ� 
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