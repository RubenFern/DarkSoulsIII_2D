#include "Archer.h"

Archer::Archer(float x, float y, Game* game) 
	: Enemy("res/actors/archer/idle/down.png", x, y, 34, 53, game) 
{
	life = 1;
	orientation = game->orientationDown;
	state = game->stateMoving;

	aIdleRight = new Animation("res/actors/archer/idle/right.png", WIDTH_IDLE_U_L_R, HEIGHT_IDLE_U_L_R, WIDTH_IDLE_U_L_R, HEIGHT_IDLE_U_L_R, 6, 1, true, game);
	aIdleLeft = new Animation("res/actors/archer/idle/left.png", WIDTH_IDLE_U_L_R, HEIGHT_IDLE_U_L_R, WIDTH_IDLE_U_L_R, HEIGHT_IDLE_U_L_R, 6, 1, true, game);
	aIdleUp = new Animation("res/actors/archer/idle/up.png", WIDTH_IDLE_U_L_R, HEIGHT_IDLE_U_L_R, WIDTH_IDLE_U_L_R, HEIGHT_IDLE_U_L_R, 6, 1, true, game);
	aIdleDown = new Animation("res/actors/archer/idle/down.png", WIDTH_IDLE_D, HEIGHT_IDLE_D, WIDTH_IDLE_D, HEIGHT_IDLE_D, 6, 1, true, game);

	/*aRunningRight = new Animation("res/archer_running_right.png", 0, 0, 55, 53, 4, 4, true, game);
	aRunningLeft = new Animation("res/archer_running_left.png", 0, 0, 55, 53, 4, 4, true, game);
	aRunningUp = new Animation("res/archer_running_up.png", 0, 0, 37, 53, 4, 4, true, game);
	aRunningDown = new Animation("res/archer_running_down.png", 0, 0, 37, 53, 4, 4, true, game);

	aAttackingRight = new Animation("res/archer_attack_right.png", 0, 0, 69, 59, 4, 4, false, game);
	aAttackingLeft = new Animation("res/archer_attack_left.png", 0, 0, 69, 59, 4, 4, false, game);
	aAttackingUp = new Animation("res/archer_attack_up.png", 0, 0, 64, 66, 4, 4, false, game);
	aAttackingDown = new Animation("res/archer_attack_down.png", 0, 0, 72, 68, 4, 4, false, game);

	aDeath = new Animation("res/archer_death.png", 0, 0, 35, 53, 4, 4, false, game);*/

	vx = 0;
	vxIntelligence = 0;
	vx = vxIntelligence;
	animation = aIdleDown;
}

void Archer::update() 
{
	//Enemy::update();
}

void Archer::draw(float scrollX, float scrollY)
{
	Enemy::draw(scrollX, scrollY);
}

void Archer::impacted() {}