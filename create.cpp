/*
  USAGE:
    ./create filename [date]
*/

#include <cstdio>
#include <cstdint>
#include <cwchar>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <clocale>

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

  setlocale(LC_CTYPE,"UTF-8");

  // Create new file
  char fileName[255];
  strcpy(fileName, argv[1]);

  // Add file type if needed
  if(!hasFileType(fileName)) {
    strcat(fileName, ".cpp");
  }

  // Err if filename too long
  if(strlen(fileName) > 32) {
    printf("Filename too long. Max 32 characters.");
  }

  // Create the file
  FILE* fout;
  fout = fopen(fileName, "w");

  // Calc the width
  uint8_t width = 4 + strlen("Author: Kuba Zeligowski");
  uint8_t fileNameWidth = strlen(fileName) + 6;
  width = (width > fileNameWidth) ? width : fileNameWidth;
  width += (strlen(fileName) + 1) % 2;
  wprintf(L"Width: %d\n", width);
  uint8_t spacing;
  wchar_t space[width - 3];

  // File name line
  wchar_t fileNameLine[width - 3];
  spacing = (width - 4 - strlen(fileName)) / 2;
  wprintf(L"Spacing: %d\n", spacing);
  wchar_t wFileName[width - 3];
  mbstowcs(wFileName, fileName, strlen(fileName));
  wmemset(space, L' ', width - 4);

  wcsncpy(fileNameLine, space, spacing);
  wprintf(L"1: (%ls)\n", fileNameLine);
  wcsncat(fileNameLine, wFileName, strlen(fileName));
  wprintf(L"2: (%ls)\n", fileNameLine);
  wcsncat(fileNameLine, space, spacing);
  wprintf(L"3: (%ls)\n", fileNameLine);

  wmemset(space, 0, width - 3);

  // Author line
  wchar_t authorLine[width - 3];
  spacing = width - 4 - strlen("Author:Kuba Zeligowski");
  wmemset(space, L' ', spacing);

  wcscpy(authorLine, L"Author:");
  wcsncat(authorLine, space, spacing);
  wcscat(authorLine, L"Kuba Zeligowski");

  wmemset(space, 0, width - 3);

  // Date line
  wchar_t dateLine[width - 3];
  wchar_t date[13];
  spacing = width - 4 - strlen("Date:mmm dd, YYYY");
  time_t timer = time(nullptr);
  wmemset(space, L' ', spacing);
  wcsftime(date, 13, L"%b %d, %Y", localtime(&timer));

  wcscpy(dateLine, L"Date:");
  wcsncat(dateLine, space, spacing);
  wcscat(dateLine, date);

  wmemset(space, 0, width - 3);

  // Print Header
  fwprintf(fout, L"/*\n\n");
  wchar_t border[] = L"═╔╗║╚╝─╟╢";
  wchar_t wstr[width - 1];

  wmemset(wstr, border[0], width - 2);
  fwprintf(fout, L"%lc%ls%lc\n", border[1], wstr, border[2]);
  fwprintf(fout, L"%lc %ls %lc\n", border[3], fileNameLine, border[3]);
  wmemset(wstr, border[6], width - 2);
  fwprintf(fout, L"%lc%ls%lc\n", border[7], wstr, border[8]);
  fwprintf(fout, L"%lc %ls %lc\n", border[3], authorLine, border[3]);
  fwprintf(fout, L"%lc %ls %lc\n", border[3], dateLine, border[3]);
  wmemset(wstr, border[0], width - 2);
  fwprintf(fout, L"%lc%ls%lc\n", border[4], wstr, border[5]);

  fwprintf(fout, L"\nDescription: \n\n*/");

  fclose(fout);
  return 0;
}








