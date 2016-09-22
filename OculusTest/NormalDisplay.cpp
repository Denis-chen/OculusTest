#include "NormalDisplay.h"
#include "SDL\SDL.h"
#include "GL\glew.h"
#include <stdexcept>


using namespace std;
NormalDisplay::NormalDisplay(int width, int height): width(width), height(height), renderingTarget(NormalRenderingTarget(width, height))
{
}

void NormalDisplay::init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		throw new runtime_error("Could not init SDL: " + string(SDL_GetError()));
	}
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	window = SDL_CreateWindow("OpenGL", 100, 100, width, height, SDL_WINDOW_OPENGL);
	if (window == NULL) {
		throw new runtime_error("Could not create window:" + string(SDL_GetError()));
	}

	context = SDL_GL_CreateContext(window);
	if (context == NULL) {
		throw new runtime_error("Could not create OpenGL context: " + string(SDL_GetError()));
	}

	GLenum glewError = glewInit();
	if (glewError != GLEW_OK)
	{
		throw new runtime_error("Error initializing GLEW: " + string((char *)glewGetErrorString(glewError)));
	}

	glEnable(GL_DEPTH);
}
void NormalDisplay::swap()
{
	SDL_GL_SwapWindow(window);
}

NormalDisplay::~NormalDisplay()
{
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

