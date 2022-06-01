#pragma once
#include "Parameter.h"
#include <cstdlib>
#include <vector>
#include <chrono>
#include <ctime>

struct Coordinate {
	int m_X;
	int m_Y;
};

enum GameResult {
	NONE,
	WIN,
	DIE
};

enum MoveType {
	NONEMOVE = 0,
	UP = 1,
	DOWN = -1,
	LEFT = 2,
	RIGHT = -2
};

class Board {
private:
	std::vector<Coordinate> m_snakeBody;
	Coordinate m_food;
	int m_snakeLength;
	GameResult m_gameResult;
public:
	Board();
	void Reset();
	GameResult getGameResult();
	std::vector<Coordinate> getSnakeBody();
	Coordinate getFood();
	GameResult UpdateGameResult();
	void Move(MoveType i_move);
	bool CheckValidFood(int i_X, int i_Y);
	bool CheckEatFood(int i_X, int i_Y);
	void CreateNewFood();
};