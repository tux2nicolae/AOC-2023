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

long long GetNextSequence(vector<int> sequence)
{
  int sumLast = sequence.back();

  while (true)
  {
    vector<int> nextSequence;
    for (size_t i = 0; i < sequence.size() - 1; i++)
      nextSequence.push_back(sequence[i + 1] - sequence[i]);

    bool allZero = true;
    for (size_t i = 0; i < nextSequence.size(); i++)
    {
      if (nextSequence[i])
        allZero = false;
    }

    if (allZero)
      break;

    sequence = nextSequence;
    sumLast += sequence.back();
  }

  return sumLast;
}

int main()
{
  ifstream in("..\\src\\_input.in");
  ofstream out("..\\src\\_output.out");

  FStreamReader reader(in);
  auto          v = reader.ReadDataAsMatrixOfNumbers();

  long long sumNext = 0;
  long long sumPrev = 0;

  for (auto line : v)
  {
    sumNext += GetNextSequence(line);

    reverse(line.begin(), line.end());
    sumPrev += GetNextSequence(line);
  }

  cout << sumNext << endl << sumPrev << endl;
  return 0;
}
