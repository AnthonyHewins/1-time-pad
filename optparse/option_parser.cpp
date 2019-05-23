#include <sodium.h>
#include <string.h>
#include "option_parser.h"
#include "option_parser_print_functions.cpp"

int OptionParser::two_args(char arg[]) {
  if (this->equals_option(arg, "-h", "--help")) {
    cout << "The 1-time pad is the \"holy grail\" of cryptosystems." << endl;
    return help();
  } else {
    return error(OptionParser::UNRECOGNIZED_ARG);
  }
}

int OptionParser::three_args(char arg1[], char arg2[]) {
  if (this->equals_option(arg1, "-g", "--generate"))
    return csprng(atoi(arg2));
  else
    return error(OptionParser::UNRECOGNIZED_ARG);
}

int OptionParser::five_args(char arg1[], char arg2[], char arg3[], char arg4[]) {
  int error_code = parse_encryption_opts(arg1, arg2) + parse_encryption_opts(arg3, arg4);
  if (error_code != 0)
    return error(error_code);

  switch (mode) {
  case OptionParser::ENCRYPT_MODE:
    // TODO
  case OptionParser::DECRYPT_MODE:
    // TODO
  default:
    return OptionParser::RETURN_FATAL;
  }
}

int OptionParser::parse_encryption_opts(char command[], char operand[]) {
  if (equals_option(command, "-e", "--encrypt")) {
    return set_encryption_opts(OptionParser::ENCRYPT_MODE, operand);
  } else if (equals_option(command, "-d", "--decrypt")) {
    return set_encryption_opts(OptionParser::DECRYPT_MODE, operand);
  } else if (equals_option(command, "-k", "--key")) {
    key = operand;
    return 0;
  } else {
    return OptionParser::UNRECOGNIZED_ARG;
  }
}

int OptionParser::set_encryption_opts(int encrypt_or_decrypt, char filename[]) {
  if (mode != 0)
    return OptionParser::INCORRECT_USAGE;
  mode = encrypt_or_decrypt;
  file = filename;
  return 0;
}

bool OptionParser::equals_option(char str1[], string str2, string str3) {
  return strcmp(str1, str2.c_str()) == 0 || strcmp(str1, str3.c_str()) == 0;
}


int OptionParser::csprng(int bytes) {
  if (sodium_init() < 0) {
    cout << "CRITICAL: libsodium couldn't be initialized. CSPRNG failed." << endl;
    return OptionParser::RETURN_FATAL;
  } else if (bytes < 1) {
    cout << "Error parsing number of bytes: not a number or less than 1 byte" << endl;
    return OptionParser::RETURN_ERROR;
  }

  char* buffer = new char[bytes];
  randombytes_buf(buffer, bytes);
  for (int i = 0; i < bytes; i++)
    cout << buffer[i];
  cout << flush;
  return OptionParser::RETURN_SUCCESS;
}
