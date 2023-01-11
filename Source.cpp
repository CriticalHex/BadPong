#include<SFML/Graphics.hpp>

class Player {
public:
	Player(int x, int y, int width, int height);
	void draw(sf::RenderWindow& screen);
	sf::RectangleShape paddle;
};

class Ball {
public:
	Ball();
	void move();
	void draw(sf::RenderWindow& screen);
	void collide(sf::RectangleShape& paddle);
	sf::RectangleShape ball;
	int vx = -5;
	int vy = 5;
};

int main() {

	sf::RenderWindow window(sf::VideoMode(0, 0), "SFML!", sf::Style::Fullscreen);
	window.setFramerateLimit(60);

	Player P1(20, 490, 10, 150);
	Player P2(1880, 490, 10, 150);
	Ball ball;

	while (window.isOpen()) {
		sf::Event event;


		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
				window.close();
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			if (P1.paddle.getPosition().y - 10 >= 0)
				P1.paddle.setPosition(P1.paddle.getPosition().x, P1.paddle.getPosition().y - 10);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			if (P1.paddle.getPosition().y + 10 <= 1080 - P1.paddle.getSize().y)
				P1.paddle.setPosition(P1.paddle.getPosition().x, P1.paddle.getPosition().y + 10);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			if (P2.paddle.getPosition().y - 10 >= 0)
				P2.paddle.setPosition(P2.paddle.getPosition().x, P2.paddle.getPosition().y - 10);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			if (P2.paddle.getPosition().y + 10 <= 1080 - P2.paddle.getSize().y)
				P2.paddle.setPosition(P2.paddle.getPosition().x, P2.paddle.getPosition().y + 10);
		}

		ball.move();
		ball.collide(P1.paddle);
		ball.collide(P2.paddle);

		window.clear(sf::Color(6, 8, 12));

		P1.draw(window);
		P2.draw(window);
		ball.draw(window);

		window.display();

	}
	return 0;
};

Player::Player(int x, int y, int width, int height) {
	paddle.setPosition(x, y);
	paddle.setSize(sf::Vector2f(width, height));
	paddle.setFillColor(sf::Color::Magenta);

};

void Player::draw(sf::RenderWindow& screen) {
	screen.draw(paddle);
}

Ball::Ball() {
	ball.setPosition(1920 / 2, 1080 / 2);
	ball.setSize(sf::Vector2f(20, 20));
	ball.setFillColor(sf::Color::Green);
};

void Ball::draw(sf::RenderWindow& screen) {
	screen.draw(ball);
}

void Ball::collide(sf::RectangleShape& paddle) {
	if (ball.getGlobalBounds().intersects(paddle.getGlobalBounds())) {
		vx *= -1;
	}
}

void Ball::move() {
	if (ball.getPosition().x <= 0 || ball.getPosition().x >= 1920 - ball.getSize().x)
		vx *= -1;
	if (ball.getPosition().y <= 0 || ball.getPosition().y >= 1080 - ball.getSize().y)
		vy *= -1;

	ball.setPosition(ball.getPosition().x + vx, ball.getPosition().y + vy);
}