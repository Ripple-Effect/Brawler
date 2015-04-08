#pragma once

class Game
{

public:
	static void start();

private:
	static bool mIsMovingUp, mIsMovingDown, mIsMovingLeft, mIsMovingRight;
	static bool isExiting();
	static void update(sf::Time deltaTime);
	static void handleKeyInput(sf::Keyboard::Key key, bool isPressed);

	static void showSplashScreen();
	static void showMenu();

	enum GameState {Uninitialized, ShowingSplash, Paused, ShowingMenu, Playing, Exiting};

	static GameState _gameState;
	static sf::RenderWindow _mainWindow;
};
