//
// Created by niels_hertoghs on 11/20/25.
//

#ifndef PACKMAN_STATE_H
#define PACKMAN_STATE_H
#include <memory>
#include <SFML/Graphics.hpp>
#include "../camera.h"
#include "../../logic/Stopwatch.h"
#include "../../view/worldView.h"

namespace logic {
    class world;
}


namespace view {
    class stateManeger;
    class worldView;
    /**
    * class state
    * brief Abstract base class for different game states.
    */
    class state {
    protected:
        sf::Font font;
        sf::Texture texture;
    public:

        state();
        virtual ~state() = default;

        virtual void run(sf::RenderWindow& window, sf::Event& event, stateManeger& manager, camera& cam, std::shared_ptr<logic::world> wereld, const
                         float& deltaTime) = 0;
    };

    /**
     * class menuState
     * brief Represents the menu state of the game.
     */
    class menuState : public state {
    public:
        menuState() = default;
        void run(sf::RenderWindow& window, sf::Event& event, stateManeger& manager, camera& cam, std::shared_ptr<logic::world> wereld, const
                 float& deltaTime) override;
    };

    /**
     * class LevelState
     * brief Represents the level state of the game.
     */
    class LevelState : public state {
    private:
        std::unique_ptr<view::worldView> worldView;
    public:
        LevelState(std::shared_ptr<logic::world> wereld,std::unique_ptr<view::worldView> worldV);
        void run(sf::RenderWindow& window, sf::Event& event, stateManeger& manager, camera& cam, std::shared_ptr<logic::world> wereld, const
                 float& deltaTime) override;
    };

    class gameOverState : public state {
    public:
        gameOverState() = default;
        void run(sf::RenderWindow& window, sf::Event& event, stateManeger& manager, camera& cam, std::shared_ptr<logic::world> wereld, const float& deltaTime) override;
    };

    class VictoryState : public state {
    public:
        VictoryState() = default;
        void run(sf::RenderWindow& window, sf::Event& event, stateManeger& manager, camera& cam, std::shared_ptr<logic::world> wereld, const float& deltaTime) override;
    };

} // view

#endif //PACKMAN_STATE_H