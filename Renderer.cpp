#include "Renderer.h"
Renderer::Renderer()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("Unable to initialize SDL %s\n", SDL_GetError());
		return;
	}

	//Create window
	m_window = SDL_CreateWindow("SNAKE - SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if (m_window == NULL)
	{
		printf("Could not create window %s", SDL_GetError());
		return;
	}

	//create a renderer
	m_sdlRenderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
	if (m_sdlRenderer == NULL)
	{
		printf("Could not create render %s", SDL_GetError());
		return;
	}
}
void Renderer::PreRendering()
{
	SDL_SetRenderDrawColor(m_sdlRenderer, 0, 0, 0, 255);
	SDL_RenderClear(m_sdlRenderer);
}

void Renderer::DrawCell(CellType i_cellType, int i_pixelX, int i_pixelY)
{
	SDL_Rect newRect;
	newRect.x = i_pixelX;
	newRect.y = i_pixelY;
	newRect.h = CELL_SIZE;
	newRect.w = CELL_SIZE;
	switch (i_cellType)
	{
	case CellType::SNAKE:
		SDL_SetRenderDrawColor(m_sdlRenderer, 255, 255, 255, 255);
		break;
	case CellType::FOOD:
		SDL_SetRenderDrawColor(m_sdlRenderer, 255, 0, 0, 255);
		break;
	default:
		break;
	}
	
	SDL_RenderFillRect(m_sdlRenderer, &newRect);
}


void Renderer::PostFrame()
{
	SDL_RenderPresent(m_sdlRenderer);
	SDL_Delay(16);
}

void Renderer::CleanUp()
{

	SDL_DestroyWindow(m_window);

	
	SDL_DestroyRenderer(m_sdlRenderer);


	SDL_Quit();
}

