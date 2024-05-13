#define _USE_MATH_DEFINES
#include "RechargeStation.h"

#include <cmath>
#include <limits>

#include "SimulationModel.h"

RechargeStation::RechargeStation(JsonObject& obj) : IEntity(obj) {}

RechargeStation::~RechargeStation() {}

void RechargeStation::update(double dt) {}
