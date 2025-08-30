/*
  showimage:  A test application for the SDL image loading library.
  Copyright (C) 1997-2025 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL_gpu.h>


/* Draw a Gimpish background pattern to show transparency in the image */
static void draw_background(SDL_Renderer *renderer, int w, int h)
{
    const SDL_Color col[2] = {
        { 0x66, 0x66, 0x66, 0x00 },
        { 0x99, 0x99, 0x99, 0xff }
    };
    const int dx = 8, dy = 8;
    SDL_FRect rect;
    int i, x, y;

    rect.w = (float)dx;
    rect.h = (float)dy;
    for (y = 0; y < h; y += dy) {
        for (x = 0; x < w; x += dx) {
            /* use an 8x8 checkerboard pattern */
            i = (((x ^ y) >> 3) & 1);
             SDL_SetRenderDrawColor(renderer, col[i].r, col[i].g, col[i].b, col[i].a);
            rect.x = (float)x;
            rect.y = (float)y;
            SDL_RenderFillRect(renderer, &rect);
        }
    }
}

/* Probe GPU device and log results */
int display_gpu_info(SDL_GPUDevice* gpu){
    int result = 0;
    const char *platform_os;
    
    SDL_Log("Probing GPU device...\n");
    SDL_PropertiesID propID = SDL_GetGPUDeviceProperties(gpu);
    if (!propID) {
        SDL_Log("SDL_GetGPUDeviceProperies() failed: %s\n", SDL_GetError());
        result = 2;
    }
    SDL_Log("SDL Revision: %s\n", SDL_GetRevision());
    platform_os = SDL_GetPlatform();
		SDL_Log("OS: %s\n", platform_os);
    SDL_Log("GPU device name: %s\n",
        SDL_GetStringProperty(propID, SDL_PROP_GPU_DEVICE_NAME_STRING, "Not Set."));
    SDL_Log("GPU device driver info: %s\n",
            SDL_GetStringProperty(propID, SDL_PROP_GPU_DEVICE_DRIVER_INFO_STRING, "Not Set."));
    SDL_Log("GPU device driver name: %s\n",
            SDL_GetStringProperty(propID, SDL_PROP_GPU_DEVICE_DRIVER_NAME_STRING, "Not Set."));
    SDL_Log("GPU device driver version: %s\n",
            SDL_GetStringProperty(propID, SDL_PROP_GPU_DEVICE_DRIVER_VERSION_STRING, "Not Set."));

    return result; 
}

int create_shader(SDL_GPUDevice* gpu){
    int result = 0;
    SDL_GPUShader *shader;
    //shader = SDL_CreateGPUShader(gpu, );
    if (!shader) {
        SDL_Log("SDL_CreateGPUShader failed: %s\n", SDL_GetError());
        result = 2;
    }

    return result;
}


int main(int argc, char *argv[])
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *texture = NULL;
    SDL_GPUDevice *gpu = NULL;
    SDL_PropertiesID  propID;
		SDL_GPUCommandBuffer *commandBuffer = NULL;
		SDL_GPUShader *shader = NULL;
		size_t vertexCodeSize;
		void *vertexCode;
		size_t fragmentCodeSize;
		void *fragmentCode;
		SDL_GPUShaderCreateInfo vertexInfo{};
		SDL_GPUShaderCreateInfo fragmentInfo{};
		//SDL_GPUCommandBuffer *commandBuffer = NULL;
    Uint32 flags;
    float w, h;
    int i;
    int done = 0;
    int quit = 0;
    SDL_Event event;
    const char *tonemap = NULL;
    const char *saveFile = NULL;
    int attempted = 0;
    int result = 0;

    (void)argc;

#if 0 /* We now allow drag and drop onto the window */
    /* Check command line usage */
    if ( !argv[1] ) {
        SDL_Log("Usage: %s [-fullscreen] [-tonemap X] [-save file.png] <image_file> ...\n", argv[0]);
        result = 1;
        goto done;
    }
