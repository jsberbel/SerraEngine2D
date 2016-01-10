#include "Gun.h"
#include <random>
#include <ctime>
#include <glm/gtx/rotate_vector.hpp>

Gun::Gun(const std::string &name, int fireRate, int bulletPerShot, float spread, float bulletSpeed, int bulletDamage) :
	_name(name),
	_fireRate(fireRate),
	_bulletsPerShot(bulletPerShot),
	_spread(spread),
	_bulletSpeed(bulletSpeed),
	_bulletDamage(bulletDamage),
	_frameCounter(0) {}

void Gun::update(bool isMouseDown, const glm::vec2 & position, const glm::vec2 & direction, std::vector<Bullet>& bullets) {
	_frameCounter++;
	if (_frameCounter >= _fireRate && isMouseDown) {
		fire(position, direction, bullets);
		_frameCounter = 0;
	}
}

void Gun::fire(const glm::vec2 & position, const glm::vec2 & direction, std::vector<Bullet>& bullets) {
	static const float PI = 3.14159265359f;
	static std::mt19937 randomEngine((unsigned)time(nullptr));
	std::uniform_real_distribution<float> randRot(-_spread * PI/180, _spread * PI/180);

	for (int i = 0; i < _bulletsPerShot; i++) {
		glm::vec2 dir = glm::rotate(direction, randRot(randomEngine));
		bullets.emplace_back(position, dir, _bulletSpeed, _bulletDamage);
	}
}