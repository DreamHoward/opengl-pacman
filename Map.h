#pragma once
class Map
{
public:
	char GetElement(int r, int c) const { return map[r][c]; }
	int GetWidth() const { return width; }
	int GetHeight() const { return height; }
	float GetCost(int srcRow, int srcCol, int dstRow, int dstCol) const;

private:
	static const int width = 28;
	static const int height = 36;
	static char map[height][width];
};