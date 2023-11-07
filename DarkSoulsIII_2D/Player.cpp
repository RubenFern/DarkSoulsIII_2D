#include "Player.h"

Player::Player(float x, float y, Game* game)
	: Actor("res/actors/player-katana/idle/down.png", x, y, 55, 53, game) {

	orientation = game->orientationDown;
	state = game->stateMoving;

	aAttackingRight = new Animation("res/actors/player-katana/attack/right.png", 69, 59, 414, 59, 3, 6, false, game);
	aAttackingLeft = new Animation("res/actors/player-katana/attack/left.png", 69, 59, 414, 59, 3, 6, false, game);
	aAttackingDown = new Animation("res/actors/player-katana/attack/down.png", 64, 66, 384, 66, 3, 6, false, game);
	aAttackingUp = new Animation("res/actors/player-katana/attack/up.png", 72, 68, 432, 68, 3, 6, false, game);

	aIdleRight = new Animation("res/actors/player-katana/idle/right.png", width, height, 55, 53, 6, 1, true, game);
	aIdleLeft = new Animation("res/actors/player-katana/idle/left.png", width, height, 55, 53, 6, 1, true, game);
	aIdleDown = new Animation("res/actors/player-katana/idle/down.png", width, height, 55, 53, 6, 1, true, game);
	aIdleUp = new Animation("res/actors/player-katana/idle/up.png", width, height, 55, 53, 6, 1, true, game);
	
	aRunningRight = new Animation("res/actors/player-katana/walk/right.png", width, height, 495, 53, 3, 9, true, game);
	aRunningLeft = new Animation("res/actors/player-katana/walk/left.png", width, height, 495, 53, 3, 9, true, game);
	aRunningDown = new Animation("res/actors/player-katana/walk/down.png", width, height, 495, 53, 3, 9, true, game);
	aRunningUp = new Animation("res/actors/player-katana/walk/up.png", width, height, 495, 53, 3, 9, true, game);

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

		Projectile* projectile = new Projectile(x, y, game);

//		if (orientation == game->orientationLeft)
//			projectile->vx = projectile->vx * -1; // Invertir
		
		return projectile;
	}
	else {
		return NULL;
	}
}

void Player::draw(float scrollX) 
{
	if (invulnerableTime == 0)
		animation->draw(x - scrollX, y);
	
	else 
		if (invulnerableTime % 10 >= 0 && invulnerableTime % 10 <= 5)
			animation->draw(x - scrollX, y);
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