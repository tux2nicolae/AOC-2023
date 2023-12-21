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

struct Pulse
{
  enum class Type
  {
    low,
    high
  };

  Type type;
};

struct Module;

unordered_map<string, unique_ptr<Module>> modules;
unordered_map<string, vector<string>>     graph;
unordered_map<string, vector<string>>     graphBack;

struct Processor
{
  void Schedule(Module * module, string from, Pulse pulse) { queue.push({ module, from, pulse }); }
  void Process();

  queue<tuple<Module *, string, Pulse>> queue;

  int totalLowPulses  = 0;
  int totalHighPulses = 0;
};

Processor processor;

struct Module
{
  enum class Type
  {
    FlipFlop,
    Conjunction,
    Broadcast,
    Output
  };

  string name;
  Type   type{};

  Module(string name, Type type)
    : name(name)
    , type(type){};

  virtual void Receive(string from, Pulse pulse) = 0;

  void SendPulse(Pulse pulse)
  {
    if (pulse.type == Pulse::Type::high)
      SendHighPulse();
    else
      SendLowPulse();
  }

  void SendHighPulse()
  {
    for (auto to : graph[name])
    {
      assert(modules[to]);
      processor.Schedule(modules[to].get(), name, { Pulse::Type::high });
    }

    processor.Process();
  };

  void SendLowPulse()
  {
    for (auto to : graph[name])
    {
      assert(modules[to]);
      processor.Schedule(modules[to].get(), name, { Pulse::Type::low });
    }

    processor.Process();
  };
};

// prefix %
struct FlipFlopModule : public Module
{
  bool state = false;

  FlipFlopModule(string name)
    : Module(name, Module::Type::FlipFlop){};

  void Receive(string from, Pulse pulse) override
  {
    if (pulse.type == Pulse::Type::high)
      return;

    if (!state)
    {
      state = true;
      SendHighPulse();
    }
    else if (state)
    {
      state = false;
      SendLowPulse();
    }
  }
};

// prefix &
struct ConjunctionModule : public Module
{
  unordered_map<string, Pulse> memory;

  ConjunctionModule(string name)
    : Module(name, Module::Type::Conjunction){};

  void Receive(string from, Pulse pulse) override
  {
    assert(memory.count(from));
    memory[from] = pulse;

    bool allHigh = all_of(memory.begin(), memory.end(),
                          [](const auto & item)
                          {
                            return item.second.type == Pulse::Type::high;
                          });

    if (allHigh)
    {
      SendLowPulse();
    }
    else
    {
      SendHighPulse();
    }
  }
};

struct BroadcastModule : public Module
{
  BroadcastModule(string name)
    : Module(name, Module::Type::Broadcast){};

  void Receive(string from, Pulse pulse) override { SendPulse(pulse); }
};

struct OutputModule : public Module
{
  OutputModule(string name)
    : Module(name, Module::Type::Output){};

  void Receive(string from, Pulse pulse) override
  {
    // cout << from << " : " << static_cast<int>(pulse.type) << endl;
  }
};

struct Button
{
  void Send()
  {
    assert(modules["broadcaster"]);

    processor.Schedule(modules["broadcaster"].get(), "button", Pulse{ Pulse::Type::low });
    processor.Process();
  }
};

void Processor::Process()
{
  while (!queue.empty())
  {
    auto [module, from, pulse] = queue.front();
    queue.pop();

    if (from == "rz" && pulse.type == Pulse::Type::high)
    {
      int xxx = 4057;
    }

    if (from == "lf" && pulse.type == Pulse::Type::high)
    {
      int xxx = 3911;
    }

    if (from == "br" && pulse.type == Pulse::Type::high)
    {
      int xxx = 3877;
    }

    if (from == "fk" && pulse.type == Pulse::Type::high)
    {
      int xxx = 4079;
    }

    module->Receive(from, pulse);

    totalLowPulses += pulse.type == Pulse::Type::low;
    totalHighPulses += pulse.type == Pulse::Type::high;
  }
}

bool AllHight(string conjunctionModule)
{
  // update Conjunction Modules memory
  auto module = modules[conjunctionModule].get();
  assert(module);

  assert(module->type == Module::Type::Conjunction);
  if (module->type == Module::Type::Conjunction)
  {
    auto conjunctionModule = static_cast<ConjunctionModule *>(module);

    return all_of(conjunctionModule->memory.begin(), conjunctionModule->memory.end(),
                  [](const auto & item)
                  {
                    return item.second.type == Pulse::Type::high;
                  });
  }

  return false;
}

