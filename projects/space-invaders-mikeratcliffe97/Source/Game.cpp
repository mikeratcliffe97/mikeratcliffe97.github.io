#include <string>
#include <Engine/Keys.h>
#include <Engine/Input.h>
#include <Engine/InputEvents.h>
#include <Engine/Sprite.h>
#include <time.h>
#include "Game.h"

/**
*   @brief   Default Constructor.
*   @details Consider setting the game's width and height
			 and even seeding the random number generator.
*/
SpaceInvaders::SpaceInvaders()
{
	srand(time(NULL));
}

/**
*   @brief   Destructor.
*   @details Remove any non-managed memory and callbacks.
*/
SpaceInvaders::~SpaceInvaders()
{
	this->inputs->unregisterCallback(key_callback_id);
	this->inputs->unregisterCallback(mouse_callback_id);


}

/**
*   @brief   Initialises the game.
*   @details The game window is created and all assets required to
			 run the game are loaded. The keyHandler and clickHandler
			 callback should also be set in the initialise function.
*   @return  True if the game initialised correctly.
*/
bool SpaceInvaders::init()
{
	setupResolution();
	if (!initAPI())
	{
		return false;
	}


	toggleFPS();
	renderer->setWindowTitle("Space Invaders!");
	renderer->setClearColour(ASGE::COLOURS::BLACK);

	// input handling functions
	inputs->use_threads = false;

	key_callback_id = inputs->addCallbackFnc(
		ASGE::E_KEY, &SpaceInvaders::keyHandler, this);

	mouse_callback_id = inputs->addCallbackFnc(
		ASGE::E_MOUSE_CLICK, &SpaceInvaders::clickHandler, this);

	if (!background.addSpriteComponent(renderer.get(), ".\\Resources\\Textures\\spaceshooter\\Backgrounds\\blue.png"))
	{
		return false;
	}
	
	
	background.spriteComponent()->getSprite()->height(game_height);
	background.spriteComponent()->getSprite()->width(game_width);
	if (!player_ship.addSpriteComponent(renderer.get(), ".\\Resources\\Textures\\spaceshooter\\PNG\\playerShip1_blue.png"))
	{
		return false;
	}
	
	ASGE::Sprite* ship_sprite = player_ship.spriteComponent()->getSprite();
	ship_sprite->yPos(game_height - 100);
	ship_sprite->xPos(game_width / 2);

	bool retflag;
	bool retval = AlienRender(retflag);
	if (retflag) return retval;
	
	
	
	for (int i = 0; i < max_lasers; i++)
	{
		if (!laser_shots[i].addSpriteComponent(renderer.get(), ".\\Resources\\Textures\\spaceshooter\\PNG\\Lasers\\laserRed13.png"))
		{
			return false;
		}

		ASGE::Sprite* laser_sprite = laser_shots[i].spriteComponent()->getSprite();
		laser_shots[i].setVisibility(false);
	}

	if (!asteroid.addSpriteComponent(renderer.get(), ".\\Resources\\Textures\\spaceshooter\\PNG\\Meteors\\meteorBrown_med1.png"))
	{
		return false;
	}
	
	asteroid.setVisibility(true);
	
	//laser_shots[0].setVisibility(true);
	return true;
}



/**
*   @brief   Sets the game window resolution
*   @details This function is designed to create the window size, any 
             aspect ratio scaling factors and safe zones to ensure the 
			 game frames when resolutions are changed in size.
*   @return  void
*/
void SpaceInvaders::setupResolution()
{
	// how will you calculate the game's resolution?
	// will it scale correctly in full screen? what AR will you use?
	// how will the game be framed in native 16:9 resolutions?
	// here are some abritrary values for you to adjust as you see fit
	// https://www.gamasutra.com/blogs/KenanBolukbasi/20171002/306822/Scaling_and_MultiResolution_in_2D_Games.php
	game_width = 1024;
	game_height = 768;
}

