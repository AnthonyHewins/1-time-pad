#include "option_parser.h"

int OptionParser::error(int error_type) {
  if (error_type == OptionParser::INCORRECT_ARGS)
    cout << "Incorrect number of args\n";
  else if (error_type == OptionParser::UNRECOGNIZED_ARG)
    cout << "Unrecognized argument\n";
  else if (error_type == OptionParser::INVALID_ARG)
    cout << "Invalid argument\n";
  else if (error_type == OptionParser::INCORRECT_USAGE)
    cout << "Incorrect usage of arguments\n";
  else
    cout << "FATAL unknown error\n";
  help();
  return OptionParser::RETURN_ERROR;
}

int OptionParser::help() {
  cout << "\t-h, --help\t\tDisplay this help message then quit.\n" \
    "\t-g, --generate BYTES\tGenerate a key of length BYTES.\n" \
    "\t-e, --encrypt FILE\tEncrypt a file. Must specify KEY.\n" \
    "\t-d, --decrypt FILE\tDecrypt a file. Must specify KEY.\n" \
    "\t-k, --key KEY\t\tSpecify a key file for use with -d or -e." << endl;
  return 0;
}
