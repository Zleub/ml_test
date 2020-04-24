#include <lib.hpp>

std::vector<std::string> split(const std::string& s, char delimiter)
{
   std::vector<std::string> tokens;
   std::string token;
   std::istringstream tokenStream(s);
   while (std::getline(tokenStream, token, delimiter))
      tokens.push_back(token);
   return tokens;
}

double identity(double i) { return i; }
double sum(std::vector<double> i) {
  double r = 0;
  for (double n : i) {
    r += n;
  }
  return r;
}
double average(std::vector<double> i) {
  double s = sum(i);
  return s / i.size();
}
double dot(std::tuple<std::vector<double>, std::vector<double>> in) {
  std::vector<double> weights = std::get<0>(in);
  std::vector<double> input = std::get<1>(in);

  double res = 0;
  for (size_t i = 0; i < weights.size(); i++) {
    res += weights[i] * input[i];
  }

  return res;
}

// double sin_test(std::tuple<std::vector<double>, std::vector<double>> in) {
//   double r = dot(in);
//   return sin(r);
// }
double sigmoid(std::tuple<std::vector<double>, std::vector<double>> in) {
  double x = dot(in);
  return x / (1. + abs(x));
}
double sigmoid(double in) {
  return in / (1. + abs(in));
}
double sigmoid_pd(double in) {
  return sigmoid(in) * (1 - sigmoid(in));
  // return x / (1. + abs(x));
}
