#pragma once

#include "Weapon.h"
#include "MagicBall.h"

class SageCrystalStaff : public Weapon
{
public:
	SageCrystalStaff(float x, float y, Game* game);
	Projectile* attack(float x, float y) override;
	int attackCadence = 80;
	int attackTime = 0;

    // ATTACK
    int getWidthAttackRight() const override { return 97; }
    int getWidthAttackLeft() const override { return 97; }
    int getWidthAttackUp() const override { return 70; }
    int getWidthAttackDown() const override { return 70; }

    int getHeightAttackRight() const override { return 52; }
    int getHeightAttackLeft() const override { return 52; }
    int getHeightAttackUp() const override { return 103; }
    int getHeightAttackDown() const override { return 92; }

    int getTotalFramesAttack() const override { return 8; }

    // MOVEMENT
    int getWidthMovementRight() const override { return 40; }
    int getWidthMovementLeft() const override { return 40; }
    int getWidthMovementUp() const override { return 31; }
    int getWidthMovementDown() const override { return 30; }

    int getHeightMovementRight() const override { return 50; }
    int getHeightMovementLeft() const override { return 50; }
    int getHeightMovementUp() const override { return 51; }
    int getHeightMovementDown() const override { return 51; }

    int getTotalFramesMovement() const override { return 9; }

    // IDLE
    int getWidthIdleRight() const override { return 32; }
    int getWidthIdleLeft() const override { return 32; }
    int getWidthIdleUp() const override { return 32; }
    int getWidthIdleDown() const override { return 32; }

    int getHeightIdleRight() const override { return 52; }
    int getHeightIdleLeft() const override { return 52; }
    int getHeightIdleUp() const override { return 52; }
    int getHeightIdleDown() const override { return 52; }

    // DEATH
    int getWidthDeath() const override { return 43; }
    int getHeightDeath() const override { return 51; }

    int getTotalFramesDeath() const override { return 6; }
};

