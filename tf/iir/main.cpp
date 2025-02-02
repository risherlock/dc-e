#include "filter.h"

#include <iomanip>
#include <fstream>
#include <iostream>

#define FILTER_ORDER 2
#define FILTER_COEFF_SIZE (FILTER_ORDER + 1)

int main()
{
  // Second-order filter
  double b[FILTER_COEFF_SIZE] = {1.23, 2.34, 1.45};
  double a[FILTER_COEFF_SIZE] = {1.43, -1.8, 0.81};

  // Initial state
  // double x0[FILTER_ORDER] = {0.12, 0.34};

  filter<FILTER_ORDER> my_filter(b, a);
  // my_filter.set_x0(x0);

  double data[] =
  {
    0.1234, 0.5678, 0.9101, 0.1121, 0.3141, 0.5161, 0.7181, 0.9202, 0.2232, 0.4252,
    0.6272, 0.8292, 0.0313, 0.2333, 0.4353, 0.6373, 0.8393, 0.0414, 0.2434, 0.4454,
    0.6474, 0.8494, 0.0515, 0.2535, 0.4555, 0.6575, 0.8595, 0.0616, 0.2636, 0.4656,
    0.6676, 0.8696, 0.0717, 0.2737, 0.4757, 0.6777, 0.8797, 0.0818, 0.2838, 0.4858,
    0.6878, 0.8898, 0.0919, 0.2939, 0.4959, 0.6979, 0.8999, 0.1020, 0.3040, 0.5060,
    0.7080, 0.9100, 0.1121, 0.3141, 0.5161, 0.7181, 0.9202, 0.2232, 0.4252, 0.6272,
    0.8292, 0.0313, 0.2333, 0.4353, 0.6373, 0.8393, 0.0414, 0.2434, 0.4454, 0.6474,
    0.8494, 0.0515, 0.2535, 0.4555, 0.6575, 0.8595, 0.0616, 0.2636, 0.4656, 0.6676,
    0.8696, 0.0717, 0.2737, 0.4757, 0.6777, 0.8797, 0.0818, 0.2838, 0.4858, 0.6878,
    0.8898, 0.0919, 0.2939, 0.4959, 0.6979, 0.8999, 0.1020, 0.3040, 0.5060, 0.7080
  };

  std::ofstream outfile("cpp.csv");

  if (!outfile)
  {
    std::cerr << "File error!" << std::endl;
    return 1;
  }

  for (size_t i = 0; i < sizeof(data) / sizeof(double); i++)
  {
    double output = my_filter.update(data[i]);
    outfile << std::fixed << std::setprecision(6) << output << std::endl;
  }

  outfile.close();
  std::cout << "Output written to 'cpp.csv'." << std::endl;
  return 0;
}
