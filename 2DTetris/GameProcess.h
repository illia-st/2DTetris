#pragma once
#include <vector>
#include "SFML/Graphics.hpp"
#include <unordered_map>
#include "Events.h"
#include "Randomizer.h"

using namespace sf;


const int Height = 20;
const int Width = 10;
const int Amount_of_figures = 7;
const int Size_of_figures = 4;
const int Size_of_sprite = 18;

std::vector<std::vector<int>> Field(Height, std::vector<int>(Width));

std::vector<std::vector<int>> Figures = {
	{1,3,5,7}, //I
	{2,4,5,7}, //S
	{3,5,4,6}, //Z
	{3,5,4,7}, //T
	{2,3,5,7}, //L
	{3,5,7,6}, //J
	{2,3,4,5}  //O
};
struct Point {
	int x;
	int y;
};

std::vector<Point> Figure(Size_of_figures);
std::vector<Point> Shadow(Size_of_figures);
bool check_if_inside();

#define CHECK(a, b)							\
	if (!check_if_inside()) {				\
		for (int i = 0; i < a.size(); ++i) {\
			a[i] = b[i];					\
		}									\
	}
void TheGame(float& timer_, float& delay_, int& type_, Clock& clock, RenderWindow& window_, Sprite& sprite_, bool& beginGame_);

void deleteFilledLines(RenderWindow& window_);