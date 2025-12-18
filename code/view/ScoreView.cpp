//
// Created by niels_hertoghs on 11/20/25.
//

#include "ScoreView.h"

#include <fstream>

#include "state_maneger/state.h"
#include "state_maneger/make_text.h"
#include "state_maneger/stateManeger.h"
#include <iostream>

namespace view {

ScoreView::ScoreView(sf::RenderWindow& window, camera& cam, int score, int level, int lives,
                     std::shared_ptr<stateManeger> manager)
    : ObserverView(window, cam), _manager(std::move(manager)) {
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
    sf::Text ScoreText = makeText(font, "SCORE: " + std::to_string(score), 0.05, sf::Color::Yellow, -0.95f, -0.95f,
                                  _camera);
    sf::FloatRect scoreTextBounds = ScoreText.getLocalBounds();
    ScoreText.setOrigin(0, scoreTextBounds.height);
    scoreText = ScoreText;

    // het level afbeelden
    sf::Text LevelText = makeText(font, "Level: " + std::to_string(level), 0.16f, sf::Color::Yellow, 0.f,
                                  1.f - 1.f / 7.f, _camera);
    levelText = LevelText;

    // remainings lifes afbeelden (rechts vanonder)
    sf::Text LifesText = makeText(font, "# LIFES REMAINING:" + std::to_string(lives), 0.05, sf::Color::Yellow, 0.95f,
                                  -0.95f, _camera);
    sf::FloatRect LifesBounds = LifesText.getLocalBounds();
    LifesText.setOrigin(LifesBounds.width, LifesBounds.height);
    livesText = LifesText;
}

void ScoreView::draw() {
    const std::pair<unsigned int, unsigned int> scorepos = _camera.worldToPixel(-0.95f, -0.95f);
    scoreText.setCharacterSize(_camera.distanceToPixelsHeight(0.05f));
    scoreText.setPosition(static_cast<float>(scorepos.first), static_cast<float>(scorepos.second));
    const sf::FloatRect scoreTextBounds = scoreText.getLocalBounds();
    scoreText.setOrigin(0, scoreTextBounds.height);
    window.draw(scoreText);

    const std::pair<unsigned int, unsigned int> levelpos = _camera.worldToPixel(-0.f, 1.f - 1.f / 7.f);
    levelText.setCharacterSize(_camera.distanceToPixelsHeight(0.16f));
    levelText.setPosition(static_cast<float>(levelpos.first), static_cast<float>(levelpos.second));
    const sf::FloatRect levelTextBounds = levelText.getLocalBounds();
    levelText.setOrigin(levelTextBounds.width / 2, levelTextBounds.height / 2);
    window.draw(levelText);

    const std::pair<unsigned int, unsigned int> livespos = _camera.worldToPixel(0.95f, -0.95f);
    livesText.setCharacterSize(_camera.distanceToPixelsHeight(0.05f));
    livesText.setPosition(static_cast<float>(livespos.first), static_cast<float>(livespos.second));
    const sf::FloatRect livesTextBounds = livesText.getLocalBounds();
    livesText.setOrigin(livesTextBounds.width, livesTextBounds.height);
    window.draw(livesText);
}

void ScoreView::notify(const logic::scoreViewNotifications& message) {
    switch (message.type) {
    case logic::scoreViewTypes::UPDATE_SCORE: {
        int currentScore = message.score;
        sf::Text ScoreText = makeText(font, "SCORE: " + std::to_string(currentScore), 0.05, sf::Color::Yellow, -0.95f,
                                      -0.95f, _camera);
        sf::FloatRect scoreTextBounds = ScoreText.getLocalBounds();
        ScoreText.setOrigin(0, scoreTextBounds.height);
        scoreText = ScoreText;
        break;
    }

    case logic::scoreViewTypes::UPDATE_LIVES: {
        int livesLeft = message.lives;
        sf::Text LifesText = makeText(font, "# LIFES REMAINING:" + std::to_string(livesLeft), 0.05, sf::Color::Yellow,
                                      0.95f, -0.95f, _camera);
        sf::FloatRect LifesBounds = LifesText.getLocalBounds();
        LifesText.setOrigin(LifesBounds.width, LifesBounds.height);
        livesText = LifesText;
        break;
    }
    case logic::scoreViewTypes::END_GAME: {
        int score = message.score;
        gameEnded(score);
        _manager->gameOverState();
        break;
    }
    case logic::scoreViewTypes::UPDATE_LEVEL: {
        int nextlevel = message.level;
        sf::Text LevelText = makeText(font, "Level: " + std::to_string(nextlevel), 0.16f, sf::Color::Yellow, 0.f,
                                      1.f - 1.f / 7.f, _camera);
        levelText = LevelText;
        _manager->startVictory();
        break;
    }
    default:
        return;
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

    std::vector<int> highscores = {score};
    int value;

    // Lees de bestaande highscores in
    while (file >> value) {
        highscores.push_back(value);
    }

    file.clear();
    file.close();

    std::sort(highscores.begin(), highscores.end(), std::greater<>());
    highscores.pop_back();

    // Schrijf terug naar het bestand
    std::ofstream out("input_output/HighScores.txt");
    for (int sc : highscores) {
        out << sc << "\n";
    }
    out.close();

}

} // view
