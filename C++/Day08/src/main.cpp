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

struct Node
{
  string str;
  string left;
  string right;
};

unordered_map<string, Node> tree;

int main()
{
  ifstream in("..\\src\\_input.in");
  ofstream out("..\\src\\_output.out");

  FStreamReader  reader(in);
  vector<string> v = reader.ReadLines();

  string instructions = v[0];

  for (size_t i = 2; i < v.size(); i++)
  {
    auto matches = AOC::ExtractMatches(v[i], "(.*) = \\((.*), (.*)\\)");
    assert(matches.size() == 3);

    Node node{ matches[0], matches[1], matches[2] };
    tree[matches[0]] = node;
  }

  vector<Node> currentNodes;
  for (auto & [nodeName, node] : tree)
  {
    if (nodeName.back() == 'A')
      currentNodes.push_back(node);
  }

  unordered_map<string, int> onZ;

  long long step = 1;
  for (;; step++)
  {
    char instruction = instructions[(step - 1) % instructions.size()];

    for (auto & currentNode : currentNodes)
    {
      if (instruction == 'L')
        currentNode = tree[currentNode.left];
      else if (instruction == 'R')
        currentNode = tree[currentNode.right];
    }

    int countZ = 0;
    for (const auto & currentNode : currentNodes)
    {
      if (currentNode.str.back() == 'Z')
      {
        if (!onZ.count(currentNode.str))
          onZ[currentNode.str] = step;

        countZ++;
      }
    }

    // if (countZ == currentNodes.size())
    //   break;

    if (onZ.size() == currentNodes.size())
      break;
  }

  cout << step << endl;

  long long test = 1;
  for (auto [_, step] : onZ)
  {
    test = AOC::Cmmmc(test, step);
  }

  cout << test;

  return 0;
}
