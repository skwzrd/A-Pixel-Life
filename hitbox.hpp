#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

const int j = 2;

class HitBox
{

private:
	int points;
	float xPos;
	float yPos;
	float w;
	float h;


public:
	enum locations {
		left_top = 0,
		left_middle = 2,
		left_bottom = 4,
		right_top = 1,
		right_middle = 3,
		right_bottom = 5
	};
	
	HitBox();
	HitBox(float _xPos, float _yPos, float _w, float _h, int _points);
	~HitBox();

	std::string getBlockNameAtPositionN(int n, float margin = 0);
	int getBlockAtPositionN(int n, float margin = 0);

	sf::Vector2f getPositionN(int n, float margin = 0) throw();


	void update(float _xPos, float _yPos);
	bool validPosition();
	bool feetInSky();

	sf::RectangleShape getShape();
};
