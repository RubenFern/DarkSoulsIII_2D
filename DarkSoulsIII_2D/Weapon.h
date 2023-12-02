#pragma once

#define IMPACTS_TO_BLEEDING 5
#define FREEZING_TIME 15

#include "Actor.h"

class Weapon : public Actor
{
public:
	Weapon(string filename, float x, float y, int width, int height, Game* game);
	void draw(float scrollX = 0, float scrollY = 0) override;
    void setDamage(int damage);
	string path;
	int damage;
	int attackCadence = 30;
	int attackTime = 0;

    bool stateBleeding = false;
    bool stateFreezing = false;

    // ATTACK
    virtual int getWidthAttackRight() const = 0;
    virtual int getWidthAttackLeft() const = 0;
    virtual int getWidthAttackUp() const = 0;
    virtual int getWidthAttackDown() const = 0;

    virtual int getHeightAttackRight() const = 0;
    virtual int getHeightAttackLeft() const = 0;
    virtual int getHeightAttackUp() const = 0;
    virtual int getHeightAttackDown() const = 0;

    // MOVEMENT
    virtual int getWidthMovementRight() const = 0;
    virtual int getWidthMovementLeft() const = 0;
    virtual int getWidthMovementUp() const = 0;
    virtual int getWidthMovementDown() const = 0;

    virtual int getHeightMovementRight() const = 0;
    virtual int getHeightMovementLeft() const = 0;
    virtual int getHeightMovementUp() const = 0;
    virtual int getHeightMovementDown() const = 0;

    // IDLE
    virtual int getWidthIdleRight() const = 0;
    virtual int getWidthIdleLeft() const = 0;
    virtual int getWidthIdleUp() const = 0;
    virtual int getWidthIdleDown() const = 0;

    virtual int getHeightIdleRight() const = 0;
    virtual int getHeightIdleLeft() const = 0;
    virtual int getHeightIdleUp() const = 0;
    virtual int getHeightIdleDown() const = 0;

    // DEATH
    virtual int getWidthDeath() const = 0;
    virtual int getHeightDeath() const = 0;
};