/**
*   @brief   Processes any key inputs
*   @details This function is added as a callback to handle the game's
			 keyboard input. For this game, calls to this function
			 are thread safe, so you may alter the game's state as you
			 see fit.
*   @param   data The event data relating to key input.
*   @see     KeyEvent
*   @return  void
*/
void SpaceInvaders::keyHandler(const ASGE::SharedEventData data)
{
	auto key = static_cast<const ASGE::KeyEvent*>(data.get());

	if (key->key == ASGE::KEYS::KEY_ESCAPE)
	{
		signalExit();
	}
	//Toggles between menu options
	if (in_menu)
	{
		if (key->key == ASGE::KEYS::KEY_RIGHT &&
		key->action == ASGE::KEYS::KEY_RELEASED ||
			key->key == ASGE::KEYS::KEY_DOWN &&
			key->action == ASGE::KEYS::KEY_RELEASED)
	{
			menu_option++;
			if (menu_option > 3)
			{
				menu_option = 0;
			}
	}

	if (key->key == ASGE::KEYS::KEY_LEFT &&
		key->action == ASGE::KEYS::KEY_RELEASED ||
		key->key == ASGE::KEYS::KEY_UP &&
		key->action == ASGE::KEYS::KEY_RELEASED)
	{
		menu_option--;

		if (menu_option < 0)
		{
			menu_option = 3;
		}
	}

	
	if (key->key == ASGE::KEYS::KEY_ENTER)
	{
		in_menu = 0;
		
		switch (menu_option)
		{
		case 0:
			{
				game = GameTypes::NORMAL;
				break;
			}

		case 1:
			{
				game = GameTypes::GRAVITY;
				break;
			}

		case 2:
			{
				game = GameTypes::QUAD;
				break;
			}

		case 3:
			{
				game = GameTypes::SINE;
				break;
			}
		}
	}
	}
	
	if (!in_menu)
	{
		if (key->key == ASGE::KEYS::KEY_A &&
			key->action == ASGE::KEYS::KEY_PRESSED)
		{
			move_left = true;

		}

		if (key->key == ASGE::KEYS::KEY_A &&
			key->action == ASGE::KEYS::KEY_RELEASED)
		{
			move_left = false;
		}

		//Bool Statements to make paddle move right
		if (key->key == ASGE::KEYS::KEY_D &&
			key->action == ASGE::KEYS::KEY_PRESSED)
		{
			move_right = true;
		}

		if (key->key == ASGE::KEYS::KEY_D &&
			key->action == ASGE::KEYS::KEY_RELEASED)
		{
			move_right = false;
		}

		//Shoot
		for (int i = 0; i < 1; i++)

		{
			if (key->key == ASGE::KEYS::KEY_SPACE &&
				key->action == ASGE::KEYS::KEY_PRESSED)
			{
				laser_fired == true;
				laser_shots[i].setVisibility(true);
			}

	
		}
	}
}
/**
*   @brief   Processes any click inputs
*   @details This function is added as a callback to handle the game's
		     mouse button input. For this game, calls to this function
             are thread safe, so you may alter the game's state as you
             see fit.
*   @param   data The event data relating to key input.
*   @see     ClickEvent
*   @return  void
*/
void SpaceInvaders::clickHandler(const ASGE::SharedEventData data)
{
	auto click = static_cast<const ASGE::ClickEvent*>(data.get());

	double x_pos, y_pos;
	inputs->getCursorPos(x_pos, y_pos);
}


