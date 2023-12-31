#pragma once

#include "Layer.h"
#include "Player.h"
#include "Background.h"
#include "Archer.h"
#include "Knight.h"
#include "Enemy.h"
#include "Projectile.h"
#include "Text.h"
#include "Tile.h"
#include "Bonfire.h"
#include "Consumable.h"
#include "FireKeeper.h"
#include "MenuUpLevel.h"
#include "Blaidd.h"
#include "Barrel.h"
#include "Message.h"

#include "Space.h" // importar

#include <fstream> // Leer ficheros
#include <sstream> // Leer l�neas / String
#include <list>

class GameLayer : public Layer
{
public:
	GameLayer(Game* game);
	void init() override;
	void processControls() override;
	void update() override;
	void draw() override;
	void playMusic() override;
	void attackEnemies();
	void keysToControls(SDL_Event event);
	void mouseToControls(SDL_Event event); // USO DE MOUSE
	void gamePadToControls(SDL_Event event); // USO DE GAMEPAD
	void loadMap(string name);
	void loadMapObject(char character, float x, float y);
	void calculateScroll();
	void impactedPlayer(Enemy* e);
	void impactedPlayer(Projectile* p);
	void processDoor();
	Actor* message;
	MenuUpLevel* menuUpLevel;
	bool pause;
	bool playingMusic;
	bool isUpLevel;
	bool playerWin;
	bool crossDoor;
	// Elementos de interfaz
	SDL_GameController* gamePad;

	Space* space;
	float scrollX;
	float scrollY;
	int mapWidth;
	int mapHeight;
	list<Tile*> tiles;

	Text* textSouls;
	Actor* iconSouls;
	int newEnemyTime = 0;
	Player* player;
	Background* background;
	FireKeeper* fireKeeper;
	list<Enemy*> enemies;
	list<Projectile*> projectiles;
	list<Projectile*> projectilesEnemies;
	list<Bonfire*> bonfires;
	list<Barrel*> barrels;
	Bonfire* currentBonfire;

	Message* messageScreen;

	Tile* doorLeft;
	Tile* doorRight;
	Tile* doorUp;
	Tile* doorDown;

	bool controlContinue = false;
	bool controlAttack = false;
	int controlMoveY = 0;
	int controlMoveX = 0;
};