/*
 * pass_string.c
 *
 * Modify a string.
 *
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int mod_str(const char* str1, char* str2) {
  *str2 = '|';
  str2++;
  while(*str1 != '\n') {
    *str2 = *str1;
    str2++;
    *str2 = '|';
    str2++;
    str1++;
  }
  *str2 = '\n';
}

int main (int argc, char* argv[]) {
  const char* mystring = "my string";
  char* result_str;
  result_str = (char *)malloc(100*sizeof(char));
  mod_str(mystring, result_str);
  printf("mystring: %s, mod_string: %s\n", mystring, result_str);
  free(result_str);
  
}
