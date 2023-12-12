/**
 * Advent of code 2023
 * @author : Nicolae Telechi
 */
#include <algorithm>
#include <array>
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

unordered_map<string, long long> memo;

string memoKey(const string & str, const vector<long long> & numbers)
{
  string numbersTokens;
  for (auto number : numbers)
    numbersTokens += to_string(number) + ",";

  return str + ":" + numbersTokens;
}

long long ComputeArrangements(const string & str, const vector<long long> & numbers)
{
  auto it = memo.find(memoKey(str, numbers));
  if (it != memo.end())
    return it->second;

  if (numbers.empty())
    return 0 == count(str.begin(), str.end(), '#');
  else if (str.empty() && !numbers.empty())
    return numbers.size() == 1 && numbers[0] == 0;

  if (str[0] == '.')
  {
    auto nextNumbers = numbers;
    if (nextNumbers.front() == 0)
      nextNumbers.erase(nextNumbers.begin());

    return ComputeArrangements(str.substr(1), nextNumbers);
  }
  else if (str[0] == '#')
  {
    auto nextNumbers = numbers;

    auto hashes = nextNumbers.front();
    if (hashes == 0 || str.size() < hashes)
      return 0;

    if (count(str.begin(), str.begin() + hashes, '.'))
      return 0;

    nextNumbers.front() = 0;
    return ComputeArrangements(str.substr(hashes), nextNumbers);
  }
  else if (str[0] == '?')
  {
    long long arrangements = 0;

    string nextString = str;

    nextString[0] = '.';
    arrangements += ComputeArrangements(nextString, numbers);

    nextString[0] = '#';
    arrangements += ComputeArrangements(nextString, numbers);

    memo[memoKey(str, numbers)] = arrangements;
    return arrangements;
  }

  return 0;
}

int main()
{
  ifstream in("..\\src\\_input.in");
  ofstream out("..\\src\\_output.out");

  FStreamReader reader(in);
  auto          lines = reader.ReadLines();

  long long sum1 = 0;
  long long sum2 = 0;

  for (auto line : lines)
  {
    auto tokens = AOC::Explode(line, " ");
    assert(tokens.size() == 2);

    auto numbersTokens = AOC::Explode(tokens[1], ",");

    vector<long long> initialNumbers;
    transform(numbersTokens.begin(), numbersTokens.end(), back_inserter(initialNumbers),
              [](const string & number)
              {
                return stoll(number);
              });

    auto str     = tokens[0];
    auto numbers = initialNumbers;

    sum1 += ComputeArrangements(str, numbers);

    // part 2;
    for (size_t i = 0; i < 4; i++)
    {
      str += "?" + tokens[0];
      copy(initialNumbers.begin(), initialNumbers.end(), back_inserter(numbers));
    }

    sum2 += ComputeArrangements(str, numbers);
  }

  cout << sum1 << endl << sum2;

  return 0;
}
