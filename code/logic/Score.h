//
// Created by niels_hertoghs on 11/20/25.
//

#ifndef PACKMAN_SCORE_H
#define PACKMAN_SCORE_H
#include "Observer.h"
#include "../view/ScoreView.h"
#include <memory>

#include "Observer.h"

// Forward declarations
namespace view {
class stateManeger;
class ScoreView;
}


namespace logic {

/**
 * @class Score
 * @brief Klasse die de score, levens en level bijhoudt.
 */
class Score : public Observer<scoreNotifications> {
    int score;     /// de huidige score van de speler.
    int livesLeft; /// Het aantal levens dat de speler nog over heeft.
    int level;     /// Het huidige level van de speler.
    view::stateManeger& manager;
    std::vector<std::shared_ptr<Observer<scoreViewNotifications>>> observers;
    //TODO: maak een methode in maneger, of laat ergens anders oproepen
    /// Reference naar de state manager, om states te kunnen veranderen bij game over of level up.
    ///
    void notifyObservers(scoreViewTypes notification) const;

public:
    void notify(const scoreNotifications& message) override;

    /**
     * @brief Constructor voor de score.
     * @param manager Reference naar de state manager, om states te kunnen veranderen bij game over of level up.
     */
    explicit Score(view::stateManeger& manager);

    // getters
    /**
     * @return De huidige score van de speler.
     */
    [[nodiscard]] int getScore() const;

    /**
     * @return Het aantal levens dat de speler nog over heeft.
     */
    [[nodiscard]] int getLivesLeft() const;

    /**
     * @return Het huidige level van de speler.
     */
    [[nodiscard]] int getLevel() const;

    void subscribe(std::shared_ptr<Observer<scoreViewNotifications>>);

    /**
     * @brief Default destructor.
     */
    ~Score() override = default;
};
} // logic

#endif //PACKMAN_SCORE_H
