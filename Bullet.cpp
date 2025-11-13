#include "Bullet.h"

Bullet::Bullet(Texture &tex, const float bulletSpeed)
{
	this->bulletSpeed = bulletSpeed;
	this->bulletSprite.setTexture(tex);

}

void Bullet::spawnBullet(Vector2f playerPosition)
{


}
