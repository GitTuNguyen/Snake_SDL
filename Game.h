#pragma once
#include "Renderer.h"
#include "Board.h"
#include <iostream>
class Game {
public:
	Game();
	void Update();
	~Game();
private:
	Board* m_board;
	Renderer* m_renderer;
	SDL_Event mainEvent;
	MoveType m_currentMove;
	void CheckMove(MoveType i_move);
	bool m_isPlayerWantExit;
	void CreateNewMatch();
	void DrawWindow();
	void UpdateMove();
	void Rematch();
};