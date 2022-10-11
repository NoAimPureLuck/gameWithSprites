#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

#include "RenderWindow.hpp"
#include "Entity.hpp"


int main(int argc, char* args[])
{
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		std::cout << "HEY.. SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;

	if (!(IMG_Init(IMG_INIT_PNG)))
		std::cout << "IMG_init has failed. Error: " << SDL_GetError() << std::endl;
	SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode(0, &DM);
	auto Width = DM.w;
	auto Height = DM.h;
	RenderWindow window("GAME v1.0", Width, Height);
	Width /= 4;
	Height /= 4;

	std::vector<Entity> entitiees;
	// Function to render grass floor
	SDL_Texture* grassTexture = window.loadTexture("res/gfx/ground_grass_1.png");
	entitiees.push_back(Entity(Vector2f(256, Height - 64), grassTexture, 1));
	for (int i = 0; i <= Width; i += 32)
	{
		entitiees.push_back(Entity(Vector2f(i, Height - 32), grassTexture, 0));
	}
	bool gameRunning = true;

	// Player
	SDL_Texture* playerTexture = window.loadTexture("res/gfx/player.png");
	Entity player(Vector2f(0, 0), playerTexture, 0);
	player.changeID(1);
	// Make a way to move the player in the player function
	SDL_Event event;

	while (gameRunning)
	{
		// Get our controls and events
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				gameRunning = false;
		}

		window.clear();
        const Uint8* keystates = SDL_GetKeyboardState(NULL);
		if(keystates[SDL_SCANCODE_A]) {
            player.updatePos(Vector2f(player.getPos().x - 0.3, player.getPos().y));
			// player.changeID(0);
        }
        if(keystates[SDL_SCANCODE_D]) {
            player.updatePos(Vector2f(player.getPos().x + 0.3, player.getPos().y));
			// player.changeID(1);
        }
		if (player.getPos().y > Height - 64)
		{
			player.onGround = true;
			player.updatePos(Vector2f(player.getPos().x, Height - 64));
		}
		
		if (player.onGround == false)
			player.updatePos(Vector2f(player.getPos().x, player.getPos().y + 0.1));
		entitiees.push_back(player);
		for (Entity& e : entitiees)
		{ 
			window.render(e);
		}
		entitiees.pop_back();

		window.display();

	}

	window.cleanUp();
	SDL_Quit();

	return 0;
}

// Fix missing pixels on grass
// Collition with entitiees
// Jump
// Make new header file with blocks and one with entities
// animated player
// texture atlas
// camera follow the player