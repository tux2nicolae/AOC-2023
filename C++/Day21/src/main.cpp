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

  AOC::Point initialPoint;
  for (long long i = 0; i < lines.size(); i++)
  {
    for (long long j = 0; j < lines[i].size(); j++)
    {
      if (lines[i][j] == 'S')
      {
        initialPoint = AOC::Point{ i, j };
        lines[i][j]  = '.';
      }
    }
  }

  // should be odd
  auto repetitions = 101;

  vector<string> bigLines = lines;
  for (size_t i = 0; i < bigLines.size(); i++)
  {
    auto & line = bigLines[i];

    for (size_t j = 0; j < repetitions - 1; j++)
    {
      line += lines[i];
    }
  }

  for (size_t i = 0; i < repetitions - 1; i++)
  {
    for (size_t j = 0; j < lines.size(); j++)
    {
      bigLines.push_back(bigLines[j]);
    }
  }

  /* for (auto line : bigLines)
   {
     out << line << endl;
   }*/

  initialPoint.x += lines.size() * (repetitions / 2);
  initialPoint.y += lines[0].size() * (repetitions / 2);

  set<AOC::Point> initialPoints;
  initialPoints.insert(initialPoint);

  vector<long long> v;

  // out << endl;
  long long previous = 0;
  for (size_t i = 0; i < 500; i++)
  {
    set<AOC::Point> nextPoints;

    for (const auto & point : initialPoints)
    {
      for (const auto & neighbour : point.GetDirect2DNeighbours())
      {
        if (!neighbour.IsInBoundary(
              { 0, 0 }, { (long long)bigLines.size() - 1, (long long)bigLines[0].size() - 1 }))
          continue;

        if (bigLines[neighbour.x][neighbour.y] == '.')
          nextPoints.insert(neighbour);
      }
    }

    initialPoints = nextPoints;

    v.push_back(initialPoints.size());

    out << initialPoints.size() << " : " << initialPoints.size() - previous << endl;
    previous = initialPoints.size();
  }

  vector<long long> constants;
  for (size_t i = 300; i < 500; i++)
  {
    auto x = v[i - 1] - v[i - lines.size() - 1] + v[i - lines.size()];
    constants.push_back(v[i] - x);

    // cout << v[i] - x << " ";
  }

  //rotate(constants.begin(), constants.begin(), constants.end());

  v.resize(26600000);
  for (size_t i = 300; i < 26501365; i++)
  {
    auto x = v[i - 1] - v[i - lines.size() - 1] + v[i - lines.size()] + constants[(i - 2) % lines.size()];
    out << x << endl;

    if (i < 500)
    {
      assert(v[i] == x);
    }

    v[i] = x;
  }

  cout << endl << v.back() << endl;

  //// computed
  // if (i >= 186)
  //{
  //   auto x1 = v[i - 1] - v[i - lines.size() - 1] + (v[i - lines.size()] + 11);
  //   auto x2 = v[i - 1] - v[i - lines.size() - 1] + (v[i - lines.size()] + 14);
  //   auto x3 = v[i - 1] - v[i - lines.size() - 1] + (v[i - lines.size()] + 16);
  //   auto x4 = v[i - 1] - v[i - lines.size() - 1] + (v[i - lines.size()] + 14);
  //   auto x5 = v[i - 1] - v[i - lines.size() - 1] + (v[i - lines.size()] + 18);
  //   auto x6 = v[i - 1] - v[i - lines.size() - 1] + (v[i - lines.size()] + 9);

  //  cout << i << " : " << (x1 == v.back()) << " " << (x2 == v.back()) << " " << (x3 == v.back())
  //        << " " << (x4 == v.back()) << " " << (x5 == v.back()) << endl;
  //  // assert(x == v.back());
  //}

  // v.resize(5000);
  // for (size_t i = 165; i < 5000; i++)
  //{
  //   v[i] = v[i - lines.size()] + v[i - 1] - v[i - lines.size() - 1] + 14;
  //   out << v[i] << endl;
  // }

  return 0;
}
