#pragma once
#include <iostream>
#define NOMAL_SCORE 10
#define POWER_SCORE 20

class SDLGameObject;

class ScoreManager //Play�� ������ �����մϴ�. ������ ���� (���� ����) �� StageController���� �ñ�ϴ�
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
	void InitializeScore()
	{
		curScore = 0;

		grade = CaculateGrade();
		ChangeScoreSprite();
	}
	void SetScoreGrade(int AllNoteNum)
	{
		if (playScore == NULL) { throw std::runtime_error("ScoreManager :: AddScoreSprite() �� ������Ʈ�� �־����� Ȯ�����ּ��� \n"); }

		curScore = 0;
		ALLScore = (float)(AllNoteNum * NOMAL_SCORE);

		ChangeScoreSprite();

		Grade_A = (int)(ALLScore * 0.9f);
		Grade_B = (int)(ALLScore * 0.7f);
		Grade_C = (int)(ALLScore * 0.5f);
		Grade_D = (int)(ALLScore * 0.4f);
		grade = CaculateGrade();
	}
	//���� �������� �ʰ� ���������� ���� �����Ҷ� ȣ�� 
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
