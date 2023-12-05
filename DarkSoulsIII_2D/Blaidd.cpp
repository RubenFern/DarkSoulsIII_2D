#include "Blaidd.h"
#include "GameLayer.h"

Blaidd::Blaidd(float x, float y, Game* game)
	: Enemy("res/actors/bosses/blaidd/idle/down.png", x, y, 35, 45, game)
{
	life = 480;
	soulsValue = 5000;
	attackTime = attackCadence;
	orientation = game->orientationDown;
	state = game->stateMoving;
	contactDamage = false;
	attackTime = attackCadence;
	
	attacks[0] = new Circular(game);
	attacks[1] = new Thrust(game);
	attacks[2] = new Magic(game);
	selectedAttack = attacks[0];
	damage = selectedAttack->damage;
	attackCadence = selectedAttack->cadence;

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

	healthBar = new HealthBar(life, 20, WIDTH * 0.2, HEIGHT * 0.91, game);

	vx = 0;
	vxIntelligence = 2;
	animation = aIdleDown;
}

void Blaidd::update()
{
	Enemy::update();
	timeChangeAttack--;

	if (life <= 0)
		static_cast<GameLayer*>(game->gameLayer)->playerWin = true;

	if (timeChangeAttack == 0)
		changeAttack();
}

Projectile* Blaidd::attack()
{
	if (!canViewPlayer())
		return NULL;

	Point* playerPosition = game->getCurrentPlayerPosition();

	int dx = playerPosition->x - x;
	int dy = playerPosition->y - y;

	if (state != game->stateDying && state != game->stateDead && attackTime == 0 
		&& abs(dx) < selectedAttack->distanceAttack && abs(dy) < selectedAttack->distanceAttack)
	{
		vx = 0, vy = 0;
		aAttackingLeft->currentFrame = 0; //"Rebobinar" animación
		aAttackingRight->currentFrame = 0; //"Rebobinar" animación
		aAttackingUp->currentFrame = 0; //"Rebobinar" animación
		aAttackingDown->currentFrame = 0; //"Rebobinar" animación

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
	selectedAttack = attacks[rand() % 3];
	damage = selectedAttack->damage;
	attackCadence = selectedAttack->cadence;

	aAttackingRight = selectedAttack->aAttackingRight;
	aAttackingLeft = selectedAttack->aAttackingLeft;
	aAttackingUp = selectedAttack->aAttackingUp;
	aAttackingDown = selectedAttack->aAttackingDown;
}

void Blaidd::draw(float scrollX, float scrollY)
{
	animation->draw(x - scrollX, y - scrollY);
	
	healthBar->draw(healthBar->x, healthBar->y);
}