#include "./benchmarker.hpp"

#include <cmath>
#include <fstream>
#include <iostream>

using namespace bm;

Timer::Timer() { reset(); }

double Timer::get()
{
  auto now = std::chrono::high_resolution_clock::now();
  double duration =
      std::chrono::duration_cast<std::chrono::nanoseconds>(now - m_chrono_ts).count() * 1e-9;

  return duration;
}

void Timer::reset() { m_chrono_ts = std::chrono::high_resolution_clock::now(); }

void Benchmarker::start(std::string &&tag) { m_timers[tag] = Timer(); }

void Benchmarker::stop(std::string &&tag)
{
  double time = m_timers[tag].get();
  m_timings[tag].push_back(time);
}

void Benchmarker::print_timings()
{
  std::map<std::string, std::list<double>>::iterator itr;
  for (itr = m_timings.begin(); itr != m_timings.end(); itr++)
  {
    auto tag = itr->first;
    std::cout << tag << "\tµ=" << average(tag) << "s\tsigma=" << std_deviation(tag)
              << "s\tmedian=" << median(tag) << "s\ttotal=" << sum(tag)
              << "\tnum_calls=" << num_calls(tag) << std::endl;
  }
}

void Benchmarker::export_csv(std::string filename)
{
  std::ofstream file;
  file.open(filename);
  if (!file.is_open())
  {
    throw std::runtime_error("Unable to open output " + filename);
  }

  // Header
  file << "tag;average;std_dev;median;total;num_calls" << std::endl;

  // Data
  for (auto itr = m_timings.begin(); itr != m_timings.end(); itr++)
  {
    // clang-format off
      auto tag = itr->first;
      file  << tag << ";" 
            << average(tag) << ";" 
            << std_deviation(tag) << ";"
            << median(tag) << ";"
            << sum(tag) << ";"
            << num_calls(tag) << std::endl;
    // clang-format on
  }

  file.close();
}

double Benchmarker::median(std::string tag)
{
  auto data = m_timings[tag];
  auto itr = data.begin();
  std::advance(itr, data.size() / 2);
  return *itr;
}

double Benchmarker::std_deviation(std::string tag)
{
  auto data = m_timings[tag];
  double avg = average(tag);
  double sigma2 = 0;

  for (double element : data)
  {
    sigma2 += (element - avg) * (element - avg);
  }

  double sigma = sqrt(sigma2) / (double)data.size();
  return sigma;
}

double Benchmarker::sum(std::string tag)
{
  double sum = 0;
  for (double element : m_timings[tag])
  {
    sum += element;
  }
  return sum;
}

size_t Benchmarker::num_calls(std::string tag) { return m_timings[tag].size(); }

double Benchmarker::average(std::string tag) { return sum(tag) / (double)m_timings[tag].size(); }
