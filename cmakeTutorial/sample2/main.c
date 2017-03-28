#include <stdio.h>
#include <libgen.h>
#include <crypt.h>


static void usage(char *pg)
{
  fprintf(stderr, "Usage: %s word_to_crypt\n", basename(pg));
} // usage


int main(int ac, char *av[])
{
char *pCrypt;

  (void)ac;
  (void)av;

  if (ac != 2)
  {
    usage(av[0]);
    return 1;
  }

  pCrypt = crypt(av[1], "ab");

  printf("Project2 : word '%s' is encrypted as '%s'\n", av[1], pCrypt);

  return 0;
} // main

