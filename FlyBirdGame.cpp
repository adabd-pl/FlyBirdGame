#include "FlyBirdGame.h"

void FlyBirdGame::initAssets()
{
	this->background.loadFromFile("assets/background.png");
	this->endGameTexture.loadFromFile("assets/EndGame.png");
	this->bird_texture1.loadFromFile("assets/bird1.png");
	this->bird_texture2.loadFromFile("assets/bird2.png");
	this->coin_texture.loadFromFile("assets/coin.png");
	this->plane_texture.loadFromFile("assets/plane.png");
	this->buttonRestart.loadFromFile("assets/reset.png");
	this->buttonStart.loadFromFile("assets/start.png");
	this->restartGame.setTexture(this->buttonRestart);
	sf::Vector2f scale = this->restartGame.getScale();
	this->restartGame.setScale(scale.x * 0.05, scale.y * 0.05);
	this->startGame.setTexture(this->buttonStart);
	scale = this->startGame.getScale();
	this->startGame.setScale(scale.x * 0.15, scale.y * 0.15);
}

void FlyBirdGame::FlyBirdGameStart()
{
	srand(time(NULL));
	this->dt_timer = this->dt_clock.restart().asSeconds();
	int randPosition = rand() % 100 + 1;
	int k = 0;
	this->game_clock.restart();
	this->speedLevel = 1;
	while ( start_game<=2 )

	{
		std::cout << "Game_clock time: " << this->game_clock.getElapsedTime().asSeconds()  << start_game  << "endGame: " << endGame << std::endl;

		sf::Event event;
		while (this->window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				this->window->close();
		
		}
		//if (start_game == 1) {
			
		//	start_game = 0;
		//}

		if (this->endGame <= 0) {

			//render endGame window
			this->setEndGameWindow();

		}
		else {
			
			dt = dt_clock.restart().asSeconds();


			if (this->game_clock.getElapsedTime().asSeconds() > timer && start_game <2) {
				if (this->planes.size() < 5) {

					randPosition = rand() % (WINDOW_HEIGHT - 50) + 1;
					this->plane.setPosition(WINDOW_WIDTH, randPosition);
					this->planes.push_back(this->plane);
				}

				if (this->coins.size() < 20) {
					randPosition = rand() % (WINDOW_HEIGHT - 50) + 1;
					this->coin.setPosition(WINDOW_WIDTH, randPosition);
					this->coins.push_back(this->coin);
				}

				timer += 1;
			}
			

			if (this->game_clock.getElapsedTime().asSeconds() > timer_animation && start_game < 2) {

				if (k == 0) {
					bird.setTexture(this->bird_texture1);
					k = 1;
				}
				else if (k == 1) {
					bird.setTexture(this->bird_texture2);
					k = 0;
				}
				timer_animation += 0.5;
			}

			//check to make planes faster after each 10sec
			if (this->game_clock.getElapsedTime().asSeconds() > speedLevel * 10 && start_game < 2) {
				this->makeGameHarder();
			}
			

			//Player movement
			velocity.y = 0.f;
			velocity.x = 0.f;

			planeVelocity.y = 0.f;
			planeVelocity.x = 0.f;

			//plane
			planeVelocity.x -= (movementSpeed / 2)* dt;

			//move bird
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				velocity.y += -movementSpeedBird * dt;
			}
			else {
				velocity.y -= (-movementSpeedBird + 100.f) * dt;
			}


			//Collision with plane
			for (auto &wall : planes)
			{
				sf::FloatRect playerBounds = this->bird.getGlobalBounds();
				sf::FloatRect wallBounds = wall.getGlobalBounds();

				nextPos = playerBounds;
				nextPos.left += velocity.x;
				nextPos.top += velocity.y;

				if (wallBounds.intersects(nextPos))
				{

					if (playerBounds.top != wallBounds.top
						&& playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height
						&& playerBounds.left < wallBounds.left + wallBounds.width
						&& playerBounds.left + playerBounds.width > wallBounds.left
						)
					{
						this->detectCollision();
					}


					else if (playerBounds.left != wallBounds.left
						&& playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width
						&& playerBounds.top < wallBounds.top + wallBounds.height
						&& playerBounds.top + playerBounds.height > wallBounds.top
						)
					{
						this->detectCollision();
					}
				}

			}
			window->clear();
			window->draw(this->backgroundView);

			//get coin
			for (auto &wall : coins)
			{
				sf::FloatRect playerBounds = bird.getGlobalBounds();
				sf::FloatRect wallBounds = wall.getGlobalBounds();

				nextPos = playerBounds;
				nextPos.left += velocity.x;
				nextPos.top += velocity.y;

				if (wallBounds.intersects(nextPos))
				{
					//Bottom collision
					if (playerBounds.top != wallBounds.top
						&& playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height
						&& playerBounds.left < wallBounds.left + wallBounds.width
						&& playerBounds.left + playerBounds.width > wallBounds.left
						)
					{
						points += 1;
						int randPosition = rand() % (WINDOW_HEIGHT -50) + 1;
						wall.setPosition(800, randPosition);


					}


					//Right collision
					if (playerBounds.left != wallBounds.left
						&& playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width
						&& playerBounds.top < wallBounds.top + wallBounds.height
						&& playerBounds.top + playerBounds.height > wallBounds.top
						)
					{
						points += 1;
						int randPosition = rand() % (WINDOW_HEIGHT-50) + 1;
						wall.setPosition(800, randPosition);

					}

				}
				else {
					if (wall.getPosition().x < -100) {
						int randPosition = rand() % (WINDOW_HEIGHT - 50) + 1;
						wall.setPosition(800, randPosition);
					}
					wall.move(planeVelocity);
					window->draw(wall);
				}

			}

			bird.move(velocity);

			this->screenCollision();

			//Render
			if (start_game == 2) {
				start_game--;
				planes.clear();
				coins.clear();
				this->bird.setPosition(20, WINDOW_HEIGHT / 2);
				window->draw(this->bird);
				this->game_clock.restart();
				movementSpeed = 400.f;
			}
			window->draw(this->bird);
			std::stringstream ss;

			ss << "Points: " << points << "\n"
				<< "Health: " << endGame << "\n";

			GameStatus.setString(ss.str());


			for (auto &wall : planes)
			{
				if (wall.getPosition().x < -200) {
					int randPosition = rand() % (WINDOW_HEIGHT - 50) + 1;
					wall.setPosition(800, randPosition);
				   
				}
				wall.move(planeVelocity);
				window->draw(wall);
			}
			window->draw(GameStatus);
			window->display();
			
		}
	}
}

