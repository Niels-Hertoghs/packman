//
// Created by niels on 10/30/25.
//

#include "game.h"
#include "camera.h"
#include <iostream>
#include <SFML/Graphics.hpp>

#include "state_maneger/stateManeger.h"

game::game() {

}

void game::playGame() {
    stateManeger manager; // state manager aanmaken

    // Vraag de resolutie van het primaire scherm op
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

    // Stel de gewenste schaal in (80% van de schermgrootte)
    float scale = 0.8f;
    unsigned int width = desktop.width * scale;
    unsigned int height = desktop.height * scale;
    camera cam(width, height);

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
            } if (event.type == sf::Event::Resized) {
                // Update camera dimensions on window resize
                cam.setDimensions(event.size.width, event.size.height);
                std::cout << "New width: " << event.size.width << ", New height: " << event.size.height << std::endl;
            }
        }
        window.clear(sf::Color::Black);
        manager.runTop(window, event, cam);

        window.display();
    }
}