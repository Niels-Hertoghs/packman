//
// Created by niels_hertoghs on 11/8/25.
//

#include "Stopwatch.h"

Stopwatch::Stopwatch() : lastTime(clock::now()), deltaTime(0.0f) {}

void Stopwatch::tick() {
    auto currentTime = clock::now();
    std::chrono::duration<float> elapsed = currentTime - lastTime;
    deltaTime = elapsed.count();
    lastTime = currentTime;
}

float Stopwatch::getDeltaTime() const {
    return deltaTime;
}
