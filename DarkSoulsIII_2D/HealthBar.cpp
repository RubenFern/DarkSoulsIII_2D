#include "HealthBar.h"

HealthBar::HealthBar(int health, int height, float x, float y, Game* game)
{
	this->health = health;
	this->x = x;
	this->y = y;
	this->height = height;
	this->game = game;
}

void HealthBar::draw()
{
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = health;
	rect.h = height;

	SDL_SetRenderDrawColor(game->renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(game->renderer, &rect);
}