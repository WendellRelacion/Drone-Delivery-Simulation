#include "PathStrategy.h"

PathStrategy::PathStrategy(std::vector<std::vector<float>> p)
  : path(p), index(0) {}

void PathStrategy::move(IEntity* entity, double dt) {
  if (isCompleted())
    return;

  Vector3 vi(path[index][0], path[index][1], path[index][2]);
  Vector3 dir = (vi - entity->getPosition()).unit();

  Vector3 posOffset = dir * entity->getSpeed() * dt;
  Vector3 newPosition = entity->getPosition() + posOffset;
  double dist = entity->getPosition().dist(newPosition);
  entity->setDistanceTraveled(entity->getDistanceTraveled() + dist);
  entity->setPosition(newPosition);
  entity->setDirection(dir);

  if (entity->getPosition().dist(vi) < 4)
    index++;
}

bool PathStrategy::isCompleted() {
  return index >= path.size();
}
