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

void Move(vector<string> & lines, int moveI, int moveJ)
{
  for (size_t n = 0; n < lines.size(); n++)
  {
    for (int i = 0; i < lines.size(); i++)
    {
      for (int j = 0; j < lines[0].size(); j++)
      {
        if (i + moveI < 0 || i + moveI >= lines.size() || j + moveJ < 0 ||
            j + moveJ >= lines[i].size())
        {
          continue;
        }

        if (lines[i][j] == 'O' && lines[i + moveI][j + moveJ] == '.')
        {
          lines[i + moveI][j + moveJ] = 'O';
          lines[i][j]                 = '.';
        }
      }
    }
  }
}

long long RoundOneCicle(vector<string> & lines)
{
  Move(lines, -1, 0);
  Move(lines, 0, -1);
  Move(lines, 1, 0);
  Move(lines, 0, 1);

  long long load = 0;
  for (size_t i = 0; i < lines.size(); i++)
  {
    for (size_t j = 0; j < lines[0].size(); j++)
    {
      if (lines[i][j] == 'O')
      {
        load += (lines.size() - i);
      }
    }
  }

  return load;
}

int main()
{
  ifstream in("..\\src\\_input.in");
  ofstream out("..\\src\\_output.out");

  FStreamReader reader(in);
  auto          lines = reader.ReadLines();

  for (int cicle = 1; cicle < 200; cicle++)
  {
    out << std::setfill('0') << std::setw(3) << cicle << " " << RoundOneCicle(lines) << endl;
  }

  // 100 -> 90176
  // 1000000000 - 100 = 999999900 % 18

  return 0;
}
