#include "Blaidd.h"

Blaidd::Blaidd(float x, float y, Game* game)
	: Enemy("res/actors/bosses/blaidd/idle/down.png", x, y, 35, 45, game)
{
	life = 480;
	damage = 105;
	soulsValue = 5000;
	attackTime = attackCadence;
	orientation = game->orientationDown;
	state = game->stateMoving;
	contactDamage = false;
	attackCadence = ATTACK_CADENCE;
	attackTime = attackCadence;
	
	attacks[0] = new Circular(game);
	selectedAttack = attacks[0];

	aAttackingRight = selectedAttack->aAttackingRight;
	aAttackingLeft = selectedAttack->aAttackingLeft;
	aAttackingUp = selectedAttack->aAttackingUp;
	aAttackingDown = selectedAttack->aAttackingDown;

	aIdleRight = new Animation("res/actors/bosses/blaidd/idle/right.png", 38, 54, 38, 54, 6, 1, true, game);
	aIdleLeft = new Animation("res/actors/bosses/blaidd/idle/left.png", 38, 53, 38, 53, 6, 1, true, game);
	aIdleUp = new Animation("res/actors/bosses/blaidd/idle/up.png", 39, 45, 39, 45, 6, 1, true, game);
	aIdleDown = new Animation("res/actors/bosses/blaidd/idle/down.png", 35, 45, 35, 45, 6, 1, true, game);

	aRunningRight = new Animation("res/actors/bosses/blaidd/walk/right.png", 46, 54, 414, 54, 3, 9, true, game);
	aRunningLeft = new Animation("res/actors/bosses/blaidd/walk/left.png", 46, 53, 414, 53, 3, 9, true, game);
	aRunningUp = new Animation("res/actors/bosses/blaidd/walk/up.png", 39, 56, 351, 56, 3, 9, true, game);
	aRunningDown = new Animation("res/actors/bosses/blaidd/walk/down.png", 35, 45, 315, 45, 3, 9, true, game);

	aDeath = new Animation("res/actors/bosses/blaidd/death/death.png", 40, 46, 240, 46, 6, 6, false, game);

	//healthBar = new HealthBar(life, 5, x - 22, y - 34, game);

	vx = 0;
	vxIntelligence = 2;
	animation = aIdleDown;
}

void Blaidd::update()
{
	Enemy::update();
	timeChangeAttack--;

	if (timeChangeAttack == 0)
		changeAttack();
}

Projectile* Blaidd::attack()
{
	Point* playerPosition = game->getCurrentPlayerPosition();

	int dx = playerPosition->x - x;
	int dy = playerPosition->y - y;

	if (state != game->stateDying && state != game->stateDead && attackTime == 0 && abs(dx) < ATTACK_DISTANCE && abs(dy) < ATTACK_DISTANCE)
	{
		vx = 0, vy = 0;
		aAttackingLeft->currentFrame = 0; //"Rebobinar" animaci�n
		aAttackingRight->currentFrame = 0; //"Rebobinar" animaci�n
		aAttackingUp->currentFrame = 0; //"Rebobinar" animaci�n
		aAttackingDown->currentFrame = 0; //"Rebobinar" animaci�n

		attackTime = attackCadence;
		state = game->stateAttacking;

		return selectedAttack->attack(x, y, orientation);
	}

	return NULL;
}

void Blaidd::changeAttack()
{
	timeChangeAttack = TIME_CHANGE_ATTACK;
	srand(time(0));
	//selectedAttack = attacks[rand() % 3];
	selectedAttack = attacks[0];

	aAttackingRight = selectedAttack->aAttackingRight;
	aAttackingLeft = selectedAttack->aAttackingLeft;
	aAttackingUp = selectedAttack->aAttackingUp;
	aAttackingDown = selectedAttack->aAttackingDown;
}