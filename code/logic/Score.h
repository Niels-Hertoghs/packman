//
// Created by niels_hertoghs on 11/20/25.
//

#ifndef PACKMAN_SCORE_H
#define PACKMAN_SCORE_H
#include "Observer.h"
#include "notifications.h"
#include <memory>
#include <vector>


namespace logic {

/**
 * @class Score
 * @brief Score observer die de score, levens en level bijhoudt.
 */
class Score : public Observer<scoreNotifications> {
    int score;     /// de huidige score van de speler.
    int livesLeft; /// Het aantal levens dat de speler nog over heeft.
    int level;     /// Het huidige level van de speler.
    std::vector<std::shared_ptr<Observer<scoreViewNotifications>>> observers;
    /// Vector met alle observers van de Score.

    /**
     * @brief Notified alle observers van Score.
     * @param notification De notificatie die gecommuniceerd moet worden.
     */
    void notifyObservers(scoreViewTypes notification) const;

public:
    /**
     * @brief Constructor voor de score.
     */
    Score();

    // Override van pure virtual, kijk declaratie methode.
    void notify(const scoreNotifications& message) override;


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

    /**
     * @brief "Subscribed" de observer aan de Score.
     */
    void subscribe(std::shared_ptr<Observer<scoreViewNotifications>>);

    /**
     * @brief Reset de hele Score.
     */
    void reset();

    /**
     * @brief Default destructor.
     */
    ~Score() override = default;
};
} // logic

#endif //PACKMAN_SCORE_H
