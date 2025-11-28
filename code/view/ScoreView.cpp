//
// Created by niels_hertoghs on 11/20/25.
//

#include "ScoreView.h"

#include <fstream>

#include "state_maneger/state.h"
#include "state_maneger/make_text.h"
#include <iostream>

namespace view {

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
            case UPDATE_SCORE: {
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

            case UPDATE_LIVES: {
                int livesLeft = 0;
                if (auto observer = scoreModel.lock()) {
                    livesLeft = observer->getLivesLeft();
                }
                sf::Text LifesText = makeText(font, "# LIFES REMAINING:" + std::to_string(livesLeft) , 0.05, sf::Color::Yellow, 0.95f, -0.95f, _camera);
                sf::FloatRect LifesBounds = LifesText.getLocalBounds();
                LifesText.setOrigin(LifesBounds.width,LifesBounds.height);
                lifesText = LifesText;
                break;
            }
            case END_GAME: {
                int score = 0;
                if (auto observer = scoreModel.lock()) {
                    score = observer->getScore();
                }
                gameEnded(score);
                break;
            }
        default: return;
        }
    }

    void ScoreView::gameEnded(int score) {
        std::ifstream file("input_output/HighScores.txt"); // open het bestand met de high score
        try {
            if (!file) {
                std::cerr << "Kon bestand niet openen.\n";
            }

        } catch (const std::exception& e) {
            std::cerr << "Fout bij het openen of verwerken van bestand: " << e.what() << std::endl;
            throw;
        }

        std::vector<int> highscores;
        int value;
        bool insertOneTime = false;

        // Lees de bestaande highscores in
        while (file >> value) {
            if (score >= value && !insertOneTime) {
                highscores.push_back(score);
                insertOneTime = true;
            }
            highscores.push_back(value);
        }
        file.clear();
        file.close();

        if (insertOneTime) {
            highscores.pop_back();
        }


        // Schrijf terug naar het bestand
        std::ofstream out("input_output/HighScores.txt");
        for (int sc : highscores) {
            out << sc << "\n";
        }
        out.close();


    }

} // view