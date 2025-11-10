//
// Created by niels_hertoghs on 11/8/25.
//

#include "Stopwatch.h"

Stopwatch::Stopwatch() : lastTime(clock::now()), deltaTime(0.0f), lastTimeEaten(clock::now()) {}

Stopwatch& Stopwatch::getInstance() {
    static Stopwatch instance;
    return instance;
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

