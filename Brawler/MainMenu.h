#pragma once
#include "stdafx.h"
#include <list>

class MainMenu
{
public:
	enum menuResult{Nothing, Exit, Play};
	struct MenuItem
	{
	public:
		sf::Rect<int> rect;
		menuResult action;
	};

	menuResult show(sf::RenderWindow &window);

private:
	menuResult getMenuResponse(sf::RenderWindow &window);
	menuResult handleClick(int x, int y);
	std::list<MenuItem> _menuItems;

};