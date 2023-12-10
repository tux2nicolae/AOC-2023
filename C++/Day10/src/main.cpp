/**
 * Advent of code 2023
 * @author : Nicolae Telechi
 */
#include <algorithm>
#include <assert.h>
#include <deque>
#include <fstream>
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

size_t ComputeCicleLength(const vector<string> & aMap, AOC::Point startingPosition)
{
  size_t maxLength = 0;

  stack<AOC::Point>     st;
  map<AOC::Point, bool> visited;

  st.push(startingPosition);
  visited[startingPosition] = true;

  while (!st.empty())
  {
    auto currentPoint = st.top();

    for (const auto & nextPoint : currentPoint.GetDirect2DNeighbours())
    {
      if (!nextPoint.IsInBoundary({ 0, 0 }, { (int)aMap[0].size() - 1, (int)aMap.size() - 1 }))
        continue;

      if (aMap[nextPoint.y][nextPoint.x] == '.')
        continue;

      bool isInCicle = false;
      char ch        = aMap[currentPoint.y][currentPoint.x];
      if (ch == 'S')
        ch = 'F';

      switch (ch)
      {
      case '-':
        isInCicle = nextPoint == currentPoint.GetRight() || nextPoint == currentPoint.GetLeft();
        break;
      case '|':
        isInCicle = nextPoint == currentPoint.GetTop() || nextPoint == currentPoint.GetBottom();
        break;
      case 'F':
        isInCicle = nextPoint == currentPoint.GetBottom() || nextPoint == currentPoint.GetRight();
        break;
      case '7':
        isInCicle = nextPoint == currentPoint.GetBottom() || nextPoint == currentPoint.GetLeft();
        break;
      case 'L':
        isInCicle = nextPoint == currentPoint.GetTop() || nextPoint == currentPoint.GetRight();
        break;
      case 'J':
        isInCicle = nextPoint == currentPoint.GetTop() || nextPoint == currentPoint.GetLeft();
        break;
      }

      if (!isInCicle)
        continue;

      if (nextPoint == startingPosition)
      {
        maxLength = max(maxLength, st.size());
        continue;
      }

      if (!visited[nextPoint])
      {
        st.push(nextPoint);
        visited[nextPoint] = true;
        break;
      }
    }

    if (st.top() == currentPoint)
      st.pop();
  }

  return maxLength;
}

int main()
{
  ifstream in("..\\src\\_input.in");
  ofstream out("..\\src\\_output.out");

  FStreamReader reader(in);
  auto          v = reader.ReadLines();

  AOC::Point startingPosition{};

  for (int i = 0; i < v.size(); i++)
  {
    for (int j = 0; j < v[i].size(); j++)
    {
      if (v[i][j] == 'S')
        startingPosition = { j, i };
    }
  }

  int lenght = ComputeCicleLength(v, startingPosition);

  cout << (lenght + 1) / 2;

  return 0;
}
