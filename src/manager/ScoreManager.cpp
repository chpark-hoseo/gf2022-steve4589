#include <ScoreManager.h>
#include <SDLGameObject.h>

ScoreManager* ScoreManager::s_pInstance = NULL;

ScoreManager::~ScoreManager() { delete playScore; } //

void ScoreManager::AddScoreSprite(SDLGameObject* getPlayScore) { playScore = getPlayScore; }
void ScoreManager::ChangeScoreSprite() { playScore->SetSpriteFrame(grade); }