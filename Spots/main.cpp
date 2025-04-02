#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Spots.h"
#include <iostream>

int main()
{
    Spots spots(200, 200, 4, 0.5);

    sf::RenderWindow window(sf::VideoMode(800, 800), "Spots");
    window.setFramerateLimit(60);

    bool update = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            window.close();
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
            update = true;

        if (update)
            spots.update();

        const std::vector<sf::RectangleShape>& pixels = spots.getPixels();

        window.clear();
        for (auto& pixel : pixels)
            window.draw(pixel);
        window.display();
    }

    //spots.saveDensityChartDataToFile("./density.txt", 1000);

	return 0;
}