#endif

    flags = SDL_WINDOW_HIDDEN;
    for ( i=1; argv[i]; ++i ) {
        if ( SDL_strcmp(argv[i], "-fullscreen") == 0 ) {
            SDL_HideCursor();
            flags |= SDL_WINDOW_FULLSCREEN;
        }
    }

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL_Init(SDL_INIT_VIDEO) failed: %s\n", SDL_GetError());
        result = 2;
        goto done;
    }

    window = SDL_CreateWindow("", 0, 0, flags);
    if (!window) {
        SDL_Log("SDL_CreateWindow() failed: %s\n", SDL_GetError());
        result = 2;
        goto done;
    }

    // Enable GPU device
    gpu = SDL_CreateGPUDevice(SDL_GPU_SHADERFORMAT_SPIRV, false, NULL);

    if (!gpu) {
        SDL_Log("SDL_CreateGPUDevice() failed: %s\n", SDL_GetError());
        result = 2;
        goto done;
    }
   
    // Probe GPU device and log results
    display_gpu_info(gpu);

    // Claim window for GPU
    if (!SDL_ClaimWindowForGPUDevice(gpu, window)){
        SDL_Log("SDL_ClaimWindowForGPUDevice failed: %s\n", SDL_GetError());
        result = 2;
        goto done;
    }

		// Load Precompiled Vertex Shader
		vertexCode = SDL_LoadFile("vertex.spv", &vertexCodeSize);
		if (!vertexCode){
			SDL_Log("SDL_LoadFile failed: %s\n", SDL_GetError());
			goto done;
		}
		SDL_Log("Vertex shader size: %ld\n", vertexCodeSize);
		vertexInfo.code = (Uint8*)vertexCode;
		vertexInfo.code_size = vertexCodeSize;
		vertexInfo.entrypoint = "main";
		vertexInfo.format = SDL_GPU_SHADERFORMAT_SPIRV;
		vertexInfo.stage = SDL_GPU_SHADERSTAGE_VERTEX;
		vertexInfo.num_samplers = 0;
		vertexInfo.num_storage_buffers = 0;
		vertexInfo.num_uniform_buffers = 0;
		vertexInfo.props = 0;
	
		// Load Precompiled Fragment Shader
		fragmentCode = SDL_LoadFile("blur.spv", &fragmentCodeSize);
		if (!fragmentCode) {
			SDL_Log("SDL_LoadFile failed: %s\n", SDL_GetError());
			goto done;
		}
		SDL_Log("Fragment shader size: %ld\n", fragmentCodeSize);
		fragmentInfo.code = (Uint8*)fragmentCode;
		fragmentInfo.code_size = fragmentCodeSize;
		fragmentInfo.entrypoint = "main";
		fragmentInfo.format = SDL_GPU_SHADERFORMAT_SPIRV;
		fragmentInfo.stage = SDL_GPU_SHADERSTAGE_FRAGMENT;
		fragmentInfo.num_samplers = 0;
		fragmentInfo.num_storage_buffers = 0;
		fragmentInfo.num_uniform_buffers = 0;
		fragmentInfo.props = 0;	

    if (SDL_GetBooleanProperty(SDL_GetDisplayProperties(SDL_GetPrimaryDisplay()), SDL_PROP_DISPLAY_HDR_ENABLED_BOOLEAN, false)) {
        SDL_PropertiesID props = SDL_CreateProperties();

        SDL_SetPointerProperty(props, SDL_PROP_RENDERER_CREATE_WINDOW_POINTER, window);
        SDL_SetNumberProperty(props, SDL_PROP_RENDERER_CREATE_OUTPUT_COLORSPACE_NUMBER, SDL_COLORSPACE_SRGB_LINEAR);
        renderer = SDL_CreateRendererWithProperties(props);
        SDL_DestroyProperties(props);
    }
    if (!renderer) {
        renderer = SDL_CreateRenderer(window, NULL);
    }
    if (!renderer) {
        SDL_Log("SDL_CreateRenderer() failed: %s\n", SDL_GetError());
        result = 2;
        goto done;
    }

    for (i=1; argv[i]; ++i) {
        if (SDL_strcmp(argv[i], "-fullscreen") == 0) {
            continue;
        }

        if (SDL_strcmp(argv[i], "-quit") == 0) {
            quit = 1;
            continue;
        }

        if (SDL_strcmp(argv[i], "-tonemap") == 0 && argv[i+1]) {
            ++i;
            tonemap = argv[i];
            continue;
        }

        if (SDL_strcmp(argv[i], "-save") == 0 && argv[i+1]) {
            ++i;
            saveFile = argv[i];
            continue;
        }

        /* Open the image file */
        ++attempted;
        if (tonemap) {
            SDL_Surface *surface, *temp;

            surface = IMG_Load(argv[i]);
            if (!surface) {
                SDL_Log("Couldn't load %s: %s\n", argv[i], SDL_GetError());
                continue;
            }

            /* Use the tonemap operator to convert to SDR output */
            SDL_SetStringProperty(SDL_GetSurfaceProperties(surface), SDL_PROP_SURFACE_TONEMAP_OPERATOR_STRING, tonemap);
            temp = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_RGBA32);
            SDL_DestroySurface(surface);
            if (!temp) {
                SDL_Log("Couldn't convert surface: %s\n", SDL_GetError());
                continue;
            }

            texture = SDL_CreateTextureFromSurface(renderer, temp);
            SDL_DestroySurface(temp);
            if (!texture) {
                SDL_Log("Couldn't create texture: %s\n", SDL_GetError());
                continue;
            }
        } else {
            texture = IMG_LoadTexture(renderer, argv[i]);
            if (!texture) {
                SDL_Log("Couldn't load %s: %s\n", argv[i], SDL_GetError());
                continue;
            }
        }
        SDL_GetTextureSize(texture, &w, &h);

        /* Save the image file, if desired */
        if (saveFile) {
            SDL_Surface *surface = IMG_Load(argv[i]);
            if (surface) {
                if (!IMG_Save(surface, saveFile)) {
                    SDL_Log("Couldn't save %s: %s\n", saveFile, SDL_GetError());
                    result = 3;
                }
            } else {
                SDL_Log("Couldn't load %s: %s\n", argv[i], SDL_GetError());
                result = 3;
            }
        }

        /* Show the window */
        SDL_SetWindowTitle(window, argv[i]);
        SDL_SetWindowSize(window, (int)w, (int)h);
        SDL_ShowWindow(window);

        done = quit;
        while ( !done ) {
            while ( SDL_PollEvent(&event) ) {
                switch (event.type) {
                    case SDL_EVENT_KEY_UP:
                        switch (event.key.key) {
                        case SDLK_LEFT:
                            if ( i > 1 ) {
                                i -= 2;
                                done = 1;
                            }
                            break;
                        case SDLK_RIGHT:
                            if ( argv[i+1] ) {
                                done = 1;
                            }
                            break;
                        case SDLK_ESCAPE:
                        case SDLK_Q:
                            argv[i+1] = NULL;
                            SDL_FALLTHROUGH;
                        case SDLK_SPACE:
                        case SDLK_TAB:
                            done = 1;
                            break;
                        default:
                            break;
                        }
                        break;
                    case SDL_EVENT_MOUSE_BUTTON_DOWN:
                        done = 1;
                        break;
                    case SDL_EVENT_QUIT:
                        argv[i+1] = NULL;
                        done = 1;
                        break;
                    default:
                        break;
                }
            }
            /* Draw a background pattern in case the image has transparency */
            draw_background(renderer, (int)w, (int)h);

            /* Display the image */
            SDL_RenderTexture(renderer, texture, NULL, NULL);
            SDL_RenderPresent(renderer);

            SDL_Delay(100);
        }
        SDL_DestroyTexture(texture);
        texture = NULL;
    }

    if (attempted == 0 && !quit) {
        /* Show the window if needed */
        SDL_SetWindowTitle(window, "showimage");
        w = 640.0f;
        h = 480.0f;
        SDL_SetWindowSize(window, (int)w, (int)h);
        SDL_ShowWindow(window);

        while ( !done ) {
            while ( SDL_PollEvent(&event) ) {
                switch (event.type) {
                    case SDL_EVENT_DROP_FILE:
                        {
                            const char *file = event.drop.data;

                            SDL_DestroyTexture(texture);

                            SDL_Log("Loading %s\n", file);
                            texture = IMG_LoadTexture(renderer, file);
                            if (!texture) {
                                SDL_Log("Couldn't load %s: %s\n", file, SDL_GetError());
                                break;
                            }
                            SDL_SetWindowTitle(window, file);
                            SDL_GetTextureSize(texture, &w, &h);
                            SDL_SetWindowSize(window, (int)w, (int)h);
                        }
                        break;
                    case SDL_EVENT_KEY_UP:
                        switch (event.key.key) {
                        case SDLK_ESCAPE:
                        case SDLK_Q:
                            done = 1;
                            break;
                        }
                        break;
                    case SDL_EVENT_MOUSE_BUTTON_DOWN:
                        done = 1;
                        break;
                    case SDL_EVENT_QUIT:
                        done = 1;
                        break;
                    default:
                        break;
                }
            }

            /* Draw a background pattern in case the image has transparency */
            draw_background(renderer, (int)w, (int)h);

            /* Display the image */
            SDL_RenderTexture(renderer, texture, NULL, NULL);
            SDL_RenderPresent(renderer);

            SDL_Delay(100);
        }
        SDL_DestroyTexture(texture);
    }

    /* We're done! */
done:
		//SDL_ReleaseGPUShader(gpu, shader);
		SDL_free(vertexCode);
		SDL_free(fragmentCode);
    SDL_ReleaseWindowFromGPUDevice(gpu, window);
    SDL_DestroyGPUDevice(gpu);
    SDL_Quit();
    return result;

}
