/*
  USAGE:
    ./create filename [author] [date]
*/

#include <fstream>
#include <cstdio>
#include <cwchar>

using namespace std;

bool hasFileType(char* fileName) {
  char* type = strstr(fileName, ".cpp");
  if(!type) {
    return 0;
  }
  if(strlen(type) > 4) {
    return 0;
  }
  return 1;
}

int main(int argc, char** argv) {
  if(argc < 2) {
    printf("Usage: %s filename [date]\n", argv[0]);
    exit(0);
  }

  // Create new file
  char fileName[255];
  strcpy(fileName, argv[1]);

  // Add file type if needed
  if(!hasFileType(fileName)) {
    strcat(fileName, ".cpp");
  }

  // 

  // Create the file
  FILE* fout;
  fout = fopen(fileName, "w");

  // Write the file
  wchar_t border[] = {L'═', L'╔', L'╗', L'╝', L'╚', L'─', L'╟', L'╢'};
  char width = 4 + strlen("Author: Kuba Zeligowski");



  return 0;
}
