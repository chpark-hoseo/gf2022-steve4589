//���� / ��ó���� -> ��ǻ���� ó���� �߽����� ó���� �����ϴ� �κ��� ���� ���� �غ����� ����� ���ϴ� ���α׷�. 
/* Ȱ��
���� �ҽ��ڵ忡�� ��������,
�̹� �ۼ��� �ٸ� ���̺귯�� ��������
�Լ�����
������� 
*/
//#paragma once -> ������ �ֱ�, #include "SDL2/SDL.h"�� �ѹ��� ����
//#paragma warning(disable : 1351) -> 1351��� �޼����� �ȳ����� ������ ����� �ȵǰ��� 
//#paragma warning(disable : 1351) -> 1351��� �޼����� �ƿ� ������ �����, ������ �ȵǰ���, ġ�����ϰ� ���� ��� ���

#ifndef __Game__ //�ߺ����Ǹ� ���ϱ� ���� ��ũ��
//�ݵ�� #endif�� ���ξ���� ��
//����ϰ� ���� #if, ���ǹ��� �����ϰ� �̶��� #endif�� �ʿ��ϴ�  

#define __Game__ // ���⼱, �ߺ� ���Ǹ� �������� ���ǵ� 
/*ex) #define PI 3.14 --> PI�ȿ� 3.14 ���ڰ� ��
  ex) #define SQUARE (x (x * x)) ó�� �Լ� ��ũ�ηε� ��밡��, �׳� �Լ�ó�� ��� ����
  ex  #define add(x, y) $ �̷������ε� ����. �̶��� $�� ����ϸ� ����*/

//#undef -> �̹� ���ǵ� ��ũ�η� ����, ex) #undef $ -> ���� ���� 3�� ��ũ�θ� ���ֱ�. 

#include "SDL2/SDL.h" //���� ó�� ��ó����, <>�� ���� �⺻���� ���̺귯���� ��������

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