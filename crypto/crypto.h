#include <vector>
#include <array>
#include <fstream>


class Crypto {
public:
  void one_time_pad(std::vector<char> &text, const std::vector<char> &key);
  std::vector<char> one_time_pad_copy(const std::vector<char> &text, const std::vector<char> &key);
private:
  void throw_if_out_of_bounds(const std::vector<char> &text, const std::vector<char> &key);
  char cast_then_xor(char textchar, char keychar);
};
