#pragma once
#include <iostream>
#define NOMAL_SCORE 10
#define POWER_SCORE 20

class SDLGameObject;

class ScoreManager //Play중 점수를 관리합니다. 데이터 저장 (점수 저장) 은 StageController에게 맡깁니다
{
public:
	static ScoreManager* GetInstance()
	{
		if (s_pInstance == NULL)
			s_pInstance = new ScoreManager();
		return s_pInstance;
	}
	void AddScoreSprite(SDLGameObject* getPlayScore);
	void AddScore() 
	{ 
		curScore += NOMAL_SCORE; 

		grade = CaculateGrade();
		ChangeScoreSprite();
	}
	void MinusScore()
	{
		curScore -= 10;
		if (curScore < NOMAL_SCORE) curScore = 0;

		grade = CaculateGrade();
		ChangeScoreSprite();
	}
	void SetScoreGrade(int AllNoteNum)
	{
		if (playScore == NULL) { throw std::runtime_error("ScoreManager :: AddScoreSprite() 에 오브젝트를 넣었는지 확인해주세요 \n"); }

		ALLScore = (float)(AllNoteNum * NOMAL_SCORE);

		Grade_A = (int)(ALLScore * 0.9f);
		Grade_B = (int)(ALLScore * 0.7f);
		Grade_C = (int)(ALLScore * 0.5f);
		Grade_D = (int)(ALLScore * 0.4f);
		grade = CaculateGrade();
	}
	//게임 오버하지 않고 스테이지가 끝에 도달할때 호출 
	int CaculateGrade()
	{
		if (curScore >= Grade_A) { return 4; }
		if (curScore >= Grade_B) { return 3; }
		if (curScore >= Grade_C) { return 2; }
		if (curScore >= Grade_D) { return 1; }
		if (curScore < Grade_D) { return 0; }
		else return -1; 
	}
private:
	ScoreManager() {}
	~ScoreManager();

	void ChangeScoreSprite();

	int curScore = 0;
	int nomalScore = 10;
	float ALLScore = 0;

	int grade = 0;

	int Grade_A;
	int Grade_B;
	int Grade_C;
	int Grade_D;

	static ScoreManager* s_pInstance;

	SDLGameObject* playScore = NULL;

};
