//
// Created by niels_hertoghs on 11/20/25.
//

#include "state.h"
#include "../../world.h"
#include <fstream>
#include <iostream>
#include "make_text.h"
#include "stateManeger.h"

namespace view {
    /// ---------------------------------------------------------------------------------------------------------------
    /// @class menuState
    /// ---------------------------------------------------------------------------------------------------------------

    void menuState::run(sf::RenderWindow& window, sf::Event& event, stateManeger& manager, camera& cam, std::shared_ptr<logic::world> wereld, const
                        float& deltaTime) {

        //lettertype inladen
        sf::Font packmanFont;
        if (!packmanFont.loadFromFile("input_output/packman_font.ttf")) {
            std::cerr << "Kon het lettertype niet laden!" << std::endl;
        }

        // menu title maken
        sf::Text menuText = makeText(packmanFont, "Menu", 0.15f, sf::Color::Yellow, 0.f, 0.55f,cam);

        // De high score tekst
        sf::Text highscoreText = makeText(packmanFont, "Previous High scores:", 0.1f, sf::Color::White, 0.f, 0.35f,cam);


        //De high scores zelf
        //De string maken
        std::ifstream file("input_output/HighScores.txt"); // open het bestand met de high score
        if (!file) {
            std::cerr << "Kon bestand niet openen.\n";
        }
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

        sf::Text highNumbText = makeText(packmanFont, highScoreText, 0.05f, sf::Color::White, 0.f, 0.f,cam);
        sf::FloatRect highNumbBounds = highNumbText.getLocalBounds();
        highNumbText.setOrigin(highNumbBounds.width / 2.f, highNumbBounds.height / 2.f); // het midden van de tekst is de coo waar het staat



        //de play butten
        int playButtenSizeHeight = cam.distanceToPixelsHeight(0.4f);
        int playButtenSizeWidth = cam.distanceToPixelsWidth(1.2f);
        sf::RectangleShape playButton(sf::Vector2f(static_cast<float>(playButtenSizeWidth),static_cast<float>(playButtenSizeHeight)));
        playButton.setFillColor(sf::Color::Green);
        sf::FloatRect boundsRect =  playButton.getLocalBounds();
        playButton.setOrigin(boundsRect.width / 2.f, boundsRect.height / 2.f);
        std::pair<int, int> playButtenPos = cam.worldToPixel(0.f,-0.5f);
        playButton.setPosition(static_cast<float>(playButtenPos.first), static_cast<float>(playButtenPos.second));

        sf::Text playText = makeText(packmanFont, "Play", 0.2f, sf::Color::Magenta, 0.f, -0.5f,cam);

        if (event.type == sf::Event::MouseButtonPressed &&
             event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
            if (playButton.getGlobalBounds().contains(mousePos)) {
                // alles in de wereld inladen
                wereld->startWorld();
                // alle view observers linken aan objecten, elk object een observer geven
                std::shared_ptr<logic::Score> score = std::make_shared<logic::Score>(); // score observer aanmaken

                std::unique_ptr<view::worldView> wereldView = std::make_unique<view::worldView>(wereld,cam,window,score);
                wereld->subscribeScore(score);

                std::unique_ptr<LevelState> level = std::make_unique<LevelState>(wereld,std::move(wereldView));
                //unique maken en in de private zetten, dan eventuele arhumenten verwijderen
                manager.pushState(std::move(level));

            }
        }


        // alles tekenen op de window
        window.draw(menuText);
        window.draw(highNumbText);
        window.draw(highscoreText);
        window.draw(playButton);
        window.draw(playText);
    }

    /// ---------------------------------------------------------------------------------------------------------------
    /// @class LevelState
    /// ---------------------------------------------------------------------------------------------------------------


    LevelState::LevelState(std::shared_ptr<logic::world> wereld,std::unique_ptr<view::worldView> world)
        : worldView(std::move(world))
    {
        // wereld.start();
    }

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


} // view