//
// Created by niels on 10/30/25.
//
#include <SFML/Graphics.hpp>
#include <memory>
#include "stateManeger.h"
#include <fstream>

#include "../../render/render.h"
#include "../../world.h"


sf::Text makeText(const sf::Font& fontF, const std::string& text, double charSize, sf::Color color,double x, double y,const camera& cam) {
    sf::Text Text;
    Text.setFont(fontF);
    Text.setString(text);
    Text.setCharacterSize(cam.distanceToPixelsHeight(charSize));
    Text.setFillColor(color);

    // Zet origin wél met top en left in aanmerking genomen
    sf::FloatRect bounds = Text.getLocalBounds();
    Text.setOrigin((bounds.left + bounds.width) / 2.f,
                   (bounds.top  + bounds.height) / 2.f);

    // En pas dan pas de positie toe (zodat position refereert aan de nieuwe origin)
    auto Pos = cam.worldToPixel(x, y);
    Text.setPosition(static_cast<float>(Pos.first), static_cast<float>(Pos.second));

    return Text;
}
/// ---------------------------------------------------------------------------------------------------------------
/// @class stateManeger
/// ---------------------------------------------------------------------------------------------------------------

stateManeger::stateManeger() {
    pushState(std::make_unique<menuState>());
}

LevelState::LevelState(std::shared_ptr<logic::world> wereld,std::unique_ptr<view::worldView> world)
    : worldView(std::move(world))
 {
    // wereld.start();
}


void stateManeger::pushState(std::unique_ptr<state> newState) {
    stack.push(std::move(newState));
}

void stateManeger::prevState() {
    if (!stack.empty()) {
        stack.pop();
    }
}

std::unique_ptr<state> stateManeger::getCurrentState() {
    if (stack.empty()) return nullptr;
    return std::move(stack.top());
}

void stateManeger::runTop(sf::RenderWindow& window, sf::Event& event, const camera& cam,std::shared_ptr<logic::world> wereld,const float &deltaTime,Stopwatch& stopwatch) {
    stack.top().get()->run(window, event,*this,cam,wereld,deltaTime, stopwatch);
}


/// ---------------------------------------------------------------------------------------------------------------
/// @class menuState
/// ---------------------------------------------------------------------------------------------------------------

void menuState::run(sf::RenderWindow& window, sf::Event& event,stateManeger& manager, const camera& cam,std::shared_ptr<logic::world> wereld,const float &deltaTime,Stopwatch& stopwatch) {

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
            std::unique_ptr<view::worldView> wereldView = std::make_unique<view::worldView>(wereld,stopwatch,cam,window);

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

void LevelState::run(sf::RenderWindow &window, sf::Event &event, stateManeger &manager, const camera& cam,std::shared_ptr<logic::world> wereld,const float &deltaTime,Stopwatch& stopwatch) {

    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) {
            wereld->updatePacmanDir("up");
        } else if (event.key.code == sf::Keyboard::Down) {
            wereld->updatePacmanDir("down");
        } else if (event.key.code == sf::Keyboard::Left) {
            wereld->updatePacmanDir("left");
        } else if (event.key.code == sf::Keyboard::Right) {
            wereld->updatePacmanDir("right");
        }
    }


    worldView->draw();



    // sf::Font Font;
    // if (!Font.loadFromFile("input_output/packman_font.ttf")) {
    //     std::cerr << "Kon het lettertype niet laden!" << std::endl;
    // }
    //
    // // alle sprites in een render classe zetten
    // std::shared_ptr<render::Render> tussen = wereld->render(cam,Font);
    //
    // // alle sprites in de window zetten
    // for (const auto& line:tussen->sprites) {
    //     window.draw(line);
    // }
    //
    // // alle coins in de window zetten
    // for (const auto& line:tussen->coins) {
    //     window.draw(line);
    // }
    //
    // // alle text in de window zetten
    // for (const auto& text:tussen->text) {
    //     window.draw(text);
    // }

    wereld->update(deltaTime);
}

