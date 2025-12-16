//
// Created by niels-hertoghs on 11/18/25.
//

#include "random.h"

namespace logic {
    random::random() : mt(std::random_device{}()) {
    }

    std::shared_ptr<random> random::getInstance() {
        if (!_instance) {
            _instance = std::shared_ptr < random > (new random());
        }
        return _instance;
    }

    int random::getNumber(const int min, const int max) {
        std::uniform_int_distribution<int> dist(min, max - 1);
        return dist(mt);
    }
} // logic