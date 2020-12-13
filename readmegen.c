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
  strncat(formattedTotal, "# ", 3);
  strncat(formattedTotal, responses[0], 100);
  strncat(formattedTotal, "\n", 2);
  // table of contents
  strncat(formattedTotal, "## Table of Contents\n- [Description](#Description)\n- [Installation](#Installation)\n- [Usage](#Usage)\n- [License](#License)\n-[Questions](#Questions)\n\n\n", 175);
  // description
  strncat(formattedTotal, "## Description\n", 16);
  strncat(formattedTotal, responses[1], 253);
  strncat(formattedTotal, "\n", 2);
  // installation
  strncat(formattedTotal, "## Installation\n", 17);
  strncat(formattedTotal, responses[2], 253);
  strncat(formattedTotal, "\n", 2);
  // usage
  strncat(formattedTotal, "## Usage\n", 11);
  strncat(formattedTotal, responses[3], 253);
  strncat(formattedTotal, "\n", 2);
  // license
  strncat(formattedTotal, "## License\n", 12);
  strncat(formattedTotal, "![License](https://img.shields.io/badge/license-", 49);

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
  strncat(formattedTotal, "-blue)\n\n", 10);
  // questions
  strncat(formattedTotal, "## Questions\n", 14);
  strncat(formattedTotal, "Any questions on this or other projects can be directed to ", 64);
  strncat(formattedTotal, responses[5], 253);
  strncat(formattedTotal, "\n", 2);
  // github
  trim(responses[6]);
  strncat(formattedTotal, "## More Of My Projects\nFind more of my work on [my GitHub](https://github.com/", 85);
  strncat(formattedTotal, responses[6], 40);
  strncat(formattedTotal, ")\n", 3);

  // write the file
  write(fd, formattedTotal, 1000);

  //check to make sure file was created
  fd = open("README.md", O_RDONLY);
  if (fd == -1) {
    printf("ERROR: Failed to open and read file.\n");
    exit(1);
  }
  read(fd, buf, 4096);
  buf[4095] = '\0';
  close(fd);
  printf("buf: %s\n", buf);

  return 0;
}