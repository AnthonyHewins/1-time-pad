#include <iostream>
#include <vector>

class Oracle {
public:
  const static int FILE_DNE = 0;
  const static int FILE_IN_USE = 1;

  int one_time_pad(char file[], char key[]);
  int csprng(int bytes);
private:
  std::vector<char> read(char file[]);
  void write(std::vector<char>& key, int bytes_to_chop_off, char file[]);
  void throw_if_file_has_errors(std::ifstream& file);
  void throw_if_file_has_errors(std::ofstream& file);
};
