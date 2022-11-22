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
	struct promise_type;
	using coro_handle = std::coroutine_handle<promise_type>;

	//coroutine_trait으로도 약속 가능, 참고자료::https://en.cppreference.com/w/cpp/language/coroutines
	struct promise_type //반환형, 컴파일러가 해당 코루틴을 작동 시킬때 여기서 정의한 해당 커스텀 코루틴 함수를 작동시킴
	{
		float value = 0;

		std::suspend_always yield_value(float value)
		{
			this->value = value;
			return {};
			//return std::suspend_always{};
		}

		//사용자 반환 객체 정의 (반드시 정의 ==> 컴파일러가 반드시 promise_type을 선언하기 때문에 없으면 오류 => 반환값을 넘겨주겠다라고 약속해야함) 
		auto get_return_object() { return LerpPanel{ NULL, coro_handle::from_promise(*this) }; } //미래에 여기 적힌 반환값(LerpPanel)을 넘겨주겠다고 약속
		auto initial_suspend() { return suspend_never{}; } // 코루틴 최초 실행 시 호출. awaitable 객체를 반환.
		auto return_void() noexcept {} // co_return을 사용할때 리턴값이 있다면 컴파일러에서 자동으로 호출, 반대 ==> return_value()
		auto final_suspend() noexcept { return suspend_always{}; } // 코루틴 종료 시 호출. noexcept => 해당 함수는 예외를 호출하지 않도록 설정
		void unhandled_exception() { std::terminate(); } // 코루틴 실행 중 예외 발생 시 호출, 여기선 사용안했습니다

		// std::coroutine_handle<Promise>::done ==> 코루틴의 수행이 완료 되면 true, 아니면 false 리턴
		// ex )) if (true == range.coroutine.done()) 
	};
	// 규칙 3. std::coroutine_handle<promise_type> 을 인자로 받아
	// 멤버 변수를 초기화 하는 생성자가 있어야 한다.
	explicit LerpPanel(const LoaderParams* pParams, coro_handle handle); //explicit => 원하지 않는 형변환이 안되게 제어

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

		promise.get_return_object();
		promise.initial_suspend();

		SetActive(true);

		alpha = 0;
		timer.WaitTime();

		while (alpha < 1)
		{
			timer.StartTimer();
			alpha += timer.getTimer() / (F_time * 0.1f);
			//SDL_SetAlpha(surface, SDL_RLEACCEL | SDL_SRCALPHA, (Uint8)alpha);
			//SDL_BlitSurface(surface, NULL, screen, NULL);
			std::cout << alpha << "\n";
			co_await std::suspend_always{};
			//co_yield 0/*NULL*/; //update문을 작동시키기 위해 
		}
		//SDL_SetAlpha(surface, SDL_RLEACCEL | SDL_SRCALPHA, (Uint8)1);

		//SetActive(false);
		
		co_return;
	}
private: //핸들러 요약 :: 핸들러는 꼭 생성 및 초기화하고 다쓰면 없애기

// 규칙 4. 소멸자에서 std::coroutine_handle<promise_type> 타입의
// 코루틴 핸들러 멤버 변수의 destroy를 호출 해야 한다.
	~LerpPanel()
	{
		if (true == (bool)m_handle) { m_handle.destroy(); }
	}

	// 규칙 2. std::coroutine_handle<promise_type> 타입의 멤버 변수가 있어야 한다.
	coro_handle m_handle;

	Timer timer;

	double alpha;
	double F_time = 10; //기본값 : 10
	//LerpPanel::promise_type promise;
};
//코루틴 참고 자료 :: https://luncliff.github.io/coroutine/ppt/[Kor]ExploringTheCppCoroutine.pdf
//https://kukuta.tistory.com/222
/*코루틴 기본 노트::
* 호출 : 루틴의 시작점으로 점프
* 활성화 : 루틴안의 임시지점으로 점프  co_return
* 중단 : 루틴을 중단하지 않고 다른 루틴의 지점으로 점프  co_await, co_yield
		 co_await() -> 실행 중인 함수를 멈추고 실행 제어권을 코루틴을 호출한 쪽으로 넘김. 그리고 제어권을 받아 재실행될때 이 문장 이후부터를 이어서 실행
* 종결 : 루틴의 끝에 도달한 후 루틴 상태의 소멸 및 정리  co_return
* 재개 : coro.resume() // coroutine_handle<P>::resume()
*
서브 루틴 : 호출 / 종결 할 수 있는 루틴 :: Finalize (Return / 루틴(Caller) -> 서브 루틴), Invoke (Call / 서브 루틴 -> 루틴(Caller))
//흔히 보는 call, return도 코루틴 (함수들은 코루틴)

프로세스 : Os에서 프로그램(루틴의 집합체)을 실행하는 방법
스레드 : 프레세스 내의 제어 흐름 (프로세서 CPU) 을 형상화한거

코루틴 : 호출 / 활성화 / 중단/ 종결 할 수 있는 루틴  (서브 루틴 확장판 같은 개념)

개념적으로 스레드(프로그래밍 언어 :: Function)와 코루틴(머신 :: Coroutine, SubRoutine)는 비슷해보이지만 서로 무관
스레드 => 여러개의 스레드가 작업을 나눠서 함 => 비동기 작동방식, 잠깐 사용할때 비효율 적이지만, 처음부터 끝까지 책임져야 한다면 코루틴 상위호환(SDL에서 비디오의 깜빡임을 보충하는 역할)
코루틴 => 한개의 스레드에서 작업을 잘게 나눠서 함 => 비동기X, 잠깐씩 사용할때 좋음, 스레드보다 가벼움, 공유자원에서 동기화오류가 생기지 않음, 너무 자주 사용되면 스레드 하위호환

StackFullCoroutine -> 코루틴의 프레임을 스택에
StackLessCoroutine -> 코루틴의 프레임을 스택바깥에 (동적 으로)

다음 함수중 하나라도 있어야 되고, 있다면 그 함수는 코루틴으로 처리
 co_await expression
 co_yield expression
 co_return statement
 for co_await statement

코루틴 반환 객체 ::
1. promise. "코루틴 내부"에서 관리 되는 객체. 코루틴의 결과나 예외를 이 객체를 통해 호출자에게 전달 하는 용도로 사용합니다.

2. coroutine handle. "코루틴 외부"에서 관리 되는 객체. 코루틴을 resume하거나 코루틴 프레임을 제거 할 때 사용 됩니다.

3. coroutine state. "힙 메모리 영역"에 할당 되는 코루틴 상태를 나타내는 객체.
coroutine state는 promise 객체를 가진다.
coroutine state는 코루틴 함수 파라메터의 복사된 값들을 가진다.
coroutine state는 resume을 위한 현재 중단 포인트와 destroy를 위한 지역 변수들을 가진다.
지역 변수와 임시 변수들은 현재 중단 포인트에서 살아 있는 것들을 의미한다
*/
/*
//유니티 코드
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