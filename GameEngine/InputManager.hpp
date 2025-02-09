#pragma once
#include <SFML/Graphics.hpp>
#include <functional>

namespace Solar {
	struct InputManager {
	private:
		struct EventStruct
		{
			std::string EventName;
			std::function<void()> StoredFunction;
		};
	public:
		std::unordered_map<std::string, bool> KeyDown;
		bool IsSpriteClick(sf::Sprite object, sf::Mouse::Button button);
		bool IsTextClicked(sf::Text object, sf::Mouse::Button button);
		bool IsRectHovered(sf::RectangleShape);
		bool Contains(sf::View view, sf::Vector2i point);
		sf::Vector2i GetMousePosition(sf::RenderWindow& window);

		std::map<int, EventStruct> EventQueue;
		void HandleEvents();
		void FireEvent(std::string Event);
		void HookEvent(std::string Event, std::function<void()> function);

	};
}