//
// Created by niels on 11/6/25.
//

#include "collectable.h"

#include <utility>


namespace logic {
    /// ---------------------------------------------------------------------------------------------------------------
    /// @class collectable
    /// ---------------------------------------------------------------------------------------------------------------

    collectable::collectable(double x, double y,int Points) : entity(x,y ), points(Points) {}

    int collectable::getPoints() const {
        return points;
    }

    void collectable::setPoints(int newPoints) {
        points = newPoints;
    }

    void collectable::collectableSubscribe(std::shared_ptr<view::collectableView> _collectableObserver) {
        collectableObserver = std::move(_collectableObserver);
    }

    void collectable::subscribeScore(const std::shared_ptr<Score>& Score) {
        score = Score;
    }



    /// ---------------------------------------------------------------------------------------------------------------
    /// @class coin
    /// ---------------------------------------------------------------------------------------------------------------

    coin::coin(double x, double y,int points) : collectable(x,y,points){}


    bool coin::collected() const {
        score->coinEaten(getPoints());
        collectableObserver->notify(notifications::COLLECTED);
        return false;
    }

    bool coin::isFruit() const {
        return false;
    }


    /// ---------------------------------------------------------------------------------------------------------------
    /// @class fruit
    /// ---------------------------------------------------------------------------------------------------------------

    fruit::fruit(double x, double y, int points) : collectable(
        x, y, points) {
    }


    bool fruit::collected() const {
        score->coinEaten(getPoints());
        collectableObserver->notify(notifications::COLLECTED);
        return true;
    }

    bool fruit::isFruit() const {
        return true;
    }

}
