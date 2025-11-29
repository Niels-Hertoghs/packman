//
// Created by niels_hertoghs on 11/20/25.
//

#include "state.h"
#include "../../logic/world.h"
#include <fstream>
#include <iostream>
#include <sstream>

#include "make_text.h"
#include "stateManeger.h"

namespace view {
    state::state() {
        sf::Font Font;
        sf::Texture Texture;
        try {

            if (!Font.loadFromFile("input_output/packman_font.ttf")) {
                throw std::runtime_error("Kon het lettertype niet laden!");
            }
            if (!Texture.loadFromFile("input_output/Logo.png")) {
                throw std::runtime_error("Texture file with name \"input_output/Logo.png\" does not exist");
            }

        } catch (const std::exception& e) {
            std::cerr << "Fout bij het openen of verwerken van bestand: " << e.what() << std::endl;
            throw;
        }
        font = Font;
        texture = Texture;
    }

    /// ---------------------------------------------------------------------------------------------------------------
    /// @class menuState
    /// ---------------------------------------------------------------------------------------------------------------

    std::pair<std::vector<sf::Text>,std::vector<sf::RectangleShape>> menuState::run(sf::RenderWindow& window, sf::Event& event, stateManeger& manager, camera& cam, std::shared_ptr<logic::world> wereld, const
                        float& deltaTime)
    {

        std::ifstream file("input_output/HighScores.txt"); // open het bestand met de high score
        try {
            if (!file) {
                std::cerr << "Kon bestand niet openen.\n";
            }

        } catch (const std::exception& e) {
            std::cerr << "Fout bij het openen of verwerken van bestand: " << e.what() << std::endl;
            throw;
        }

        std::vector<sf::Text> text;
        std::vector<sf::RectangleShape> rectangles;

        // menu title maken
        sf::Text menuText = makeText(font, "Menu", 0.15f, sf::Color::Yellow, 0.f, 0.55f,cam);
        text.push_back(menuText);

        // De high score tekst
        sf::Text highscoreText = makeText(font, "Previous High scores:", 0.1f, sf::Color::White, 0.f, 0.35f,cam);
        text.push_back(highscoreText);

        //De high scores zelf
        //De string maken
        std::string inhoud((std::istreambuf_iterator<char>(file)),
                       std::istreambuf_iterator<char>()); // lees alles

        // score inlezen uit file, elke score op een aparte lijn
        std::string highScoreText;
        std::stringstream ss(inhoud);
        std::string lijn;

        int teller = 1;

        while (std::getline(ss, lijn) && teller <= 5) {
            highScoreText += std::to_string(teller) + ": " + lijn + "\n";
            teller++;
        }

        sf::Text highNumbText = makeText(font, highScoreText, 0.05f, sf::Color::White, 0.f, 0.f,cam);
        sf::FloatRect highNumbBounds = highNumbText.getLocalBounds();
        highNumbText.setOrigin(highNumbBounds.width / 2.f, highNumbBounds.height / 2.f); // het midden van de tekst is de coo waar het staat
        text.push_back(highNumbText);



        //de play butten
        sf::RectangleShape playButton = makeButton(0.4f,1.2f,sf::Color::Green,cam,0.f,-0.5f);
        rectangles.push_back(playButton);

        sf::Text playText = makeText(font, "Play", 0.2f, sf::Color::Magenta, 0.f, -0.5f,cam);
        text.push_back(playText);

        if (event.type == sf::Event::MouseButtonPressed &&
             event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
            if (playButton.getGlobalBounds().contains(mousePos)) {
                // voor als het programma meerdere keren achter elkaar gerund wordt zonder te sluiten
                logic::Stopwatch::getInstance()->reset();
                wereld->clear();

                // alle view observers linken aan objecten, elk object een observer geven
                std::shared_ptr<logic::Score> score = std::make_shared<logic::Score>(manager); // score observer aanmaken


                // alles in de wereld inladen
                wereld->startWorld(score->getLevel());


                std::unique_ptr<view::worldView> wereldView = std::make_unique<view::worldView>(wereld,cam,window,score);
                wereld->subscribeScore(score);

                std::unique_ptr<LevelState> level = std::make_unique<LevelState>(wereld,std::move(wereldView));
                //unique maken en in de private zetten, dan eventuele arhumenten verwijderen
                manager.pushState(std::move(level));
                return {};
            }
        }
        return {text,rectangles};

    }