/**
*   @brief   Updates the scene
*   @details Prepares the renderer subsystem before drawing the
		     current frame. Once the current frame is has finished
		     the buffers are swapped accordingly and the image shown.
*   @return  void
*/
void SpaceInvaders::update(const ASGE::GameTime& us)
{
	
	ASGE::Sprite* alien_sprites = alien_ship[0].spriteComponent()->getSprite();
	ASGE::Sprite* ship_sprite = player_ship.spriteComponent()->getSprite();
	ASGE::Sprite* astro_sprite = asteroid.spriteComponent()->getSprite();
	
	//make sure you use delta time in any movement calculations!
	auto dt_sec = us.delta_time.count() / 1000.0;
	auto ship_pos = player_ship.spriteComponent()->getSprite()->xPos();


	if (!in_menu)
	{
		if ((us.game_time.count() / 1000) % 1 == 0)
		{
			tick_count++;
		}
		switch (game)
		{
			case GameTypes::NORMAL:
			{
				PlayerMovement(ship_pos, us);

				NormalAlienMovement(dt_sec);

				LaserUpdate(ship_sprite, dt_sec);

				AstroUpdate(astro_sprite, dt_sec, alien_sprites);
				for (int i = 0; i < max_aliens; i++)
				{
					if (alien_ship[i].isvisible() &&
						alien_ship[i].spriteComponent()->getSprite()->yPos() + alien_sprites->height() >= player_ship.spriteComponent()->getSprite()->yPos())
					{
						alien_win = true;
					}
				}
				break;
			}

			case GameTypes::GRAVITY:
			{
				PlayerMovement(ship_pos, us);
				
				GravityAlienMovement(dt_sec);
				
				LaserUpdate(ship_sprite, dt_sec);
				
				AstroUpdate(astro_sprite, dt_sec, alien_sprites);
				for (int i = 0; i < max_aliens; i++)
				{
					if (alien_ship[i].isvisible() &&
						alien_ship[i].spriteComponent()->getSprite()->yPos() + alien_sprites->height() >= player_ship.spriteComponent()->getSprite()->yPos())
					{
						alien_win = true;
					}
				}
				break;
				
			}

			case GameTypes::QUAD:
			{
				PlayerMovement(ship_pos, us);
			
				QuadAlienMovement(dt_sec);
			
				LaserUpdate(ship_sprite, dt_sec);
			
				AstroUpdate(astro_sprite, dt_sec, alien_sprites);
				for (int i = 0; i < max_aliens; i++)
				{
					if (alien_ship[i].isvisible() &&
						alien_ship[i].spriteComponent()->getSprite()->yPos() + alien_sprites->height() >= player_ship.spriteComponent()->getSprite()->yPos())
					{
						alien_win = true;
					}
				}
				break;
			}

			case GameTypes::SINE:
			{
				PlayerMovement(ship_pos, us);
				SineAlienMovement(dt_sec, tick_count);
				LaserUpdate(ship_sprite, dt_sec);
				AstroUpdate(astro_sprite, dt_sec, alien_sprites);
				for (int i = 0; i < max_aliens; i++)
				{
					if (alien_ship[i].isvisible() &&
						alien_ship[i].spriteComponent()->getSprite()->yPos() + alien_sprites->height() >= player_ship.spriteComponent()->getSprite()->yPos())
					{
						alien_win = true;
					}
				}
				break;
			}
		}
		
			
		}
	}








/**
*   @brief   Renders the scene
*   @details Renders all the game objects to the current frame.
	         Once the current frame is has finished the buffers are
			 swapped accordingly and the image shown.
*   @return  void
*/
void SpaceInvaders::render(const ASGE::GameTime &)
{
	renderer->setFont(0);
	ASGE::Sprite* back_sprite = background.spriteComponent()->getSprite();
	
		renderer->renderSprite(*back_sprite);
		ASGE::Sprite* ship_sprite = player_ship.spriteComponent()->getSprite();		
		ASGE::Sprite* astro_sprite = asteroid.spriteComponent()->getSprite();

	if (in_menu)
	{
		renderer->renderText("Welcome to Space Invaders!", 368, 212, 1.0, ASGE::COLOURS::WHITE);
		renderer->renderText("Destroy all the attacking Alien Ships to win", 318, 242, 1.0, ASGE::COLOURS::WHITE);
		renderer->renderText("Choose Game Mode: ", 338, 302, 1.0, ASGE::COLOURS::WHITE);

		//Options
		renderer->renderText(menu_option == 0 ? ">Normal" : "Normal", 368, 332, 1.0, ASGE::COLOURS::WHITE);
		renderer->renderText(menu_option == 1 ? ">Gravity" : "Gravity", 368, 362, 1.0, ASGE::COLOURS::WHITE);
		renderer->renderText(menu_option == 2 ? ">Quad" : "Quad", 368, 392, 1.0, ASGE::COLOURS::WHITE);
		renderer->renderText(menu_option == 3 ? ">Sine" : "Sine", 368, 422, 1.0, ASGE::COLOURS::WHITE);
	}
	else if (!alien_win && aliens_destroyed != 30)
	{
		
		renderer->renderSprite(*ship_sprite);

		std::string score_str = "SCORE: " + std::to_string(score);
		renderer->renderText(score_str, 40, 750, 1.0, ASGE::COLOURS::WHITE);

		for (int i = 0; i < max_aliens; i++)
		{
			if (alien_ship[i].isvisible())
			{
			ASGE::Sprite* alien_sprites = alien_ship[i].spriteComponent()->getSprite();

				renderer->renderSprite(*alien_sprites);
			}
		}

		
			for (int i = 0; i < max_lasers; i++)
			{
				if (laser_shots[i].isvisible())
				{
					ASGE::Sprite* laser_sprites = laser_shots[i].spriteComponent()->getSprite();
					renderer->renderSprite(*laser_sprites);
				}
			}	


			if (asteroid.isvisible())
			{
			renderer->renderSprite(*astro_sprite);
				
			}
	}
	
	else if (aliens_destroyed >= 30)
	{
		renderer->renderText("CONGRATULATIONS", 368, 212, 1.5, ASGE::COLOURS::WHITE);
		renderer->renderText("YOU WIN", 398, 242, 1.5, ASGE::COLOURS::WHITE);
		std::string final_score_str = "Your final score was: " + std::to_string(score);
		renderer->renderText(final_score_str, 288, 342, 1.5, ASGE::COLOURS::WHITE);
	}

	else 
	{
		renderer->renderText("YOU LOSE", 368, 212, 1.5, ASGE::COLOURS::WHITE);
		renderer->renderText("BAD LUCK", 368, 262, 1.5, ASGE::COLOURS::WHITE);

		std::string final_score_str = "Your final score was: " + std::to_string(score);
		renderer->renderText(final_score_str, 288, 342, 1.5, ASGE::COLOURS::WHITE);
	}
}


