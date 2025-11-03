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

    // window aanmaken
    sf::RenderWindow window(sf::VideoMode(800,600), "window", sf::Style::Default);
    window.setVerticalSyncEnabled(true); // max FPS aan de FPS van aparaat

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