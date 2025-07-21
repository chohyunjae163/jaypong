#define SDL_MAIN_USE_CALLBACKS 1 /* use the calllbacks instead of main() */

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_stdinc.h>
#include "Physics/Particle.c"

/* We will use this renderer to draw into this window every frame. */
static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

static const int WINDOW_SIZE = 640;

static const double FPS = 120.0;
static const double MILLISECS_PER_FRAME = 1/120 * 1000;
static const float particle_size = 50.0f;

static Uint64 prev_ticks = 0;
static const Uint64 PIXELS_PER_METER = 50;
static const float GRAVITY = 9.8;
static Vector2 input_force = { .x = 0, .y = 0 };

//todo: create a fluid
static SDL_FRect liquid;

#define NUM_PARTICLE 10

Particle particles[NUM_PARTICLE];

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    SDL_SetAppMetadata("Example Renderer Clear", "1.0", "com.example.renderer-clear");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("examples/renderer/clear", WINDOW_SIZE, WINDOW_SIZE, 0, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

		particles[0].position.x = 250.0;
		particles[0].position.y = 50.0;
		particles[0].mass = 1.0f;

		liquid.x = 0;
		liquid.y = WINDOW_SIZE / 2;
		liquid.w = WINDOW_SIZE;
		liquid.h = WINDOW_SIZE / 2;

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
	if (event->type == SDL_EVENT_QUIT) {
		return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
	}

	//handle inputs
	switch(event->type) {
		case SDL_EVENT_KEY_DOWN:
			switch (event->key.scancode) {
			case SDL_SCANCODE_W: break; //go up
			case SDL_SCANCODE_A: break; //go left
			case SDL_SCANCODE_S: break; //go down
			case SDL_SCANCODE_D: break; //go right
		} break;
		case SDL_EVENT_KEY_UP:
			switch (event->key.scancode) {
				case SDL_SCANCODE_W: break; //zero out
				case SDL_SCANCODE_A: break; //zero out
				case SDL_SCANCODE_S: break; //zero out
				case SDL_SCANCODE_D: break; //zero out
		} break;
	}


	return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void *appstate)
{
	
	Uint64 current_ticks = SDL_GetTicks();
	int timeToWait = MILLISECS_PER_FRAME - (current_ticks - prev_ticks);
	if (timeToWait > 0) {
		SDL_Delay(timeToWait);
	}
	double delta_time = (current_ticks - prev_ticks) / 1000.0f;

	// add force to a particle
	Vector2 force = { .x = 0, .y = 0 };

	// apply a weightforce to my particles
	Vector2 weight = { .x = 0.0f, .y = particles[0].mass * GRAVITY * PIXELS_PER_METER };
	force = Vec2_Add(force, weight);

	force = Vec2_Add(force, input_force);

	//integrate the acceleration and the velocity to find the new position
	Particle_Integrate(&particles[0], force, delta_time);


	//TODO:
	//check the particle position, and keep the particle inside the boundaries of the window
	

	//update prev_ticks
	prev_ticks = current_ticks; 

	/* clear the window to the draw color. */
	SDL_SetRenderDrawColor(renderer,0,0,0,SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	//draw liquid
	SDL_SetRenderDrawColor(renderer,0x00,0x00,0xFF,SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(renderer,&liquid);

	//draw particles
	SDL_SetRenderDrawColor(renderer,0x00,0xFF,0x00,SDL_ALPHA_OPAQUE);
	//draw circle with render lines
	{
		int cx = particles[0].position.x;
		int cy = particles[0].position.y;
		const float radius = PARTICLE_RADIUS;
		for (int dy = -radius; dy <= radius; ++dy) {
			int dx = (int)(SDL_sqrtf(radius * radius - dy * dy));
			int x1 = cx - dx;
			int x2 = cx + dx;
			SDL_RenderLine(renderer, x1, cy + dy, x2, cy + dy);
		}
	}

	/* put the newly-cleared rendering on the screen. */
	SDL_RenderPresent(renderer);

	return SDL_APP_CONTINUE;  /* carry on with the program! */
}



/* This function runs once at shutdown. */
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
	/* SDL will clean up the window/renderer for us. */
}
