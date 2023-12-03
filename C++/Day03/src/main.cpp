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

struct Number
{
  int                mNumber{};
  vector<AOC::Point> mPoints;
};

int main()
{
  ifstream in("..\\src\\_input.in");
  ofstream out("..\\src\\_output.out");

  FStreamReader  reader(in);
  vector<string> v = reader.ReadLines();

  vector<Number> numbers;

  for (int i = 0; i < v.size(); i++)
  {
    Number currentNumber;

    for (int j = 0; j < v[0].size(); j++)
    {
      AOC::Point currentPoint{ i, j };

      if ('0' <= v[i][j] && v[i][j] <= '9')
      {
        currentNumber.mNumber = currentNumber.mNumber * 10 + (v[i][j] - '0');
        currentNumber.mPoints.push_back(currentPoint);
      }
      else if (currentNumber.mPoints.size())
      {
        numbers.push_back(currentNumber);
        currentNumber = {};
      }
    }

    if (currentNumber.mPoints.size())
    {
      numbers.push_back(currentNumber);
    }
  }

  int sum = 0;
  for (auto number : numbers)
  {
    bool hasSymbols = false;

    for (const auto & point : number.mPoints)
    {
      for (const auto & neighbour : point.GetAll2DNeighbours())
      {
        if (!neighbour.IsInBoundary({ 0, 0 },
                                    { (long long)v.size() - 1, (long long)v[0].size() - 1 }))
          continue;

        auto neighbourSymbol = v[neighbour.x][neighbour.y];
        if (neighbourSymbol != '.' && !('0' <= neighbourSymbol && neighbourSymbol <= '9'))
        {
          hasSymbols = true;
        }
      }
    }

    if (hasSymbols)
      sum += number.mNumber;
  }

  cout << sum << endl;

  vector<AOC::Point> candidateGears;

  for (int i = 0; i < v.size(); i++)
  {
    for (int j = 0; j < v[0].size(); j++)
    {
      AOC::Point currentPoint{ i, j };
      if (v[i][j] == '*')
      {
        candidateGears.push_back(currentPoint);
      }
    }
  }

  long long sum2 = 0;
  for (const auto & candidateGear : candidateGears)
  {
    set<int> adjiacents;

    for (const auto & candidateGearNeigbour : candidateGear.GetAll2DNeighbours())
    {
      for (const auto & number : numbers)
      {
        for (const auto & numberPoint : number.mPoints)
        {
          if (numberPoint == candidateGearNeigbour)
            adjiacents.insert(number.mNumber);
        }
      }
    }

    if (adjiacents.size() == 2)
    {
      sum2 += *adjiacents.begin() * *(next(adjiacents.begin()));
    }
  }

  cout << sum2;

  return 0;
}
