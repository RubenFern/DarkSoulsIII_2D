#pragma once

#include "Uchigatana.h"

class UchigatanaFreezing : public Uchigatana
{
public:
    UchigatanaFreezing(float x, float y, Game* game);
    int attackCadence = 15;
    int attackTime = 0;

    // ATTACK
    int getWidthAttackRight() const override { return 108; }
    int getWidthAttackLeft() const override { return 108; }
    int getWidthAttackUp() const override { return 102; }
    int getWidthAttackDown() const override { return 106; }

    int getHeightAttackRight() const override { return 52; }
    int getHeightAttackLeft() const override { return 52; }
    int getHeightAttackUp() const override { return 70; }
    int getHeightAttackDown() const override { return 69; }

    // MOVEMENT
    int getWidthMovementRight() const override { return 47; }
    int getWidthMovementLeft() const override { return 47; }
    int getWidthMovementUp() const override { return 42; }
    int getWidthMovementDown() const override { return 40; }

    int getHeightMovementRight() const override { return 56; }
    int getHeightMovementLeft() const override { return 56; }
    int getHeightMovementUp() const override { return 56; }
    int getHeightMovementDown() const override { return 53; }

    // IDLE
    int getWidthIdleRight() const override { return 40; }
    int getWidthIdleLeft() const override { return 40; }
    int getWidthIdleUp() const override { return 42; }
    int getWidthIdleDown() const override { return 40; }

    int getHeightIdleRight() const override { return 56; }
    int getHeightIdleLeft() const override { return 56; }
    int getHeightIdleUp() const override { return 53; }
    int getHeightIdleDown() const override { return 53; }

    // DEATH
    int getWidthDeath() const override { return 40; }
    int getHeightDeath() const override { return 53; }
};

