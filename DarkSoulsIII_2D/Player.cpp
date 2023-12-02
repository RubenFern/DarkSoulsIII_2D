#include "Player.h"

Player::Player(float x, float y, Game* game)
	: Actor("res/actors/player-katana/idle/down.png", x, y, 37, 53, game) {

	orientation = game->orientationDown;
	state = game->stateMoving;

	healthBar = new HealthBar(life, 15, WIDTH * 0.02, HEIGHT * 0.04, game);
	selectedWeapon = new Uchigatana(WIDTH * 0.13, HEIGHT * 0.90, game);

	loadConsumables();
	selectedConsumable = consumables[0];
	loadWeapons();
	selectedWeapon = weapons[0];

	loadCurrentWeapon();

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


	if (selectedWeapon->attackTime > 0)
		selectedWeapon->attackTime--;

	for (int i = 0; i < TOTAL_CONSUMABLES; i++)
		consumables[i]->update();
}

void Player::moveX(float axis) {
	vx = axis * 3;
}

void Player::moveY(float axis) {
	vy = axis * 3;
}

Projectile* Player::attack() {

	if (selectedWeapon->attackTime == 0) 
	{
		state = game->stateAttacking;

		aAttackingLeft->currentFrame = 0; //"Rebobinar" animación
		aAttackingRight->currentFrame = 0; //"Rebobinar" animación
		aAttackingUp->currentFrame = 0; //"Rebobinar" animación
		aAttackingDown->currentFrame = 0; //"Rebobinar" animación

		selectedWeapon->attackTime = selectedWeapon->attackCadence;

		Projectile* projectile = selectedWeapon->attack(x, y);
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

	healthBar->draw(healthBar->x, healthBar->y);
	selectedConsumable->draw(scrollX, scrollY);
	selectedWeapon->draw(scrollX, scrollY);
}

void Player::loseLife(int damage) {
	if (invulnerableTime <= 0) 
	{
		if (life > 0) 
		{
			life -= damage;
			invulnerableTime = 30;
			healthBar->health = life;
			// 100 actualizaciones 
		}
	}
}

void Player::loadConsumables()
{
	consumables[0] = new EstusFlask(WIDTH * 0.06, HEIGHT * 0.90, game);
	consumables[1] = new BloodGem(WIDTH * 0.06, HEIGHT * 0.90, game);
	consumables[2] = new FireGem(WIDTH * 0.06, HEIGHT * 0.90, game);
	consumables[3] = new FreezeGem(WIDTH * 0.06, HEIGHT * 0.90, game);
}

void Player::nextConsumable()
{
	indexConsumables++;

	if (indexConsumables >= TOTAL_CONSUMABLES)
		indexConsumables = 0;

	selectedConsumable = consumables[indexConsumables];
}

void Player::restoreLife() 
{
	life = LIFE;
	healthBar->health = life;
	
	consumables[0]->num = static_cast<EstusFlask*>(consumables[0])->totalEstus;
	consumables[0]->text->content = to_string(consumables[0]->num);
}

void Player::loadWeapons()
{
	weapons[0] = new Uchigatana(WIDTH * 0.13, HEIGHT * 0.90, game);
}

void Player::nextWeapon()
{
	indexWeapons++;

	if (indexWeapons >= TOTAL_WEAPONS)
		indexWeapons = 0;

	selectedWeapon = weapons[indexWeapons];
	loadCurrentWeapon();
}

void Player::loadCurrentWeapon()
{
	aAttackingRight = new Animation("res/actors/player/" + selectedWeapon->path + "/attack/right.png", 
		selectedWeapon->getWidthAttackRight(), selectedWeapon->getHeightAttackRight(), 
		selectedWeapon->getWidthAttackRight() * 6, selectedWeapon->getHeightAttackRight(), 3, 6, false, game);
	aAttackingLeft = new Animation("res/actors/player/" + selectedWeapon->path + "/attack/left.png",
		selectedWeapon->getWidthAttackLeft(), selectedWeapon->getHeightAttackLeft(), 
		selectedWeapon->getWidthAttackLeft() * 6, selectedWeapon->getHeightAttackLeft(), 3, 6, false, game);
	aAttackingDown = new Animation("res/actors/player/" + selectedWeapon->path + "/attack/down.png", 
		selectedWeapon->getWidthAttackDown(), selectedWeapon->getHeightAttackDown(), 
		selectedWeapon->getWidthAttackDown() * 6, selectedWeapon->getHeightAttackDown(), 3, 6, false, game);
	aAttackingUp = new Animation("res/actors/player/" + selectedWeapon->path + "/attack/up.png",
		selectedWeapon->getWidthAttackUp(), selectedWeapon->getHeightAttackUp(), 
		selectedWeapon->getWidthAttackUp() * 6, selectedWeapon->getHeightAttackUp(), 3, 6, false, game);
	
	aIdleRight = new Animation("res/actors/player/" + selectedWeapon->path + "/idle/right.png",
		selectedWeapon->getWidthIdleRight(), selectedWeapon->getHeightIdleRight(), 
		selectedWeapon->getWidthIdleRight(), selectedWeapon->getHeightIdleRight(), 6, 1, true, game);
	aIdleLeft = new Animation("res/actors/player/" + selectedWeapon->path + "/idle/left.png",
		selectedWeapon->getWidthIdleLeft(), selectedWeapon->getHeightIdleLeft(), 
		selectedWeapon->getWidthIdleLeft(), selectedWeapon->getHeightIdleLeft(), 6, 1, true, game);
	aIdleDown = new Animation("res/actors/player/" + selectedWeapon->path + "/idle/down.png",
		selectedWeapon->getWidthIdleDown(), selectedWeapon->getHeightIdleDown(), 
		selectedWeapon->getWidthIdleDown(), selectedWeapon->getHeightIdleDown(), 6, 1, true, game);
	aIdleUp = new Animation("res/actors/player/" + selectedWeapon->path + "/idle/up.png",
		selectedWeapon->getWidthIdleUp(), selectedWeapon->getHeightIdleUp(), 
		selectedWeapon->getWidthIdleUp(), selectedWeapon->getHeightIdleUp(), 6, 1, true, game);

	aRunningRight = new Animation("res/actors/player/" + selectedWeapon->path + "/walk/right.png",
		selectedWeapon->getWidthMovementRight(), selectedWeapon->getHeightMovementRight(), 
		selectedWeapon->getWidthMovementRight() * 9, selectedWeapon->getHeightMovementRight(), 3, 9, true, game);
	aRunningLeft = new Animation("res/actors/player/" + selectedWeapon->path + "/walk/left.png",
		selectedWeapon->getWidthMovementLeft(), selectedWeapon->getHeightMovementLeft(), 
		selectedWeapon->getWidthMovementLeft() * 9, selectedWeapon->getHeightMovementLeft(), 3, 9, true, game);
	aRunningDown = new Animation("res/actors/player/" + selectedWeapon->path + "/walk/down.png",
		selectedWeapon->getWidthMovementDown(), selectedWeapon->getHeightMovementDown(), 
		selectedWeapon->getWidthMovementDown() * 9, selectedWeapon->getHeightMovementDown(), 3, 9, true, game);
	aRunningUp = new Animation("res/actors/player/" + selectedWeapon->path + "/walk/up.png", 
		selectedWeapon->getWidthMovementUp(), selectedWeapon->getHeightMovementUp(), 
		selectedWeapon->getWidthMovementUp() * 9, selectedWeapon->getHeightMovementUp(), 3, 9, true, game);

	aDeath = new Animation("res/actors/player/" + selectedWeapon->path + "/death/death.png",
		selectedWeapon->getWidthDeath(), selectedWeapon->getHeightDeath(), 
		selectedWeapon->getWidthDeath() * 6, selectedWeapon->getHeightDeath(), 6, 6, false, game);
}

void Player::setSelectedWeapon(Weapon* weapon)
{
	selectedWeapon = weapon;
	loadCurrentWeapon();
}