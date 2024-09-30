#include "../World.h"
#include "Random.h"
#include "RecursiveBacktrackerExample.h"
#include <climits>
bool RecursiveBacktrackerExample::Step(World* w) {
    //Checks if this is the first point of the world
  if (stack.empty() && visited.empty()) {
    stack.push_back(randomStartPoint(w));
  }

  if (!stack.empty()) {

    Point2D point = stack.back();
    std::vector<Point2D> list = getVisitables(w, point);
    Node node = w->GetNode(point);

    if (!list.empty()) {
      w->SetNodeColor(point, Color::Red);

      //Use random number to get next point
      Point2D next = list[getRandomNumber() % list.size()];
      stack.push_back(next);

      Point2D direction = next - point;

      //breaks down walls depending on where the next movement goes
      if (direction.y == -1) {
        node.SetNorth(false);
      } else if (direction.y == 1) {
        node.SetSouth(false);
      } else if (direction.x == -1) {
        node.SetWest(false);
      } else if (direction.x == 1) {
        node.SetEast(false);
      }
      //Updates node data in the worldspace
      w->SetNode(point, node);
    }
    else {
        //If there are no neighbors, mark point as finished
      Point2D point = stack.back();
      w->SetNodeColor(point, Color::Black);
      stack.pop_back();
    }

  }

  return !stack.empty();
}

void RecursiveBacktrackerExample::Clear(World* world) {
  visited.clear();
  stack.clear();
  auto sideOver2 = world->GetSize() / 2;

  for (int i = -sideOver2; i <= sideOver2; i++) {
    for (int j = -sideOver2; j <= sideOver2; j++) {
      visited[i][j] = false;
    }
  }
}

Point2D RecursiveBacktrackerExample::randomStartPoint(World* world) {
  auto sideOver2 = world->GetSize() / 2;

  for (int y = -sideOver2; y <= sideOver2; y++)
    for (int x = -sideOver2; x <= sideOver2; x++)
      if (!visited[y][x]) return {x, y};
  return {INT_MAX, INT_MAX};
}

int RecursiveBacktrackerExample::getRandomNumber() {
  static int randomIndex = 0;
  const int randomInts[100]
      = {72, 99, 56, 34, 43, 62, 31, 4,  70, 22, 6,  65, 96, 71, 29, 9,  98, 41, 90, 7,  30, 3,  97, 49, 63, 88, 47, 82, 91, 54, 74, 2,  86, 14,
         58, 35, 89, 11, 10, 60, 28, 21, 52, 50, 55, 69, 76, 94, 23, 66, 15, 57, 44, 18, 67, 5,  24, 33, 77, 53, 51, 59, 20, 42, 80, 61, 1,  0,
         38, 64, 45, 92, 46, 79, 93, 95, 37, 40, 83, 13, 12, 78, 75, 73, 84, 81, 8,  32, 27, 19, 87, 85, 16, 25, 17, 68, 26, 39, 48, 36};

  //Loops index at end of array
  if (randomIndex >= 100) {
    randomIndex = 0;
  }
  return randomInts[randomIndex++];
}

std::vector<Point2D> RecursiveBacktrackerExample::getVisitables(World* w, const Point2D& p) {
  auto sideOver2 = w->GetSize() / 2;
  std::vector<Point2D> visitables;

  //Get the world node at point p
  Node basic = w->GetNode(p);
  //Check all 4 points if they are in stack or visited, then they are not visitable
  //Check north point
  if (p.Up().y >= -sideOver2 && w->GetNodeColor(p.Up()) != Color::Black)
  {
    visitables.push_back(p.Up());
  }
  //Check Right point
  if (p.Right().x < sideOver2 && w->GetNodeColor(p.Right()) != Color::Black)
  {
    visitables.push_back(p.Right());
  }
  //Check Down point
  if (p.Down().y < sideOver2 && w->GetNodeColor(p.Down()) != Color::Black)
  {
    visitables.push_back(p.Down());
  }
  //Check Left point
  if (p.Left().x >= -sideOver2 && w->GetNodeColor(p.Left()) != Color::Black)
  {
    visitables.push_back(p.Left());
  }


  return visitables;
}
