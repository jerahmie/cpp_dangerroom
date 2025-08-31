/*
 * A template SDL3 project that uses gpu shaders.
 */
#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>

SDL_Window *window;
SDL_GPUDevice * device;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv)
{
	// create a window
	window = SDL_CreateWindow("Hello, Triangle!", 960, 540, SDL_WINDOW_RESIZABLE);

	// create gpu device
	device = SDL_CreateGPUDevice(SDL_GPU_SHADERFORMAT_SPIRV, false, NULL);
	SDL_ClaimWindowForGPUDevice(device, window);

	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
	// close the window on request
	
	switch (event->type) {
		case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
		case SDL_EVENT_QUIT:
			return SDL_APP_SUCCESS;
			break;
		default:
			break;
	}

	return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
	// destroy the GPU device
	SDL_DestroyGPUDevice(device);

	// destroy the window
	SDL_DestroyWindow(window);
}
