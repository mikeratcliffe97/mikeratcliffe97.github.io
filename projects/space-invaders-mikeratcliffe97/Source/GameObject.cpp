#include <Engine\Renderer.h>
#include "GameObject.h"

GameObject::~GameObject()
{
	freeSpriteComponent();
}

bool GameObject::addSpriteComponent(
	ASGE::Renderer* renderer, const std::string& texture_file_name)
{
	freeSpriteComponent();

	sprite_component = new SpriteComponent();
	if (sprite_component->loadSprite(renderer, texture_file_name))
	{
		return true;
	}

	freeSpriteComponent();
	return false;
}

void  GameObject::freeSpriteComponent()
{
	delete sprite_component;
	sprite_component = nullptr;
}


SpriteComponent* GameObject::spriteComponent() 
{
	return sprite_component;
}


bool GameObject::isvisible() const { return visibility; }

void GameObject::setVisibility(bool v) 
{ 
	visibility = v; 
}

int GameObject::get_speed()
{
	return speed;
}

void GameObject::set_speed(int spd_)
{
	speed = spd_;
}
