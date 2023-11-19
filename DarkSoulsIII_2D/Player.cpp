#include "Player.h"

Player::Player(float x, float y, Game* game)
	: Actor("res/actors/player-katana/idle/down.png", x, y, 37, 53, game) {

	orientation = game->orientationDown;
	state = game->stateMoving;
	
	aAttackingRight = new Animation("res/actors/player-katana/attack/right.png", WIDTH_ATTACK_R_L, HEIGHT_ATTACK_R_L, 414, 59, 3, 6, false, game);
	aAttackingLeft = new Animation("res/actors/player-katana/attack/left.png", WIDTH_ATTACK_R_L, HEIGHT_ATTACK_R_L, 414, 59, 3, 6, false, game);
	aAttackingDown = new Animation("res/actors/player-katana/attack/down.png", WIDTH_ATTACK_U, HEIGHT_ATTACK_U, 384, 66, 3, 6, false, game);
	aAttackingUp = new Animation("res/actors/player-katana/attack/up.png", WIDTH_ATTACK_D, HEIGHT_ATTACK_D, 432, 68, 3, 6, false, game);

	aIdleRight = new Animation("res/actors/player-katana/idle/right.png", WIDTH_RIGHT, HEIGHT_RIGHT, 55, 53, 6, 1, true, game);
	aIdleLeft = new Animation("res/actors/player-katana/idle/left.png", WIDTH_LEFT, HEIGHT_LEFT, 55, 53, 6, 1, true, game);
	aIdleDown = new Animation("res/actors/player-katana/idle/down.png", WIDTH_DOWN, HEIGHT_DOWN, 55, 53, 6, 1, true, game);
	aIdleUp = new Animation("res/actors/player-katana/idle/up.png", WIDTH_UP, HEIGHT_UP, 55, 53, 6, 1, true, game);
	
	aRunningRight = new Animation("res/actors/player-katana/walk/right.png", WIDTH_RIGHT, HEIGHT_RIGHT, 495, 53, 3, 9, true, game);
	aRunningLeft = new Animation("res/actors/player-katana/walk/left.png", WIDTH_LEFT, HEIGHT_LEFT, 495, 53, 3, 9, true, game);
	aRunningDown = new Animation("res/actors/player-katana/walk/down.png", WIDTH_DOWN, HEIGHT_DOWN, 333, 53, 3, 9, true, game);
	aRunningUp = new Animation("res/actors/player-katana/walk/up.png", WIDTH_UP, HEIGHT_UP, 333, 53, 3, 9, true, game);

	aDeath = new Animation("res/actors/player-katana/death/death.png", WIDTH_DEATH, HEIGHT_DEATH, 210, 53, 6, 6, false, game);

	animation = aIdleDown;
}

void Player::update() {
	if (invulnerableTime > 0)
		invulnerableTime--;

	bool endAnimation = animation->update();

	// Acabo la animación, no sabemos cual
	if (endAnimation)
		// Estaba atacando
		if (state == game->stateAttacking)
			state = game->stateMoving;


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

void Player::moveX(float axis) {
	vx = axis * 3;
}

void Player::moveY(float axis) {
	vy = axis * 3;
}

Projectile* Player::attack() {

	if (attackTime == 0) 
	{
		state = game->stateAttacking;

		aAttackingLeft->currentFrame = 0; //"Rebobinar" animación
		aAttackingRight->currentFrame = 0; //"Rebobinar" animación
		aAttackingUp->currentFrame = 0; //"Rebobinar" animación
		aAttackingDown->currentFrame = 0; //"Rebobinar" animación

		attackTime = attackCadence;

		Projectile* projectile = new Sword("res/disparo_jugador.png", x, y, 20, 20, game);
		float vx = 0, vy = 0;

		if (orientation == game->orientationLeft)
			vx = -4;
		else if (orientation == game->orientationDown)
			vy = 4;
		else if (orientation == game->orientationUp)
			vy = -4;
		else if (orientation == game->orientationRight)
			vx = 4;
		
		projectile->vx = vx;
		projectile->vy = vy;
		
		return projectile;
	}
	else {
		return NULL;
	}
}

void Player::draw(float scrollX, float scrollY)
{
	if (invulnerableTime == 0)
		animation->draw(x - scrollX, y - scrollY);
	
	else 
		if (invulnerableTime % 10 >= 0 && invulnerableTime % 10 <= 5)
			animation->draw(x - scrollX, y - scrollY);
}

void Player::loseLife() {
	if (invulnerableTime <= 0) 
	{
		if (life > 0) 
		{
			life--;
			invulnerableTime = 30;
			// 100 actualizaciones 
		}
	}
}