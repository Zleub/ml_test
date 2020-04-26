#ifndef LIB
# define LIB

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <tuple>

#include <identity.hpp>
#include <load.hpp>

std::vector<std::string> split(const std::string& s, char delimiter);
double identity(double i);
double sum(std::vector<double> i);
double average(std::vector<double> i);
double dot(std::tuple<std::vector<double>, std::vector<double>> in);
double sigmoid(std::tuple<std::vector<double>, std::vector<double>> in);
double sigmoid(double in);
double sigmoid_pd(double in);

#endif
