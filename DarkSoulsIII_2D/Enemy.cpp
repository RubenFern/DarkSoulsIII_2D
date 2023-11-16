#include "Enemy.h"

Enemy::Enemy(string filename, float x, float y, int width, int height, Game* game)
	: Actor(filename, x, y, width, height, game) {
}

void Enemy::draw(float scrollX, float scrollY) {
	animation->draw(x - scrollX, y - scrollY);
}

void Enemy::impacted() {
	if (state != game->stateDying) {
		state = game->stateDying;
	}
}

void Enemy::update() {
	// Actualizar la animación
	bool endAnimation = animation->update();

	// Acabo la animación, no sabemos cual
	if (endAnimation) 
	{
		// Estaba muriendo
		if (state == game->stateDying)
			state = game->stateDead;

		// Estaba atacando
		if (state == game->stateAttacking)
			state = game->stateMoving;
	}

	if (state == game->stateDying) {
		animation = aDeath;
	}

	// Establecer orientación
	if (vx > 0)
		orientation = game->orientationRight;
	if (vx < 0)
		orientation = game->orientationLeft;
	if (vy > 0)
		orientation = game->orientationDown;
	if (vy < 0)
		orientation = game->orientationUp;

	// Selección de animación basada en estados
	if (state == game->stateAttacking)
	{
		if (orientation == game->orientationRight)
			animation = aAttackingRight;

		if (orientation == game->orientationLeft)
			animation = aAttackingLeft;

		if (orientation == game->orientationUp)
			animation = aAttackingUp;

		if (orientation == game->orientationDown)
			animation = aAttackingDown;
	}

	if (state == game->stateMoving)
	{
		if (vx != 0)
		{
			if (orientation == game->orientationRight)
				animation = aRunningRight;

			if (orientation == game->orientationLeft)
				animation = aRunningLeft;
		}

		if (vy != 0)
		{
			if (orientation == game->orientationUp)
				animation = aRunningUp;

			if (orientation == game->orientationDown)
				animation = aRunningDown;
		}

		if (vx == 0)
		{
			if (orientation == game->orientationRight)
				animation = aIdleRight;

			if (orientation == game->orientationLeft)
				animation = aIdleLeft;
		}

		if (vy == 0)
		{
			if (orientation == game->orientationUp)
				animation = aIdleUp;

			if (orientation == game->orientationDown)
				animation = aIdleDown;
		}
	}

	if (attackTime > 0)
		attackTime--;
}

void Enemy::move()
{
}

Projectile* Enemy::attack() 
{
	return NULL;
}