//Laser Movement and Collision
//Includes scoring system - 100 points for each alien hit and -20 for each shot missed and 10,000 for asteroid
void SpaceInvaders::LaserUpdate(ASGE::Sprite * ship_sprite, double dt_sec)
{
	ASGE::Sprite* astro_sprite = asteroid.spriteComponent()->getSprite();
	for (int i = 0; i < max_aliens; i++)
	{
		for (int j = 0; j < max_lasers; j++)
		{
			ASGE::Sprite* laser_sprite = laser_shots[j].spriteComponent()->getSprite();
			auto laser_ypos = laser_sprite->yPos();
			auto laser_xpos = laser_sprite->xPos();

			if (laser_shots[j].isvisible() == false)
			{
				laser_sprite->xPos(ship_sprite->xPos() + (ship_sprite->width() / 2));
				laser_sprite->yPos(ship_sprite->yPos() - (ship_sprite->height() / 2));
			}

			if (laser_shots[j].isvisible() == true)
			{

				laser_ypos -= 75 * dt_sec;


				//Alien collision
				if (laser_shots[j].spriteComponent()->getBoundingBox().isInside(
					alien_ship[ i].spriteComponent()->getBoundingBox()) == true
					&& laser_shots[j].isvisible() == true
					&& alien_ship[i].isvisible() == true)
				{
					laser_shots[j].setVisibility(false);
					alien_ship[i].setVisibility(false);
					score += 100;
					laser_sprite->yPos(ship_sprite->yPos());
					laser_sprite->xPos(ship_sprite->xPos() + (ship_sprite->width() / 2));
					aliens_destroyed++;
					break;
				}


				if (laser_shots[j].spriteComponent()->getBoundingBox().isInside(
					asteroid.spriteComponent()->getBoundingBox()) == true
					&& laser_shots[j].isvisible() == true
					&& asteroid.isvisible() == true)
				{
					laser_shots[j].setVisibility(false);
					asteroid.setVisibility(false);
					score += 10000;
					laser_sprite->yPos(ship_sprite->yPos());
					laser_sprite->xPos(ship_sprite->xPos() + (ship_sprite->width() / 2));
				
				}

				if (laser_sprite->yPos() + laser_sprite->height() <= 0)
				{
					laser_sprite->yPos(ship_sprite->yPos());
					laser_shots[j].setVisibility(false);
					shots_missed++;
					score -= 20;
				}

				laser_shots[j].spriteComponent()->getSprite()->yPos(laser_ypos);
				laser_shots[j].spriteComponent()->getSprite()->xPos(laser_xpos);
				break;
			}
		}
	}
}




bool SpaceInvaders::AlienRender(bool &retflag)
{
	retflag = true;
	int x_alien_total = 0;
	int y_alien_total = 0;
	for (int i = 0; i < max_aliens; i++)
	{
		if (i <= 9)
		{
			if (!alien_ship[i].addSpriteComponent(renderer.get(), ".\\Resources\\Textures\\spaceshooter\\PNG\\Enemies\\enemyGreen1.png"))
			{
				return false;
			}
		}

		if (i >= 10)
		{
			if (!alien_ship[i].addSpriteComponent(renderer.get(), ".\\Resources\\Textures\\spaceshooter\\PNG\\Enemies\\enemyBlue1.png"))
			{
				return false;
			}
		}

		if (i >= 20)
		{
			if (!alien_ship[i].addSpriteComponent(renderer.get(), ".\\Resources\\Textures\\spaceshooter\\PNG\\Enemies\\enemyRed1.png"))
			{
				return false;
			}
		}

		ASGE::Sprite* alien_sprites = alien_ship[i].spriteComponent()->getSprite();
		//alien_ship[i].spriteComponent()->getSprite()->xPos(x_alien_total * alien_width);
		alien_sprites->xPos((x_alien_total * alien_width) + 20);
		alien_sprites->yPos(y_alien_total * alien_height);
		 x_alien_total++;
		if (i == 9 || i == 19)
		{
			x_alien_total = 0;
			y_alien_total++;
		}
		
		
	}
	retflag = false;
	return {};
}

