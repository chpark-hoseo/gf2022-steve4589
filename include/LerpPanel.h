#pragma once
#include <SDLGameObject.h>
#include <Timer.h>
//#include <Coroutine> 
//코루틴 참고 자료 :: https://luncliff.github.io/coroutine/ppt/[Kor]ExploringTheCppCoroutine.pdf

class LerpPanel : public SDLGameObject
{
public:
	LerpPanel(const LoaderParams* pParams);

	virtual void draw();
	virtual void update();
	virtual void clean() {}

	void FadeOut(string sort)
	{
		time = 0;
		//StartCoroutine(Fadeout(sort));
	}
	void FadeIn(string sort)
	{
		time = 0;
		//StartCoroutine(Fadein(sort));
	}

	/*IEnumerator Fadeout(string sort)
	{
		on.gameObject.SetActive(true);
		this.color = new Color(1, 1, 1, 1);
		Color alpha = this.color;
		alpha.a = 0;

		while (alpha.a < 1f)
		{
			time += Time.deltaTime / (F_time / 10f);
			alpha.a = Mathf.Lerp(0, 1, time);
			on.color = alpha;
			yield return null;
		}
		on.gameObject.SetActive(false);
		yield return null;
	}

	IEnumerator Fadein(string sort)
	{
		on.gameObject.SetActive(true);
		Color alpha = on.color;
		alpha.a = 1;

		while (alpha.a > 0f)
		{
			time += Time.deltaTime / (F_time / 10f);
			alpha.a = Mathf.Lerp(1, 0, time);
			on.color = alpha;
			yield return null;
		}
		on.gameObject.SetActive(false);
		yield return null;
	}*/


	void startLerp(float r, float g, float b, float a, float time) {}
	void FadeOut(float time) {}
	void FadeIn(float time) {}
private:
	float curTime;

	float time = 0;
	float F_time = 10;
};
/*
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class FadePanel : MonoBehaviour
{
	SpriteRenderer spriteRenderer;
	public Image deadPanel;
	public Image WhilePanel;
	public Image BlackPanel;
	Image on;

	float time = 0;
	float F_time = 10f;

	public void FadeOut(string sort)
	{
		time = 0;
		StartCoroutine(Fadeout(sort));
	}

	public void FadeIn(string sort)
	{
		time = 0;
		StartCoroutine(Fadein(sort));
	}

	IEnumerator Fadeout(string sort)
	{
		if (sort == "black") //죽었을때
		{
			on = deadPanel;
		}
		else //연출 적용
		{
			WhilePanel.color = new Color(1, 1, 1, 1);
			on = WhilePanel;
		}
		on.gameObject.SetActive(true);
		Color alpha = on.color;
		alpha.a = 0;

		while (alpha.a < 1f)
		{
			time += Time.deltaTime / (F_time / 10f);
			alpha.a = Mathf.Lerp(0, 1, time);
			on.color = alpha;
			yield return null;
		}

		if (GameObject.FindWithTag("Player") != null)
		{
			while (true)
			{
				if (Input.anyKeyDown)
				{
					//체력을 3으로 다시 채워줌
					GameObject.FindWithTag("Player").GetComponent<PlayerAction>().life = 3;
					GameObject gameManager = GameObject.FindWithTag("GameManager");

					gameManager.GetComponent<GameManager>().GameLoad(false);

					FadeIn(sort);
					break;
				}
				yield return null;
			}
		}
		yield return null;
	}

	IEnumerator Fadein(string sort)
	{
		if (sort == "black") //죽었을때
		{
			on = deadPanel;
		}
		else if (sort == "load")
		{
			on = BlackPanel;
		}
		else
		{
			on = WhilePanel;
		}

		on.gameObject.SetActive(true);
		Color alpha = on.color;
		alpha.a = 1;

		while (alpha.a > 0f)
		{
			time += Time.deltaTime / (F_time / 10f);
			alpha.a = Mathf.Lerp(1, 0, time);
			on.color = alpha;
			yield return null;
		}
		if (GameObject.FindWithTag("Player") != null)
		{
			GameObject.FindWithTag("Player").GetComponent<PlayerAction>().waitTime = 0; //다시 게임시작할때 폭탄이 바로 발사되지 않도록
		}
		on.gameObject.SetActive(false);
		yield return null;
	}
	public void EnforceOff()
	{
		WhilePanel.color = new Color(1, 1, 1, 0);
	}
}
*/