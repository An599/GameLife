#include "GameL.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>

GameL::GameL(int n) : n(n), mLastBorned(0), mLastDied(0), mMatrix(n, std::vector<bool>(n, 0))
{
	std::srand(std::time(nullptr));
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			mMatrix[i][j] = std::rand() % 2;
			if (mMatrix[i][j])
				++mLastBorned;
		}
	}
}

GameL::~GameL() {}

void GameL::print()
{
	std::cout << "Last Died: " << mLastDied << std::endl;
	std::cout << "Last Borned: " << mLastBorned << std::endl;
	for (int i = 0; i < n;i++)
	{
		for (int j = 0; j < n; j++)
			std::cout << mMatrix[i][j] << ' ';
		std::cout << std::endl;
	}
}

void GameL::run()
{
	while (is_end())
	{
		update();
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		system("cls");
	}
}

void GameL::update()
{
	print();
	logic();
}

void GameL::logic()
{
	mLastDied = 0;
	mLastBorned = 0;
	const std::vector<std::vector<bool>> old(mMatrix);
	for (int i = 0; i < n; i++) 
	{
		for (int j = 0; j < n; j++)
		{
			int count = count_count(i, j, old);
			if (!old[i][j] && count == 3)
			{
				mMatrix[i][j] = true;
				++mLastBorned;
			}
			else if (old[i][j] && (count < 2 || count > 3))
			{
				mMatrix[i][j] = false;
				++mLastDied;
			}
		}
	}
}

int GameL::count_count(int i, int j, const std::vector<std::vector<bool>>& old)
{
	return old[(i == 0? n - 1 : i - 1)][(j == 0 ? n - 1 : j - 1)] +
		old[(i == 0 ? n - 1 : i - 1)][j] +
		old[(i == 0 ? n - 1 : i - 1)][(j == n - 1 ? 0 : j + 1)] +
		old[i][(j == 0 ? n - 1 : j - 1)] +
		old[i][(j == n - 1 ? 0 : j + 1)] +
		old[(i == n - 1 ? 0 : i + 1)][(j == 0 ? n - 1 : j - 1)] +
		old[(i == n - 1 ? 0 : i + 1)][j] +
		old[(i == n - 1 ? 0 : i + 1)][(j == n - 1 ? 0 : j + 1)];
}

bool GameL::is_end()
{
	if (!mLastBorned && !mLastDied)
		return false;
	int count = 0;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			if (mMatrix[i][j])
				++count;
	return (count != 0);
}
