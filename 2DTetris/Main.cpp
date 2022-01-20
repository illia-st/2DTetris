#include <SFML/Graphics.hpp>
#include <vector>
#include "Randomizer.h"
#include "Main.h"
#include "Events.h"
#include <iostream>

using namespace sf;


bool check_if_inside();
Events Event_Check(const Event& event) {

}

#define CHECK(a, b)\
	if (!check_if_inside()) {\
		for (int i = 0; i < a.size(); ++i) {\
			a[i] = b[i];\
		}\
	}

int main() {
	srand(time(0));

	RenderWindow window(VideoMode(320, 480), "Tetris");

	Texture texture;
	texture.loadFromFile("D:\\programming\\c++\\Tetris\\sprites\\tiles.png");
	Sprite sprite(texture);
	int type = getRandomNumber(0, Figures.size() - 1);
	int dx = 0; bool rotate = false; int colorNum = 1; bool beginGame = true;
	sprite.setTextureRect(IntRect(0, 0, Size_of_sprite, Size_of_sprite));

	float timer = 0, delay = 0.3;
	Clock clock;

	while (window.isOpen()) {
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;
		Event event;
		std::map<Events, int> events;
		while (window.pollEvent(event)) {
			Events cur_event = Event_Check(event);
			if (cur_event == Events::Close) {
				window.close();
			}
			events[cur_event] += 1;
		}

		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			delay = 0.05;
		}

		for (int i = 0; i < Figure.size(); i++) {
			Shadow[i].x = Figure[i].x;
			Figure[i].x += events[Events::Left] + events[Events::Right];
		}

		CHECK(Figure, Shadow)


		if (events.count(Events::Rotate) != 0) {
			Point p = Figure[1];
			for (int i = 0; i < Figure.size(); ++i) {
				int x = Figure[i].y - p.y;
				int y = Figure[i].x - p.x;
				Figure[i].y = p.y + y;
				Figure[i].x = p.x - x;
			}
			CHECK(Figure, Shadow)
		}

		if (timer > delay)
		{
			for (int i = 0; i < Figure.size(); i++) {
				Shadow[i].y = Figure[i].y;
				Figure[i].y += 1;
			}
			if (!check_if_inside()) {//якщо false то ми дійшли до низу
				for (int i = 0; i < Figure.size(); ++i) {
					Field[Shadow[i].y][Shadow[i].x] = type;
				}
				type = getRandomNumber(0, Figures.size() - 1);
				
				for (int i = 0; i < Figure.size(); ++i) {
					Figure[i] = { Figures[type][i] % 2 , Figures[type][i] / 2 };
				}
			}
			timer = 0;
		}

		if (beginGame) {
			beginGame = false;
			type = getRandomNumber(0, Figures.size() - 1);
			for (int i = 0; i < Figure.size(); ++i) {
				Figure[i] = { Figures[type][i] % 2 , Figures[type][i] / 2 };
			}
		}

		dx = 0;
		rotate = false;
		delay = 0.3;
		window.clear(Color::White);
		for (int i = 0; i < Height; ++i) {
			for (int j = 0; j < Width; ++j) {
				if (Field[i][j] == 0) {
					continue;
				}
				sprite.setTextureRect(IntRect(Field[i][j] * Size_of_sprite, 0, Size_of_sprite, Size_of_sprite));
				sprite.setPosition(j * Size_of_sprite, i * Size_of_sprite);
				window.draw(sprite);
			}
		}
		for (int i = 0; i < 4; i++)
		{
			sprite.setTextureRect(IntRect(colorNum * 18, 0, 18, 18));

			sprite.setPosition(Figure[i].x * Size_of_figures, Figure[i].y * Size_of_figures);

			window.draw(sprite);
		}
		window.display();
	}

	return 0;
}

bool check_if_inside() {
	for (int i = 0; i < Figure.size(); ++i) {
		if (Figure[i].x > Width || Figure[i].y > Height) {
			return false;
		}
		else if (Field[Figure[i].y][Figure[i].x]) {
			return false;
		}
	}
	return true;
}