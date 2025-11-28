//
// Created by niels_hertoghs on 11/8/25.
//

#include "Stopwatch.h"
namespace logic {
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

    void Stopwatch::startFearMode() {
        _startFearMode = clock::now();
    }

    bool Stopwatch::isFearDone(int level) {
        auto currentTime = clock::now();
        // Met deze formule duurt de fearmode op level 1, 10 seconden
        // hoe hoger het level hoe korter de fearMode, het is een hyperbolische daling, zodat het nooit 0 is of negatief
        // level 2 = 8.3 sec, ... level 10 = 3.6 ,...
        float lengthOfFear = 10.f / ( 1.f + ((0.2f) * static_cast<float>(level - 1)));
        std::chrono::duration<float> elapsed = currentTime - _startFearMode;
        if (elapsed.count() > lengthOfFear) {
            return true;
        }
        return false;
    }


}