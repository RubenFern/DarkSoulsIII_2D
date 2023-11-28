#include "HealthBar.h"

HealthBar::HealthBar(int health, float x, float y, Game* game) 
{
	this->health = health;
	this->x = x;
	this->y = y;
	this->game = game;
}

void HealthBar::draw()
{
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = health;
	rect.h = 20;

	SDL_SetRenderDrawColor(game->renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(game->renderer, &rect);

	rect.w = (int)((float)health / 100.0f * (float)width);
	SDL_SetRenderDrawColor(game->renderer, 0, 255, 0, 255);
	SDL_RenderFillRect(game->renderer, &rect);
}