    /// ---------------------------------------------------------------------------------------------------------------
    /// @class LevelState
    /// ---------------------------------------------------------------------------------------------------------------


    LevelState::LevelState(std::shared_ptr<logic::world> wereld,std::unique_ptr<view::worldView> worldV)
        : worldView(std::move(worldV)) {}

    std::pair<std::vector<sf::Text>,std::vector<sf::RectangleShape>> LevelState::run(sf::RenderWindow& window, sf::Event& event, stateManeger& manager, camera& cam, std::shared_ptr<logic::world> wereld, const
                         float& deltaTime) {

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Up) {
                wereld->updatePacmanDir(directions::UP);
            } else if (event.key.code == sf::Keyboard::Down) {
                wereld->updatePacmanDir(directions::DOWN);
            } else if (event.key.code == sf::Keyboard::Left) {
                wereld->updatePacmanDir(directions::LEFT);
            } else if (event.key.code == sf::Keyboard::Right) {
                wereld->updatePacmanDir(directions::RIGHT);
            } else if (event.key.code == sf::Keyboard::Escape) {
                manager.pushState(std::make_unique<pausedState>());
            }
        }

        worldView->draw();
        wereld->update(deltaTime);
        return {};
    }

    /// --------------------------------------------------------------------------------------------------------------
    /// @class gameOverState
    /// --------------------------------------------------------------------------------------------------------------

    std::pair<std::vector<sf::Text>,std::vector<sf::RectangleShape>> gameOverState::run(sf::RenderWindow& window, sf::Event& event, stateManeger& manager, camera& cam, std::shared_ptr<logic::world> wereld, const float& deltaTime) {
        std::vector<sf::Text> text;
        std::vector<sf::RectangleShape> rectangles;

        // game over text
        sf::Text gameOverText = makeText(font, "GAME OVER", 0.2f, sf::Color::Red,0.f,0.1f,cam);
        text.push_back(gameOverText);

        // pacman logo
        sf::RectangleShape logo = makeButton(0.4f,1.2f,sf::Color::White,cam, 0.f, 0.7f);
        logo.setTexture(&texture);
        rectangles.push_back(logo);

        // Back to menu buttom
        sf::RectangleShape backToMenuButton = makeButton(0.4f,1.2f,sf::Color::Green,cam,0.f,-0.5f);
        rectangles.push_back(backToMenuButton);

        sf::Text playText = makeText(font, "Back To Menu", 0.15f, sf::Color::Magenta, 0.f, -0.5f,cam);
        text.push_back(playText);

        if (event.type == sf::Event::MouseButtonPressed &&
             event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
            if (backToMenuButton.getGlobalBounds().contains(mousePos)) {
                manager.prevState();
                return {};
            }
        }

    return {text,rectangles};
    }

    std::pair<std::vector<sf::Text>,std::vector<sf::RectangleShape>> VictoryState::run(sf::RenderWindow& window, sf::Event& event, stateManeger& manager, camera& cam, std::shared_ptr<logic::world> wereld, const float& deltaTime) {

        sf::Texture Texture;
        try {
            if (!Texture.loadFromFile("input_output/victoryPacman.png")) {
                throw std::runtime_error("Texture file with name \"input_output/victoryPacman.png\" does not exist");
            }

        } catch (const std::exception& e) {
            std::cerr << "Fout bij het openen of verwerken van bestand: " << e.what() << std::endl;
            throw;
        }
        victoryTexture = Texture;

        std::vector<sf::Text> text;
        std::vector<sf::RectangleShape> rechthoeken;

        // pacman logo
        sf::RectangleShape logo = makeButton(0.4f,1.2f,sf::Color::White,cam, 0.f, 0.7f);
        logo.setTexture(&texture);
        rechthoeken.push_back(logo);

        // win afbeelding
        sf::RectangleShape victory = makeButton(0.7f, 0.7f,sf::Color::White,cam, 0.f, 0.1f);
        victory.setTexture(&victoryTexture);
        rechthoeken.push_back(victory);

        // next Level button
        sf::RectangleShape backToMenuButton = makeButton(0.4f,1.2f,sf::Color::Green,cam,0.f,-0.5f);
        rechthoeken.push_back(backToMenuButton);

        sf::Text playText = makeText(font, "Next Level", 0.15f, sf::Color::Magenta, 0.f, -0.5f,cam);
        text.push_back(playText);

        if (event.type == sf::Event::MouseButtonPressed &&
             event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
            if (backToMenuButton.getGlobalBounds().contains(mousePos)) {
                // alles ven reseten
                logic::Stopwatch::getInstance()->reset();
                wereld->clear();

                // alles opnieuw in de wereld inladen
                std::shared_ptr<logic::Score> score = wereld->get_score();

                wereld->startWorld(score->getLevel());

                // alle view observers linken aan objecten, elk object een observer geven
                std::unique_ptr<view::worldView> wereldView = std::make_unique<view::worldView>(wereld,cam,window,score);

                std::unique_ptr<LevelState> level = std::make_unique<LevelState>(wereld,std::move(wereldView));

                //unique maken en in de private zetten, dan eventuele arhumenten verwijderen
                manager.pushStateAndDelete(std::move(level));
                return {};
            }
        }

        return {text,rechthoeken};
    }

    /// --------------------------------------------------------------------------------------------------------------
    /// @class pausedState
    /// --------------------------------------------------------------------------------------------------------------

    std::pair<std::vector<sf::Text>,std::vector<sf::RectangleShape>> pausedState::run(sf::RenderWindow& window, sf::Event& event, stateManeger& manager, camera& cam, std::shared_ptr<logic::world> wereld, const float& deltaTime) {

        std::vector<sf::Text> text;
        std::vector<sf::RectangleShape> rechthoeken;

        // continue playing button
        sf::RectangleShape continuePlayingButton = makeButton(0.4f,1.2f,sf::Color::Green,cam,0.f,0.f);
        rechthoeken.push_back(continuePlayingButton);

            // continue playing text
        sf::Text playText = makeText(font, "continue playing", 0.11f, sf::Color::Magenta, 0.f, 0.f,cam);
        text.push_back(playText);

        // back to menu button
        // een zwarte butten rond de tekst zodat je daar op kan klikken om terug naar menu te gaan, je ziet de butten niet
        // voordeel: je kan rond de tekst klikken en het werkt (In de buurt)
        // (om te zien waar de button ligt, verander de kleur zwart naar een andere kleur)
        sf::RectangleShape backToMenuButton = makeButton(0.2f,1.0f,sf::Color::Black,cam,-0.97f,0.87f);
        backToMenuButton.setOrigin(0,0); // de linker boven hoek van de buttom altijd in de linkerbovenhoek van het scherm zetten
        rechthoeken.push_back(backToMenuButton);

            // back to menu text
        sf::Text backToMenuText = makeText(font, "< Back to menu", 0.11f, sf::Color::Yellow, -0.95f, 0.85f,cam);

        // de linker boven hoek van de text altijd in de linkerbovenhoek van het scherm zetten
        backToMenuText.setOrigin(0,0);
        text.push_back(backToMenuText);


        if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
            if (continuePlayingButton.getGlobalBounds().contains(mousePos)) {
                manager.prevState();
            } else if (backToMenuButton.getGlobalBounds().contains(mousePos)) {
                // de paused state poppen en de level state poppen -> in menu state
                manager.pop2State();
            }
        }

        // alles op het scherm tekenen
        return {text,rechthoeken};
    }

} // view