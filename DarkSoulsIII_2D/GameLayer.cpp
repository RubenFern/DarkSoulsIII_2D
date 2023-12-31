#include "GameLayer.h"

GameLayer::GameLayer(Game* game)
	: Layer(game) {
	//llama al constructor del padre : Layer(renderer)
	pause = true;
	message = new Actor("res/menu/tutorial.png", WIDTH * 0.5, HEIGHT * 0.5, 846, 477, game);
	menuUpLevel = new MenuUpLevel(game);
	messageScreen = new Message(game);

	gamePad = SDL_GameControllerOpen(0);
	init();
}

void GameLayer::init() {
	space = new Space(0);
	scrollX = 0;
	scrollY = 0;
	tiles.clear();

	fireKeeper = NULL;
	iconSouls = new Actor("res/actors/icon/souls.png", WIDTH * 0.9, HEIGHT * 0.94, 26, 26, game);
	textSouls = new Text("hola", WIDTH * 0.95, HEIGHT * 0.94, game);
	textSouls->content = to_string(0);

	message = new Actor("res/menu/tutorial.png", WIDTH * 0.5, HEIGHT * 0.5, 846, 477, game);
	background = new Background("res/fondo.png", WIDTH * 0.5, HEIGHT * 0.5, 0, game);

	enemies.clear(); 
	projectiles.clear(); 
	projectilesEnemies.clear(); 
	bonfires.clear();
	barrels.clear(); 

	int level = 0;
	bool loadFromBonfire = false;

	if (currentBonfire != NULL && !playerWin && !crossDoor)
	{
		level = currentBonfire->level;
		loadFromBonfire = true;
	}
	else if (playerWin)
	{
		level = 0;
		currentBonfire = NULL;
		playerWin = false;
	}
	else
	{
		level = game->currentLevel;
		crossDoor = false;
	}

	loadMap("res/" + to_string(level) + ".txt");

	if (currentBonfire != NULL && !playerWin && loadFromBonfire)
	{
		player->x = currentBonfire->playerX;
		player->y = currentBonfire->playerY;
	}
}

void GameLayer::playMusic() {
	if (!playingMusic)
	{
		audioBackground = Audio::createAudio("res/music/DarkSouls3OSTLudexGundyr.mp3", true);
		audioBackground->play();
		playingMusic = true;
	}
}

void GameLayer::loadMap(string name) {
	char character;
	string line;
	ifstream streamFile(name.c_str());
	if (!streamFile.is_open()) {
		cout << "Falla abrir el fichero de mapa" << endl;
		return;
	}
	else {
		// Por línea
		int i;
		for (i = 0; getline(streamFile, line); i++) {
			istringstream streamLine(line);
			mapWidth = line.length() * 40; // Ancho del mapa en pixels
			// Por carácter (en cada línea)
			for (int j = 0; !streamLine.eof(); j++) {
				streamLine >> character; // Leer character 
				cout << character;
				float x = 40 / 2 + j * 40; // x central
				float y = 32 + i * 32; // y suelo
				loadMapObject(character, x, y);
			}

			cout << character << endl;
		}
		mapHeight = i * 32; // Alto del mapa en pixels
	}
	streamFile.close();
}

