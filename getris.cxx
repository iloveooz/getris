
	// clone of tetris

	#include <SFML/Graphics.hpp>
	#include <iostream>
	#include <time.h>
	
	const int M = 20;
	const int N = 10;
	
	int field[M][N] = { 0 };
	
	struct Point {
		int x;
		int y;
	} a[4], b[4];
	
	int figures[7][4] = {
		1, 3, 5, 7, // I
		2, 4, 5, 7, // Z
		3, 5, 4, 6, // S
		3, 5, 4, 7, // T
		2, 3, 5, 7, // L
		3, 5, 7, 6, // J
		2, 3, 4, 5 // O 
		
	};
	
	bool check() {
		for (int i = 0; i < 4; i++ ) 
			if (a[i].x < 0 || a[i].x >= N || a[i].y >= M) return 0;
			else if (field[a[i].y] [a[i].x]) return 0;
		return 1;
	}
	
	int main() {
		
		srand(time(NULL));
		
		sf::RenderWindow window(sf::VideoMode(320, 480), "Getris!");
		
		sf::Texture t, bt;
		t.loadFromFile("images/tiles.png");
		bt.loadFromFile("images/background.png");
		
		sf::Sprite s(t), bb(bt);
		//s.setTextureRect(sf::IntRect(0, 0, 18, 18));
		
		int dx = 0;
		bool rotate = 0;
		int colorNum = 1;
				
		float timer = 0; 
		float delay = 0.3;
		
		sf::Clock clock;

		a[0].x = 0, a[0].y = 1;
		a[1].x = 1, a[1].y = 1;
		a[2].x = 1, a[2].y = 2;
		a[3].x = 1, a[3].y = 3;	
		
		while (window.isOpen()) {
			
			float time = clock.getElapsedTime().asSeconds();
			clock.restart();
			timer += time;
			
			sf::Event event;
			
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed)
					window.close();
				if (event.type == sf::Event::KeyPressed) {
					if (event.key.code == sf::Keyboard::Up) rotate = true;
					else if (event.key.code == sf::Keyboard::Left) dx = -1;
					else if (event.key.code == sf::Keyboard::Right) dx = 1;
				}
			}
			
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) delay = 0.05;
					
			// MOVE
			
			for (int i = 0; i < 4; i++) {
				b[i] = a[i];
				a[i].x += dx;
			}
			
			if (!check()) for (int i = 0; i < 4; i++) a[i] = b[i];
			
			// ROTATE
			if (rotate) {
				Point p = a[1]; // center of rotation
				for (int i = 0; i < 4; i++) {
					int x = a[i].y - p.y;
					int y = a[i].x - p.x;
					
					a[i].x = p.x - x; 
					a[i].y = p.y + y;
				}
				if (!check()) for (int i = 0; i < 4; i++) a[i] = b[i];
			}
			
			// TICK-TACK
			if (timer > delay) {
				for (int i = 0; i < 4; i++) {
					b[i] = a[i];
					a[i].y += 1;
				}
				
				if (!check()) {
					for (int i = 0; i < 4; i++) 
						field[b[i].y] [b[i].x] = colorNum;
					colorNum = 1 + rand() % 7;
					int n = rand() % 7;
			
					for (int i = 0; i < 4; i++) {
						a[i].x = figures[n][i] % 2;
						a[i].y = figures[n][i] / 2;
					}
				
				
				}
				timer = 0;
			}
			
			// check lines
			
			int k = M - 1;
			for (int i = M - 1; i > 0; i--) {
				int count = 0;
				for (int j = 0; j < N; j++) {
					if (field[i][j]) count++;
					field[k][j] = field[i][j];
				}
				if (count < N) k--;
			}

			dx = 0;
			rotate = 0;
			delay = 0.3;
			
			// DRAW
			window.clear(sf::Color::White);
			window.draw(bb);
			
			for (int i = 0; i < M; i++)
				for (int j = 0; j < N; j++) {
					if (field[i][j] == 0) continue;
					s.setTextureRect(sf::IntRect(field[i][j] * 18, 0, 18, 18));
					s.setPosition(j * 18, i  * 18);	
					s.move(28, 31); //offset
					window.draw(s);
				}
			
			for (int i = 0; i < 4; i++) {
				s.setTextureRect(sf::IntRect(colorNum * 18, 0, 18, 18));
				s.setPosition(a[i].x * 18, a[i].y * 18);
				s.move(28, 31); //offset
				//std::cout << "setPos: " << i << ", a[" << i << "].x * 18 = " << (a[i].x * 18)  << ", a[" << i << "].y * 18 = " << (a[i].y * 18) << '\n';
				window.draw(s);
				
			}
			
			window.display();
			// return 0;
		}
		
		return 0;
	}
