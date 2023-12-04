#include "Message.h"

Message::Message(Game* game)
{
	xImage = WIDTH * 0.78;
	yImage = HEIGHT * 0.05;
	xText = WIDTH * 0.9;
	yText = HEIGHT * 0.05;

	this->game = game;
	message = new Text("", xText, yText, game);
	image = NULL;
}

void Message::update()
{
	if (lifeTime > 0)
		lifeTime--;

	if (lifeTime == 0)
		image = NULL;
}

void Message::draw()
{
	if (lifeTime > 0)
	{
		SDL_Rect rect;
		rect.x = xImage - 20;
		rect.y = yImage - 15;
		rect.w = 250;
		rect.h = 30;

		SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 0);
		SDL_RenderFillRect(game->renderer, &rect);

		if (image != NULL)
			image->draw();
		message->draw();
	}
}

void Message::setMessage(string message, string image, int wImage, int hImage)
{
	this->image = new Actor(image, xImage, yImage,wImage, hImage, game);
	this->message->content = message;

	lifeTime = 80;
}