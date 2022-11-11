#pragma once
#include <NotePad.h>
#include <NormalButton.h>
#include <PowerNotePadButton.h>
#include <Player.h>

class Command
{
public:
	virtual void execute() = 0;
    virtual void Undo() = 0;
};

class Button //Å° -> 5°³ 
{
private:
    Command* command;

public:
    Button(Command* getCommand)
    {
        SetKeyMode(getCommand);
    }
    void SetKeyMode(Command* getCommand) { command = getCommand; }
    void Pressed()
    {
        command->execute();
    }
    void UnPressed()
    {
        command->Undo();
    }
};
//Main
class NULLCommand : public Command {
public:
    virtual void execute() {}
    virtual void Undo() {}
};
class UpCommand : public Command {
public:
    UpCommand(NormalButton* getNormalButton) { normalButton = getNormalButton; }
    virtual void execute() {
        normalButton->IsPressed(true); 
    }
    virtual void Undo() {
        normalButton->PressOut(false);
    }
private:
    NormalButton* normalButton;
};
class DownCommand : public Command {
public:
    DownCommand(NormalButton* getNormalButton) { normalButton = getNormalButton; }
    virtual void execute() {
        normalButton->IsPressed(true);
    }
    virtual void Undo() {
        normalButton->PressOut(false);
    }
private:
    NormalButton* normalButton;
};
class LeftCommand : public Command {
public:
    LeftCommand(NormalButton* getNormalButton) { normalButton = getNormalButton; }
    virtual void execute() {
    }
    virtual void Undo(){
    }
private :
    NormalButton* normalButton;
};
class RightCommand : public Command {
public:
    RightCommand(NormalButton* getNormalButton) { normalButton = getNormalButton; }
    virtual void execute() {
    }
    virtual void Undo() {
    }
private:
    NormalButton* normalButton;
};
class SpaceCommand : public Command {
public:
    SpaceCommand(NormalButton* getNormalButton) { normalButton = getNormalButton; }
    virtual void execute() {
        normalButton->PressIn(true);
    }
    virtual void Undo() {
        normalButton->PressIn(false);
    }
private:
    NormalButton* normalButton;
};
//Play
class Up_NoteCommand : public Command {
public:
    Up_NoteCommand(NotePad * getNotePad, Player* getPlayer)
    {
        notePad = getNotePad;
        player = getPlayer;
    }
    virtual void execute() {
        notePad->IsPressed(true);
        player->PressIn_Up();
    }
    virtual void Undo(){
        notePad->PressOut(false);
        player->PressOut_Up();
    }
private:
    NotePad* notePad;
    Player* player;
};
class Down_NoteCommand : public Command {
public:
    Down_NoteCommand(NotePad* getNotePad, Player* getPlayer)
    {
        notePad = getNotePad;
        player = getPlayer;
    }
    virtual void execute() {
        notePad->IsPressed(true);
        player->PressIn_Down();
    }
    virtual void Undo() {
        notePad->PressOut(false);
        player->PressOut_Down();
    }
private:
    NotePad* notePad;
    Player* player;
};
class Left_NoteCommand : public Command {
public:
    Left_NoteCommand(NotePad* getNotePad, Player* getPlayer)
    {
        notePad = getNotePad;
        player = getPlayer;
    }
    virtual void execute() {
        notePad->IsPressed(true);
        player->PressIn_Left();
    }
    virtual void Undo() {
        notePad->PressOut(false);
        player->PressOut_Left();
    }
private:
    NotePad* notePad;
    Player* player;
};
class Right_NoteCommand : public Command {
public:
    Right_NoteCommand(NotePad* getNotePad, Player* getPlayer)
    {
        notePad = getNotePad;
        player = getPlayer;
    }
    virtual void execute() {
        notePad->IsPressed(true);
        player->PressIn_Right();
    }
    virtual void Undo() {
        notePad->PressOut(false);
        player->PressOut_Right();
    }
private:
    NotePad* notePad;
    Player* player;
};
class Space_NoteCommand : public Command {
public:
    Space_NoteCommand(PowerNotePadButton* getNotePad, Player* getPlayer)
    {
        notePad = getNotePad;
        player = getPlayer;
    }
    virtual void execute() {
        notePad->IsPressed(true);
        player->PressIn_Space();
    }
    virtual void Undo() {
        notePad->PressOut(false);
        player->PressOut_Space();
    }
private:
    PowerNotePadButton* notePad;
    Player* player;
};