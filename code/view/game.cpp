//
// Created by niels on 10/30/25.
//

#include "game.h"

namespace view {
void game::playGame() {
    view::stateManeger manager; // state manager aanmaken
    std::shared_ptr<logic::world> wereld = std::make_shared<logic::world>("input_output/map.txt");

    // Vraag de resolutie van het primaire scherm op
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

    // Stel de gewenste schaal in (80% van de schermgrootte)
    double scale = 0.8f;
    unsigned int width = desktop.width * scale;
    unsigned int height = desktop.height * scale;
    view::camera cam(width, height);

    // window aanmaken
    sf::RenderWindow window(sf::VideoMode(width,height), "window", sf::Style::Default);
    window.setVerticalSyncEnabled(true);


    // Plaats het venster in het midden van het scherm
    window.setPosition(sf::Vector2i(
        (static_cast<int>(desktop.width - width)) / 2,
        (static_cast<int>(desktop.height - height)) / 2
    ));

    // main window loop
    while(window.isOpen()) {
        logic::Stopwatch::getInstance()->tick(); //stopwatch updaten
        double deltaTime = logic::Stopwatch::getInstance()->getDeltaTime(); // tijd sinds laatste tick

        sf::Event event{};
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::Resized) {
                // centreert de inhoud terug
                sf::FloatRect visibleArea(0, 0, static_cast<float>(event.size.width), static_cast<float>(event.size.height));
                window.setView(sf::View(visibleArea));

                // Update camera dimensions on window resize
                cam.setDimensions(event.size.width, event.size.height);
            }
        }
        window.clear(sf::Color::Black);
        manager.runTop(window, event, cam,wereld,static_cast<float>(deltaTime));

        window.display();
    }
};
}