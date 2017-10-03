/*
 * ========================================================
 *
 *       Filename:  papercomputer.c
 *
 *
 *         Author:  Christian Pujol (),
 *                  pujolchr@gmail.com
 *                  christian.pujol@etud.univ-paris8.fr
 * Student number:  15611221
 *
 * =======================================================
 */

#include    <stdio.h>
#include    <stdlib.h>
#include    "papercomputer.h"

unsigned char BOOTSTRAP_DEFAULT[32] =
    { 0x49, 0x20, 0x49, 0x22, 0x40, 0x20, 0x48, 0x21,
    0xC9, 0x21, 0x40, 0x22, 0x21, 0x01, 0x12, 0x1F,
    0x48, 0x22, 0x40, 0x21, 0x20, 0x01, 0x10, 0x06,
    0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10
};

/* ===  FUNCTION  runOne ===================================== */
int
runOne(computer * machine, unsigned char instruction, unsigned char V)
{
    unsigned int readed;

    switch (instruction) {

        /* Arithmetique */
    case 0x20:
        machine->registerA += V;
        break;
    case 0x60:
        machine->registerA += machine->memory[V];
        break;
    case 0xE0:
        machine->registerA += machine->memory[machine->memory[V]];
        break;
    case 0x21:
        machine->registerA -= V;
        break;
    case 0x61:
        machine->registerA -= machine->memory[V];
        break;
    case 0xE1:
        machine->registerA -= machine->memory[machine->memory[V]];
        break;

        /* Logique */
    case 0x22:
        machine->registerA = ~(machine->registerA & V);
        break;
    case 0x62:
        machine->registerA = ~(machine->registerA & machine->memory[V]);
        break;
    case 0xE2:
        machine->registerA =
            ~(machine->registerA & machine->memory[machine->memory[V]]);
        break;

        /* Transfer */
    case 0x00:
        machine->registerA = V;
        break;
    case 0x40:
        machine->registerA = machine->memory[V];
        break;
    case 0xC0:
        machine->registerA = machine->memory[machine->memory[V]];
        break;
    case 0x48:
        machine->memory[V] = machine->registerA;
        break;
    case 0xC8:
        machine->memory[machine->memory[V]] = machine->registerA;
        break;

        /* I/O  */
    case 0x49:
        printf("in ? ");
        scanf("%x", &readed);
        machine->memory[V] = (unsigned char) readed;
        break;
    case 0xC9:
        printf("in ? ");
        scanf("%x", &readed);
        machine->memory[machine->memory[V]] = (unsigned char) readed;
        break;
    case 0x41:
        printf("out: 0x%02x\n", machine->memory[V]);
        printf("\n");
        break;
    case 0xC1:
        printf("out: 0x%02x\n",
                machine->memory[machine->memory[V]]);
        break;

        /* Jump  */
    case 0x10:
        machine->pc = V;
        break;
    case 0x11:
        if (machine->registerA < 0)
            machine->pc = V;
        break;
    case 0x12:
        if (machine->registerA == 0)
            machine->pc = V;
        break;
    default:
        fprintf(stderr, "Instruction not found.\n");
        exit(1);
    }
    return 0;
}

/* -----  end of function runOne  ----- */


/* ===  FUNCTION  loadBootstrap ============================== */
int
loadBootstrap(computer * machine, unsigned int length,
              unsigned char * bootstrap)
{
    int i;
    for (i = 0; i < 32; i++) {
        machine->memory[i] = *(bootstrap + i);
    }
    return 1;
}

/* -----  end of function loadBootstrap  ----- */

/* ===  FUNCTION  loadFile =============================== */

int
loadFile(computer * machine, str filename)
{
    FILE *image = fopen(filename, "r");

    if (image == NULL) {
        perror(filename);
        return 1;
    }

    int addresse;
    unsigned int readed;

    while (true) {
        if (fscanf(image, "%x", &addresse) == EOF)
            break;
        if (fscanf(image, "%x", &readed) == EOF)
            break;
        else *((machine -> memory) + addresse) = (unsigned char) readed;
    }
    return 0;
}

/* -----  end of function loadBootFile  ----- */
