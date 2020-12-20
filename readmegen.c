#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

void trim(char * s) {
  char * p = s;
  int l = strlen(p);

  while (isspace(p[l - 1])) p[--l] = 0;
  while ( * p && isspace( * p)) ++p, --l;

  memmove(s, p, l + 1);
}

int main(int argc, char * argv[]) {
  // create file
  int fd;
  char buf[4096];
  fd = open("README.md", O_CREAT | O_WRONLY, 0600);
  if (fd == -1) {
    printf("ERROR: file create/open error.\n");
    exit(1);
  }

  char formattedTotal[4096] = "\0";

  // make array of questions
  char responses[7][253];
  char questionsList[7][128];
  strcpy(questionsList[0], "What is the title of this project?\n");
  strcpy(questionsList[1], "Please describe the app.\n");
  strcpy(questionsList[2], "How is this app installed?\n");
  strcpy(questionsList[3], "How is this app used?\n");
  strcpy(questionsList[4], "What kind of license does this app have?\nGNU GPLv3\nMIT\nISC\nApache 2.0\n");
  strcpy(questionsList[5], "What email can people direct their questions to?\n");
  strcpy(questionsList[6], "What is your github username?\n");

  // get user input
  for (int i = 0; i < 7; i++) {
    printf("%s", questionsList[i]);
    fgets(responses[i], 253, stdin);
	system("clear");
  }

  // format input into markdown
  // title
  strncat(formattedTotal, "<h1 align='center'>", 21);
  strncat(formattedTotal, responses[0], 100);
  strncat(formattedTotal, "</h1>\n", 7);
  // table of contents
  strncat(formattedTotal, "<p align='center'><a href='#description'>Description</a></p><p align='center'><a href='#installation'>Installation</a></p><p align='center'><a href='#usage'>Usage</a></p><p align='center'><a href='#license'>License</a></p><p align='center'><a href='#questions'>Questions</a></p>\n\n\n", 400);
  // description
  strncat(formattedTotal, "<h2 align='center'>Description</h2>\n", 37);
  strncat(formattedTotal, "<p align='center'>", 19);
  strncat(formattedTotal, responses[1], 253);
  strncat(formattedTotal, "</p>", 5);
  strncat(formattedTotal, "\n", 2);
  // installation
  strncat(formattedTotal, "<h2 align='center'>Installation</h2>\n", 38);
  strncat(formattedTotal, "<p align='center'>", 19);
  strncat(formattedTotal, responses[2], 253);
  strncat(formattedTotal, "</p>", 5);
  strncat(formattedTotal, "\n", 2);
  // usage
  strncat(formattedTotal, "<h2 align='center'>Usage</h2>\n", 31);
  strncat(formattedTotal, "<p align='center'>", 19);
  strncat(formattedTotal, responses[3], 253);
  strncat(formattedTotal, "</p>", 5);
  strncat(formattedTotal, "\n", 2);

  // license
  strncat(formattedTotal, "<h2 align='center'>License</h2>\n", 33);
  strncat(formattedTotal, "<p align='center'>", 19);
  strncat(formattedTotal, "<img src='https://img.shields.io/badge/license-", 48);
  char apacheLic[11] = "Apache 2.0";
  char gnuLic[10] = "GNU GPLv3";
  trim(responses[4]);
  int zeroIfApache = strcmp(responses[4], apacheLic);
  int zeroIfGnu = strcmp(responses[4], gnuLic);
  if (zeroIfApache == 0) {
    strncat(formattedTotal, "Apache%202.0", 40);
  } else if (zeroIfGnu == 0) {
    strncat(formattedTotal, "GNU%20GPLv3", 40);
  } else {
    strncat(formattedTotal, responses[4], 40);
  }
  strncat(formattedTotal, "-blue' alt='license'></img>", 28);
  strncat(formattedTotal, "</p>\n", 6);

  // questions
  strncat(formattedTotal, "<h2 align='center'>Questions</h2>\n", 35);
  strncat(formattedTotal, "<p align='center'>", 19);
  strncat(formattedTotal, "Any questions on this or other projects can be directed to ", 64);
  strncat(formattedTotal, responses[5], 253);
  strncat(formattedTotal, "</p>", 5);
  strncat(formattedTotal, "\n", 2); 
  // github
  trim(responses[6]);
  strncat(formattedTotal, "<h2 align='center'>More Of My Projects</h2>\n", 45);
  strncat(formattedTotal, "<p align='center'>Find more of my work on <a href='https://github.com/", 71);
  strncat(formattedTotal, responses[6], 40);
  strncat(formattedTotal, "'>my GitHub</a></p>\n", 21);

  // write the file
  write(fd, formattedTotal, strlen(formattedTotal));

  printf("File printed to README.md \ntotal length is %lu\n", strlen(formattedTotal));

  return 0;
}