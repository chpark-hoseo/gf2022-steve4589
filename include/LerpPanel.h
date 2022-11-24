#pragma once
#include <SDLGameObject.h>
#include <Timer.h>
#include <SDL2/SDL.h>
#include <coroutine>
#include <exception>

using namespace std;

//template <class T>
class LerpPanel : public SDLGameObject
{
public:
	// ��Ģ 4. �Ҹ��ڿ��� std::coroutine_handle<promise_type> Ÿ����
    // �ڷ�ƾ �ڵ鷯 ��� ������ destroy�� ȣ�� �ؾ� �Ѵ�.
	~LerpPanel()
	{
		if (m_handle != NULL) { m_handle.destroy(); }
	}

	struct promise_type;
	using coro_handle = std::coroutine_handle<promise_type>;

	//coroutine_trait���ε� ��� ����, �����ڷ�::https://en.cppreference.com/w/cpp/language/coroutines
	struct promise_type //��ȯ��, �����Ϸ��� �ش� �ڷ�ƾ�� �۵� ��ų�� ���⼭ ������ �ش� Ŀ���� �ڷ�ƾ �Լ��� �۵���Ŵ
	{
		float value = 0;

		//�ڷ�ƾ �Լ����� co_yield ȣ���Ҷ� ���� :: ������ �ʿ����
		/*std::suspend_always yield_value(float value)
		{
			this->value = value;
			return {};
		}*/
		// suspend_always{} ==> ȣ���ڿ��� ������� �ѱ�
		// suspend_never{} ==> �ѱ��� ����
		
		//����� ��ȯ ��ü ���� (�ݵ�� ���� ==> �����Ϸ��� �ݵ�� promise_type�� �����ϱ� ������ ������ ���� => ��ȯ���� �Ѱ��ְڴٶ�� ����ؾ���) 
		LerpPanel get_return_object() { return LerpPanel{ get_pParams, std::coroutine_handle<promise_type>::from_promise(*this) }; } //�̷��� ���� ���� ��ȯ���� �Ѱ��ְڴٰ� ���, ������ �����ϱ� voidŸ������ ���� ����
		auto initial_suspend() { return suspend_never{}; } // �ڷ�ƾ ���� ���� �� ȣ��. awaitable ��ü�� ��ȯ.
		auto return_void() noexcept {} // co_return�� ����Ҷ� ���ϰ��� �ִٸ� �����Ϸ����� �ڵ����� ȣ��, �ݴ� ==> return_value()
		auto final_suspend() noexcept { return suspend_always{}; } // �ڷ�ƾ ���� �� ȣ��. noexcept => �ش� �Լ��� ���ܸ� ȣ������ �ʵ��� ����
		void unhandled_exception() { std::terminate(); } // �ڷ�ƾ ���� �� ���� �߻� �� ȣ��, ���⼱ �����߽��ϴ�

		// std::coroutine_handle<Promise>::done ==> �ڷ�ƾ�� ������ �Ϸ� �Ǹ� true, �ƴϸ� false ����
		// ex )) if (true == range.coroutine.done()) 
	};
	// ��Ģ 3. std::coroutine_handle<promise_type> �� ���ڷ� �޾�
	// ��� ������ �ʱ�ȭ �ϴ� �����ڰ� �־�� �Ѵ�.
	explicit LerpPanel(const LoaderParams* pParams, coro_handle handle); //explicit => ������ �ʴ� ����ȯ�� �ȵǰ� ����

	virtual void draw();
	virtual void update();
	virtual void clean() {}

	void FadeIn()
	{
		SetActive(true);

		timer.WaitTime();
		timer.getTimer();
	}

	LerpPanel Fadeout()
	{
		promise_type promise;

		promise.get_return_object(); //����� �̷��� promise_type�� �ݳ�
		co_await promise.initial_suspend();
		
		SetActive(true);

		alpha = 0;
		timer.WaitTime();

		while (true) //alpha < 1
		{
			timer.StartTimer();
			alpha += timer.getTimer() / (F_time * 0.1f);
			//SDL_SetAlpha(surface, SDL_RLEACCEL | SDL_SRCALPHA, (Uint8)alpha);
			//SDL_BlitSurface(surface, NULL, screen, NULL);
			std::cout << "���İ� : " << alpha << "\n";
			co_await std::suspend_always{}; //main �ѹ� ������ ���� ������� main������ �Ѱ��ݴϴ� (update���� �簳)
		}
		//SDL_SetAlpha(surface, SDL_RLEACCEL | SDL_SRCALPHA, (Uint8)1);

		SetActive(false);
		co_return;
	}
private: //�ڵ鷯 ��� :: �ڵ鷯�� �� ���� �� �ʱ�ȭ�ϰ� �پ��� ���ֱ�
	// ��Ģ 2. std::coroutine_handle<promise_type> Ÿ���� ��� ������ �־�� �Ѵ�.
	coro_handle m_handle = NULL;
	const LoaderParams* get_pParams;

