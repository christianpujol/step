
#include    <stdlib.h>
#include    <stdio.h>
#include    <unistd.h>

#include    "papercomputer.h"

char *USAGE = "usage: %s [OPTION]\n"
  "    -h           display this help.\n"
  "    -i <file>    use this file to load memory image.\n"
  "    -n number    set PC using decimal notation.\n"
  "    -x number    set PC using hexadecimal notation.\n";

computer PC;
computer *machine = &PC;
int step = 0;

/* ===  MAIN  ================================================ */
int
main (int argc, char *argv[])
{
  int opt;
  /*  load bootstrap */
  loadBootstrap (machine, 32, BOOTSTRAP_DEFAULT);

  /*   init machine  */
  machine->pc = 0;

  while ((opt = getopt (argc, argv, "hx:d:i:")) != -1)
    {
      switch (opt)
	{

	  /* option h : display help  */
	case 'h':
	  printf (USAGE, argv[0]);
	  exit (0);

	  /* load memoryimage from file */
	case 'i':
	  if (loadFile (machine, optarg)) exit(1);
	  break;

	  /*  set PC */
	case 'd':
	  machine->pc = strtol (optarg, NULL, 10);
	  break;
	case 'x':
	  machine->pc = strtol (optarg, NULL, 16);
	  break;

	case '?':
	  exit (1);

	case ':':
	  exit (1);
	}
    }


  /* run machine */
  printf ("stepper> ");

  while (yylex ());

  return EXIT_SUCCESS;
}

/* -----  end of function main  ----- */

/* ===  FUNCTION  runNfois ===================
 *  Description:  
 * ================================================= */

void
runNfois (int N)
{
  extern computer *machine;
  unsigned int instruction, V, i;

  for (i = 0; i < N; i++)
    {

      step++;

      printf ("\n############### step %d\n", step);

      printf ("PC = 0x%02x | %03d | A = 0x%02x | %03d\n ",
	      machine->pc, machine->pc, machine->registerA,
	      machine->registerA);

      instruction = machine->memory[machine->pc];
      machine->pc++;
      V = machine->memory[machine->pc];
      machine->pc++;

      runOne (machine, instruction, V);

      printf ("instruction : 0x%02x | V = 0x%02x | %03d\n", instruction, V,
	      V);
      printf ("############### step %d\n\n", step);
    }
}

/* -----  end of function runNfois  ----- */
