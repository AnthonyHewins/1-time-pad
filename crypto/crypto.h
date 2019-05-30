#ifndef CRYPTO_H
#define CRYPTO_H

#include <vector>
#include <fstream>

class Crypto {
public:
  const static int KEY_TOO_SMALL = 0;
  const static int BYTES_TOO_SMALL = 1;
  const static int SODIUM_FAILURE = 2;

  void one_time_pad(std::vector<char> &text, const std::vector<char> &key);
  char* csprng(int bytes);
  std::vector<char> one_time_pad_copy(const std::vector<char> &text, const std::vector<char> &key);
private:
  void throw_if_out_of_bounds(const std::vector<char> &text, const std::vector<char> &key);
  char cast_then_xor(char textchar, char keychar);
};

#endif
