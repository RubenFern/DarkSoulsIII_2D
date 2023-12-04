#pragma once

#include "Game.h"
#include "Actor.h"
#include "Text.h"

class Message
{
public:
	Message(Game* game);
	void update();
	void draw();
	void setMessage(string message, string image, int wImage, int hImage);
	
	int xImage = 0;
	int yImage = 0;
	int xText = 0;
	int yText = 0;
	int lifeTime = 0;

	Game* game;
	Actor* image;
	Text* message;
};
