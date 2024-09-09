#include "JohnConway.h"

// Reference: https://playgameoflife.com/info
void JohnConway::Step(World& world) {
  // todo: implement
  for(int i = 0; i < world.SideSize(); i++) {
    for(int j = 0; j < world.SideSize(); j++) {
      Point2D p = Point2D(i,j);
      int neighbors = CountNeighbors(world,p);
      //if point is live
      if(world.Get(p)) {
        //If point has fewer than 2 live neighbors, it dies
        if(neighbors < 2) {
          world.SetCurrent(p,false);
        }
        //If point has more than 3 live neighbors, it dies
        else if(neighbors > 3) {
          world.SetCurrent(p,false);
        }
      }
      //if point is dead
      else {
        //If point has exactly 3 live neighbors, it comes to life
        if(neighbors == 3) {
          world.SetCurrent(p,true);
        }
      }
    }
  }
}

int JohnConway::CountNeighbors(World& world, Point2D point) {
  int neighbors = 0;
  for(int i = -1; i <= 1; i++) {
    for(int j = -1; j <= 1; j++) {
      Point2D neighbor = point + Point2D(i,j);
      if(i == 0 && j == 0) {
        continue;
      }
      neighbors += world.Get(neighbor);
    }
  }

  return neighbors;
}
