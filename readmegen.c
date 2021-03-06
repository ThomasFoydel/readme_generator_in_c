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
  char buf[8190];

  if (argc > 1){
    fd = open(argv[1], O_CREAT | O_WRONLY, 0600);
  } else {
    fd = open("README.md", O_CREAT | O_WRONLY, 0600);
  }

  if (fd == -1) {
    printf("ERROR: file create/open error.\n");
    exit(1);
  }

  char formattedTotal[8190] = "\0";

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
    fgets(responses[i], 1020, stdin);
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
  strncat(formattedTotal, responses[1], 1020);
  strncat(formattedTotal, "</p>", 5);
  strncat(formattedTotal, "\n", 2);
  // installation
  strncat(formattedTotal, "<h2 align='center'>Installation</h2>\n", 38);
  strncat(formattedTotal, "<p align='center'>", 19);
  strncat(formattedTotal, responses[2], 1020);
  strncat(formattedTotal, "</p>", 5);
  strncat(formattedTotal, "\n", 2);
  // usage
  strncat(formattedTotal, "<h2 align='center'>Usage</h2>\n", 31);
  strncat(formattedTotal, "<p align='center'>", 19);
  strncat(formattedTotal, responses[3], 1020);
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

  // badge color
  char *lic = responses[4];
  char *mitCheck = "MIT";
  char *apacheCheck = "Apache";
  char *gnuCheck = "GNU";
  char *iscCheck = "ISC";
  if (argv[2]) {
     strncat(formattedTotal, "-", 2);
     strncat(formattedTotal, argv[2], 18);
     strncat(formattedTotal, "'", 2);
  }
  else if (strcasestr(lic, mitCheck) != NULL) {
    strncat(formattedTotal, "-yellow'", 9);
  } 
  else if (strcasestr(lic, apacheCheck) != NULL) {
    strncat(formattedTotal, "-yellowgreen'", 14);
  }
  else if (strcasestr(lic, gnuCheck) != NULL) {
    strncat(formattedTotal, "-blue'", 7);
  } 
  else if (strcasestr(lic, iscCheck) != NULL) {
    strncat(formattedTotal, "-red'", 6);
  }
  else {
    strncat(formattedTotal, "-9cf'", 6);
  }
  strncat(formattedTotal, " alt='license'></img>", 22);
  

  // questions
  strncat(formattedTotal, "<h2 align='center'>Questions</h2>\n", 35);
  strncat(formattedTotal, "<p align='center'>", 19);
  strncat(formattedTotal, "Any questions on this or other projects can be directed to ", 64);
  strncat(formattedTotal, responses[5], 1020);
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

  printf("Total length: %lu characters. ", strlen(formattedTotal));

  if (argc > 1){
    printf("File printed to %s \n", argv[1]);
  } else {
    printf("File printed to README.md \n");
  }

  return 0;
}