#pragma once
#include<iostream>
#include<vector>
#include<ctime>
#include<sstream>
#include<cmath>
#include<stdlib.h>
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include <list>
#include <iterator>

class FlyBirdGame 
{
	private:
		//Window
		
		sf::Event ev;
		const unsigned WINDOW_WIDTH = 800;
		const unsigned WINDOW_HEIGHT = 600;
		sf::RenderWindow* window; 

		//Resources
		sf::Font font;
	    sf::Texture background;
		sf::Texture endGameTexture;
		sf::Texture buttonRestart;
		sf::Texture buttonStart;
		sf::Sprite backgroundView;
		sf::Sprite restartGame;
		sf::Sprite startGame;
		//Text
		sf::Text Text;

		//Game logic
		
		int points;
		int health;


		//Mouse positions
		sf::Vector2i mousePosWindow;
		sf::Vector2f mousePosView;

		//time control
		float birdFlyTimer;
		float planeSpawnTimer;
		

		float planeSpeed;
		

		//Game objects
		std::vector<sf::Sprite> planes;
		sf::Sprite plane;
		sf::Texture plane_texture;

		std::vector<sf::Sprite> coins;
		sf::Sprite coin;
		sf::Texture coin_texture;

		sf::Sprite bird;
		sf::Texture bird_texture1;
		sf::Texture bird_texture2;



		float movementSpeed = 400.f;
		float movementSpeedBird = 400.f;
		sf::Vector2f velocity;
		sf::Vector2f planeVelocity;
		sf::FloatRect nextPos;


		//wall generator timer
		double timer = 0.0001;


		float dt;
		sf::Clock dt_clock;
		

		//bird animation
		double timer_animation = 0.0001;
		double dt_timer;
		sf::Clock game_clock;

		//number if health
		int endGame = 3;

		sf::Font openSans;
		sf::Text GameStatus;
		sf::Text GameStatusEnd;
		sf::Text GameTitle;
		sf::Text GameRules;

		//make plane moving faster
		int speedLevel = 1;
		
		int restarted = 0;
		int start_game = 0;
		int startWindowDisplay = 1;
	public:
		
		FlyBirdGame();
		void updateMousePositions();
		void setWindow();
	    bool isEndGame();
		void setEndGameWindow();
		void setPlayer();
		void setPlanes();
		void setCoins();
		void initAssets();
		void FlyBirdGameStart();
		void setFont();
		void detectCollision();
		void screenCollision();
		void setStartGameWindow();
		void makeGameHarder();
		


};
