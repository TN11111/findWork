#pragma once
class GameNumber
{
public:
	GameNumber() {}
	~GameNumber() {}

	const int& GetLevel() const { return level; }
	void LevelUP() { level++; }
	void LevelDown() { level--; }

private:
	int level = 1;
};