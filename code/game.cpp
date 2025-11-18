//
// Created by niels on 10/30/25.
//

#include "game.h"


game::game() {

}

void game::playGame() {
    stateManeger manager; // state manager aanmaken
    Stopwatch& stopwatch = Stopwatch::getInstance(); //stopwatch aanmaken, als singleton
    std::shared_ptr<logic::world> wereld = std::make_shared<logic::world>("input_output/map.txt");
    // wereld->startWorld();


    // Vraag de resolutie van het primaire scherm op
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

    // Stel de gewenste schaal in (80% van de schermgrootte)
    double scale = 0.8f;
    unsigned int width = desktop.width * scale;
    unsigned int height = desktop.height * scale;
    camera cam(width, height);

    // window aanmaken
    sf::RenderWindow window(sf::VideoMode(width,height), "window", sf::Style::Default);


    // Plaats het venster in het midden van het scherm
    window.setPosition(sf::Vector2i(
        (desktop.width - width) / 2,
        (desktop.height - height) / 2
    ));

    // main window loop
    while(window.isOpen()) {
        stopwatch.tick(); //stopwatch updaten
        double deltaTime = stopwatch.getDeltaTime(); // tijd sinds laatste tick

        sf::Event event{};
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::Resized) {
                // centreert de inhoud terug
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));

                // Update camera dimensions on window resize
                cam.setDimensions(event.size.width, event.size.height);
            }
        }
        window.clear(sf::Color::Black);
        manager.runTop(window, event, cam,wereld,deltaTime);

        window.display();
    }
    // max 60 fps
    std::this_thread::sleep_for(std::chrono::milliseconds(16));
}
