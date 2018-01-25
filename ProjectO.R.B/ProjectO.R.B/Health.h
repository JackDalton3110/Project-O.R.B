#pragma once

/*
/Author: Aaron Curry
/date started:25/1/2018
/date finished:
/time spent: 7 hours
*/
#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include <iostream>
#include "Xbox360Controller.h"
#include <sstream>
#include "Player.h"

class Health
{
public:
	Health();
	~Health();

	bool dead = false;
	void update(sf::Time t);
	void render(sf::RenderWindow &window);
	sf::Vector2f m_position;
	int m_health;

private:
	sf::Texture health3_0Txt;
	sf::Texture health2_5Txt;
	sf::Texture health2_0Txt;
	sf::Texture health1_5Txt;
	sf::Texture health1_0Txt;
	sf::Texture health0_5Txt;
	sf::Texture health0_0Txt;
	sf::Sprite healthSprite;
	Player *m_player;
};
