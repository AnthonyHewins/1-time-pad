#include <iostream>
#include "middleware/oracle.cpp"

using namespace std;

int main(int argc, char* argv[]) {
  Oracle().one_time_pad(argv[1], argv[2]);
}

/*
  OptionParser parser;
  switch (argc) {
  case 2:
    return parser.two_args(argv[1]);
  case 3:
    return parser.three_args(argv[1], argv[2]);
  case 5:
    return parser.five_args(argv[1], argv[2], argv[3], argv[4]);
  default:
    return parser.error(0);
  }
*/
