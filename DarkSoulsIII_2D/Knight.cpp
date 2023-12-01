#include "Knight.h"

Knight::Knight(float x, float y, Game* game)
	: Enemy("res/actors/knight/idle/down.png", x, y, 41, 58, game)
{
	life = 70;
	damage = 45;
	orientation = game->orientationDown;
	state = game->stateMoving;
	contactDamage = false;

	aAttackingRight = new Animation("res/actors/knight/attack/right.png", WIDTH_ATTACK_R, HEIGHT_ATTACK_R, 515, 57, 4, 5, false, game);
	aAttackingLeft = new Animation("res/actors/knight/attack/left.png", WIDTH_ATTACK_L, HEIGHT_ATTACK_L, 520, 60, 4, 5, false, game);
	aAttackingUp = new Animation("res/actors/knight/attack/up.png", WIDTH_ATTACK_U, HEIGHT_ATTACK_U, 415, 70, 4, 5, false, game);
	aAttackingDown = new Animation("res/actors/knight/attack/down.png", WIDTH_ATTACK_D, HEIGHT_ATTACK_D, 414, 76, 4, 5, false, game);

	aIdleRight = new Animation("res/actors/knight/idle/right.png", 41, 58, 41, 58, 6, 1, true, game);
	aIdleLeft = new Animation("res/actors/knight/idle/left.png", 41, 58, 41, 58, 6, 1, true, game);
	aIdleUp = new Animation("res/actors/knight/idle/up.png", 41, 58, 41, 58, 6, 1, true, game);
	aIdleDown = new Animation("res/actors/knight/idle/down.png", 41, 58, 41, 58, 6, 1, true, game);

	aRunningRight = new Animation("res/actors/knight/walk/right.png", WIDTH_WALK_L_R, HEIGHT_WALK_L_R_U_D, 477, 58, 3, 9, true, game);
	aRunningLeft = new Animation("res/actors/knight/walk/left.png", WIDTH_WALK_L_R, HEIGHT_WALK_L_R_U_D, 477, 58, 3, 9, true, game);
	aRunningUp = new Animation("res/actors/knight/walk/up.png", WIDTH_WALK_U, HEIGHT_WALK_L_R_U_D, 406, 58, 3, 9, true, game);
	aRunningDown = new Animation("res/actors/knight/walk/down.png", WIDTH_WALK_D, HEIGHT_WALK_L_R_U_D, 369, 58, 3, 9, true, game);

	aDeath = new Animation("res/actors/knight/death/death.png", WIDTH_DEATH, HEIGHT_DEATH, 294, 57, 6, 6, false, game);

	healthBar = new HealthBar(life, 5, x - 22, y - 34, game);

	vx = 0;
	vxIntelligence = 0;
	vx = vxIntelligence;
	animation = aIdleDown;
}

Projectile* Knight::attack()
{
	return nullptr;
}