void SpaceInvaders::PlayerMovement(float &ship_pos, const ASGE::GameTime & us)
{
	//Ship Movement
	if (move_left)
	{
		if (player_ship, ship_pos >= 0)
		{
			ship_pos -= player_ship.get_speed() * (us.delta_time.count() / 1000.f);
		}

		else
		{
			move_left = false;
		}
	}
	if (move_right)
	{
		if (player_ship, ship_pos + player_ship.spriteComponent()->getSprite()->width() <= game_width)
		{
			ship_pos += player_ship.get_speed() * (us.delta_time.count() / 1000.f);
		}

		else
		{
			move_right = false;
		}
	}
	player_ship.spriteComponent()->getSprite()->xPos(ship_pos);
}



void SpaceInvaders::AstroUpdate(ASGE::Sprite * astro_sprite, double dt_sec, ASGE::Sprite * alien_sprites)
{
	auto astro_ypos = astro_sprite->yPos();
	auto astro_xpos = astro_sprite->xPos();
	astro_xpos += (asteroid.get_speed() / 2) * dt_sec;

	if (astro_sprite->xPos() + astro_sprite->width() >= game_width)
	{
		astro_xpos = 0;
		astro_sprite->yPos(alien_sprites->yPos() - alien_height);
		astro_sprite->xPos(astro_xpos);
	}

	astro_sprite->xPos(astro_xpos);
}

//Alien Movement and Wall collision
//Aliens move across the X axis according to vectors
//Aliens move down 20 pixels per second according to dt_sec
void SpaceInvaders::NormalAlienMovement(double dt_sec)
{
	for (int i = 0; i < max_aliens; i++)
	{
		ASGE::Sprite* alien_sprites = alien_ship[i].spriteComponent()->getSprite();
		auto alien_x_pos = alien_ship[i].spriteComponent()->getSprite()->xPos();
		auto alien_y_pos = alien_ship[i].spriteComponent()->getSprite()->yPos();

		if (alien_ship[i].isvisible())
		{
			// left/right
			if (alien_ship[i].spriteComponent()->getSprite()->xPos() + alien_width >= game_width && bounce_right)
			{

				alien_movement.x_set(alien_movement.get_x() * -1);


				bounce_right = false;
				bounce_left = true;

			}
			else if (alien_ship[i].spriteComponent()->getSprite()->xPos() <= 0 && bounce_left)
			{

				alien_movement.x_set(alien_movement.get_x() * -1);
				bounce_right = true;
				bounce_left = false;
			}

			alien_y_pos += 20 * dt_sec;

			//Update Position
			alien_ship[i].spriteComponent()->getSprite()->xPos(alien_x_pos + alien_ship[i].get_speed() / 10 * alien_movement.get_x() * dt_sec);
			alien_ship[i].spriteComponent()->getSprite()->yPos(alien_y_pos);


		}
	}
}