void GameLayer::loadMapObject(char character, float x, float y)
{
	switch (character) {
	case '1': {
		Tile* tile = new Tile("res/blocks/floor.png", x, y, game);
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);

		if (player == NULL)
			player = new Player(x, y, game);
		else
		{
			player->x = x;
			player->y = y;
		}
		// modificación para empezar a contar desde el suelo.
		player->y = player->y - player->height / 2;
		space->addDynamicActor(player);
		break;
	}
	case '#': {		// Muro delimitador
		Tile* tile = new Tile("res/blocks/wall.png", x, y, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case '-': {		// Suelo
		Tile* tile = new Tile("res/blocks/floor.png", x, y, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		break;
	}
	case 'A': {		// Arquero
		Tile* tile = new Tile("res/blocks/floor.png", x, y, game);
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);

		Archer* enemy = new Archer(x, y, game);
		// modificación para empezar a contar desde el suelo.
		enemy->y = enemy->y - enemy->height / 2;
		enemies.push_back(enemy);
		space->addDynamicActor(enemy);
		break;
	}
	case 'B': {		// Hoguera
		Tile* tile = new Tile("res/blocks/floor.png", x, y, game);
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);

		Bonfire* bonfire = new Bonfire(x, y, game);
		// modificación para empezar a contar desde el suelo.
		bonfire->y = bonfire->y - bonfire->height / 2;
		tiles.push_back(bonfire);
		space->addStaticActor(bonfire);
		bonfires.push_back(bonfire);
		break;
	}
	case 'L': {		// Puerta izquierda
		doorLeft = new Tile("res/blocks/door-left.png", x, y, game);
		doorLeft->y = doorLeft->y - doorLeft->height / 2;
		tiles.push_back(doorLeft);
		break;
	}
	case 'H': { 	// Puerta derecha
		doorRight = new Tile("res/blocks/door-right.png", x, y, game);
		doorRight->y = doorRight->y - doorRight->height / 2;
		tiles.push_back(doorRight);
		break;
	}
	case 'J': {		// Puerta arriba
		doorUp = new Tile("res/blocks/door-up.png", x, y, game);
		doorUp->y = doorUp->y - doorUp->height / 2;
		tiles.push_back(doorUp);
		break;
	}
	case 'G': {		// Puerta abajo
		doorDown = new Tile("res/blocks/door-down.png", x, y, game);
		doorDown->y = doorDown->y - doorDown->height / 2;
		tiles.push_back(doorDown);
		break;
	}
	case 'K': {		// Caballero
		Tile* tile = new Tile("res/blocks/floor.png", x, y, game);
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);

		Knight* enemy = new Knight(x, y, game);
		// modificación para empezar a contar desde el suelo.
		enemy->y = enemy->y - enemy->height / 2;
		enemies.push_back(enemy);
		space->addDynamicActor(enemy);
		break;
	}
	case 'F': {		// Guardiana del santuario de fuego
		Tile* tile = new Tile("res/blocks/floor.png", x, y, game);
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);

		fireKeeper = new FireKeeper(x, y, game);
		// modificación para empezar a contar desde el suelo.
		fireKeeper->y = fireKeeper->y - fireKeeper->height / 2;
		space->addDynamicActor(fireKeeper);
		break;
	}
	case 'D': {
		Tile* tile = new Tile("res/blocks/floor.png", x, y, game);
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);

		Blaidd* enemy = new Blaidd(x, y, game);
		// modificación para empezar a contar desde el suelo.
		enemy->y = enemy->y - enemy->height / 2;
		enemies.push_back(enemy);
		space->addDynamicActor(enemy);
		break;
	}
	case 'R': {		// Barril
		Tile* tile = new Tile("res/blocks/floor.png", x, y, game);
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);

		Barrel* barrel = new Barrel(x, y, game);
		barrel->y = barrel->y - barrel->height / 2;
		tiles.push_back(barrel);
		space->addStaticActor(barrel);
		barrels.push_back(barrel);
		break;
	}
	}
}


void GameLayer::processControls() {
	// obtener controles
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_CONTROLLERDEVICEADDED) {
			gamePad = SDL_GameControllerOpen(0);
			if (gamePad == NULL) {
				cout << "error en GamePad" << endl;
			}
			else {
				cout << "GamePad conectado" << endl;
			}
		}

		// Cambio automático de input
		// PONER el GamePad
		if (event.type == SDL_CONTROLLERBUTTONDOWN || event.type == SDL_CONTROLLERAXISMOTION) {
			game->input = game->inputGamePad;
		}
		if (event.type == SDL_KEYDOWN) {
			game->input = game->inputKeyboard;
		}
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			game->input = game->inputMouse;
		}
		// Procesar teclas
		if (game->input == game->inputKeyboard) {
			keysToControls(event);
		}
		if (game->input == game->inputMouse) {
			mouseToControls(event);
		}
		// Procesar Mando
		if (game->input == game->inputGamePad) {  // gamePAD
			gamePadToControls(event);
		}
	}
	//procesar controles
	//procesar controles
	// Disparar
	if (controlContinue) {
		pause = false;
		controlContinue = false;
	}
	if (controlAttack) {
		Projectile* newProjectile = player->attack();
		if (newProjectile != NULL)
			projectiles.push_back(newProjectile);
	}

	// Eje X
	if (controlMoveX > 0)
		player->moveX(1);
	else if (controlMoveX < 0)
		player->moveX(-1);
	else
		player->moveX(0);

	// Eje Y
	if (controlMoveY > 0)
		player->moveY(1);
	else if (controlMoveY < 0)
		player->moveY(-1);
	else 
		player->moveY(0);
}

