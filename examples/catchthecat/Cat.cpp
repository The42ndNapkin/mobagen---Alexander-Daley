#include "Cat.h"
#include "World.h"
#include <stdexcept>

Point2D Cat::Move(World* world) {
    //Move to last point on the path (since it's generated backwards)  Randomly move in 6 directions if no generated path
  std::vector<Point2D> path = generatePath(world);
  if (!path.empty())
  {
    return (path[path.size() - 1]);
  }

  auto rand = Random::Range(0, 5);
  auto pos = world->getCat();
  switch (rand) {
    case 0:
      return World::NE(pos);
    case 1:
      return World::NW(pos);
    case 2:
      return World::E(pos);
    case 3:
      return World::W(pos);
    case 4:
      return World::SW(pos);
    case 5:
      return World::SE(pos);
    default:
      throw "random out of range";
  }
}
