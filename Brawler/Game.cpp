#include "stdafx.h"
#include "Game.h"
#include "ResourceHolder.h"

sf::Sprite circle;
const sf::Time timePerFrame = sf::seconds(1.f / 60.f);

void Game::start(void)
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	if (_gameState != Uninitialized)
		return;

	_mainWindow.create(sf::VideoMode(1024, 768, 32), "Pang!");
	_gameState = Game::Playing;

	ResourceHolder<sf::Texture, Textures::ID> textures;
	textures.load(Textures::Player, "images/Alien.png");

	circle.setTexture(textures.get(Textures::Player));
	circle.setPosition(100.f, 100.f);


	while (!isExiting())
	{
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			update(timePerFrame);
		}
	}

	_mainWindow.close();
}

bool Game::isExiting()
{
	if (_gameState == Game::Exiting)
		return true;
	else
		return false;
}

void Game::update(sf::Time deltaTime)
{
		switch (_gameState)
		{
		case Game::ShowingMenu:
		{
			showMenu();
			break;
		}

		case Game::ShowingSplash:
		{
			showSplashScreen();
			break;
		}
			
		case Game::Playing:
		{
			sf::Event currentEvent;
			while (_mainWindow.pollEvent(currentEvent))
			{
				_mainWindow.clear(sf::Color(255, 255, 0));
				_mainWindow.display();
								
				switch (currentEvent.type)
				{
				case sf::Event::KeyPressed:
				{
					if (currentEvent.key.code == sf::Keyboard::Escape) showMenu();
					handleKeyInput(currentEvent.key.code, true);
				}
				break;

				case sf::Event::KeyReleased:
					handleKeyInput(currentEvent.key.code, false);
					break;

				case sf::Event::Closed:
					_gameState = Game::Exiting;
					break;

				}

				_mainWindow.clear();
				_mainWindow.draw(circle);
				_mainWindow.display();

				sf::Vector2f movement(0.f, 0.f);
				if (mIsMovingUp)
					movement.y -= 100.f;
				if (mIsMovingDown)
					movement.y += 100.f;
				if (mIsMovingLeft)
					movement.x -= 100.f;
				if (mIsMovingRight)
					movement.x += 100.f;
				
				circle.move(movement * deltaTime.asSeconds());
			}

			break;
		}
	}
}

void Game::showSplashScreen()
{
	SplashScreen splashScreen;
	splashScreen.show(_mainWindow);
	_gameState = Game::ShowingMenu;
}

void Game::showMenu()
{
	MainMenu mainMenu;
	MainMenu::menuResult result = mainMenu.show(_mainWindow);

	switch (result)
	{
	case MainMenu::Exit:
		_gameState = Game::Exiting;
		break;
	case MainMenu::Play:
		_gameState = Game::Playing;
		break;
	}
}

void Game::handleKeyInput(sf::Keyboard::Key key,
	bool isPressed)
{
	if (key == sf::Keyboard::W)
		mIsMovingUp = isPressed;
	else if (key == sf::Keyboard::S)
		mIsMovingDown = isPressed;
	else if (key == sf::Keyboard::A)
		mIsMovingLeft = isPressed;
	else if (key == sf::Keyboard::D)
		mIsMovingRight = isPressed;
}
bool Game::mIsMovingUp = false;
bool Game::mIsMovingDown = false;
bool Game::mIsMovingLeft = false;
bool Game::mIsMovingRight = false;
Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;