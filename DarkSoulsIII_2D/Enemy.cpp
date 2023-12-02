#include "Enemy.h"

Enemy::Enemy(string filename, float x, float y, int width, int height, Game* game)
	: Actor(filename, x, y, width, height, game) 
{
	healthBar = new HealthBar(life, 5, x - 22, y - 34, game);
}

void Enemy::draw(float scrollX, float scrollY) {
	animation->draw(x - scrollX, y - scrollY);

	healthBar->draw(x - 22 - scrollX, y - 34 - scrollY);
}

void Enemy::impacted(Weapon* weapon) {
	// El arma tiene sangrado
	if (weapon->stateBleeding)
	{
		numberOfImpacts++;

		if (numberOfImpacts == IMPACTS_TO_BLEEDING)
		{
			numberOfImpacts = 0;
			life -= 130;
		}
	}
	else
		numberOfImpacts = 0;

	if (weapon->stateFreezing)
		freezeTime = FREEZING_TIME;
	else
		freezeTime = 0;

	life -= weapon->damage;

	if (life < 0)
		life = 0;

	healthBar->health = life;

	if (life <= 0)
		state = game->stateDying;
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

	if (freezeTime > 0)
		freezeTime--;

	cout << freezeTime << endl;
	move();
}

void Enemy::move()
{
	if (freezeTime > 0)
		return;

	if (state == game->stateDying || state == game->stateAttacking)
	{
		vx = 0;
		vy = 0;
		return;
	}

	Point* playerPosition = game->getCurrentPlayerPosition();

	int dx = playerPosition->x - x;
	int dy = playerPosition->y - y;

	// Si el jugador está fuera del rango de visión del arquero
	if (abs(dx) > VISION_FIELD || abs(dy) > VISION_FIELD)
	{
		vx = 0;
		vy = 0;

		if (dx > 0)
		{
			orientation = game->orientationLeft;
			animation = aIdleLeft;
		}
		else if (dx < 0)
		{
			orientation = game->orientationRight;
			animation = aIdleRight;
		}
		else if (dy > 0)
		{
			orientation = game->orientationUp;
			animation = aIdleUp;
		}
		else if (dy < 0)
		{
			orientation = game->orientationDown;
			animation = aIdleDown;
		}

		return;
	}

	// Si el jugador está en el rango de visión horizontal del arquero
	if (abs(dx) < VISION_FIELD && abs(dx) > ERROR)
	{
		if (dx < 0)
		{
			orientation = game->orientationLeft;
			animation = aRunningLeft;
			vx = -1;
		}
		else
		{
			orientation = game->orientationRight;
			animation = aRunningRight;
			vx = 1;
		}
	}

	// Si el jugador está en el rango de visión vertical del arquero
	if (abs(dy) < VISION_FIELD && abs(dy) > ERROR)
	{
		if (dy < 0)
		{
			orientation = game->orientationUp;
			animation = aRunningUp;
			vy = -1;
		}
		else
		{
			orientation = game->orientationDown;
			animation = aRunningDown;
			vy = 1;
		}
	}

	// Si el jugador está en el rango de ataque del arquero	
	if (abs(dx) < ERROR && abs(dy) < ERROR && abs(dx) > 20 && abs(dy) > 20)
	{
		// Esquina superior izquierda
		if (dx > 20 && dy < -20)
		{
			orientation = game->orientationRight;
			animation = aRunningRight;
			vx = 1;
		}
		// Esquina superior derecha
		else if (dx < -20 && dy < -20)
		{
			orientation = game->orientationLeft;
			animation = aRunningLeft;
			vx = -1;
		}
		// Esquina inferior izquierda
		else if (dx > 20 && dy > 20)
		{
			orientation = game->orientationRight;
			animation = aRunningRight;
			vx = 1;
		}
		// Esquina inferior derecha
		else if (dx < -20 && dy > 20)
		{
			orientation = game->orientationLeft;
			animation = aRunningLeft;
			vx = -1;
		}
		else
		{
			if (vx > 0)
			{
				orientation = game->orientationLeft;
				animation = aIdleLeft;
			}
			else if (vx < 0)
			{
				orientation = game->orientationRight;
				animation = aIdleRight;
			}
			else if (vy > 0)
			{
				orientation = game->orientationUp;
				animation = aIdleUp;
			}
			else if (vy < 0)
			{
				orientation = game->orientationDown;
				animation = aIdleDown;
			}

			vx = 0;
			vy = 0;
		}
	}
}

Projectile* Enemy::attack() 
{
	return NULL;
}