void GameLayer::update() {
	if (pause || isUpLevel)
		return;

	if (playerWin)
	{
		message = new Actor("res/menu/you_win.png", WIDTH * 0.5, HEIGHT * 0.5, WIDTH, 115, game);
		pause = true;

		init();
		return;
	}

	processDoor();

	messageScreen->update();
	space->update();
	background->update();
	player->update();
	if (fireKeeper != NULL)
		fireKeeper->update();

	for (auto const& bonfire : bonfires)
		if (player->isOverlap(bonfire))
		{
			currentBonfire = bonfire;
			bonfire->savePositionPlayer(player->x, player->y, game->currentLevel);
			player->restoreLife();
		}

	for (auto const& enemy : enemies)
		enemy->update();
	
	for (auto const& projectile : projectiles)
		projectile->update();

	for (auto const& projetileEnemy : projectilesEnemies)
		projetileEnemy->update();

	attackEnemies();

	// Colisiones
	for (auto const& enemy : enemies)
		if (player->isOverlap(enemy) && enemy->contactDamage)
			impactedPlayer(enemy);

	// Colisiones , Enemy - Projectile

	list<Enemy*> deleteEnemies;
	list<Projectile*> deleteProjectiles;
	list<Projectile*> deleteProjectilesEnemies;
	list<Barrel*> deleteBarrels;
	for (auto const& projectile : projectiles) {
		if (projectile->isInRender(scrollX, scrollY) == false || (projectile->vx == 0 && projectile->vy == 0) 
			|| (dynamic_cast<Sword*>(projectile) != nullptr && dynamic_cast<Sword*>(projectile)->lifeTime == 0)) {

			bool pInList = std::find(deleteProjectiles.begin(),
				deleteProjectiles.end(),
				projectile) != deleteProjectiles.end();

			if (!pInList) {
				deleteProjectiles.push_back(projectile);
			}
		}
	}

	for (auto const& projectileEnemy : projectilesEnemies) {
		if (projectileEnemy->isInRender(scrollX, scrollY) == false || (projectileEnemy->vx == 0 && projectileEnemy->vy == 0)
			|| (dynamic_cast<Sword*>(projectileEnemy) != nullptr && dynamic_cast<Sword*>(projectileEnemy)->lifeTime == 0)) {

			bool pInList = std::find(deleteProjectilesEnemies.begin(),
								deleteProjectilesEnemies.end(),
								projectileEnemy) != deleteProjectilesEnemies.end();

			if (!pInList) {
				deleteProjectilesEnemies.push_back(projectileEnemy);
			}
		}
	}

	for (auto const& enemy : enemies) {
		for (auto const& projectile : projectiles) {
			if (enemy->isOverlap(projectile)) {
				bool pInList = std::find(deleteProjectiles.begin(),
					deleteProjectiles.end(),
					projectile) != deleteProjectiles.end();

				if (!pInList) {
					deleteProjectiles.push_back(projectile);
				}

				enemy->impacted(player);
				
				if (enemy->life <= 0) 
				{
					if (player->souls < 9999999)
					{
						player->souls += enemy->soulsValue;
						textSouls->content = to_string(player->souls);
					}
				}
			}
		}
	}

	for (auto const& projectileEnemy : projectilesEnemies) {
		if (player->isOverlap(projectileEnemy)) {
			bool pInList = std::find(deleteProjectilesEnemies.begin(),
								deleteProjectilesEnemies.end(),
								projectileEnemy) != deleteProjectilesEnemies.end();
			if (!pInList)
				deleteProjectilesEnemies.push_back(projectileEnemy);

			impactedPlayer(projectileEnemy);
		}
	}

	for (auto const& enemy : enemies) {
		if (enemy->state == game->stateDead) {
			bool eInList = std::find(deleteEnemies.begin(),
				deleteEnemies.end(),
				enemy) != deleteEnemies.end();

			if (!eInList) {
				deleteEnemies.push_back(enemy);
			}
		}
	}

	for (auto const& barrel : barrels)
	{
		for (auto const& projectile : projectiles)
		{
			if (barrel->isOverlap(projectile))
			{
				bool pInList = std::find(deleteProjectiles.begin(),
					deleteProjectiles.end(),
					projectile) != deleteProjectiles.end();

				if (!pInList)
					deleteProjectiles.push_back(projectile);

				bool bInList = std::find(deleteBarrels.begin(),
					deleteBarrels.end(),
					barrel) != deleteBarrels.end();

				if (!bInList)
					deleteBarrels.push_back(barrel);

				int index = barrel->destroy(player);

				messageScreen->setMessage(player->consumables[index]->name, "res/actors/objects/" + player->consumables[index]->pathImage, 32, 32);
			}
		}
	}

	for (auto const& delEnemy : deleteEnemies) {
		enemies.remove(delEnemy);
		space->removeDynamicActor(delEnemy);
	}
	deleteEnemies.clear();

	for (auto const& delProjectile : deleteProjectiles) {
		projectiles.remove(delProjectile);
		space->removeDynamicActor(delProjectile);
		delete delProjectile;
	}
	deleteProjectiles.clear();

	for (auto const& delProjectileEnemy : deleteProjectilesEnemies) {
		projectilesEnemies.remove(delProjectileEnemy);
		space->removeDynamicActor(delProjectileEnemy);
		delete delProjectileEnemy;
	}
	deleteProjectilesEnemies.clear();

	for (auto const& delBarrel : deleteBarrels) {
		barrels.remove(delBarrel);
		space->removeStaticActor(delBarrel);
		tiles.remove(delBarrel);
		delete delBarrel;
	}
	deleteBarrels.clear();

	if (player->life <= 0) 
	{
		message = new Actor("res/menu/you_died.png", WIDTH * 0.5, HEIGHT * 0.5, WIDTH, 98, game);
		pause = true;
			
		init();
		return;
	}

	//cout << "update GameLayer" << endl;
}

