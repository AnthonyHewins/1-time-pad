#include <iostream>
#include <iterator>
#include "oracle.h"
#include "../crypto/crypto.cpp"

using namespace std;

void Oracle::one_time_pad(char file[], char key[]) {
  vector<char> text = read(file), pad = read(key);
  Crypto c;
  c.one_time_pad(text, pad);
  for (auto& i : text) cout << i;
}

vector<char> Oracle::read(char file[]) {
  ifstream io(file, ios::in | ios::binary | ios::ate);
  throw_if_file_has_errors(io);

  streampos file_size_in_bytes = io.tellg();
  char* buffer = new char[file_size_in_bytes];
  io.seekg(0, ios::beg);
  io.read(buffer, file_size_in_bytes);

  vector<char> v;
  for (int i = 0; i < file_size_in_bytes; ++i)
    v.push_back(buffer[i]);

  delete [] buffer;
  io.close();

  return v;
}

void Oracle::throw_if_file_has_errors(ofstream& file) {
  if (file.fail()) {
    cout << "Unable to open file: does it not exist?" << endl;
    file.close();
    throw 1;
  }
}

void Oracle::throw_if_file_has_errors(ifstream& file) {
  if (file.fail()) {
    cout << "Unable to open file: does it not exist?" << endl;
    file.close();
    throw 1;
  }

  if (file.fail()) {
    cout << "Unable to open file: something else may be using it" << endl;
    file.close();
    throw 2;
  }
}
