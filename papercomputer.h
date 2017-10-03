/*
 * ======================================================
 *
 *       Filename:  papercomputer.h
 *
 *    Description: 
 *
 *        Version:  1.0
 *        Created:  25. mars 2017 kl. 23.02 +0100
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Christian Pujol (),
 *                  pujolchr@gmail.com
 *                  christian.pujol@etud.univ-paris8.fr
 * Student number:  15611221
 *
 * =====================================================
 */


#ifndef PAPERCOMPUTER_H
#define PAPERCOMPUTER_H

#define MEMORYSIZE 256
#define PRINTSTATE printf(" PC = %03d / 0x%02x | A = %03d / 0x%02x\n", machine -> pc, machine -> pc, machine -> registerA, machine -> registerA)
#define DEBUG(...) fprintf(stderr,  __VA_ARGS__)


typedef struct computer
{
    unsigned char pc;
    unsigned char registerA;
    unsigned char memory[MEMORYSIZE];
    FILE *in;
    FILE *out;
} computer;

typedef char *str;
typedef enum bool
{ false = 0, true = 1 } bool;


int runOne(computer *, unsigned char, unsigned char);
int loadBootstrap(computer *, unsigned int, unsigned char *);
int loadFile(computer *, str);

void runNfois(int N);

unsigned char BOOTSTRAP_DEFAULT[32];


extern char *yytext;

int yylex();                    // scanner prototype

#endif /* PAPERCOMPUTER_H */
