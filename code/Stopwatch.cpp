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
        changedSprite.clear();
    }
    if (changedSprite.find(id) == changedSprite.end()) {
        changedSprite.insert(id);
        return true;
    }

    return false;
}

void Stopwatch::reset() {
    lastTime = clock::now();
    deltaTime = 0.0f;
    lastTimeEaten = clock::now();
    lastChangedSprite = clock::now();
    changedSprite.clear();
    startTime = clock::now();
}

bool Stopwatch::canStartAfter5Sec() const {
    auto currentTime = clock::now();
    std::chrono::duration<float> elapsed = currentTime - startTime;
    return elapsed.count() >= 5.0f;
}

bool Stopwatch::canStartAfter10Sec() const {
    auto currentTime = clock::now();
    std::chrono::duration<float> elapsed = currentTime - startTime;
    return elapsed.count() >= 10.0f;
}