	Timer timer;

	double alpha;
	double F_time = 10; //�⺻�� : 10
	//LerpPanel::promise_type promise;
};
//�ڷ�ƾ ���� �ڷ� :: https://luncliff.github.io/coroutine/ppt/[Kor]ExploringTheCppCoroutine.pdf
//https://kukuta.tistory.com/222
/*�ڷ�ƾ �⺻ ��Ʈ::
* ȣ�� : ��ƾ�� ���������� ����
* Ȱ��ȭ : ��ƾ���� �ӽ��������� ����  co_return
* �ߴ� : ��ƾ�� �ߴ����� �ʰ� �ٸ� ��ƾ�� �������� ����  co_await, co_yield
		 co_await() -> ���� ���� �Լ��� ���߰� ���� ������� �ڷ�ƾ�� ȣ���� ������ �ѱ�. �׸��� ������� �޾� �����ɶ� �� ���� ���ĺ��͸� �̾ ����
* ���� : ��ƾ�� ���� ������ �� ��ƾ ������ �Ҹ� �� ����  co_return
* �簳 : coro.resume() // coroutine_handle<P>::resume()
*
���� ��ƾ : ȣ�� / ���� �� �� �ִ� ��ƾ :: Finalize (Return / ��ƾ(Caller) -> ���� ��ƾ), Invoke (Call / ���� ��ƾ -> ��ƾ(Caller))
//���� ���� call, return�� �ڷ�ƾ (�Լ����� �ڷ�ƾ)

���μ��� : Os���� ���α׷�(��ƾ�� ����ü)�� �����ϴ� ���
������ : �������� ���� ���� �帧 (���μ��� CPU) �� ����ȭ�Ѱ�

�ڷ�ƾ : ȣ�� / Ȱ��ȭ / �ߴ�/ ���� �� �� �ִ� ��ƾ  (���� ��ƾ Ȯ���� ���� ����)

���������� ������(���α׷��� ��� :: Function)�� �ڷ�ƾ(�ӽ� :: Coroutine, SubRoutine)�� ����غ������� ���� ����
������ => �������� �����尡 �۾��� ������ �� => �񵿱� �۵����, ��� ����Ҷ� ��ȿ�� ��������, ó������ ������ å������ �Ѵٸ� �ڷ�ƾ ����ȣȯ(SDL���� ������ �������� �����ϴ� ����)
�ڷ�ƾ => �Ѱ��� �����忡�� �۾��� �߰� ������ �� => �񵿱�X, ��� ����Ҷ� ����, �����庸�� ������, �����ڿ����� ����ȭ������ ������ ����, �ʹ� ���� ���Ǹ� ������ ����ȣȯ

StackFullCoroutine -> �ڷ�ƾ�� �������� ���ÿ�
StackLessCoroutine -> �ڷ�ƾ�� �������� ���ùٱ��� (���� ����)

���� �Լ��� �ϳ��� �־�� �ǰ�, �ִٸ� �� �Լ��� �ڷ�ƾ���� ó��
 co_await expression
 co_yield expression
 co_return statement
 for co_await statement

�ڷ�ƾ ��ȯ ��ü ::
1. promise. "�ڷ�ƾ ����"���� ���� �Ǵ� ��ü. �ڷ�ƾ�� ����� ���ܸ� �� ��ü�� ���� ȣ���ڿ��� ���� �ϴ� �뵵�� ����մϴ�.

2. coroutine handle. "�ڷ�ƾ �ܺ�"���� ���� �Ǵ� ��ü. �ڷ�ƾ�� resume�ϰų� �ڷ�ƾ �������� ���� �� �� ��� �˴ϴ�.

3. coroutine state. "�� �޸� ����"�� �Ҵ� �Ǵ� �ڷ�ƾ ���¸� ��Ÿ���� ��ü.
coroutine state�� promise ��ü�� ������.
coroutine state�� �ڷ�ƾ �Լ� �Ķ������ ����� ������ ������.
coroutine state�� resume�� ���� ���� �ߴ� ����Ʈ�� destroy�� ���� ���� �������� ������.
���� ������ �ӽ� �������� ���� �ߴ� ����Ʈ���� ��� �ִ� �͵��� �ǹ��Ѵ�
*/
/*
//����Ƽ �ڵ�
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
		if (sort == "black") //�׾�����
		{
			on = deadPanel;
		}
		else //���� ����
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
					//ü���� 3���� �ٽ� ä����
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
		if (sort == "black") //�׾�����
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
			GameObject.FindWithTag("Player").GetComponent<PlayerAction>().waitTime = 0; //�ٽ� ���ӽ����Ҷ� ��ź�� �ٷ� �߻���� �ʵ���
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