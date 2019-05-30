#include <sodium.h>
#include "crypto.h"

using namespace std;

void Crypto::one_time_pad(vector<char> &text, const vector<char> &key) {
  throw_if_out_of_bounds(text, key);

  auto j = key.begin();
  for (auto i = text.begin(); i != text.end(); ++i) {
    *i = cast_then_xor(*i, *j);
    ++j;
  }
}

vector<char> Crypto::one_time_pad_copy(const vector<char> &text, const vector<char> &key) {
  throw_if_out_of_bounds(text, key);

  vector<char> new_text;
  for (auto i = text.begin(), j = key.begin(); i != text.end(); ++i) {
    new_text.push_back( cast_then_xor(*i, *j) );
    ++j;
  }

  return new_text;
}

void Crypto::throw_if_out_of_bounds(const vector<char>& text, const vector<char>& key) {
  int end_of_key = key.size(), end_of_text = text.size();

  if (end_of_text > end_of_key)
    throw Crypto::KEY_TOO_SMALL;
}

char Crypto::cast_then_xor(char textchar, char keychar) {
  return (char) (  (int)textchar ^ (int)keychar  );
}

char* Crypto::csprng(int bytes) {
  if (bytes < 1)
    throw Crypto::BYTES_TOO_SMALL;
  if (sodium_init() < 0)
    throw Crypto::SODIUM_FAILURE;

  char* buffer = new char[bytes];
  randombytes_buf(buffer, bytes);

  return buffer;
}
