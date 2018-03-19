
#pragma once
#include <string>
#include <Engine/OGLGame.h>
#include <time.h>
#include "GameObject.h"
#include "Rect.h"


/**
*  An OpenGL Game based on ASGE.
*/
class SpaceInvaders :
	public ASGE::OGLGame
{
public:
	SpaceInvaders();
	~SpaceInvaders();
	virtual bool init() override;
	bool AlienRender(bool &retflag);
	

private:
	void keyHandler(const ASGE::SharedEventData data);
	void clickHandler(const ASGE::SharedEventData data);
	void setupResolution();

	virtual void update(const ASGE::GameTime &) override;
	void AstroUpdate(ASGE::Sprite * astro_sprite, double dt_sec, ASGE::Sprite * alien_sprites);
	void LaserUpdate(ASGE::Sprite * ship_sprite, double dt_sec);

	void NormalAlienMovement(double dt_sec);

	void GravityAlienMovement(double dt_sec);
	void QuadAlienMovement(double dt_sec);
	void SineAlienMovement(double dt_sec, int ticks);
	void PlayerMovement(float &ship_pos, const ASGE::GameTime & us);
	virtual void render(const ASGE::GameTime &) override;

	int  key_callback_id = -1;	        /**< Key Input Callback ID. */
	int  mouse_callback_id = -1;        /**< Mouse Input Callback ID. */

	enum class GameTypes : int{NORMAL, GRAVITY, QUAD, SINE};
	GameTypes game = GameTypes::NORMAL;
	//Add your GameObjects
	GameObject background;

	GameObject player_ship;
	
	static const int max_aliens = 30;
	GameObject alien_ship[max_aliens] = {};
	int alien_width = 93;
	int alien_height = 84;
	int aliens_destroyed = 0;
	bool alien_win = false;
	int collision_count = 0;
	
	GameObject laser_shots[5] = {};
	int max_lasers = 5;
	bool laser_fired = false;
	int shots_missed = 0;
	
	GameObject asteroid;

	bool in_menu = true;
	int menu_option = 0;
	
	//Ship Movement
	bool move_left = false;
	bool move_right = false;
	bool bounce_right = true;
	bool bounce_left = false;

	int score = 0;
	
	float gravity = 0;
	int tick_count = 0;
	int curve_change = 7;
	int curve_base = (8 - game_height / 4);
	vector2 alien_movement{ 2, 1 };
};