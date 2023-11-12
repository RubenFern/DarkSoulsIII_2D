#include "Archer.h"

Archer::Archer(float x, float y, Game* game) 
	: Enemy("res/actors/archer/idle/down.png", x, y, 34, 53, game) 
{
	life = 1;
	orientation = game->orientationDown;
	state = game->stateMoving;

	aAttackingRight = new Animation("res/actors/archer/attack/right.png", WIDTH_ATTACK_L_R, HEIGHT_ATTACK_L_R, 663, 60, 4, 13, false, game);
	aAttackingLeft = new Animation("res/actors/archer/attack/left.png", WIDTH_ATTACK_L_R, HEIGHT_ATTACK_L_R, 663, 60, 4, 13, false, game);
	aAttackingUp = new Animation("res/actors/archer/attack/up.png", WIDTH_ATTACK_U, HEIGHT_ATTACK_U, 533, 61, 4, 13, false, game);
	aAttackingDown = new Animation("res/actors/archer/attack/down.png", WIDTH_ATTACK_D, HEIGHT_ATTACK_D, 520, 54, 4, 13, false, game);

	aIdleRight = new Animation("res/actors/archer/idle/right.png", WIDTH_IDLE_U_L_R, HEIGHT_IDLE_U_L_R, WIDTH_IDLE_U_L_R, HEIGHT_IDLE_U_L_R, 6, 1, true, game);
	aIdleLeft = new Animation("res/actors/archer/idle/left.png", WIDTH_IDLE_U_L_R, HEIGHT_IDLE_U_L_R, WIDTH_IDLE_U_L_R, HEIGHT_IDLE_U_L_R, 6, 1, true, game);
	aIdleUp = new Animation("res/actors/archer/idle/up.png", WIDTH_IDLE_U_L_R, HEIGHT_IDLE_U_L_R, WIDTH_IDLE_U_L_R, HEIGHT_IDLE_U_L_R, 6, 1, true, game);
	aIdleDown = new Animation("res/actors/archer/idle/down.png", WIDTH_IDLE_D, HEIGHT_IDLE_D, WIDTH_IDLE_D, HEIGHT_IDLE_D, 6, 1, true, game);

	aRunningRight = new Animation("res/actors/archer/walk/right.png", WIDTH_WALK_L_R, HEIGHT_WALK_L_R, 459, 54, 3, 9, true, game);
	aRunningLeft = new Animation("res/actors/archer/walk/left.png", WIDTH_WALK_L_R, HEIGHT_WALK_L_R, 459, 54, 3, 9, true, game);
	aRunningUp = new Animation("res/actors/archer/walk/up.png", WIDTH_WALK_U, HEIGHT_WALK_U, 504, 54, 3, 9, true, game);
	aRunningDown = new Animation("res/actors/archer/walk/down.png", WIDTH_WALK_D, HEIGHT_WALK_D, 405, 54, 3, 9, true, game);

	aDeath = new Animation("res/actors/archer/death/death.png", WIDTH_DEATH, HEIGHT_DEATH, 246, 54, 6, 6, false, game);

	vx = 0;
	vxIntelligence = 0;
	vx = vxIntelligence;
	animation = aIdleDown;
}

void Archer::update() 
{
	Enemy::update();

	Point* playerPosition = game->getCurrentPlayerPosition();

	if (abs(playerPosition->x - x) < VISION_FIELD && abs(playerPosition->x - x) > 10)
	{
		if (playerPosition->x - x < 0)
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
	else
		vx = 0;

	if (abs(playerPosition->y - y) < VISION_FIELD && abs(playerPosition->y - y) > 10)
	{
		if (playerPosition->y - y < 0)
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
	else
		vy = 0;
}

Projectile* Archer::attack()
{
	Point* playerPosition = game->getCurrentPlayerPosition();

	if (attackTime == 0 && (playerPosition->x - x < VISION_FIELD && playerPosition->y - y < VISION_FIELD))
	{
		vx = 0, vy = 0;
		aAttackingLeft->currentFrame = 0; //"Rebobinar" animación
		aAttackingRight->currentFrame = 0; //"Rebobinar" animación
		aAttackingUp->currentFrame = 0; //"Rebobinar" animación
		aAttackingDown->currentFrame = 0; //"Rebobinar" animación

		attackTime = attackCadence;

		string arrowPath = "";
		int width = 0, height = 0, vx = 0, vy = 0;

		int dx = playerPosition->x - x;
		int dy = playerPosition->y - y;

		if (dx < -ERROR) 
		{
			orientation = game->orientationLeft;
			animation = aAttackingLeft;

			if (dy < -ERROR)
				arrowPath = "left_up.png", width = 40, height = 40, vx = -6, vy = -6;
			else if (dy > ERROR)
				arrowPath = "down_left.png", width = 40, height = 40, vx = -6, vy = 6;
			else
				arrowPath = "left.png", width = 40, height = 10, vx = -6;
		}
		else if (dx > ERROR) 
		{
			orientation = game->orientationRight;
			animation = aAttackingRight;

			if (dy < -ERROR)
				arrowPath = "up_right.png", width = 40, height = 40, vx = 6, vy = -6;
			else if (dy > ERROR)
				arrowPath = "right_down.png", width = 40, height = 40, vx = 6, vy = 6;
			else
				arrowPath = "right.png", width = 40, height = 10, vx = 6;
		}
		else 
		{
			// El jugador está en la misma columna que el arquero
			if (dy < -ERROR) {
				orientation = game->orientationUp;
				animation = aAttackingUp;
				arrowPath = "up.png", width = 10, height = 40, vy = -6;
			}
			else if (dy > ERROR) {
				orientation = game->orientationDown;
				animation = aAttackingDown;
				arrowPath = "down.png", width = 10, height = 40, vy = 6;
			}
		}

		Projectile* arrow = new Arrow(arrowPath, x, y, width, height, game);

		arrow->vx = vx;
		arrow->vy = vy;

		return arrow;
	}
	else {
		return NULL;
	}
}

void Archer::draw(float scrollX, float scrollY)
{
	Enemy::draw(scrollX, scrollY);
}

void Archer::impacted() {}