#include "Package.h"

#include "DataCollectorSingleton.h"
#include "Robot.h"

Package::Package(JsonObject& obj)
    : IEntity(obj), deltaTime(0.0), tickCount(0) {}

Vector3 Package::getDestination() const { return destination; }

std::string Package::getStrategyName() const { return strategyName; }

void Package::setStrategyName(std::string strategyName_) {
  strategyName = strategyName_;
}

void Package::update(double dt) {
  deltaTime += dt;  // Update deltaTime
  tickCount++;      // Increment tickCount
}

void Package::initDelivery(Robot* owner) {
  this->owner = owner;
  owner->requestedDelivery = false;
  requiresDelivery = false;
  destination = owner->getPosition();
}

void Package::handOff() {
  if (owner) {
    owner->receive(this);
  }
  DataCollectorSingleton* instance = DataCollectorSingleton::getInstance();
  const JsonObject& details = this->getDetails();
  double distanceTraveled = this->getDistanceTraveled();
  instance->logPackageData(details, deltaTime, distanceTraveled);
  instance->saveToCSV("Package-Data.csv");
  std::cout << "Delta Time for Package delivery: " << deltaTime << " seconds"
            << std::endl;
}

double Package::getDeltaTime() const { return deltaTime; }

int Package::getTickCount() const { return tickCount; }
