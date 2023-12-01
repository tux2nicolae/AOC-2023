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

vector<pair<string, string>> digits{ {
  { "one", "1" },
  { "two", "2" },
  { "three", "3" },
  { "four", "4" },
  { "five", "5" },
  { "six", "6" },
  { "seven", "7" },
  { "eight", "8" },
  { "nine", "9" },
} };

void Replace(string & line, size_t offset)
{
  for (auto [word, number] : digits)
  {
    if (line.substr(offset)._Starts_with(word))
    {
      line.replace(offset, word.size(), number);
    }
  }
}

void ReplaceDigits(string & line)
{
  for (int offset = 0; offset < line.size(); offset++)
  {
    Replace(line, offset);
  }
}

void ReplaceDigitsBackward(string & line)
{
  for (int offset = line.size() - 1; offset >= 0; offset--)
  {
    Replace(line, offset);
  }
}

int main()
{
  ifstream in("..\\src\\_input.in");
  ofstream out("..\\src\\_output.out");

  FStreamReader  reader(in);
  vector<string> v         = reader.ReadLines();
  vector<string> vBackward = v;

  int s = 0;

  // part 2
  for (auto & line : v)
  {
    ReplaceDigits(line);
  }

  for (auto & line : vBackward)
  {
    ReplaceDigitsBackward(line);
  }

  // part 1
  for (int i = 0; i < v.size(); i++)
  {
    auto line         = v[i];
    auto lineBackward = vBackward[i];

    auto pos = line.find_first_of("123456789");
    assert(pos != string::npos);
    int first = line[pos] - '0';

    pos = lineBackward.find_last_of("123456789");
    assert(pos != string::npos);
    int last = lineBackward[pos] - '0';

    assert(first);
    assert(last);

    s += first * 10 + last;
  }

  cout << s;

  // out
  FStreamWriter writer(out);
  for (const auto & element : v)
  {
    out << element << endl;
  }

  return 0;
}
