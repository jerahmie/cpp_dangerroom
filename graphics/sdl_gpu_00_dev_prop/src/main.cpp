#define SDL_MAIN_USE_CALLBACKS 1 // use the callbacks insteead of main()
#include <SDL3/SDL.h>
#include <SDL3/SDL_gpu.h>

/* create a window context */
static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

// This function runs once at startup.
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
	SDL_SetAppMetadata("Example Renderer Clear", "1.0", "com.example");

	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

}
