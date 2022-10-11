#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <Math.hpp>
#include <iostream>

class Entity
{
public:
	Entity(Vector2f p_pos, SDL_Texture* p_tex, int ID);
	Vector2f& getPos()
	{
		return pos;
	}
	SDL_Texture* getTex();
	SDL_Rect getCurrentFrame();
	int getID();
	bool onGround = false;
	void updatePos(Vector2f p_pos)
	{
		pos = p_pos;
	}
	void updateAcc(Vector2f p_acc)
	{
		acc = p_acc;
	}
	void changeID(int p_ID)
	{
		ID = p_ID;
	}

private:
	Vector2f acc;
	Vector2f pos;
	SDL_Rect currentFrame;
	SDL_Texture* tex;
	int ID;
};