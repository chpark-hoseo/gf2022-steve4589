//복습 / 전처리기 -> 컴퓨터의 처리의 중심적인 처리를 수행하는 부분을 위해 사전 준비적인 계산을 행하는 프로그램. 
/* 활용
내부 소스코드에서 버전관리,
이미 작성된 다른 라이브러리 가져오기
함수정의
상수정의 
*/
//#paragma once -> 맨위에 넣기, #include "SDL2/SDL.h"는 한번만 실행
//#paragma warning(disable : 1351) -> 1351경고 메세지가 안나오게 강제로 출력이 안되게함 
//#paragma warning(disable : 1351) -> 1351경고 메세지를 아예 오류로 만들어, 실행이 안되게함, 치명적일것 같은 경고에 사용

#ifndef __Game__ //중복정의를 피하기 위한 매크로
//반드시 #endif로 끝맺어줘야 함
//비슷하게 생긴 #if, 조건문을 수행하고 이또한 #endif가 필요하다  

#define __Game__ // 여기선, 중복 정의를 막기위해 정의됨 
/*ex) #define PI 3.14 --> PI안에 3.14 숫자가 들어감
  ex) #define SQUARE (x (x * x)) 처럼 함수 매크로로도 사용가능, 그냥 함수처럼 사용 가능
  ex  #define add(x, y) $ 이런식으로도 가능. 이때엔 $로 사용하면 가능*/

//#undef -> 이미 정의된 매크로롤 지움, ex) #undef $ -> 위의 예제 3번 메크로를 없애기. 

#include "SDL2/SDL.h" //파일 처리 전처리기, <>에 적힌 기본적인 라이브러리를 가져오기

class Game
{
public:
	Game() { }
	~Game() { }

	bool init(const char* title, int xpos, int ypos, int width, int height, int flags);
	void render();
	void update();
	bool running();
	void handleEvents();
	void clean();

private:
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	bool m_bRunning;
};
#endif /* defined(__Game__) */