/*
 * A template SDL3 project that uses gpu shaders.
 */
#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>

// the vertex input layout
struct Vertex
{
	float x, y, z;	  // vec3 position
	float r, g, b, a; // vec4 color
};

// a list of vertices
static Vertex vertices[]
{
	{0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f},    // top vertex
	{-0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f},  // bottom left vertex
	{0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f} // bottom right vertex
};


SDL_Window *window;
SDL_GPUDevice *device;
SDL_GPUBuffer *vertexBuffer;
SDL_GPUTransferBuffer *transferBuffer;
SDL_GPUGraphicsPipeline *graphicsPipeline;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv)
{
	SDL_Log("SDL_AppInit\n");
	// create a window
	window = SDL_CreateWindow("Hello, Triangle!", 960, 540, SDL_WINDOW_RESIZABLE);

	// create gpu device
	device = SDL_CreateGPUDevice(SDL_GPU_SHADERFORMAT_SPIRV, true, NULL);
	SDL_ClaimWindowForGPUDevice(device, window);

	// load vertex shader code
	SDL_Log("Loading Vertex Shader...\n");
	size_t vertexCodeSize;
	void *vertexCode = SDL_LoadFile("vertex_triangle.spv", &vertexCodeSize);
	if (!vertexCodeSize) {
		SDL_Log("Load vertex shader failed: %s\n", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	// create vertex shader
	SDL_GPUShaderCreateInfo vertexInfo{};
	vertexInfo.code = (Uint8*)vertexCode;
	vertexInfo.code_size = vertexCodeSize;
	vertexInfo.entrypoint = "main";
	vertexInfo.format = SDL_GPU_SHADERFORMAT_SPIRV;
	vertexInfo.stage = SDL_GPU_SHADERSTAGE_VERTEX;
	vertexInfo.num_samplers = 0;
	vertexInfo.num_storage_buffers = 0;
	vertexInfo.num_storage_textures = 0;
	vertexInfo.num_uniform_buffers = 0;

	SDL_GPUShader *vertexShader = SDL_CreateGPUShader(device, &vertexInfo);	

	// free the vertex shader file
	SDL_free(vertexCode);

	// load the fragment shader code
	SDL_Log("Loading Fragment Shader...\n");
	size_t fragmentCodeSize;
	void *fragmentCode = SDL_LoadFile("fragment_triangle.spv", &fragmentCodeSize);
	if (!fragmentCodeSize) {
		SDL_Log("Load fragment shader failed: %s\n", SDL_GetError());
		return SDL_APP_FAILURE;
	}
		

	// create the fragment shader
	SDL_GPUShaderCreateInfo fragmentInfo{};
	fragmentInfo.code = (Uint8*)fragmentCode;
	fragmentInfo.code_size = fragmentCodeSize;
	fragmentInfo.entrypoint = "main";
	fragmentInfo.format = SDL_GPU_SHADERFORMAT_SPIRV;
	fragmentInfo.stage = SDL_GPU_SHADERSTAGE_FRAGMENT;
	fragmentInfo.num_samplers = 0;
	fragmentInfo.num_storage_buffers = 0;
	fragmentInfo.num_storage_textures = 0;
	fragmentInfo.num_uniform_buffers = 1;

	SDL_GPUShader *fragmentShader = SDL_CreateGPUShader(device, &fragmentInfo);
	// free the fragment file
	SDL_free(fragmentCode);
	
	// Create the graphics pipeline
	SDL_GPUGraphicsPipelineCreateInfo pipelineInfo{};
	pipelineInfo.vertex_shader = vertexShader;
	pipelineInfo.fragment_shader = fragmentShader;
  pipelineInfo.primitive_type = SDL_GPU_PRIMITIVETYPE_TRIANGLELIST;
	
	// describe the vertex buffers
	SDL_GPUVertexBufferDescription vertexBufferDescriptions[1];
	vertexBufferDescriptions[0].slot = 0;
	vertexBufferDescriptions[0].input_rate = SDL_GPU_VERTEXINPUTRATE_VERTEX;
	vertexBufferDescriptions[0].instance_step_rate = 0;
	vertexBufferDescriptions[0].pitch = sizeof(Vertex);
	
	pipelineInfo.vertex_input_state.num_vertex_buffers = 1;
	pipelineInfo.vertex_input_state.vertex_buffer_descriptions = vertexBufferDescriptions;

	// describe the vertex attribute
	SDL_GPUVertexAttribute vertexAttributes[2];

  // a_position
	vertexAttributes[0].buffer_slot = 0;
	vertexAttributes[0].location = 0;
	vertexAttributes[0].format = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT3;
	vertexAttributes[0].offset = 0;

	// a_color
	vertexAttributes[1].buffer_slot = 0;
	vertexAttributes[1].location = 1;
	vertexAttributes[1].format = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT4;

	pipelineInfo.vertex_input_state.num_vertex_attributes = 2;
	pipelineInfo.vertex_input_state.vertex_attributes = vertexAttributes;	

	// describe the color target
	SDL_GPUColorTargetDescription colorTargetDescriptions[1];
	colorTargetDescriptions[0] = {};
	colorTargetDescriptions[0].blend_state.enable_blend = true;
	colorTargetDescriptions[0].blend_state.color_blend_op = SDL_GPU_BLENDOP_ADD;
	colorTargetDescriptions[0].blend_state.alpha_blend_op = SDL_GPU_BLENDOP_ADD;
	colorTargetDescriptions[0].blend_state.src_color_blendfactor = SDL_GPU_BLENDFACTOR_SRC_ALPHA;
	colorTargetDescriptions[0].blend_state.dst_color_blendfactor = SDL_GPU_BLENDFACTOR_ONE_MINUS_SRC_ALPHA;
	colorTargetDescriptions[0].blend_state.src_alpha_blendfactor = SDL_GPU_BLENDFACTOR_SRC_ALPHA;
	colorTargetDescriptions[0].blend_state.dst_alpha_blendfactor = SDL_GPU_BLENDFACTOR_ONE_MINUS_SRC_ALPHA;
	colorTargetDescriptions[0].format = SDL_GetGPUSwapchainTextureFormat(device, window);

	pipelineInfo.target_info.num_color_targets = 1;
	pipelineInfo.target_info.color_target_descriptions = colorTargetDescriptions;

	// create the pipeline
	graphicsPipeline = SDL_CreateGPUGraphicsPipeline(device, &pipelineInfo);	
	
	// release shaders
	SDL_ReleaseGPUShader(device, vertexShader);
	SDL_ReleaseGPUShader(device, fragmentShader);

	// create the vertex buffer
	SDL_GPUBufferCreateInfo bufferInfo{};
	bufferInfo.size = sizeof(vertices);
	bufferInfo.usage = SDL_GPU_BUFFERUSAGE_VERTEX;
	
	vertexBuffer = SDL_CreateGPUBuffer(device, &bufferInfo);

	// create a transfer buffer to upload to the vertex buffer
	SDL_GPUTransferBufferCreateInfo transferInfo{};
	transferInfo.size = sizeof(vertices);
	transferInfo.usage = SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD;
	transferBuffer = SDL_CreateGPUTransferBuffer(device, &transferInfo);

	// fill the transfer buffer
	Vertex *data = (Vertex*)SDL_MapGPUTransferBuffer(device, transferBuffer, false);
	SDL_memcpy(data, (void*)vertices, sizeof(vertices));

	SDL_UnmapGPUTransferBuffer(device, transferBuffer);

	// start a copy pass
	SDL_GPUCommandBuffer *commandBuffer = SDL_AcquireGPUCommandBuffer(device);
	SDL_GPUCopyPass *copyPass = SDL_BeginGPUCopyPass(commandBuffer);

	// where is the data
	SDL_GPUTransferBufferLocation location{};
	location.transfer_buffer = transferBuffer;
	location.offset = 0;

	// where to upload the data
	SDL_GPUBufferRegion region{};
	region.buffer = vertexBuffer;
	region.size = sizeof(vertices);
	region.offset = 0;

	// upload the data
	SDL_UploadToGPUBuffer(copyPass, &location, &region, true);

	// end the copy pass
	SDL_EndGPUCopyPass(copyPass);
	SDL_SubmitGPUCommandBuffer(commandBuffer);

	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
	struct UniformBuffer
	{
		float time;
	};

	static UniformBuffer timeUniform{};

	// acquire the command buffer
	SDL_GPUCommandBuffer* commandBuffer = SDL_AcquireGPUCommandBuffer(device);

	// get the swapchain texture
	SDL_GPUTexture* swapchainTexture;
	Uint32 width, height;
	SDL_WaitAndAcquireGPUSwapchainTexture(commandBuffer, window, &swapchainTexture, &width, &height);

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
	SDL_GPURenderPass* renderPass = SDL_BeginGPURenderPass(commandBuffer, &colorTargetInfo, 1, NULL);	

	// draw something
	SDL_BindGPUGraphicsPipeline(renderPass, graphicsPipeline);

	// bind the vertex buffer
	SDL_GPUBufferBinding bufferBindings[1];
	bufferBindings[0].buffer = vertexBuffer;
	bufferBindings[0].offset = 0;

	SDL_BindGPUVertexBuffers(renderPass, 0, bufferBindings, 1);
	
	timeUniform.time = SDL_GetTicksNS() /1e9f;
	SDL_PushGPUFragmentUniformData(commandBuffer, 0, &timeUniform, sizeof(UniformBuffer));
	// issue a draw call
	SDL_DrawGPUPrimitives(renderPass, 3, 1, 0, 0);	
	
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
	SDL_ReleaseGPUBuffer(device, vertexBuffer);
	SDL_ReleaseGPUTransferBuffer(device, transferBuffer);
	// release the pipeline
	SDL_ReleaseGPUGraphicsPipeline(device, graphicsPipeline);
	
	// destroy the GPU device
	SDL_DestroyGPUDevice(device);

	// destroy the window
	SDL_DestroyWindow(window);
}
