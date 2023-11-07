#pragma once

#include "Game.h"
#include "Audio.h"

class Game;

class Layer
{
public:
	Layer(Game* game);
	virtual void init() {};
	virtual void processControls() {};
	virtual void update() {};
	virtual void draw() {};
	virtual void playMusic() {};

	Game* game;
	Audio* audioBackground;
};