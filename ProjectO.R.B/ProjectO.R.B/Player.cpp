#include "Player.h"
Player::Player() :
	m_position(500, 800),
	m_initialVelocity(1, 1),
	m_gravity(0, .07*pixelsToMetres),
	pixelsToMetres(5),
	m_maxForce(15, 30),
	m_force(12.5, -30),
	m_groundLocation(0, 1500),
	m_radius(15),
	playerRect(sf::Vector2f(100.f, 100.f)),
	animation(&playerTxt, sf::Vector2u(12,4),10.f)
	//m_tileMap(tileMap)
{
	if (!playerTxt.loadFromFile("resources/images/sprite.png"))
	{
		std::string s("error loading texture from file");
		throw std::exception(s.c_str());
	}

	playerRect.setTexture(&playerTxt);
	playerRect.setTextureRect(animation.uvRect);
	animation = Animation(&playerTxt, sf::Vector2u(11, 4), 10.f);
	//animation.Update(3, 0.f);
}
	Player::~Player()
{

}

void Player::update(sf::Time t)
{
	
	if (gravity == true)
	{
		m_velocity.y += m_gravity.y*pixelsToMetres;

	}
	if (m_velocity.y < 1)
	{
		animation.Update(2, 1.f);

	}

	
	playerRect.setTextureRect(animation.uvRect);
	playerRect.setPosition(m_position);

	 keyHandler();

	 m_position = m_position + m_velocity;

}
void Player::moveLeft()
{
	if (m_velocity.x < m_maxForce.x )
	{
		m_velocity.x = - m_force.x;
		if(m_velocity.y>=0&& jumped == true)
		animation.Update(1, 5.f);
	}
	
	
}
void Player::moveRight()
{
	if (m_velocity.x < m_maxForce.x  )
	{
		m_velocity.x = + m_force.x;
		if (m_velocity.y>=0 && jumped ==true)
			animation.Update(0, 5.f);
	}


}
void Player::jump()
{
	if (m_velocity.y == 0 && m_velocity.y < m_maxForce.y)
	{
		m_velocity.y = m_velocity.y - 30;
	}

	
}

void Player::keyHandler()
{
	collision();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		jump();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) == false || sf::Keyboard::isKeyPressed(sf::Keyboard::Right) == false)
	{
		m_velocity.x = 0;
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) )
	{

		moveLeft();
		
	}
	 if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && moveX == true )
	{
		moveRight();
	}

	



}
void Player::collision()
{

	for (int i = 0; i < m_tileMap.m_object_position.size(); i++)
	{	
		//Top of the onject 
		if (m_position.y + animation.uvRect.height  >= m_tileMap.m_object_position.at(i).y && m_position.y + animation.uvRect.height  <= m_tileMap.m_object_position.at(i).y + 40
		&& m_position.x >= m_tileMap.m_object_position.at(i).x && m_position.x  <= m_tileMap.m_object_position.at(i).x + m_tileMap.m_object_WH.at(i).x)
		{
			if (m_velocity.y > 0)
			{
				gravity = false;
				m_velocity.y = 0;
				m_position.y = m_tileMap.m_object_position.at(i).y - animation.uvRect.height;
				jumped = false;
			}
			
	
			
		}
		else
		{
			gravity = true;
			jumped = true; 
		}
		/*if (m_position.y - m_radius <= m_tileMap.m_object_position.at(i).y + m_tileMap.m_object_WH.at(i).y && m_position.y - m_radius >= m_tileMap.m_object_position.at(i).y + m_tileMap.m_object_WH.at(i).y - 40
			&& m_position.x >= m_tileMap.m_object_position.at(i).x && m_position.x <= m_tileMap.m_object_position.at(i).x + m_tileMap.m_object_WH.at(i).x)
		{
			
			m_velocity.y = 0;
			


		}
		std::cout << gravity << std::endl;*/
		
	}
	for (int i = 0; i < m_tileMap.m_wall_position.size(); i++)
	{
		//Top of the onject 
		
		//m_position.y + animation.uvRect.height <= m_tileMap.m_wall_position.at(i).y && m_position.y >= m_tileMap.m_wall_position.at(i).y + m_tileMap.m_wall_WH.at(i).y
			//&& m_position.x + animation.uvRect.width >= m_tileMap.m_wall_position.at(i).x && m_position.x <= m_tileMap.m_wall_position.at(i).x + m_tileMap.m_wall_WH.at(i).x)
		if(m_position.x + animation.uvRect.width >= m_tileMap.m_wall_position.at(i).x && m_position.x + +animation.uvRect.width < m_tileMap.m_wall_position.at(i).x + m_tileMap.m_wall_WH.at(i).x
			&& m_position.y + animation.uvRect.height >= m_tileMap.m_wall_position.at(i).y &&  m_position.y <= m_tileMap.m_wall_position.at(i).y + m_tileMap.m_wall_WH.at(i).y)
		{
			moveX = false;
			m_velocity.x = 0;

			


		}
		else
		{
			moveX = true;
		}
		
	}
}

void Player::render(sf::RenderWindow &window)
{
	//window.clear();
	window.draw(playerRect);
}

