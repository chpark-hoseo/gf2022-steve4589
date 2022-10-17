#pragma once
#include <NotePad.h>
class PlayController
{
public:
	PlayController()
	{
		notePad->SetPosition(Vector2D(1024 * 0.5f - 200, 450));
		notePad1->SetPosition(Vector2D(1024 * 0.5f - 100, 450));
		notePad2->SetPosition(Vector2D(1024 * 0.5f, 450));
		notePad3->SetPosition(Vector2D(1024 * 0.5f + 100, 450));
	}
	~PlayController() {}

	SDLGameObject* InItNotes(int i) { return notePads[i]; };
	//Use CommanPattern (³ªÁß¿¡)
	void handleInput();
	void Input_Note();
	void Input_Menu() {}

private:
	SDLGameObject* notePads[4] = { notePad , notePad1 , notePad2 , notePad3 };
	SDLGameObject* notePad = new NotePad(new LoaderParams(0, 0, 96, 96, 0, 0, "notesPad_sprite"));
	SDLGameObject* notePad1 = new NotePad(new LoaderParams(0, 0, 96, 96, 0, 1, "notesPad_sprite"));
	SDLGameObject* notePad2 = new NotePad(new LoaderParams(0, 0, 96, 96, 0, 2, "notesPad_sprite"));
	SDLGameObject* notePad3 = new NotePad(new LoaderParams(0, 0, 96, 96, 0, 3, "notesPad_sprite"));
};