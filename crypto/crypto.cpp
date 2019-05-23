#include "crypto.h"

char* Crypto::symmetric_encryption(char key[], char file[]) {
  int size;
  char* contents = this->read_file(file, &size);

  if (size != 0) {
    for (int i = 0; i < size; i++)
      cout << (char) ((int)contents[i] | 0);
    cout << endl;
  }
}

char* Crypto::read_file(char file[], int* size) {
  ifstream io(file, ios::in | ios::binary | ios::ate);

  if (this->file_has_errors(&io)) {
    *size = 0;
    return NULL;
  }

  streampos file_size_in_bytes = io.tellg();
  *size = file_size_in_bytes;
  char* buffer = new char[file_size_in_bytes];
  io.seekg(0, ios::beg);
  io.read(buffer, file_size_in_bytes);

  return buffer;
}

int Crypto::file_has_errors(ifstream* file) {
  if (file->fail()) {
    cout << "Unable to open file: does it not exist?" << endl;
    return 1;
  }

  if (!file->is_open()) {
    cout << "Unable to open file: something else may be using it" << endl;
    return 1;
  }

  return 0;
}