int main()
{
  ifstream in("..\\src\\_input.in");
  ofstream out("..\\src\\_output.out");

  FStreamReader reader(in);
  auto          lines = reader.ReadLines();

  for (auto line : lines)
  {
    auto matches = AOC::ExtractMatches(line, "(.*) -> (.*)");
    assert(matches.size() == 2);

    const auto from         = matches[0];
    auto       dependencies = AOC::Explode(matches[1], ", ");

    if (from == "broadcaster")
    {
      modules[from] = make_unique<BroadcastModule>(from);

      for (auto dependency : dependencies)
      {
        graph[from].push_back(dependency);
        graphBack[dependency].push_back(from);
      }
    }
    else if (from[0] == '%')
    {
      modules[from.substr(1)] = make_unique<FlipFlopModule>(from.substr(1));

      for (auto dependency : dependencies)
      {
        graph[from.substr(1)].push_back(dependency);
        graphBack[dependency].push_back(from.substr(1));
      }
    }
    else if (from[0] == '&')
    {
      modules[from.substr(1)] = make_unique<ConjunctionModule>(from.substr(1));

      for (auto dependency : dependencies)
      {
        graph[from.substr(1)].push_back(dependency);
        graphBack[dependency].push_back(from.substr(1));
      }
    }
  }

  for (auto [to, fromVector] : graphBack)
  {
    // output module
    if (!modules[to])
    {
      modules[to] = make_unique<OutputModule>(to);
    }

    // update Conjunction Modules memory
    auto module = modules[to].get();
    if (module->type == Module::Type::Conjunction)
    {
      auto conjunctionModule = static_cast<ConjunctionModule *>(module);

      for (auto from : fromVector)
        conjunctionModule->memory[from];
    }
  }

  // vector<FlipFlopModule *> flipFlopModules;
  // for (auto & [_, module] : modules)
  //{
  //   if (module->type == Module::Type::FlipFlop)
  //   {
  //     auto flipFlopModule = static_cast<FlipFlopModule *>(module.get());
  //     flipFlopModules.push_back(flipFlopModule);
  //   }
  // }

  string sortedFlipFlopModules =
    "lz nn mj tx qn vq zc np qz fq ms bt dn xd tp bh hf hq nm gp cm qk hn mh xn zb xp fm hh kb gz "
    "mq vf cr jd dq vx fl nc dj sf rq ds sx xv xb kz fn";

  auto sortedFlipFlop = AOC::Explode(sortedFlipFlopModules, " ");
  reverse(sortedFlipFlop.begin(), sortedFlipFlop.end());

  vector<FlipFlopModule *> flipFlopModules;
  for (auto & moduleName : sortedFlipFlop)
  {
    auto module = modules[moduleName].get();
    if (module->type == Module::Type::FlipFlop)
    {
      auto flipFlopModule = static_cast<FlipFlopModule *>(module);
      flipFlopModules.push_back(flipFlopModule);
    }
  }

  // queue<pair<string, bool>> q;
  // q.push({ "rx", false });

  // unordered_map<string, bool> visited;

  // while (!q.empty())
  //{
  //   auto [currentNode, currentState] = q.front();
  //   q.pop();

  //  for (auto from : graphBack[currentNode])
  //  {
  //    auto fromModule = modules[from].get();
  //    if (fromModule->type == Module::Type::FlipFlop)
  //    {
  //      auto flipFlopModule   = static_cast<FlipFlopModule *>(fromModule);
  //      flipFlopModule->state = !currentState;
  //    }

  //    if (!visited[from])
  //    {
  //      q.push({ from, !currentState });
  //      visited[from] = true;
  //    }
  //  }
  //}

  unordered_map<string, int>  cicles;
  unordered_map<string, bool> values;

  for (auto module : flipFlopModules)
  {
    values[module->name] = module->state;
  }

  Button button;
  for (size_t i = 1; i <= 10000; i++)
  {
    processor.totalLowPulses  = 0;
    processor.totalHighPulses = 0;

    button.Send();

    for (auto module : flipFlopModules)
    {
      if (!cicles.count(module->name) && module->state)
        cicles[module->name] = i;

      out << /*module->name << " " <<*/ module->state /* << endl*/;
    }

    out << endl;

    // auto rz = AllHight("rz");
    // auto lf = AllHight("lf");
    // auto br = AllHight("br");
    //
    // auto lbTest = AllHight("lb");
    // auto lb     = fk && rz && lf && br;

    /* out << "LOW:HIGH " << processor.totalLowPulses << " : " << processor.totalHighPulses << " = "
         << processor.totalLowPulses + processor.totalHighPulses << endl;*/
  }

  sort(begin(flipFlopModules), end(flipFlopModules),
       [&](FlipFlopModule * first, FlipFlopModule * second)
       {
         return cicles[first->name] < cicles[second->name];
       });

  for (auto module : flipFlopModules)
  {
    out << module->name << " ";
  }

  out << endl;

  cout << "LOW: " << processor.totalLowPulses << endl;
  cout << "HIGH:" << processor.totalHighPulses << endl;
  cout << processor.totalLowPulses * processor.totalHighPulses << endl;

  // for (auto & [_, module] : modules)
  //{
  //   if (module->type == Module::Type::FlipFlop)
  //   {
  //     auto flipFlopModule = static_cast<FlipFlopModule *>(module.get());
  //   }
  // }

  // too high -> 501848147836682
  cout << AOC::Cmmmc(AOC::Cmmmc(4057, 3911), AOC::Cmmmc(3877, 4079));

  return 0;
}
