/**
 * Advent of code 2023
 * @author : Nicolae Telechi
 */
#include <algorithm>
#include <array>
#include <assert.h>
#include <deque>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <numeric>
#include <optional>
#include <queue>
#include <regex>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

#include "../../AOCLib/src/Algorithm.h"
#include "../../AOCLib/src/FStreamReader.h"
#include "../../AOCLib/src/FStreamWriter.h"
#include "../../AOCLib/src/Math.h"
#include "../../AOCLib/src/Parse.h"
#include "../../AOCLib/src/Point.h"
#include "../../AOCLib/src/Ship.h"
#include "../../AOCLib/src/Time.h"
#include "../../AOCLib/src/Util.h"

struct Brick
{
  AOC::Point from;
  AOC::Point to;

  int minZ() const { return min(from.z, to.z); }

  void fall()
  {
    from.z--;
    to.z--;
  }

  void rise()
  {
    from.z++;
    to.z++;
  }

  bool operator<(const Brick & other) { return minZ() < other.minZ(); }
};

bool Intersects(Brick & a, Brick & b)
{
  set<AOC::Point> pointsA;

  for (auto x = a.from.x; x <= a.to.x; x++)
  {
    for (auto y = a.from.y; y <= a.to.y; y++)
    {
      for (auto z = a.from.z; z <= a.to.z; z++)
      {
        pointsA.insert(AOC::Point{ x, y, z });
      }
    }
  }

  for (auto x = b.from.x; x <= b.to.x; x++)
  {
    for (auto y = b.from.y; y <= b.to.y; y++)
    {
      for (auto z = b.from.z; z <= b.to.z; z++)
      {
        if (pointsA.count(AOC::Point{ x, y, z }))
          return true;
      }
    }
  }

  return false;
}

int RunFall(vector<Brick> & bricks)
{
  int falls = 0;

  for (int i = 0; i < bricks.size(); i++)
  {
    auto & brick = bricks[i];

    bool falled = false;
    while (brick.minZ() > 1)
    {
      brick.fall();

      bool intersects = false;
      for (int j = i - 1; j >= 0; j--)
      {
        auto & with = bricks[j];
        if (Intersects(brick, with))
        {
          intersects = true;
          break;
        }
      }

      if (intersects)
      {
        brick.rise();
        break;
      }

      falled = true;
    }

    falls += falled;
  }

  return falls;
}

int main()
{
  ifstream in("..\\src\\_input.in");
  ofstream out("..\\src\\_output.out");

  FStreamReader reader(in);
  auto          lines = reader.ReadLines();

  vector<Brick> bricks;

  for (auto & line : lines)
  {
    auto matches = AOC::ExtractMatches(line, "(.*),(.*),(.*)~(.*),(.*),(.*)");
    assert(matches.size());

    AOC::Point from{ stoi(matches[0]), stoi(matches[1]), stoi(matches[2]) };
    AOC::Point to{ stoi(matches[3]), stoi(matches[4]), stoi(matches[5]) };

    bricks.push_back(Brick{ from, to });
  }

  std::sort(bricks.begin(), bricks.end());

  RunFall(bricks);

  int sum = 0;

  int disintegrated = 0;
  for (int i = 0; i < bricks.size(); i++)
  {
    auto nextBricks = bricks;
    nextBricks.erase(nextBricks.begin() + i);

    auto falls = RunFall(nextBricks);
    if (!falls)
      disintegrated++;

    sum += falls;
  }

  cout << disintegrated << endl;
  cout << sum << endl;

  return 0;
}
