#ifndef OPTION_PARSER_H
#define OPTION_PARSER_H

class OptionParser {
public:
  int two_args(char arg[]);
  int three_args(char arg1[], char arg2[]);
  int five_args(char arg1[], char arg2[], char arg3[], char arg4[]);
  int error(int error_type);
private:
  static const int INCORRECT_ARGS = 0;
  static const int UNRECOGNIZED_ARG = 1;
  static const int INVALID_ARG = 2;
  static const int INCORRECT_USAGE = 3;

  static const int RETURN_SUCCESS = 0;
  static const int RETURN_ERROR = 1;
  static const int RETURN_FATAL = 2;

  static const int ENCRYPT_MODE = 0;
  static const int DECRYPT_MODE = 1;
  
  int mode = 0;
  char* file;
  char* key;

  int csprng(int bytes);
  int parse_encryption_opts(char command[], char operand[]);
  int set_encryption_opts(int encrypt_or_decrypt, char filename[]);
  bool equals_option(char str1[], string str2, string str3);
  int help();
};

#endif
