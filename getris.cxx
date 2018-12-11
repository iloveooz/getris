
	// clone of tetris

	#include <SFML/Graphics.hpp>
	#include <time.h>
	
	int main() {
		sf::RenderWindow window(sf::VideoMode(320, 480), "Getris!");
		
		while (window.isOpen()) {
			sf::Event event;
			
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed)
				window.close();
				
			}
			window.clear(sf::Color::White);
			window.display();
		
		}
		
		return 0;
	}
