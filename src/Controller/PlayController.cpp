#include <PlayController.h>
#include <InputHandler.h>
/*
void PlayController::handleInput()
{
    //Command Pattern
    //SetCommand(NoteInput)
    Input_Note();
}
void PlayController::Input_Note()
{
    //KeyUp
    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT)) {
        notePad->IsPressed(true);
    }
    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT)) {
       notePad1->IsPressed(true);
    }
    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP)) {
        notePad2->IsPressed(true);
    }
    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN)) {
        notePad3->IsPressed(true);
    }
    //KeyUp
    /*
    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT)) {
        notePad->Pushed(false);
    }
    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT)) {
        notePad1->Pushed(false);
    }
    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP)) {
        notePad2->Pushed(false);
    }
    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN)) {
        notePad3->Pushed(false);
    }
}*/