//Alien Movement and Wall collision
//Aliens move across the X axis according to vectors
//Aliens move down 20 pixels per second according to dt_sec
void SpaceInvaders::GravityAlienMovement(double dt_sec)
{
	
	for (int i = 0; i < max_aliens; i++)
	{
		ASGE::Sprite* alien_sprites = alien_ship[i].spriteComponent()->getSprite();
		auto alien_x_pos = alien_ship[i].spriteComponent()->getSprite()->xPos();
		auto alien_y_pos = alien_ship[i].spriteComponent()->getSprite()->yPos();


		gravity += 0.0005;

		if (alien_ship[i].isvisible())
		{
			// left/right
			if (alien_ship[i].spriteComponent()->getSprite()->xPos() + alien_width >= game_width && bounce_right)
			{

				alien_movement.x_set(alien_movement.get_x() * -1);


				bounce_right = false;
				bounce_left = true;

			}
			else if (alien_ship[i].spriteComponent()->getSprite()->xPos() <= 0 && bounce_left)
			{

				alien_movement.x_set(alien_movement.get_x() * -1);
				bounce_right = true;
				bounce_left = false;
			}




			//((gravity * alien_ship[29].spriteComponent()->getSprite()->yPos()) * (dt_sec) / 2);

			//Alien Down Movement
			alien_x_pos += (((gravity)* alien_ship[i].get_speed() / 10) * (alien_movement.get_x() * (dt_sec / 1000)));
			alien_y_pos += (((gravity)* alien_ship[i].get_speed() / 10) * (dt_sec / 1000));
			//Update Position
			alien_ship[i].spriteComponent()->getSprite()->xPos(alien_x_pos);
			alien_ship[i].spriteComponent()->getSprite()->yPos(alien_y_pos);

		}

		}
	}


//Alien Movement and Wall collision
//Aliens move across the X axis according to vectors
//Aliens move down 20 pixels per second according to dt_sec
void SpaceInvaders::QuadAlienMovement(double dt_sec)
{
	for (int i = 0; i < max_aliens; i++)
	{
		ASGE::Sprite* alien_sprites = alien_ship[i].spriteComponent()->getSprite();
		auto alien_x_pos = alien_ship[i].spriteComponent()->getSprite()->xPos();
		auto alien_y_pos = -0.001 * pow((-alien_x_pos + (game_width / 2)), 2) - curve_base;

		if (i != 0 && i % 10 == 0)
		{
			curve_base -= alien_width;
			alien_y_pos= (alien_ship[0].spriteComponent()->getSprite()->yPos() + (alien_width * (i / 10)));
		}

		if (alien_ship[i].isvisible())
		{
			// left/right
			if (alien_ship[i].spriteComponent()->getSprite()->xPos() + alien_width >= game_width && bounce_right)
			{

				alien_movement.x_set(alien_movement.get_x() * -1);
				
				if (bounce_right)
				{
					collision_count++;
				
				}	
				bounce_right = false;
				bounce_left = true;

			}
			
			else if (alien_ship[i].spriteComponent()->getSprite()->xPos() <= 0 && bounce_left)
			{

				alien_movement.x_set(alien_movement.get_x() * -1);				
				if (bounce_left)
				{
					collision_count++;
				}
				bounce_right = true;
				bounce_left = false;


			}
		}
		alien_ship[i].spriteComponent()->getSprite()->xPos(alien_x_pos + alien_ship[i].get_speed() / 10 * alien_movement.get_x() * dt_sec);
		alien_ship[i].spriteComponent()->getSprite()->yPos(alien_y_pos);
	}

	 curve_base = ((8 - (game_height / 4)) - (collision_count * 10));
}


//Alien Movement and Wall collision
//Aliens move across the X axis according to vectors
//Aliens move down 20 pixels per second according to dt_sec
void SpaceInvaders::SineAlienMovement(double dt_sec, int ticks)
{ 
	for (int i = 0; i < max_aliens; i++)
	{
	
		ASGE::Sprite* alien_sprites = alien_ship[i].spriteComponent()->getSprite();
		auto alien_x_pos = alien_ship[i].spriteComponent()->getSprite()->xPos();
		auto alien_y_pos = alien_ship[i].spriteComponent()->getSprite()->yPos();

		if (alien_ship[i].isvisible())
		{
			// left/right
			if (alien_ship[i].spriteComponent()->getSprite()->xPos() + alien_width >= game_width && bounce_right)
			{

				alien_movement.x_set(alien_movement.get_x() * -1);
			

				bounce_right = false;
				bounce_left = true;

			}
			else if (alien_ship[i].spriteComponent()->getSprite()->xPos() <= 0 && bounce_left)
			{

				alien_movement.x_set(alien_movement.get_x() * -1);
				bounce_right = true;
				bounce_left = false;
			}

			//Alien Down Movement
			alien_y_pos += 30 * sin(ticks / 180) * (dt_sec);
			alien_y_pos += 20 * dt_sec;
		}


		//Update Position
		alien_ship[i].spriteComponent()->getSprite()->xPos(alien_x_pos + alien_ship[i].get_speed() / 10 * alien_movement.get_x() * dt_sec);
		alien_ship[i].spriteComponent()->getSprite()->yPos(alien_y_pos);


	}
}