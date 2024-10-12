#ifndef AGENT_H
#define AGENT_H
#include "math/Point2D.h"
#include <vector>
#include <unordered_set>
#include <unordered_map>

class World;

struct AStarNode {
  Point2D position;
  int heuristic;
  int accCost;
  //Overload < operator
  bool operator<(const AStarNode& other) const {
	  //looking for the smallest cost
    return accCost + heuristic > other.accCost + other.heuristic;
  }

  int calcHeuristic(Point2D p, int sideSizeOver2){
    if (p.x - p.y > 0 && p.x + p.y > 0) {  // this is just for the right
      return sideSizeOver2 - p.x;
    }
    else if (p.x - p.y < 0 && p.x + p.y < 0) {  // this is just for the left
      return p.x - sideSizeOver2;
    }
    else if (p.x - p.y < 0 && p.x + p.y > 0) {  // this is just for the top
      return p.y - sideSizeOver2;
    } 
    else {  // this is just for the bottom
      return sideSizeOver2 - p.y;
    }
  };
};

class Agent {
public:
  explicit Agent() = default;

  virtual Point2D Move(World*) = 0;
  Point2D nearestExit(World* w, Point2D p);
  std::vector<Point2D> generatePath(World* w);
  std::vector<Point2D> getVisitableNeighbors(World* w, Point2D p, std::unordered_map<Point2D, bool> visited, std::unordered_set<Point2D> frontierSet);
};

#endif  // AGENT_H
