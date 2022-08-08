#pragma once
#include <chrono>

#include <list>
#include <map>
#include <string>

/*
  Benchmarker for tracking multiple timers
  Example usage:
    Benchmarker b;
    using namespace std::chrono_literals;
    b.start("sleep1");
    b.start("sleep2");
    std::this_thread::sleep_for(100ms);
    b.stop("sleep1");
    b.start("sleep1");
    std::this_thread::sleep_for(100ms);
    b.stop("sleep1");
    b.stop("sleep2");
    b.print_timings();
  possible output:
    >>>> sleep1s µ=0.100062s     sigma=9.21007e-07s   total=0.200123
    >>>> sleep2s µ=0.200125s     sigma=0s             total=0.200125
*/

namespace bm
{
// Basic Timer class
class Timer
{
public:
  Timer();

  // get the time in seconds since the last reset
  double get();

  // set timer to 0
  void reset();

private:
  std::chrono::time_point<std::chrono::high_resolution_clock> m_chrono_ts;
};

class Benchmarker
{
public:
  Benchmarker(){};

  // start timer for a given tag
  void start(std::string &&tag);

  // stop timer for a given tag and store the elapsed time
  void stop(std::string &&tag);

  // Print all Timing results to console
  void print_timings();

  // export all Timing results to a csv file
  void export_csv(std::string filename);

  double average(std::string tag);
  double median(std::string tag);
  double std_deviation(std::string tag);
  double sum(std::string tag);
  size_t num_calls(std::string tag);

private:
  std::map<std::string, std::list<double>> m_timings;
  std::map<std::string, Timer> m_timers;
};
} // namespace bm