//
// Created by niels on 10/30/25.
//

#ifndef PACKMAN_STATEMANEGER_H
#define PACKMAN_STATEMANEGER_H
#include <iostream>
#include <memory>
#include <stack>
#include <vector>
#include "../camera.h"
#include "../../logic/Stopwatch.h"
#include "../../view/worldView.h"
#include "state.h"

// Forward declarations
namespace logic {
    class world;
}

namespace view {
// Forward declarations
    class state;

    /**
     * @class stateManeger
     * @brief Manages the different states of the game (menu, level, pause, etc.).
     */
    class stateManeger {
        std::stack<std::unique_ptr<view::state>> stack; /// Stack met de verschillende staten.
    public:
        /**
         * @brief Constructor
         */
        stateManeger();

        /**
         * @brief Pusht een nieuwe staat op de stack.
         * @param newState De nieuwe staat, die gepushed moet worden.
         */
        void pushState(std::unique_ptr<view::state> newState);

        /**
         * @brief Vervangt de huidige staat met een nieuwe staat.
         * @param newState De nieuwe staat, die gepushed moet worden.
         */
        void pushStateAndDelete(std::unique_ptr<view::state> newState);

        /**
         * @brief Popt een staat van de stack, zodat het terug gaat naar de vorige staat.
         */
        void prevState();

        /**
         * @brief Popt twee staten van de stack, zodat het terug gaat naar de staat daarvoor.
         */
        void pop2State();

        void startVictory();

        /**
         * @return Unique pointer naar de huidige staat.
         */
        std::unique_ptr<view::state> getCurrentState();

        /**
         * @brief Laat de bovenste staat op de stack draaien/ updaten.
         * @param window De window waar alles op getekend moet worden.
         * @param event Als eventuate evenementen te verwerken.
         * @param cam Camera voor het omzetten van wereld naar pixel coordinaten.
         * @param wereld Pointer naar de wereld logica, om het eventueel te laten lopen.
         * @param deltaTime Het verschil in tijd sinds de laatste update.
         */
        void runTop(sf::RenderWindow& window, sf::Event& event, view::camera& cam, std::shared_ptr<logic::world> wereld, const float& deltaTime);
    };
}



#endif //PACKMAN_STATEMANEGER_H