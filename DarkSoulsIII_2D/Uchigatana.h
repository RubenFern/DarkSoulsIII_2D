#pragma once

#include "Weapon.h"

class Uchigatana : public Weapon
{
public:
	Uchigatana(float x, float y, Game* game);
    Projectile* attack(float x, float y) override;
	int attackCadence = 15;
	int attackTime = 0;

    // ATTACK
    int getWidthAttackRight() const override { return 69; }
    int getWidthAttackLeft() const override { return 69; }
    int getWidthAttackUp() const override { return 72; }
    int getWidthAttackDown() const override { return 64; }

    int getHeightAttackRight() const override { return 59; }
    int getHeightAttackLeft() const override { return 59; }
    int getHeightAttackUp() const override { return 68; }
    int getHeightAttackDown() const override { return 66; }

    // MOVEMENT
    int getWidthMovementRight() const override { return 55; }
    int getWidthMovementLeft() const override { return 55; }
    int getWidthMovementUp() const override { return 37; }
    int getWidthMovementDown() const override { return 37; }

    int getHeightMovementRight() const override { return 53; }
    int getHeightMovementLeft() const override { return 53; }
    int getHeightMovementUp() const override { return 53; }
    int getHeightMovementDown() const override { return 53; }

    // IDLE
    int getWidthIdleRight() const override { return 55; }
    int getWidthIdleLeft() const override { return 55; }
    int getWidthIdleUp() const override { return 37; }
    int getWidthIdleDown() const override { return 37; }

    int getHeightIdleRight() const override { return 53; }
    int getHeightIdleLeft() const override { return 53; }
    int getHeightIdleUp() const override { return 53; }
    int getHeightIdleDown() const override { return 53; }

    // DEATH
    int getWidthDeath() const override { return 35; }
    int getHeightDeath() const override { return 53; }
};

