#include "decrypt.h"

void Decrypt::decrypt(char key[], char file[]) {
  this->symmetric_encryption(key, file);
}
