#pragma once

#include <SFML\Main.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>

#include <list>
#include <vector>

#include "Constants.h"


enum EnemyType
{
	GroundLightEnemy = 0,
	GroundHeavyEnemy,
	AirEnemy
};

enum JobState
{
	Moved = 0,
	Shot = 0,
	IsDestroyed,
    ReachedEnd
};

template<class Dot>
float distanceBetween(const Dot &a, const Dot &b)
{
	return sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2));
}

template<class Vec>
float lengthOf(const Vec &a)
{
	return sqrt(pow(a.x, 2), pow(a.y, 2));
}

template<class Vec>
Vec makeVec(const Vec &a, const Vec &b)
{
	return Vec(b.x - a.x, b.y - a.y);
}

template<class Vec>
Vec makeVecWithLength(const Vec &a, const Vec &b, const float length)
{
	Vec c = makeVec(a, b);
	return makeVecWithLength(c, length);
}

template<class Vec>
Vec makeVecWithLength(Vec a, const float length)
{
	a *= length / lengthOf(c);
	return a;
}
