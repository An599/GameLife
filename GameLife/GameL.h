#pragma once
#include <vector>
class GameL
{
private:
	int n;
	int mLastDied;
	int mLastBorned;
	std::vector<std::vector<bool>> mMatrix;
private:
	void print();
	void update();
	void logic();
	int count_count(int i, int j, const std::vector<std::vector<bool>>& old);
	bool is_end();
	GameL(int n);
public:
	GameL(const GameL& other) = delete;
	GameL& operator=(const GameL& other) = delete;
	~GameL();
	static GameL& get_instance(int n)
	{
		static GameL gm(n);
		return gm;
	}
	void run();
	
};

