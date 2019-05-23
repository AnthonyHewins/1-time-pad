#include <stack>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

class Crypto {
protected:
  char* text_buffer;
  char* symmetric_encryption(char key[], char file[]);
private:
  char* read_file(char file[], int* size);
  int file_has_errors(ifstream* file);
};
