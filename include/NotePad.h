#pragma once
#include <SDLGameObject.h>

//need for A+_notesPad
class NotePad : public SDLGameObject
{
private:
	NotePad(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean() {}
public:
	//Basic NotesPad
	SDLGameObject* notePad = new NotePad(new LoaderParams(0, 0, 96, 96, 0, 0, "notesPad_sprite"));
	SDLGameObject* notePad1 = new NotePad(new LoaderParams(0, 0, 96, 96, 0, 0, "notesPad_sprite"));
	SDLGameObject* notePad2 = new NotePad(new LoaderParams(0, 0, 96, 96, 0, 0, "notesPad_sprite"));
	SDLGameObject* notePad3 = new NotePad(new LoaderParams(0, 0, 96, 96, 0, 0, "notesPad_sprite"));
	//SpecialNotesPad
	//SDLGameObject* notePad4 = new NotePad(new LoaderParams(0, 0, 192, 192, 0, 0, "specialNotesPad_sprite"));
};