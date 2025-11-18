//
// Created by niels_hertoghs on 11/8/25.
//

#include "Stopwatch.h"

Stopwatch::Stopwatch() : lastTime(clock::now()), deltaTime(0.0f), lastTimeEaten(clock::now()) {}

std::shared_ptr<Stopwatch> Stopwatch::getInstance() {
    if (!_instance) {
        _instance = std::shared_ptr<Stopwatch>(new Stopwatch());
    }
    return _instance;
}


void Stopwatch::tick() {
    auto currentTime = clock::now();
    std::chrono::duration<float> elapsed = currentTime - lastTime;
    deltaTime = elapsed.count();
    lastTime = currentTime;
}

float Stopwatch::getDeltaTime() const {
    return deltaTime;
}

float Stopwatch::eatCollectable() {
    auto currentEaten = clock::now();
    std::chrono::duration<float> elapsed = currentEaten - lastTimeEaten;
    lastTimeEaten = currentEaten;
    return elapsed.count();
}

bool Stopwatch::changeSprite(int id) {
    auto currentTime = clock::now();
    std::chrono::duration<float> elapsed = currentTime - lastChangedSprite;
    if (elapsed.count() > 0.1f) {
        lastChangedSprite = currentTime;
        changed.clear();
    }
    if (changed.find(id) == changed.end()) {
        changed.insert(id);
        return true;
    }

    return false;
}