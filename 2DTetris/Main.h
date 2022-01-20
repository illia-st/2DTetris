#pragma once
#include <vector>


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