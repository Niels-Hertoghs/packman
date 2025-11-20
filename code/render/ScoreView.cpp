//
// Created by niels_hertoghs on 11/20/25.
//

#include "ScoreView.h"

#include <iostream>

namespace view {
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

    ScoreView::ScoreView(sf::RenderWindow& window, camera& cam,std::shared_ptr<logic::Score>& Score) : Observer(window,cam), scoreModel(Score) {
        try {
            sf::Font Font;
            if (!Font.loadFromFile("input_output/packman_font.ttf")) {
                throw std::runtime_error("Kon het lettertype niet laden!");
            }
            font = Font;

        } catch (const std::exception& e) {
            std::cerr << "Fout bij het openen of verwerken van bestand: " << e.what() << std::endl;
            throw;
        }

        // de score afbeelden
        int currentScore = Score->getScore();
        sf::Text ScoreText = makeText(font, "SCORE: " + std::to_string(currentScore) , 0.05, sf::Color::Yellow, -0.95f, -0.95f, _camera);
        sf::FloatRect scoreTextBounds = ScoreText.getLocalBounds();
        ScoreText.setOrigin(0,scoreTextBounds.height);
        scoreText = ScoreText;

        // het level afbeelden
        int level = Score->getLevel();
        sf::Text LevelText = makeText(font, "Level: " + std::to_string(level), 0.16f, sf::Color::Yellow, 0.f, 1.f - 1.f/7.f,_camera);
        levelText = LevelText;

        // remainings lifes afbeelden (rechts vanonder)
        int remainingLifes = Score->getLivesLeft();
        sf::Text LifesText = makeText(font, "# LIFES REMAINING:" + std::to_string(remainingLifes) , 0.05, sf::Color::Yellow, 0.95f, -0.95f, _camera);
        sf::FloatRect LifesBounds = LifesText.getLocalBounds();
        LifesText.setOrigin(LifesBounds.width,LifesBounds.height);
        lifesText = LifesText;
    }

    void ScoreView::draw() {
        window.draw(scoreText);
        window.draw(levelText);
        window.draw(lifesText);
    }

    void ScoreView::notify(enum notifications message) {
        switch (message) {
            case UPDATE_SCORE:
                int currentScore = 0;
                if (auto observer = scoreModel.lock()) {
                    currentScore = observer->getScore();
                }
                sf::Text ScoreText = makeText(font, "SCORE: " + std::to_string(currentScore) , 0.05, sf::Color::Yellow, -0.95f, -0.95f, _camera);
                sf::FloatRect scoreTextBounds = ScoreText.getLocalBounds();
                ScoreText.setOrigin(0,scoreTextBounds.height);
                scoreText = ScoreText;
                break;

        }
    }

} // view