#include <LerpPanel.h>
#include <CustomPhysics.h>

LerpPanel::LerpPanel(const LoaderParams* pParams, coro_handle handle) : SDLGameObject(pParams), m_handle(handle) 
{
	get_pParams = pParams;
	//m_handle = Fadeout();
}

void LerpPanel::draw()
{
	if (!onOff) return;
	SDLGameObject::draw();
}

void LerpPanel::update()
{
	if (!onOff) return;
	std::cout << timer.getTimer() << "\n";
	//if (m_handle.done() == false) { std::cout << "코루틴 실행중...\n"; coroutine_handle<P>::resume(); }
	std::cout << "resume test\n";
	timer.StartTimer();
}