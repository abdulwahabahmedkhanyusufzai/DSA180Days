#include <string>
#include <vector>

using namespace std;

class Robot {
private:
  int w, h, pos, perimeter;
  bool moved;

public:
  Robot(int width, int height) {
    w = width;
    h = height;
    pos = 0; // Total distance traveled around the perimeter
    perimeter = 2 * (w + h - 2);
    moved = false; // To track if we've ever moved (affects direction at 0,0)
  }

  void step(int num) {
    moved = true;
    pos = (pos + num) % perimeter;
  }

  vector<int> getPos() {
    // Map the single 'pos' value back to (x, y) coordinates
    if (pos <= w - 1)
      return {pos, 0}; // Bottom edge
    if (pos <= (w - 1) + (h - 1))
      return {w - 1, pos - (w - 1)}; // Right edge
    if (pos <= 2 * (w - 1) + (h - 1))
      return {(w - 1) - (pos - (w - 1) - (h - 1)), h - 1}; // Top edge

    return {0, (w - 1) * 2 + (h - 1) * 2 - pos}; // Left edge
  }

  string getDir() {
    // If the robot has never moved, it's still facing the default East
    if (pos == 0 && !moved)
      return "East";

    // If it has moved and is at 0, it finished a lap and 'hit' the wall
    if (pos == 0 && moved)
      return "South";

    if (pos >= 1 && pos <= w - 1)
      return "East";
    if (pos <= (w - 1) + (h - 1))
      return "North";
    if (pos <= 2 * (w - 1) + (h - 1))
      return "West";

    return "South";
  }
};