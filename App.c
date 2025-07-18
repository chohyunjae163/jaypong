#define SDL_MAIN_USE_CALLBACKS 1 /* use the calllbacks instead of main() */

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_stdinc.h>
#include "Physics/Particle.c"

/* We will use this renderer to draw into this window every frame. */
static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

static const double MILLISECS_PER_FRAME = 1/120 * 1000;
static Uint64 prev_ticks = 0;
static const float particle_size = 50.0f;

Particle particle = { 
	.position = { .x = 250, .y = 120 }, 
	.velocity = { .x = 50, .y = 0 } 
};

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    SDL_SetAppMetadata("Example Renderer Clear", "1.0", "com.example.renderer-clear");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("examples/renderer/clear", 640, 480, 0, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
	if (event->type == SDL_EVENT_QUIT) {
		return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
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

	//adding velocity per frame
	//todo: adding velocity per second. cuz it makes more sense. 
	//meter / sec 
	
	Vector2 added_pos = Vec2_Scale(particle.velocity, delta_time);
	particle.position = Vec2_Add(particle.position, added_pos);


	prev_ticks = current_ticks; 

	/* clear the window to the draw color. */
	SDL_SetRenderDrawColor(renderer,0,0,0,SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	const SDL_FRect rect = { .x = particle.position.x, .y = particle.position.y, .w = particle_size, .h = particle_size };

	SDL_SetRenderDrawColor(renderer,0x00,0xFF,0x00,SDL_ALPHA_OPAQUE);

	//draw circle with render lines
	{
		int cx = particle.position.x;
		int cy = particle.position.y;
		float radius = 15.0f;
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
