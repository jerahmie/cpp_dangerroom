/*
 * A template SDL3 project that uses gpu shaders.
 */
#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>

SDL_Window *window;
SDL_GPUDevice *device;
SDL_GPUBuffer *vertexBuffer;
SDL_GPUTransferBuffer *transferBuffer;
SDL_GPUGraphicsPipeline *graphicsPipeline;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv)
{
	// create a window
	window = SDL_CreateWindow("Hello, Triangle!", 960, 540, SDL_WINDOW_RESIZABLE);

	// create gpu device
	device = SDL_CreateGPUDevice(SDL_GPU_SHADERFORMAT_SPIRV, false, NULL);
	SDL_ClaimWindowForGPUDevice(device, window);

	// load vertex shader code
	//
	// create vertex shader
	//
	// free the file
	//
	// load the fragment shader code
	//
	// create the fragment shader
	//
	// free the file
	//
	// describe the vertex buffers
	//
	// describe the vertex attribute
	//
  // a_position
	//
	// a_color
	//
	// describe the color target
	//
	// create the pipeline
	//
	// release shaders
	//
	// create the vertex buffer
	//
	// create a transfer buffer to upload to the vertex buffer
	//
	// fill the transfer buffer
	//
	// start a copy pass
	//
	// where is the data
	//
	// where to upload the data
	//
	// upload the data
	//
	// end the copy pass

	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
	// acquire the command buffer
	SDL_GPUCommandBuffer* commandBuffer = SDL_AcquireGPUCommandBuffer(device);

	// get the swapchain texture
	SDL_GPUTexture* swapchainTexture;
	Uint32 width, height;
	SDL_WaitAndAcquireGPUSwapchainTexture(commandBuffer, window,
																				&swapchainTexture, &width, &height);

	// end the frame early if a swapchain texture is not available
	if (swapchainTexture == NULL)
	{
		// must always submit the command buffer
		SDL_SubmitGPUCommandBuffer(commandBuffer);
		return SDL_APP_CONTINUE;
	}

	// create the color target
	SDL_GPUColorTargetInfo colorTargetInfo{};

	// discard previous content and clear to color
	colorTargetInfo.clear_color = {240/255.0f, 240/255.0f, 240/255.0f, 255/255.0f};
	colorTargetInfo.load_op = SDL_GPU_LOADOP_CLEAR; // SDL_GPU_LOADOP_LOAD

	// store the content to the texture
	colorTargetInfo.store_op = SDL_GPU_STOREOP_STORE;

	// save texture
	colorTargetInfo.texture = swapchainTexture;

	// Begin a render pass
	SDL_GPURenderPass* renderPass = SDL_BeginGPURenderPass(commandBuffer,
																											&colorTargetInfo, 1, NULL);	
	// draw something
	
	// End the render pass
	SDL_EndGPURenderPass(renderPass);

	// Execute the commands in the command buffer
	SDL_SubmitGPUCommandBuffer(commandBuffer);	

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
	// release buffers
	//
	// release the pipeline
	//
	// destroy the GPU device
	SDL_DestroyGPUDevice(device);

	// destroy the window
	SDL_DestroyWindow(window);
}
