/* primatives.cpp ... */

/*
 * This example code creates an SDL window and renderer, and then clears the
 * window to a different color every frame, so you'll effectively get a window
 * that's smoothly fading between colors.
 *
 * This code is public domain. Feel free to use it for any purpose!
 */

#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

// Create frame renderer and window
static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_FPoint points[500];


// SDL Initialize Window -- called once at startup
SDL_AppResult SDL_AppInit(void **appstate, int *argc, char *argv[])
{
	SDL_SetAppMetadata("Example Renderer Primitives", "1.0", "com.example.renderer-primitives");
	
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_Log("Could not initialize SDL: %s", SDL_GetError());
		return SDL_APP_FAILURE;	
	}

	if(!SDL_CreateWindowAndRenderer("renderer/primitives", 640, 480, 0, &window, &renderer)) {
		SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	// create set of random points
	for (int i = 0; i < SDL_arraysize(points); i++) {
		points[i].x = (SDL_randf() * 440.0f) + 100.0f;
		points[i].y = (SDL_randf() * 280.0f) + 100.0f;
	}

	return SDL_APP_CONTINUE; 
}

// Handle App Events
SDL_AppResult SDL_AppEvent(void ** appstate, SDL_Event *event)
{
	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
	return SDL_APP_CONTINUE;
}

// Exit SdL App
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
	// Will clean up window/renderer.
}
