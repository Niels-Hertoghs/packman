//
// Created by niels on 11/6/25.
//

#ifndef PACKMAN_COLLECTABLE_H
#define PACKMAN_COLLECTABLE_H
#include "entity.h"
#include "../../render/collectableView.h"


namespace render {
     class Render;
}

namespace logic {

     /**
      * @class collectable
      * @brief Een abstracte klasse voor collectables.
      */
     class collectable : public entity {
     private:
          int points; /// Hoeveel punten er bij de score worden toegevoegd als het object na 1 seconde wordt opgegeten.
     public:
          // constructor
          collectable(double x, double y,int points);


          // methods
          int getPoints() const;
          void setPoints(int newPoints);
     };

     /**
      * @class coin
      * @brief Een concrete klasse voor de coins.
      */
     class coin : public collectable {
     private:
          std::shared_ptr<view::coinView> coinObserver;

     public:
          coin(double x, double y, int points);
          void coinSubscribe(std::shared_ptr<view::coinView> coinObserver);

          void collected() const;
     };

     class fruit : public collectable {
     private:
          std::shared_ptr<view::fruitView> fruitObserver;

     public:
          fruit(double x, double y,int points);
          void fruitSubscribe(std::shared_ptr<view::fruitView> fruitObserver);
          void collected() const;

     };
}
#endif //PACKMAN_COLLECTABLE_H