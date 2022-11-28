#pragma once
#include <SDLGameObject.h>
#include <Timer.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <coroutine>
#include <exception>
#include <vector>

using namespace std;

//template <class T>
class LerpPanel : public SDLGameObject
{
public:
	struct promise_type;
	//coroutine_trait���ε� ��� ����, �����ڷ�::https://en.cppreference.com/w/cpp/language/coroutines
	struct Coroutine;
	struct Coroutine
	{
		struct promise_type;
		using coro_handle = std::coroutine_handle<promise_type>;
		struct promise_type //��ȯ��, �����Ϸ��� �ش� �ڷ�ƾ�� �۵� ��ų�� ���⼭ ������ �ش� Ŀ���� �ڷ�ƾ �Լ��� �۵���Ŵ
		{
			//�ڷ�ƾ �Լ����� co_yield ȣ���Ҷ� ���� :: ������ �ʿ����
			/*std::suspend_always yield_value(float value)*/
			// suspend_always{} ==> ȣ���ڿ��� ������� �ѱ�
			// suspend_never{} ==> �ѱ��� ����
			//����� ��ȯ ��ü ���� (�ݵ�� ���� ==> �����Ϸ��� �ݵ�� promise_type�� �����ϱ� ������ ������ ���� => ��ȯ���� �Ѱ��ְڴٶ�� ����ؾ���) 
			Coroutine get_return_object() { return Coroutine{ std::coroutine_handle<promise_type>::from_promise(*this) }; } //�̷��� ���� ���� ��ȯ���� �Ѱ��ְڴٰ� ���, ������ �����ϱ� voidŸ������ ���� ����
			auto initial_suspend() { std::cout << "Coroutine_Start\n"; return suspend_never{}; } // �ڷ�ƾ ���� ���� �� ȣ��. awaitable ��ü�� ��ȯ.
			auto return_void() noexcept {} // co_return�� ����Ҷ� ���ϰ��� �ִٸ� �����Ϸ����� �ڵ����� ȣ��, �ݴ� ==> return_value()
			auto final_suspend() noexcept { std::cout << "Coroutine_Done\n"; return suspend_never{}; } // �ڷ�ƾ ���� �� ȣ��. noexcept => �ش� �Լ��� ���ܸ� ȣ������ �ʵ��� ����
			void unhandled_exception() { std::terminate(); } // �ڷ�ƾ ���� �� ���� �߻� �� ȣ��, ���⼱ �����߽��ϴ�

			// std::coroutine_handle<Promise>::done ==> �ڷ�ƾ�� ������ �Ϸ� �Ǹ� true, �ƴϸ� false ����
			// ex )) if (true == range.coroutine.done()) 
		};
	public:
		explicit Coroutine(std::coroutine_handle<promise_type> get) { std::cout << " -------------------- �ڷ�ƾ ������ ȣ�� ---------------------\n";  m_handle = get; }
		~Coroutine() { /*if (m_handle != NULL) { m_handle.destroy(); }  std::cout << ":::Coroutine Destroy:::\n";*/ }
		std::coroutine_handle<promise_type> m_handle;

		bool Done()
		{
			std::cout << "�ּ� : " << m_handle.address() << "\n";
			return m_handle.done();
		}
		void Resume()
		{
			std::cout << "�ڷ�ƾ �簳\n";
			m_handle.resume();
		}
	};
	// ��Ģ 3. std::coroutine_handle<promise_type> �� ���ڷ� �޾�
	// ��� ������ �ʱ�ȭ �ϴ� �����ڰ� �־�� �Ѵ�.
	explicit LerpPanel(const LoaderParams* pParams, float getFadeInTime, float getFateOutTime); //explicit => ������ �ʴ� ����ȯ�� �ȵǰ� ����
	~LerpPanel() {}

	virtual void draw();
	virtual void update();
	virtual void clean() {}

	Coroutine FadeOutIn(float outTime, float inTime) //time default ==> 0.01f
	{
		//FadeOut
		if (outTime != 0)
		{
			while (alpha < 256)
			{
				timer.StartTimer();
				alpha += (Uint32)(timer.getTimer() / (F_time * outTime) * 0.5f);

				co_await std::suspend_always{}; //������� main������ �Ѱ��ݴϴ� (draw�� �۵��Ǿ� �������Ƿ�)
			}
		}
		//FadeIn
		alpha = 256;
		while (alpha > 0)
		{
			timer.StartTimer();
			alpha -= (Uint32)(timer.getTimer() / (F_time * inTime) * 0.5f);

			co_await std::suspend_always{};
		}
		SetActive(false);
	}
private:
	float fadeInTime = 0;
	float fadeOutTime = 0;
	double alpha = 0;
	double F_time = 100;

	Timer timer;
	Coroutine lerp = FadeOutIn(fadeOutTime, fadeInTime);
	SDL_Texture* texture;

	//test
	void LerpTextureLoad();
	void drawImg();
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