void FlyBirdGame::setWindow()
{

	this->window->setFramerateLimit(120);
	this->backgroundView = sf::Sprite(this->background);
	this->setStartGameWindow();
	
}

bool FlyBirdGame::isEndGame()
{

	return true;
}

void FlyBirdGame::setEndGameWindow()
{
	sf::Sprite test(this->endGameTexture);
	this->updateMousePositions();

	restartGame.setPosition(330, 400);
	test.setPosition(280, 120);
	
	
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{

		if (this->restartGame.getGlobalBounds().contains(this->mousePosView))
		{
			start_game = 2;
			points = 0;
			speedLevel = 1;
			timer = 0.0001;
			timer_animation = 0.0001;

			this->game_clock.restart();

			this->window->draw(backgroundView);
			this->bird.setPosition(20, WINDOW_HEIGHT / 2);

			velocity.y = 0.f;
			velocity.x = 0.f;


			bird.move(velocity);
			this->window->draw(bird);

			this->planes.clear();
			this->coins.clear();
			this->window->display();
			restarted = 0;
			endGame = 3;
		}
	}

	std::stringstream ss;
	ss << "Your score: " << points << "\n";
	GameStatusEnd.setFont(this->openSans);
	GameStatusEnd.setString(ss.str());
	GameStatusEnd.setFillColor(sf::Color(0, 0, 0, 255));
	GameStatusEnd.setPosition(270, 320);


	this->window->clear(sf::Color(0, 200, 0, 255));
	this->window->draw(backgroundView);
	
	this->window->draw(test);
	this->window->draw(GameStatusEnd);
	this->window->draw(restartGame);
	this->window->display();

}

