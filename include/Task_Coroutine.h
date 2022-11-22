#pragma once
#include <coroutine>
#include <iostream>
//���� �ڷ� : https://zapary.blogspot.com/2020/10/cpp20-coroutine.html
//https://kukuta.tistory.com/222#footnote_link_222_1
using namespace std;

//c++������ �ڷ�ƾ�� Ŀ���͸���¡�� �����ϸ�, �̴� ������
class Task_Coroutine // �м��� �ڵ�
{
public:
	struct promise_type;
	using coro_handle = coroutine_handle<promise_type>;
	struct promise_type
	{
		auto initial_suspend() { return suspend_always{}; }

		//����� ��ȯ ��ü ���� (�ݵ�� �����ؾ��� :: �����Ϸ��� �ݵ�� promise_type�� �����ϱ� ������ ������ ��ȯ ����)
		auto get_return_object() { return Task_Coroutine{ std::coroutine_handle<promise_type>::from_promise(*this) }; } 
		auto initial_suspend() { return suspend_never{}; } // �ڷ�ƾ ���� ���� �� ȣ��. awaitable ��ü�� ��ȯ �Ѵ�.
		auto return_void() { return suspend_never{}; } // co_return�� ����ϴ� ��� ����. ���߿� �ڷ�ƾ ���Ḧ ���� �� �� ���� ����
		auto final_suspend() { return suspend_always{}; } // �ڷ�ƾ ���� �� ȣ��. ���߿� �ڷ�ƾ ���Ḧ ���� �� �� ���� ����
		void unhandled_exception() { std::terminate(); } // �ڷ�ƾ ���� �� ���� �߻� �� ȣ��
	};

private: //�ڵ鷯 ��� :: �ڵ鷯�� �� ���� �� �ʱ�ȭ�ϰ� �پ��� ���ֱ�

	// ��Ģ 4. �Ҹ��ڿ��� std::coroutine_handle<promise_type> Ÿ����
	// �ڷ�ƾ �ڵ鷯 ��� ������ destroy�� ȣ�� �ؾ� �Ѵ�.
	~Task_Coroutine()
	{
		if (true == (bool)m_handle) { m_handle.destroy(); }
	}

	// ��Ģ 2. std::coroutine_handle<promise_type> Ÿ���� ��� ������ �־�� �Ѵ�.
	coro_handle m_handle;

	// ��Ģ 3. std::coroutine_handle<promise_type> �� ���ڷ� �޾�
	// ��� ������ �ʱ�ȭ �ϴ� �����ڰ� �־�� �Ѵ�.
	explicit Task_Coroutine(coro_handle handle) : m_handle(handle) {}
};

//co_yield -> ȣ���ڷ� ���ư��� ��ȯ