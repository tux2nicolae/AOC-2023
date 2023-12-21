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

int main()
{
  ifstream in("..\\src\\_input.in");
  ofstream out("..\\src\\_output.out");

  FStreamReader reader(in);
  auto          lines = reader.ReadLines();

  set<AOC::Point> initialPoints;
  for (long long i = 0; i < lines.size(); i++)
  {
    for (long long j = 0; j < lines[i].size(); j++)
    {
      if (lines[i][j] == 'S')
      {
        initialPoints.insert(AOC::Point{ i, j });
        lines[i][j] = '.';
      }
    }
  }

  for (size_t i = 0; i < 64; i++)
  {
    set<AOC::Point> nextPoints;

    for (const auto & point : initialPoints)
    {
      for (const auto & neighbour : point.GetDirect2DNeighbours())
      {
        if (!neighbour.IsInBoundary({ 0, 0 }, { (int)lines.size() - 1, (int)lines[0].size() - 1 }))
          continue;

        if (lines[neighbour.x][neighbour.y] == '.')
          nextPoints.insert(neighbour);
      }
    }

    initialPoints = nextPoints;
  }

  cout << initialPoints.size() << endl;

  return 0;
}
