#include <iostream>
#include <iterator>
#include "oracle.h"
#include "../crypto/crypto.cpp"

using namespace std;

int Oracle::one_time_pad(char file[], char key[]) {
  vector<char> text = read(file), pad = read(key);
  Crypto().one_time_pad(text, pad);
  write(pad, text.size(), key);
  for (auto& i : text) cout << i;
}

int Oracle::csprng(int bytes) {
  try {
    char* buffer = Crypto().csprng(bytes);
    for (int i = 0; i < bytes; ++i) cout << buffer[i];
    delete [] buffer;
    return 0;
  } catch(int error) {
    switch (error) {
    case Crypto::BYTES_TOO_SMALL:
      cout << "# of bytes must be at least 1.";
      return 1;
    case Crypto::SODIUM_FAILURE:
      cout << "CRITICAL: libsodium failed to load.";
      return 2;
    default:
      cout << "Unspecified error; try again?";
      return 2;
    }
  }
}

vector<char> Oracle::read(char file[]) {
  ifstream io(file, ios::in | ios::binary);
  throw_if_file_has_errors(io);

  char buffer;
  vector<char> v;
  while(io.get(buffer)) v.push_back(buffer);
  io.close();

  return v;
}

void Oracle::write(vector<char>& key, int bytes_to_chop_off, char file[]) {
  if (key.size() <= bytes_to_chop_off) {
    string rm("rm ");
    system(rm.append(file).c_str());
  }

  ofstream io(file);
  throw_if_file_has_errors(io);
  
  auto iterator = key.begin() + bytes_to_chop_off;
  while (iterator != key.end()) {
    io.put(*(iterator++));
  }

  io.close();
}

void Oracle::throw_if_file_has_errors(ofstream& file) {
  if (file.fail()) {
    cout << "Unable to open file: is it open somewhere else?" << endl;
    file.close();
    throw Oracle::FILE_DNE;
  }
}

void Oracle::throw_if_file_has_errors(ifstream& file) {
  if (file.fail()) {
    cout << "Unable to open file: does it not exist?" << endl;
    file.close();
    throw Oracle::FILE_DNE;
  }

  if (!file.is_open()) {
    cout << "Unable to open file: something else may be using it" << endl;
    file.close();
    throw Oracle::FILE_IN_USE;
  }
}
