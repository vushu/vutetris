#include "bismuth/iomanager.hpp"
#include "bismuth/logging.hpp"
#include <bismuth/utils/counter.hpp>
using namespace bi::utils;

void Counter::updateDecrement() {
    counting(false);
}

void Counter::updateIncrement() {
    counting(true);
}

void Counter::start() {
    startCount = true;
}

void Counter::stop() {
    startCount = false;
}

void Counter::counting(bool increment) {
    if (!startCount) {
        return;
    }
    accumulatedTime += ioManager().getDeltaTime();
    if (accumulatedTime > interval){
        accumulatedTime = 0;
        counter += (increment ? 1 : -1);
        countdownCallback(counter);
    }
}

void Counter::onCount(CountdownCallback callback) {
    this->countdownCallback = callback;
}

int Counter::getCount() {
    return counter;
}

void Counter::setCount(int count) {
    counter = count;
}

void Counter::resetCount() {
    counter = initialCount;
}