void GameLayer::attackEnemies() 
{
	for (auto const& enemy : enemies)
	{
		Projectile* newProjectile = enemy->attack();

		if (newProjectile != NULL)
			projectilesEnemies.push_back(newProjectile);
	}
}

void GameLayer::calculateScroll() {
	// limite izquierda
	if (player->x > WIDTH * 0.3)
		if (player->x - scrollX < WIDTH * 0.3)
			scrollX = player->x - WIDTH * 0.3;

	// limite derecha
	if (player->x < mapWidth - WIDTH * 0.3)
		if (player->x - scrollX > WIDTH * 0.7)
			scrollX = player->x - WIDTH * 0.7;

	// limite arriba
	if (player->y > HEIGHT * 0.3)
		if (player->y - scrollY > HEIGHT * 0.7)
			scrollY = player->y - HEIGHT * 0.7;

	// limite abajo
	if (player->y < mapHeight - HEIGHT * 0.3)
		if (player->y - scrollY < HEIGHT * 0.3)
			scrollY = player->y - HEIGHT * 0.3;
}


void GameLayer::draw() {
	calculateScroll();

	background->draw();
	for (auto const& tile : tiles)
		tile->draw(scrollX, scrollY);

	for (auto const& projectile : projectiles)
		projectile->draw(scrollX, scrollY);

	for (auto const& projectileEnemy : projectilesEnemies)
		projectileEnemy->draw(scrollX, scrollY);

	for (auto const& enemy : enemies)
		enemy->draw(scrollX, scrollY);

	if (fireKeeper != NULL)
		fireKeeper->draw(scrollX, scrollY);

	player->draw(scrollX, scrollY);

	iconSouls->draw();
	textSouls->draw();

	// HUD
	if (pause)
		message->draw();

	if (isUpLevel)
		menuUpLevel->draw();

	messageScreen->draw();

	SDL_RenderPresent(game->renderer); // Renderiza
}

void GameLayer::gamePadToControls(SDL_Event event) {

	// Leer los botones
	bool buttonRB = SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER);
	bool buttonA = SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_A);
	bool buttonX = SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_X);
	bool buttonRightArrow = SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
	bool buttonDownArrow = SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_DPAD_DOWN);
	int stickX = SDL_GameControllerGetAxis(gamePad, SDL_CONTROLLER_AXIS_LEFTX);
	int stickY = SDL_GameControllerGetAxis(gamePad, SDL_CONTROLLER_AXIS_LEFTY);
	cout << "stickX" << stickX << endl;
	cout << "stickY" << stickY << endl;

	// Retorna aproximadamente entre [-32800, 32800], el centro debería estar en 0
	// Si el mando tiene "holgura" el centro varia [-4000 , 4000]
	if (stickX > 8000)
		controlMoveX = 1;
	else if (stickX < -8000)
		controlMoveX = -1;
	else
		controlMoveX = 0;

	if (stickY > 8000)
		controlMoveY = 1;
	else if (stickY < -8000)
		controlMoveY = -1;
	else
		controlMoveY = 0;

	if (buttonRB)
		controlAttack = true;
	else
		controlAttack = false;

	if (buttonA)	// interactuar
	{
		if (abs(player->x - fireKeeper->x) < 40 && abs(player->y - fireKeeper->y) < 40)
		{
			player->interact(fireKeeper);
			isUpLevel = true;
		}
	}

	if (buttonX)	// usar objeto
		player->selectedConsumable->consume();

	if (buttonRightArrow) 		// cambiar arma
		player->nextWeapon();

	if (buttonDownArrow)		// cambiar objeto consumible
		player->nextConsumable();
}


