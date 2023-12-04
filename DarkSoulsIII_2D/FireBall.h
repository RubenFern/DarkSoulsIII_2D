#include "Projectile.h"

class FireBall : public Projectile
{
public:
	FireBall(float x, float y, Game* game);
	void update() override;
	void draw(float scrollX = 0, float scrollY = 0) override;
};