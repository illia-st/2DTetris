#include "Game_Process.h"
#include <unordered_map>


bool Game_Process::Check_if_inside() {
	for (int i = 0; i < Figure.size(); ++i) {
		if (Figure[i].x >= Width || Figure[i].x < 0 || Figure[i].y >= Height) {
			return false;
		}
		else if (Field[Figure[i].y][Figure[i].x]) {
			return false;
		}
	}
	return true;
}
void Game_Process::DeleteFilledLines(sf::RenderWindow& window_) {
	std::vector<int> filledLines;
	for (int i = 0; i < Height; ++i) {
		std::vector<int> notEmpty;
		for (int j = Width - 1; j >= 0; --j) {
			if (Field[i][j] != 0) {
				if (i == 0) {
					window_.close();
				}
				notEmpty.push_back(j);
			}
		}
		if (notEmpty.size() == Width) {
			filledLines.push_back(i);
		}
	}
	int counter = 0;
	for (int l = 0; l < filledLines.size(); ++l) {
		filledLines[l] += counter;
		for (int i = filledLines[l]; i >= 1; --i) {
			for (int j = 0; j < Width; ++j) {
				Field[i][j] = Field[i - 1][j];
			}
		}
		++counter;
	}
}
void Game_Process::TheGame(float& timer_, float& delay_, int& type_, sf::Clock& clock, sf::RenderWindow& window_, sf::Sprite& sprite_, bool& beginGame_) {
	float time = clock.getElapsedTime().asSeconds();
	clock.restart();
	timer_ += time;
	sf::Event event;
	std::unordered_map<Events, int> events;
	while (window_.pollEvent(event)) {
		Events cur_event = Event_Check(event);
		if (cur_event == Events::Close) {
			window_.close();
		}
		events[cur_event] += 1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		delay_ = 0.05;
	}

	for (int i = 0; i < Figure.size(); i++) {
		Shadow[i].x = Figure[i].x;
		Figure[i].x += events[Events::Right] - events[Events::Left];
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

	if (timer_ > delay_)
	{
		for (int i = 0; i < Figure.size(); i++) {
			Shadow[i].y = Figure[i].y;
			Figure[i].y += 1;
		}
		if (!Check_if_inside()) {
			for (int i = 0; i < Figure.size(); ++i) {
				Field[Shadow[i].y][Shadow[i].x] = type_ == 0 ? -1 : type_;
			}
			type_ = Randomizer::getRandomNumber(0, Figures.size() - 1);

			for (int i = 0; i < Figure.size(); ++i) {
				Figure[i] = { Figures[type_][i] % 2 , Figures[type_][i] / 2 };
			}
		}
		timer_ = 0;
	}

	if (beginGame_) {
		beginGame_ = false;
		type_ = Randomizer::getRandomNumber(0, Figures.size() - 1);
		for (int i = 0; i < Figure.size(); ++i) {
			Figure[i] = { Figures[type_][i] % 2 , Figures[type_][i] / 2 };
		}
	}
	delay_ = 0.3;
	window_.clear(sf::Color::White);

	DeleteFilledLines(window_);

	for (int i = 0; i < Height; ++i) {
		for (int j = 0; j < Width; ++j) {
			if (Field[i][j] == 0) {
				continue;
			}
			int figure = Field[i][j] == -1 ? 0 : Field[i][j];
			sprite_.setTextureRect(sf::IntRect(figure * Size_of_sprite, 0, Size_of_sprite, Size_of_sprite));
			sprite_.setPosition(j * Size_of_sprite, i * Size_of_sprite);
			window_.draw(sprite_);
		}

	}
	for (int i = 0; i < Size_of_figures; i++)
	{
		sprite_.setTextureRect(sf::IntRect(type_ * Size_of_sprite, 0, Size_of_sprite, Size_of_sprite));

		sprite_.setPosition(Figure[i].x * Size_of_sprite, Figure[i].y * Size_of_sprite);

		window_.draw(sprite_);
	}

	window_.display();
}
int Game_Process::Get_figures_size() {
	return Figures.size();
}