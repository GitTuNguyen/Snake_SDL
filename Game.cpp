#include "Game.h"

Game::Game()
{
	m_board = new Board();
	m_renderer = new Renderer();
	m_isPlayerWantExit = false;
	m_currentMove = MoveType::NONEMOVE;
}

void Game::CreateNewMatch()
{
	m_board->Reset();
}

void Game::DrawWindow()
{
	std::vector<Coordinate> snakeBody = m_board->getSnakeBody();
	for (int i = 0; i < snakeBody.size(); i++)
	{
		m_renderer->DrawCell(CellType::SNAKE, snakeBody[i].m_X, snakeBody[i].m_Y);
	}
	Coordinate food = m_board->getFood();
	m_renderer->DrawCell(CellType::FOOD, food.m_X, food.m_Y);
}

void Game::Rematch() 
{
	char inputPlayer;
	std::cout << "Play again? (Y to play again, another key to quit): ";
	std::cin >> inputPlayer;
	if (inputPlayer == 'Y' || inputPlayer == 'y')
	{
		CreateNewMatch();
	}
	else {
		m_isPlayerWantExit = true;
	}
}

void Game::CheckMove(MoveType i_move)
{
	if (m_currentMove + i_move != 0)
	{
		m_currentMove = i_move;
	}
}

void Game::Update()
{
	Uint32 before = SDL_GetTicks(), after;
	while (!m_isPlayerWantExit)
	{
		m_renderer->PreRendering();
		GameResult gameResult = m_board->getGameResult();
		if (gameResult == GameResult::NONE)
		{
			while (SDL_PollEvent(&mainEvent))
			{
				switch (mainEvent.type)
				{
					case SDL_QUIT:
					{
						m_isPlayerWantExit = true;
						break;
					}
					case SDL_KEYUP:
					{
						switch (mainEvent.key.keysym.sym)
						{
						case SDLK_UP:
						{
							CheckMove(MoveType::UP);
							break;
						}
						case SDLK_DOWN:
						{
							CheckMove(MoveType::DOWN);
							break;
						}
						case SDLK_LEFT:
						{
							CheckMove(MoveType::LEFT);
							break;
						}
						case SDLK_RIGHT:
						{
							CheckMove(MoveType::RIGHT);
							break;
						}
						default:
							break;
						}
					}
					default:
					{
					break;
					}
				}
			}
			after = SDL_GetTicks();
			if (after - before >= 100)
			{
				before = after;
				m_board->Move(m_currentMove);
			}
			DrawWindow();
		}
		else {
			Rematch();
		}
		m_renderer->PostFrame();
	}
	m_renderer->CleanUp();
}

Game::~Game()
{
	delete m_board;
	delete m_renderer;
}