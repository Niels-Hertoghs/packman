//
// Created by niels on 10/30/25.
//

#include "game.h"

#include <iostream>
#include <SFML/Graphics.hpp>

#include "state_maneger/stateManeger.h"

game::game() {

}

void game::playGame() {
    stateManeger manager; // state manager aanmaken

    // Vraag de resolutie van het primaire scherm op
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

    std::cout << "Desktop resolutie: " << desktop.width << "x" << desktop.height << std::endl;

    // Stel de gewenste schaal in (bijv. 80% van de schermgrootte)
    float scale = 0.8f;
    unsigned int width = static_cast<unsigned int>(desktop.width * scale);
    unsigned int height = static_cast<unsigned int>(desktop.height * scale);

    // window aanmaken
    sf::RenderWindow window(sf::VideoMode(width,height), "window", sf::Style::Default);
    window.setVerticalSyncEnabled(true); // max FPS aan de FPS van aparaat

    // Plaats het venster in het midden van het scherm
    window.setPosition(sf::Vector2i(
        (desktop.width - width) / 2,
        (desktop.height - height) / 2
    ));

    // main wondow loop
    while(window.isOpen()) {
        sf::Event event{};
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear(sf::Color::Black);

        manager.runTop(window, event);

        window.display();
    }
}