#pragma once
#include <SDL.h>
#include "Board.h"
#include <iostream>
enum CellType {
	SNAKE,
	FOOD
};
class Renderer {
public:
	Renderer();
	void PreRendering();
	void DrawCell(CellType i_cellType, int i_pixelX, int i_pixelY);
	void DrawWindow();
	void PostFrame();
	void CleanUp();
private:
	SDL_Window* m_window = NULL;
	SDL_Renderer* m_sdlRenderer = NULL;
	Board* m_board;
};