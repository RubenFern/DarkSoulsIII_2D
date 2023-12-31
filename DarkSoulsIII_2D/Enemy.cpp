#include "Enemy.h"
#include "GameLayer.h"

Enemy::Enemy(string filename, float x, float y, int width, int height, Game* game)
	: Actor(filename, x, y, width, height, game) 
{
	healthBar = new HealthBar(life, 5, x - 22, y - 34, game);
	vxIntelligence = 1;
}

void Enemy::draw(float scrollX, float scrollY) {
	animation->draw(x - scrollX, y - scrollY);

	healthBar->draw(x - 22 - scrollX, y - 34 - scrollY);
}

void Enemy::impacted(Player* player) {
	// El arma tiene sangrado
	if (player->selectedWeapon->stateBleeding)
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

	if (player->selectedWeapon->stateFreezing)
		freezeTime = FREEZING_TIME;
	else
		freezeTime = 0;

	life -= player->getDamage();

	if (life < 0)
		life = 0;

	healthBar->health = life;

	if (life <= 0)
		state = game->stateDying;
}

void Enemy::update() {
	// Actualizar la animaci�n
	bool endAnimation = animation->update();

	// Acabo la animaci�n, no sabemos cual
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

	// Establecer orientaci�n
	if (vx > 0)
		orientation = game->orientationRight;
	if (vx < 0)
		orientation = game->orientationLeft;
	if (vy > 0)
		orientation = game->orientationDown;
	if (vy < 0)
		orientation = game->orientationUp;

	// Selecci�n de animaci�n basada en estados
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

	move();
}

void Enemy::move()
{
	if (!canViewPlayer())
		return;

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

	// Si el jugador est� fuera del rango de visi�n del arquero
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

	// Si el jugador est� en el rango de visi�n horizontal del arquero
	if (abs(dx) < VISION_FIELD && abs(dx) > ERROR)
	{
		if (dx < 0)
		{
			orientation = game->orientationLeft;
			animation = aRunningLeft;
			vx = vxIntelligence * -1;
		}
		else
		{
			orientation = game->orientationRight;
			animation = aRunningRight;
			vx = vxIntelligence;
		}
	}

	// Si el jugador est� en el rango de visi�n vertical del arquero
	if (abs(dy) < VISION_FIELD && abs(dy) > ERROR)
	{
		if (dy < 0)
		{
			orientation = game->orientationUp;
			animation = aRunningUp;
			vy = vxIntelligence * -1;
		}
		else
		{
			orientation = game->orientationDown;
			animation = aRunningDown;
			vy = vxIntelligence;
		}
	}

	// Si el jugador est� en el rango de ataque del arquero	
	if (abs(dx) < ERROR && abs(dy) < ERROR && abs(dx) > 20 && abs(dy) > 20)
	{
		// Esquina superior izquierda
		if (dx > 20 && dy < -20)
		{
			orientation = game->orientationRight;
			animation = aRunningRight;
			vx = vxIntelligence;
		}
		// Esquina superior derecha
		else if (dx < -20 && dy < -20)
		{
			orientation = game->orientationLeft;
			animation = aRunningLeft;
			vx = vxIntelligence * -1;
		}
		// Esquina inferior izquierda
		else if (dx > 20 && dy > 20)
		{
			orientation = game->orientationRight;
			animation = aRunningRight;
			vx = vxIntelligence;
		}
		// Esquina inferior derecha
		else if (dx < -20 && dy > 20)
		{
			orientation = game->orientationLeft;
			animation = aRunningLeft;
			vx = vxIntelligence * -1;
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

bool Enemy::canViewPlayer()
{
	Point* playerPosition = game->getCurrentPlayerPosition();

	int dx = playerPosition->x - x;
	int dy = playerPosition->y - y;

	if (abs(dx) > VISION_FIELD && abs(dy) > VISION_FIELD)
		return false;

	// Si hay un muro entre el jugador y el enemigo
	GameLayer* gameLayer = static_cast<GameLayer*>(game->gameLayer);

	int numF = 0, numD = 0, numR = 0, numL = 0;

	for (auto const& wall : gameLayer->space->staticActors)
	{
		if (wall->x == x && dy != 0) // Mismo eje X pero posiciones verticales diferentes
		{
			int minY = std::min(y, playerPosition->y);
			int maxY = std::max(y, playerPosition->y);
			if (wall->y > minY && wall->y < maxY)
			{
				return false; // Hay un muro entre el jugador y el enemigo
			}
		}
		else if (wall->y == y && dx != 0) // Mismo eje Y pero posiciones horizontales diferentes
		{
			int minX = std::min(x, playerPosition->x);
			int maxX = std::max(x, playerPosition->x);
			if (wall->x > minX && wall->x < maxX)
			{
				return false; // Hay un muro entre el jugador y el enemigo
			}
		}
	}

	return true;
}