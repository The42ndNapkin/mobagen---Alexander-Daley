#include "Catcher.h"
#include "World.h"

Point2D Catcher::Move(World* world) {
    //Get the first point on the generated path, random space if no path is generated
  std::vector<Point2D> path = generatePath(world);
  if (!path.empty()) {
    return (path[0]);
  }
  auto side = world->getWorldSideSize() / 2;
  for (;;) {
    Point2D p = {Random::Range(-side, side), Random::Range(-side, side)};
    auto cat = world->getCat();
    if (cat.x != p.x && cat.y != p.y && !world->getContent(p)) return p;
  }
}
