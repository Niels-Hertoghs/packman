//
// Created by niels_hertoghs on 11/20/25.
//

#ifndef PACKMAN_SCOREVIEW_H
#define PACKMAN_SCOREVIEW_H
#include "../observer.h"
#include "../logic/entities/Score.h"

namespace view {
    class ScoreView : public Observer {
    private:
        sf::Font font;
        std::weak_ptr<logic::Score> scoreModel;
        sf::Text scoreText;
        sf::Text levelText;
        sf::Text lifesText;
    public:
        ScoreView(sf::RenderWindow& window,camera& cam,std::shared_ptr<logic::Score>& Score);
        void notify(enum notifications message) override;
        void draw() override;

    };
} // view

#endif //PACKMAN_SCOREVIEW_H