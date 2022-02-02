#pragma once
#include "SFML/Graphics.hpp"
enum Events {
	Rotate,
	Left,
	Right,
	Close,
};
Events Event_Check(const sf::Event& event);