void FlyBirdGame::setPlayer()
{
	this->bird = sf::Sprite(this->bird_texture1);
	sf::Vector2f scale = this->bird.getScale();
	this->bird.setScale(scale.x * 0.2, scale.y * 0.2);
	this->bird.setPosition(20, 300);
}

void FlyBirdGame::setPlanes()
{
	planeVelocity.y = 0.f;
	planeVelocity.x = 0.f;
	
	this->plane_texture.setSmooth(true);
	this->plane.setTexture(this->plane_texture);
	sf::Vector2f scale_plane = this->plane.getScale();
	this->plane.setScale(scale_plane.x * 0.1, scale_plane.y * 0.1);
	this->plane.setPosition(this->WINDOW_WIDTH, this->WINDOW_HEIGHT/2);
	this->plane.move(planeVelocity);
}

void FlyBirdGame::setCoins()
{
	this->coin_texture.setSmooth(true);
	this->coin.setTexture(this->coin_texture);
	sf::Vector2f scale_coin = this->coin.getScale();
	this->coin.setScale(scale_coin.x * 0.04, scale_coin.y * 0.04);
	this->coin.setPosition(this->WINDOW_WIDTH, this->WINDOW_HEIGHT / 2);
}

void FlyBirdGame::setFont() {
	this->openSans.loadFromFile("assets/slkscr.ttf");
	this->GameStatus.setFont(this->openSans);
}

void FlyBirdGame::detectCollision() {
	endGame -= 1;
	velocity.y = 0.f;
	this->bird.setPosition(20, this->WINDOW_HEIGHT/2);
	this->planes.clear();
	this->coins.clear();
}

void FlyBirdGame::screenCollision() {
	//Left collision
	if (bird.getPosition().x < 0.f)
		bird.setPosition(0.f, bird.getPosition().y);
	//Top collision
	if (bird.getPosition().y < 0.f)
		bird.setPosition(bird.getPosition().x, 0.f);
	//Right collision
	if (bird.getPosition().x + bird.getGlobalBounds().width > WINDOW_WIDTH)
		bird.setPosition(WINDOW_WIDTH - bird.getGlobalBounds().width, bird.getPosition().y);
	//Bottom collision
	if (bird.getPosition().y + bird.getGlobalBounds().height > WINDOW_HEIGHT)
		bird.setPosition(bird.getPosition().x, WINDOW_HEIGHT - bird.getGlobalBounds().height);
}

void FlyBirdGame::makeGameHarder() {
	this->speedLevel++;
	this->movementSpeed += 100.f;
}

void FlyBirdGame::updateMousePositions()
{

	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void FlyBirdGame::setStartGameWindow()
{
	while (this->window->isOpen())
	{
		sf::Event event;
		while (this->window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				this->window->close();

		}
		this->updateMousePositions();

		if (startWindowDisplay == 1) {
			startGame.setPosition(305, 420);

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (this->startGame.getGlobalBounds().contains(this->mousePosView))
				{


					startWindowDisplay = 0;
					this->setCoins();
					this->setPlanes();
					this->setPlayer();
					start_game = 1;
					this->FlyBirdGameStart();
				}

			}
			if (startWindowDisplay == 1) {
				std::stringstream ss;
				ss << "Fly Bird!";
				GameTitle.setFont(this->openSans);
				GameTitle.setString(ss.str());
				GameTitle.setCharacterSize(80);
				GameTitle.setFillColor(sf::Color(0, 0, 0, 255));

				GameTitle.setPosition(190, 120);
				std::stringstream ss1;
				ss1 << "Fly up - backspace\nYou have 3 healths \nCoin - 1 point \nAfter each 10 s\ngame is faster \n             Enjoy!\n";

				GameRules.setFont(this->openSans);
				GameRules.setString(ss1.str());
				GameRules.setFillColor(sf::Color(0, 0, 0, 255));
				GameRules.setCharacterSize(25);
				GameRules.setPosition(250, 240);


				window->draw(backgroundView);
				window->draw(startGame);
				window->draw(GameTitle);
				window->draw(GameRules);
				window->display();
			}
		}

	}
}

FlyBirdGame::FlyBirdGame() {
	this->window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Game");
}

int main()
{
	FlyBirdGame game =  FlyBirdGame();

	game.initAssets();
	game.setFont();
	game.setWindow();
	


}