void GameLayer::mouseToControls(SDL_Event event) {
	// Modificación de coordenadas por posible escalado
	float motionX = event.motion.x / game->scaleLower;
	float motionY = event.motion.y / game->scaleLower;
	// Cada vez que hacen click
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		controlContinue = true;
	}
}


void GameLayer::keysToControls(SDL_Event event) {
	if (event.type == SDL_KEYDOWN) {
		int code = event.key.keysym.sym;
		// Pulsada
		switch (code) {
		case SDLK_ESCAPE:
			game->loopActive = false;
			break;
		case SDLK_p:
			pause = true;
			break;
		case SDLK_1:
			game->scale();
			break;
		case SDLK_d: // derecha
			controlMoveX = 1;
			break;
		case SDLK_a: // izquierda
			controlMoveX = -1;
			break;
		case SDLK_w: // arriba
			controlMoveY = -1;
			break;
		case SDLK_s: // abajo
			controlMoveY = 1;
			break;
		case SDLK_SPACE: // dispara
			controlAttack = true;
			break;
		case SDLK_e: // usar objeto
			player->selectedConsumable->consume();
			break;
		case SDLK_v: // cambiar arma
			player->nextWeapon();
			break;
		case SDLK_f: // cambiar objeto consumible
			player->nextConsumable();
			break;
		case SDLK_q: // interactuar
			if (abs(player->x - fireKeeper->x) < 40 && abs(player->y - fireKeeper->y) < 40)
			{
				player->interact(fireKeeper);
				isUpLevel = true;
			}
			break;
		case SDLK_2: // Subir vida
			if (isUpLevel && player->souls >= player->costSoulsUpLife)
			{
				player->souls -= player->costSoulsUpLife;
				player->costSoulsUpLife *= 2;
				player->life += 20;
				player->maxLife += 20;
				textSouls->content = to_string(player->souls);
				player->healthBar->health = player->life;
				player->healthBar->width = player->life;
			}
			break;
		case SDLK_3: // Subir magia
			if (isUpLevel && player->souls >= player->costSoulsUpMana)
			{
				player->souls -= player->costSoulsUpMana;
				player->costSoulsUpMana *= 2;
				player->mana += 20;
				player->maxMana += 20;
				textSouls->content = to_string(player->souls);
				player->manaBar->mana = player->mana;
				player->manaBar->width = player->mana;
			}
			break;
		case SDLK_4: // Subir ataque
			if (isUpLevel && player->souls >= player->costSoulsUpDamage)
			{
				player->souls -= player->costSoulsUpDamage;
				player->costSoulsUpDamage *= 2;
				player->damageBase += 10;
				textSouls->content = to_string(player->souls);
			}
			break;
		case SDLK_5: // Abandonar menú subir nivel
			isUpLevel = false;
			break;
		}
	}
	if (event.type == SDL_KEYUP) {
		int code = event.key.keysym.sym;
		// Levantada
		switch (code) {
		case SDLK_d: // derecha
			if (controlMoveX == 1) {
				controlMoveX = 0;
			}
			break;
		case SDLK_a: // izquierda
			if (controlMoveX == -1) {
				controlMoveX = 0;
			}
			break;
		case SDLK_w: // arriba
			if (controlMoveY == -1) {
				controlMoveY = 0;
			}
			break;
		case SDLK_s: // abajo
			if (controlMoveY == 1) {
				controlMoveY = 0;
			}
			break;
		case SDLK_SPACE: // dispara
			controlAttack = false;
			break;
		}
	}
}

void GameLayer::impactedPlayer(Enemy* e) {
	player->loseLife(e->damage);
}

void GameLayer::impactedPlayer(Projectile* p) {
	player->loseLife(p->damage);
}

void GameLayer::processDoor() {
	if (doorLeft != NULL && player->isOverlap(doorLeft)) {
		crossDoor = true;
		game->currentLevel = 0;
		init();
	}
	if (doorRight != NULL && player->isOverlap(doorRight)) {
		crossDoor = true;
		game->currentLevel = 1;
		init();
	}
	if (doorUp != NULL && player->isOverlap(doorUp)) {
		crossDoor = true;
		game->currentLevel = 1;
		init();
	}
	if (doorDown != NULL && player->isOverlap(doorDown)) {
		crossDoor = true;
		game->currentLevel = 2;
		init();
	}
}

