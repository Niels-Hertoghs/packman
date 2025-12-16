//
// Created by niels_hertoghs on 11/20/25.
//

#ifndef PACKMAN_STATE_H
#define PACKMAN_STATE_H
#include <memory>
#include <SFML/Graphics.hpp>
#include "../camera.h"
#include "../../view/worldView.h"

// Forward declarations
namespace logic {
class world;
}


namespace view {
// Forward declarations
class stateManeger;
class worldView;

/**
* @class state
* @brief Abstracte basis klasse voor alle staten van de game.
*/
class state {
protected:
    sf::Font font;       /// Font voor de tekst in deze state.
    sf::Texture texture; /// Texture voor de achtergrond of andere elementen in deze state.
public:
    /**
     * @brief Constructor
     */
    state();

    // Pure virtual methodes
    /**
     * @brief Laat de staat draaien, print het op het window.
     * @param window De window waar alles op getekend moet worden.
     * @param event Om eventuate evenementen te verwerken.
     * @param manager De state manager om van state te veranderen indien nodig.
     * @param cam Camera voor het omzetten van wereld naar pixel coordinaten.
     * @param wereld Pointer naar de wereld logica, om het eventueel te laten lopen.
     * @param deltaTime Het verschil in tijd sinds de laatste update.
     * @return Pair van vectoren met text en rechthoeken die getekend moeten worden.
     */
    virtual std::pair<std::vector<sf::Text>, std::vector<sf::RectangleShape> > run(
        sf::RenderWindow& window, sf::Event& event, stateManeger& manager, camera& cam,
        std::shared_ptr<logic::world> wereld, const
        float& deltaTime) = 0;

    /**
     * @brief Destructor
     */
    virtual ~state() = default;
};

/**
 * @class menuState
 * @brief Concrete klasse voor de menu staat van de game.
 */
class menuState final : public state {
public:
    /**
     * @brief Default constructor.
     */
    menuState() = default;

    // override methodes van pure virtual, voor commentaar en uitleg zie de originele pure virtual.
    [[nodiscard]] std::pair<std::vector<sf::Text>, std::vector<sf::RectangleShape> > run(
        sf::RenderWindow& window, sf::Event& event, stateManeger& manager, camera& cam,
        std::shared_ptr<logic::world> wereld, const
        float& deltaTime) override;
};

/**
 * @class LevelState
 * @brief Concrete klasse voor de level staat van de game.
 */
class LevelState final : public state {
    std::unique_ptr<view::worldView> worldView; /// Pointer naar de representatie van de wereld.
public:
    /**
     * @brief Constructor
     * @param wereld Pointer naar de logica van de wereld.
     * @param worldV Pointer naar de representatie van de wereld.
     */
    LevelState(const std::shared_ptr<logic::world>& wereld, std::unique_ptr<view::worldView> worldV);

    // override methodes van pure virtual, voor commentaar en uitleg zie de originele pure virtual.
    [[nodiscard]] std::pair<std::vector<sf::Text>, std::vector<sf::RectangleShape> > run(
        sf::RenderWindow& window, sf::Event& event, stateManeger& manager, camera& cam,
        std::shared_ptr<logic::world> wereld, const
        float& deltaTime) override;
};

/**
 * @class gameOverState
 * @brief Concrete klasse voor de game over staat van de game (als de player dood is).
 */
class gameOverState final : public state {
public:
    /**
     * @brief Default constructor.
     */
    gameOverState() = default;

    // override methodes van pure virtual, voor commentaar en uitleg zie de originele pure virtual.
    [[nodiscard]] std::pair<std::vector<sf::Text>, std::vector<sf::RectangleShape> > run(
        sf::RenderWindow& window, sf::Event& event, stateManeger& manager, camera& cam,
        std::shared_ptr<logic::world> wereld, const float& deltaTime) override;
};

/**
* @class VictoryState
* @brief Concrete klasse voor de virctory staat van de game (voor het naar een volgend level gaat).
*/
class VictoryState final : public state {
    sf::Texture victoryTexture;

public:
    /**
     * @brief Default constructor.
     */
    VictoryState() = default;

    // override methodes van pure virtual, voor commentaar en uitleg zie de originele pure virtual.
    [[nodiscard]] std::pair<std::vector<sf::Text>, std::vector<sf::RectangleShape> > run(
        sf::RenderWindow& window, sf::Event& event, stateManeger& manager, camera& cam,
        std::shared_ptr<logic::world> wereld, const float& deltaTime) override;
};

/**
* @class pausedState
* @brief Concrete klasse voor paused staat inj de game (als de esc knop ingedrukt wordt tijdens het spelen).
*/
class pausedState final : public state {
public:
    /**
     * @brief Default constructor.
     */
    pausedState() = default;

    // override methodes van pure virtual, voor commentaar en uitleg zie de originele pure virtual.
    [[nodiscard]] std::pair<std::vector<sf::Text>, std::vector<sf::RectangleShape> > run(
        sf::RenderWindow& window, sf::Event& event, stateManeger& manager, camera& cam,
        std::shared_ptr<logic::world> wereld, const float& deltaTime) override;
};

} // view

#endif //PACKMAN_STATE_H
