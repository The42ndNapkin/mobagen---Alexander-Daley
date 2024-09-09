#include "CohesionRule.h"
#include "../gameobjects/Boid.h"

Vector2f CohesionRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  Vector2f cohesionForce;
  Vector2f position = boid->getPosition();
  int neighbors = 0;
  Vector2f CoM = Vector2f(0,0);

  //Iterates over the neighborhood to get the location of the center of mass
  for(Boid* b : neighborhood) {
    if(b->getPosition() == position) {
      continue;
    }

    CoM += b->getPosition();
    neighbors++;
  }

  // Average out to find center of mass
  if(neighbors != 0) {
    CoM /= neighbors;
  }else {
      //In case there's no nearby boids
    return(Vector2f(0,0));
  }

  //Finishes the calculations for the cohesion formula, gets a cohesion position away from the boid and returns a normalized vector in that direction
  Vector2f cohesionPos = CoM - position;

  cohesionForce = cohesionPos/boid->getDetectionRadius();

  cohesionForce = cohesionForce.normalized();

  return cohesionForce;
}