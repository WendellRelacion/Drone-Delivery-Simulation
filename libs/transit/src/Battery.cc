#include "Battery.h"

Battery::Battery(JsonObject& obj) : IEntity(obj) {}
Battery::~Battery() {}
void Battery::update(double dt) {}

double Battery::getBattery() {
    return batteryLevel;
}
void Battery::setBattery(double newBattery) {
    batteryLevel = newBattery;
}

bool Battery::getIsCharging() {
    return isCharging;
}
void Battery::setIsCharging(bool newIsCharging) {
    isCharging = newIsCharging;
}
