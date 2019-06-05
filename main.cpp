#include <unistd.h>
#include <iostream>
#include "middleware/oracle.cpp"

using namespace std;

void help() {
  cout << "\t-h\t\tDisplay this help message then quit.\n" \
    "\t-g BYTES\tGenerate a key of length BYTES.\n" \
    "\t-f FILE\t\tEncrypt/Decrypt a file. Must specify KEY.\n" \
    "\t-k KEY\t\tSpecify a key file for use. Must specify FILE." << endl;
}

int main(int argc, char* argv[]) {
  int option;

  char *file(nullptr), *key(nullptr);
  bool using_one_time_pad = false;
  while((option = getopt(argc, argv, "hf:g:k:")) != -1) {
    switch(option) {
    case 'k':
      key = optarg;
      using_one_time_pad = true;
      break;
    case 'f':
      file = optarg;
      using_one_time_pad = true;
      break;
    case 'g':
      return Oracle().csprng(atoi(optarg));
    case 'h':
      help();
      return 0;
    default:
      help();
      return 1;
    }
  }

  if (using_one_time_pad) {
    if (key == nullptr ^ file == nullptr) {
      cout << "Must specify both KEY and FILE" << endl;
      help();
      return 1;
    }
    
    Oracle().one_time_pad(file, key);
  }
}
