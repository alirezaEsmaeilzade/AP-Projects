#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

void print_string_vector(std::vector< std::string> input);
void print_sorted_string_vector(std::vector< std::string> input);
std::vector<std::string> split_string(std::string unsplit, char separator);
#endif