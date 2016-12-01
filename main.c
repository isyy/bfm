// brainfvck-modified interpreter //
// copyright (C) 2016 isy //
// under the GPLv2-License (SEE LICENSE.md) //

#include <stdio.h>

int main(void) {

// init tape //
char array[] = {0};
char *ptr=array;

x = 0 
 
// open file "main.bfm" //
FILE *fp;
fp=fopen("main.bfm", "r");

while  ( ( x = fgetc( file ) ) != EOF )
{
 if (x == 76) {
   ++ptr;
 }
 
 else if (x == 74) {
   --ptr;
 }
 else if (x == 53) {
   ++*ptr;
 }
 
 else if (x == 55) {
   --*ptr;
 }
  
 else if (x == 56) {
   putchar(*ptr);
 }
  
 else if (x == 54) {
   *ptr=getchar();
 }
  
 else if (x == 133) {
   while (*ptr) {
 }
 
 else if (x == 135) {
   }
 }
 
 else if (x == 41) {
   break;
 }
}

exit(0);
}
