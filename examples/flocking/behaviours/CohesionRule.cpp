#include "CohesionRule.h"
#include "../gameobjects/Boid.h"

Vector2f CohesionRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  Vector2f cohesionForce;

  // todo: add your code here to make a force towards the center of mass
  // hint: iterate over the neighborhood
  Vector2f position = boid->getPosition();
  int neighbors = 0;
  Vector2f CoM = boid->getPosition();

  for(Boid* b : neighborhood) {
    if(b->getPosition() == position) {
      continue;
    }
    CoM += b->getPosition();
    neighbors++;
  }

  // find center of mass
  CoM /= neighbors;
  Vector2f cohesionPos = Vector2f(CoM.x * position.x, CoM.y * position.y);
  cohesionForce = cohesionPos/boid->getDetectionRadius();

  cohesionForce = cohesionForce.normalized();
  if(cohesionForce.getMagnitude() > 0.2f) {
    cohesionForce*=0.2f;
  }
  return cohesionForce;
}