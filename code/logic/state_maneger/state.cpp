//
// Created by niels_hertoghs on 11/20/25.
//

#include "state.h"
#include "../world.h"
#include <fstream>
#include <iostream>
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

    void menuState::run(sf::RenderWindow& window, sf::Event& event, stateManeger& manager, camera& cam, std::shared_ptr<logic::world> wereld, const
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

        std::string highScoreText = "1: ";
        int teller = 1;
        for (char c : inhoud) {
             if (c == ' ') {
                 highScoreText += '\n' +std::to_string(teller) + ":";
                 teller++;
             }
            highScoreText.push_back(c);
        }

        sf::Text highNumbText = makeText(font, highScoreText, 0.05f, sf::Color::White, 0.f, 0.f,cam);
        sf::FloatRect highNumbBounds = highNumbText.getLocalBounds();
        highNumbText.setOrigin(highNumbBounds.width / 2.f, highNumbBounds.height / 2.f); // het midden van de tekst is de coo waar het staat
        text.push_back(highNumbText);



        //de play butten
        sf::RectangleShape playButton = makeButton(0.4f,1.2f,sf::Color::Green,cam,0.f,-0.5f);

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
                return;
            }
        }


        // alles tekenen op de window
        window.draw(playButton);
        for (auto& Text : text) {
            window.draw(Text);
        }

    }

    /// ---------------------------------------------------------------------------------------------------------------
    /// @class LevelState
    /// ---------------------------------------------------------------------------------------------------------------


    LevelState::LevelState(std::shared_ptr<logic::world> wereld,std::unique_ptr<view::worldView> worldV)
        : worldView(std::move(worldV)) {}

    void LevelState::run(sf::RenderWindow& window, sf::Event& event, stateManeger& manager, camera& cam, std::shared_ptr<logic::world> wereld, const
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
            }
        }

        worldView->draw();
        wereld->update(deltaTime);
    }

    /// --------------------------------------------------------------------------------------------------------------
    /// @class gameOverState
    /// --------------------------------------------------------------------------------------------------------------

    void gameOverState::run(sf::RenderWindow& window, sf::Event& event, stateManeger& manager, camera& cam, std::shared_ptr<logic::world> wereld, const float& deltaTime) {
        std::vector<sf::Text> text;

        // game over text
        sf::Text gameOverText = makeText(font, "GAME OVER", 0.2f, sf::Color::Red,0.f,0.1f,cam);
        text.push_back(gameOverText);

        // pacman logo
        sf::RectangleShape logo = makeButton(0.4f,1.2f,sf::Color::White,cam, 0.f, 0.7f);
        logo.setTexture(&texture);

        // Back to menu buttom
        sf::RectangleShape backToMenuButton = makeButton(0.4f,1.2f,sf::Color::Green,cam,0.f,-0.5f);

        sf::Text playText = makeText(font, "Back To Menu", 0.15f, sf::Color::Magenta, 0.f, -0.5f,cam);
        text.push_back(playText);

        if (event.type == sf::Event::MouseButtonPressed &&
             event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
            if (backToMenuButton.getGlobalBounds().contains(mousePos)) {
                manager.prevState();
                return;
            }
        }

        // alles tekenen op de window
        window.draw(backToMenuButton);
        window.draw(logo);
        for (auto& Text : text) {
            window.draw(Text);
        }
    }

    void VictoryState::run(sf::RenderWindow& window, sf::Event& event, stateManeger& manager, camera& cam, std::shared_ptr<logic::world> wereld, const float& deltaTime) {

        sf::Texture Texture;
        try {
            if (!Texture.loadFromFile("input_output/victoryPacman.png")) {
                throw std::runtime_error("Texture file with name \"input_output/victoryPacman.png\" does not exist");
            }

        } catch (const std::exception& e) {
            std::cerr << "Fout bij het openen of verwerken van bestand: " << e.what() << std::endl;
            throw;
        }

        std::vector<sf::Text> text;
        std::vector<sf::RectangleShape> rechthoeken;

        // pacman logo
        sf::RectangleShape logo = makeButton(0.4f,1.2f,sf::Color::White,cam, 0.f, 0.7f);
        logo.setTexture(&texture);
        rechthoeken.push_back(logo);

        // win afbeelding
        sf::RectangleShape victory = makeButton(0.7f, 0.7f,sf::Color::White,cam, 0.f, 0.1f);
        victory.setTexture(&Texture);
        rechthoeken.push_back(victory);

        // next Level
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
                return;
            }
        }


        // alles op het scherm tekenen
        for (auto& rechthoek : rechthoeken) {
            window.draw(rechthoek);
        }
        for (auto& Text : text) {
            window.draw(Text);
        }
    }



} // view