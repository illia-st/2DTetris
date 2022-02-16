#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
#include "Events.h"
#include "Randomizer.h"

struct Point {
	int x;
	int y;
};

class Game_Process {
private:
	const int Height = 20;
	const int Width = 10;
	const int Amount_of_figures = 7;
	const int Size_of_figures = 4;
	const int Size_of_sprite = 18;
	
	int Score = 0;
	int Deleted_lines = 0;

	std::vector<std::vector<int>> Field = std::vector<std::vector<int>>(Height, std::vector<int>(Width));

	std::vector<std::vector<int>> Figures = {
		{1,3,5,7}, //I
		{2,4,5,7}, //S
		{3,5,4,6}, //Z
		{3,5,4,7}, //T
		{2,3,5,7}, //L
		{3,5,7,6}, //J
		{2,3,4,5}  //O
	};
	std::vector<Point> Figure = std::vector<Point>(Size_of_figures);
	std::vector<Point> Shadow = std::vector<Point>(Size_of_figures);
	#define CHECK(a, b)							\
		if (!Check_if_inside()) {				\
			for (int i = 0; i < a.size(); ++i) {\
				a[i] = b[i];					\
			}									\
		}
	bool Check_if_inside();
	
	void DeleteFilledLines(sf::RenderWindow& window_);

	bool Check_if_lose(sf::Window& window);
public:

	void TheGame(float& timer_, float& delay_, int& type_, sf::Clock& clock, sf::RenderWindow& window_,
		sf::Sprite& sprite_, sf::Sprite& frame, sf::Sprite& background, bool& beginGame_);

	int Get_figures_size();
};