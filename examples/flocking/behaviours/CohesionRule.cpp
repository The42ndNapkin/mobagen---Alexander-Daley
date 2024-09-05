#include "CohesionRule.h"
#include "../gameobjects/Boid.h"

Vector2f CohesionRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  Vector2f cohesionForce;

  // todo: add your code here to make a force towards the center of mass
  // hint: iterate over the neighborhood
  Vector2f position = boid->getPosition();
  int neighbors = 0;
  Vector2f CoM = Vector2f(0,0);

  for(Boid* b : neighborhood) {
    if(b->getPosition() == position) {
      continue;
    }

    CoM += b->getPosition();
    neighbors++;
  }

  // find center of mass
  if(neighbors != 0) {
    CoM /= neighbors;
  }else {
    return(Vector2f(0,0));
  }

  Vector2f cohesionPos = CoM - position;

  cohesionForce = cohesionPos/boid->getDetectionRadius();

  cohesionForce = cohesionForce.normalized();



  return cohesionForce;
}