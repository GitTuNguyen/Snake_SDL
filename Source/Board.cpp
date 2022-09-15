#include "Board.h"

Board::Board()
{
	Reset();
}

void Board::Reset()
{
	m_snakeBody.clear();
	Coordinate snake;
	snake.m_X = WINDOW_WIDTH / 2;
	snake.m_Y = WINDOW_HEIGHT / 2;
	m_snakeBody.push_back(snake);
	m_snakeLength = 1;
	m_gameResult = GameResult::NONE;
	CreateNewFood();
}

GameResult  Board::getGameResult()
{
	return m_gameResult;
}

void Board::Move(MoveType i_move)
{
	Coordinate snakeHead = m_snakeBody.back();
	
	switch (i_move)
	{
	case MoveType::UP:
		snakeHead.m_Y -= CELL_SIZE;
		break;
	case MoveType::DOWN:
		snakeHead.m_Y += CELL_SIZE;
		break;
	case MoveType::LEFT:
		snakeHead.m_X -= CELL_SIZE;
		break;
	case MoveType::RIGHT:
		snakeHead.m_X += CELL_SIZE;
		break;
	case MoveType::NONEMOVE:
		break;
	default:
		break;
	}
	m_snakeBody.push_back(snakeHead);
	bool eatFood = CheckEatFood(snakeHead.m_X, snakeHead.m_Y);
	if (eatFood)
	{
		CreateNewFood();
	}
	else {
		m_snakeBody.erase(m_snakeBody.begin());
	}
	m_gameResult = UpdateGameResult();
}

GameResult Board::UpdateGameResult()
{
	Coordinate head = m_snakeBody.back();
	if (head.m_X < 0 || head.m_X > WINDOW_WIDTH || head.m_Y < 0 || head.m_Y > WINDOW_HEIGHT)
	{
		return GameResult::DIE;
	}
	else if (m_snakeLength == (WINDOW_HEIGHT * WINDOW_WIDTH) / (CELL_SIZE * CELL_SIZE)) 
	{
		return GameResult::WIN;
	}
	else {
		return GameResult::NONE;
	}
}

std::vector<Coordinate> Board::getSnakeBody()
{
	return m_snakeBody;
}

Coordinate Board::getFood()
{
	return m_food;
}

bool Board::CheckValidFood(int i_X, int i_Y)
{
	for (int i = 0; i < m_snakeBody.size(); i++)
	{
		if (i_X >= m_snakeBody[i].m_X && i_X <= m_snakeBody[i].m_X + CELL_SIZE && i_Y >= m_snakeBody[i].m_Y && i_X <= m_snakeBody[i].m_Y + CELL_SIZE)
		{
			return false;
		}
	}
	return true;
}

bool Board::CheckEatFood(int i_X, int i_Y)
{
	if (i_X == m_food.m_X && i_Y == m_food.m_Y)
	{
		return true;
	}
	else return false;
}

void Board::CreateNewFood()
{
	bool validFood = false;
	while (!validFood)
	{
		srand(time(NULL));
		int x = rand() % (WINDOW_WIDTH/CELL_SIZE);
		int y = rand() % (WINDOW_HEIGHT/CELL_SIZE);
		m_food.m_X = x * CELL_SIZE;
		m_food.m_Y = y * CELL_SIZE;
		validFood = CheckValidFood(m_food.m_X, m_food.m_Y);
	}
}