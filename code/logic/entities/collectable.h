//
// Created by niels on 11/6/25.
//

#ifndef PACKMAN_COLLECTABLE_H
#define PACKMAN_COLLECTABLE_H
#include "entity.h"
#include "Score.h"
#include "../../view/collectableView.h"



namespace logic {

     /**
      * @class collectable
      * @brief Een abstracte klasse voor collectables.
      */
     class collectable : public entity {
     private:
          int points; /// Hoeveel punten er bij de score worden toegevoegd als het object na 1 seconde wordt opgegeten.
     protected:
          std::shared_ptr<view::collectableView> collectableObserver;
          std::shared_ptr<Score> score; /// pointer naar de score observer
     public:
          // constructor
          collectable(double x, double y,int points);

          /**
           * @brief Laat de observer weten dat het gegeten is + of de movables in chasing mode moeten.
           * @return True als het een fruit gegeten heeft en in chasing mode moet gaan.
           */
          [[nodiscard]] virtual bool collected() const = 0;

          /**
           * @return Of de collectable en fruit is.
           */
          [[nodiscard]] virtual bool isFruit() const = 0;


          // methods
          [[nodiscard]] int getPoints() const;
          void setPoints(int newPoints);
          void collectableSubscribe(std::shared_ptr<view::collectableView> collectableObserver);
          void subscribeScore(const std::shared_ptr<Score>& score);

     };

     /**
      * @class coin
      * @brief Een concrete klasse voor de coins.
      */
     class coin : public collectable {
     private:
     public:
          coin(double x, double y, int points);

          /**
           * @brief Laat de observer weten dat het gegeten is + of de movables in chasing mode moeten.
           * @return True als het een fruit gegeten heeft en in chasing mode moet gaan.
           */
          [[nodiscard]] bool collected() const override;

          /**
          * @return Of de collectable en fruit is.
          */
          [[nodiscard]] bool isFruit() const override;
     };

     class fruit : public collectable {
     private:

     public:
          fruit(double x, double y,int points);


          /**
          * @brief Laat de observer weten dat het gegeten is + of de movables in chasing mode moeten.
          * @return True als het een fruit gegeten heeft en in chasing mode moet gaan.
          */
          [[nodiscard]] bool collected() const override;

          /**
          * @return Of de collectable en fruit is.
          */
          [[nodiscard]] bool isFruit() const override;

     };
}
#endif //PACKMAN_COLLECTABLE_H