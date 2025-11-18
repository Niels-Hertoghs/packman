//
// Created by niels-hertoghs on 11/18/25.
//

#ifndef PACKMAN_RANDOM_H
#define PACKMAN_RANDOM_H
#include <memory>
#include <random>

namespace logic {
    class random {
    private:
        random();
        inline static std::shared_ptr<random> _instance;

        std::mt19937 mt; // Mersenne Twister
    public:
        static std::shared_ptr<random> getInstance();

        // Verwijder copy constructor en assignment operator, om singleton behouden
        random(const random&) = delete;
        random& operator=(const random&) = delete;

        int getNumber(int min, int max);

        ~random() = default;
    };
} // logic

#endif //PACKMAN_RANDOM_H