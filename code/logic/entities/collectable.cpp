//
// Created by niels on 11/6/25.
//

#include "collectable.h"


namespace logic {
    /// ---------------------------------------------------------------------------------------------------------------
    /// @class collectable
    /// ---------------------------------------------------------------------------------------------------------------
    ///
    collectable::collectable(double x, double y,int Points) : entity(x,y ), points(Points) {}

    int collectable::getPoints() const {
        return points;
    }

    void collectable::setPoints(int newPoints) {
        points = newPoints;
    }

    /// ---------------------------------------------------------------------------------------------------------------
    /// @class coin
    /// ---------------------------------------------------------------------------------------------------------------

    coin::coin(double x, double y,int points) : collectable(x,y,points){}


    void coin::coinSubscribe(std::shared_ptr<view::coinView> CoinObserver) {
        coinObserver = std::move(CoinObserver);
    }

    void coin::collected() const {
        coinObserver->notify(notifications::COLLECTED);
    }


    /// ---------------------------------------------------------------------------------------------------------------
    /// @class fruit
    /// ---------------------------------------------------------------------------------------------------------------

    fruit::fruit(double x, double y,int points) : collectable(x,y,points){}


    void fruit::fruitSubscribe(std::shared_ptr<view::fruitView> FruitObserver) {
        fruitObserver = std::move(FruitObserver);
    }

    void fruit::collected() const {
        fruitObserver->notify(notifications::COLLECTED);
    }


}
