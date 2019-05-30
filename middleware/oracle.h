#include <iostream>
#include <vector>

class Oracle {
public:
  void one_time_pad(char file[], char key[]);
private:
  std::vector<char> read(char file[]);
  void throw_if_file_has_errors(std::ofstream& file);
  void throw_if_file_has_errors(std::ifstream& file);
};
