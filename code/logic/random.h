//
// Created by niels-hertoghs on 11/18/25.
//

#ifndef PACKMAN_RANDOM_H
#define PACKMAN_RANDOM_H
#include <memory>
#include <random>

namespace logic {
/**
 * @class random
 * @brief Singleton klasse voor het genereren van random getallen.
 */
class random {
    /**
     * @brief Default constructor (private) , initialiseerd de random number generator.
     */
    random();

    inline static std::shared_ptr<random> _instance;
    /// Statische pointer naar de enige instantie van de random klasse.

    std::mt19937 mt; /// Mersenne Twister, random number generator.
public:
    /**
     * @return De enige instantie van de random klasse (pointer).
     */
    static std::shared_ptr<random> getInstance();

    // Verwijder copy constructor en assignment operator, om singleton behouden
    random(const random&) = delete;

    random& operator=(const random&) = delete;

    /**
     * @brief Genereer een random getal tussen min (inclusief) en max (exclusief).
     * @param min Het minimum getal.
     * @param max Het maximum getal.
     * @return Een random getal tussen min en max.
     */
    [[nodiscard]] int getNumber(int min, int max);

    /**
     * @brief Default destructor.
     */
    ~random() = default;
};
} // logic

#endif //PACKMAN_RANDOM_H
