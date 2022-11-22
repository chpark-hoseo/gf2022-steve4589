#pragma once
#include <coroutine>
#include <iostream>
//참고 자료 : https://zapary.blogspot.com/2020/10/cpp20-coroutine.html
//https://kukuta.tistory.com/222#footnote_link_222_1
using namespace std;

//c++에서의 코루틴은 커스터마이징이 가능하며, 이는 강제됨
class Task_Coroutine // 분석용 코드
{
public:
	struct promise_type;
	using coro_handle = coroutine_handle<promise_type>;
	struct promise_type
	{
		auto initial_suspend() { return suspend_always{}; }

		//사용자 반환 객체 정의 (반드시 정의해야함 :: 컴파일러가 반드시 promise_type을 선언하기 때문에 없으면 반환 못함)
		auto get_return_object() { return Task_Coroutine{ std::coroutine_handle<promise_type>::from_promise(*this) }; } 
		auto initial_suspend() { return suspend_never{}; } // 코루틴 최초 실행 시 호출. awaitable 객체를 반환 한다.
		auto return_void() { return suspend_never{}; } // co_return을 사용하는 경우 구현. 나중에 코루틴 종료를 설명 할 때 같이 설명
		auto final_suspend() { return suspend_always{}; } // 코루틴 종료 시 호출. 나중에 코루틴 종료를 설명 할 때 같이 설명
		void unhandled_exception() { std::terminate(); } // 코루틴 수행 중 예외 발생 시 호출
	};

private: //핸들러 요약 :: 핸들러는 꼭 생성 및 초기화하고 다쓰면 없애기

	// 규칙 4. 소멸자에서 std::coroutine_handle<promise_type> 타입의
	// 코루틴 핸들러 멤버 변수의 destroy를 호출 해야 한다.
	~Task_Coroutine()
	{
		if (true == (bool)m_handle) { m_handle.destroy(); }
	}

	// 규칙 2. std::coroutine_handle<promise_type> 타입의 멤버 변수가 있어야 한다.
	coro_handle m_handle;

	// 규칙 3. std::coroutine_handle<promise_type> 을 인자로 받아
	// 멤버 변수를 초기화 하는 생성자가 있어야 한다.
	explicit Task_Coroutine(coro_handle handle) : m_handle(handle) {}
};

//co_yield -> 호출자로 돌아갈때 반환