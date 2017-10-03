hexd  0x[0-9a-fA-F]{2}
number   [[:digit:]]+
file [a-zà-9.+

%x RUN
%x SET
%x PRINT 
%x SETMEM
%x SETPC
%x SETA
%x LOAD

%option caseless

%{

    #include    "papercomputer.h"
    void runNfois(int N);
    extern computer * machine;
    int memcell;
%}

%%

<*>[ \t]+       {;}


^l |
^load     {BEGIN(LOAD);}

^r |
^run      {BEGIN(RUN);}

^s |
^set      {BEGIN(SET);}

^p |
^print    {BEGIN(PRINT);}

^quit |
^q |
^exit     {return 0;}

{number}$ {
                 runNfois(strtol(yytext, NULL, 10));
                }


%{/*########### PRINT STATE #######*/%}
<PRINT>{hexd}   {
                 int mem = strtol(yytext, NULL, 16);
                 printf("MEM 0x%02x | %03d: 0x%02x | %d\n", mem, mem, machine -> memory[mem], machine -> memory[mem]);
                 BEGIN(INITIAL);
                }
<PRINT>{number} {
                 int mem = strtol(yytext, NULL, 10);
                 printf("MEM 0x%02x | %03d: 0x%02x | %d\n", mem, mem, machine -> memory[mem], machine -> memory[mem]);
                 BEGIN(INITIAL);
}
<PRINT>mem      {
                 int i,j,k;
                 for (j=0; j < 32; j++) {
                     for (i=0; i < 8; i++){
                         k = j * 8 + i; 
                         printf("| 0x%02x : 0x%02x -  %4d |", k, machine -> memory[k], machine -> memory[k]);
                     }
                     printf("\n");
                 }
                 BEGIN(INITIAL);
                }

<PRINT>pc       {
                 printf("PC: 0x%02x - %03d \n", machine->pc, machine->pc );
                 BEGIN(INITIAL);
                }

<PRINT>state |
<PRINT>s        {
                 printf("PC = 0x%02x - %03d - A = 0x%02x - %03d\n",machine -> pc, machine -> pc, machine -> registerA, machine -> registerA);
                 BEGIN(INITIAL);
                }

<PRINT>a        {
                 printf("A: 0x%02x - %03d\n", machine -> registerA, machine -> registerA);
                 BEGIN(INITIAL);
                }

<PRINT>.        {
                 BEGIN(INITIAL);
                }

%{/*########### RUN STATE #######*/%}

<RUN>{number}$  {
                 runNfois(strtol(yytext, NULL, 10));
                }
 
<RUN>.          {;}
<RUN>\n         {
                 BEGIN(INITIAL);
                }

%{/*########### SET STATE #######*/%}

<SET>pc         {
                 BEGIN(SETPC);
                }

<SET>a          {
                 BEGIN(SETA);
                }
<SET>{hexd}     {
                 memcell = strtol(yytext, NULL, 16);
                 BEGIN(SETMEM);
                }
<SET>{number}   {
                 memcell = strtol(yytext, NULL, 10);
                 BEGIN(SETMEM);
                }
<SET>.          {
                 BEGIN(INITIAL);
                }

%{/*########### SETPC STATE #######*/%}
<SETPC>{hexd}   {
                 int hex = strtol(yytext, NULL, 16);
                 printf("set PC to 0x%02x - %03d\n", hex, hex);
                 machine -> pc = hex;
                 BEGIN(INITIAL);
                }
<SETPC>{number} {
                 int hex = strtol(yytext, NULL, 10);
                 printf("set PC to 0x%02x - %03d\n", hex, hex);
                 machine -> pc = hex;
                 BEGIN(INITIAL);
                }
<SETPC>.        {
                 BEGIN(INITIAL);
                }

%{/*########### SETA STATE #######*/%}
<SETA>{number}  {
                 int value = strtol(yytext, NULL, 10);
                 printf("set A to 0x%02x - %d\n", value, value);
                 BEGIN(INITIAL);
                }
<SETA>{hexd}    {
                 int value = strtol(yytext, NULL, 16);
                 printf("set A to 0x%02x - %d\n", value, value);
                 BEGIN(INITIAL);
                }

<SETA>.         {
                 BEGIN(INITIAL);
                }

%{/*########### LOAD MEMORY IMAGE ##*/%}

<LOAD>[^\t\n ]+ {
                 printf("load :%s:\n", yytext);                
                 if (loadFile(machine, yytext))
                     printf("memory image not loaded\n");
                 else 
                     printf("memory image loaded\n");
                 BEGIN(INITIAL);
                }

%{/*########### SETMEM STATE #######*/%}
<SETMEM>{hexd}  {
                 int value = strtol(yytext, NULL, 16);
                 printf("set memcell 0x%02x - %03d to 0x%02x - %d\n", memcell, memcell, value, value); 
                 machine -> memory[memcell] = value;
                 BEGIN(INITIAL);
                }
<SETMEM>{number} {
                 int value = strtol(yytext, NULL, 10);
                 printf("set memcell 0x%02x - %03d to 0x%02x - %d\n", memcell, memcell, value, value); 
                 machine -> memory[memcell] = value;
                 BEGIN(INITIAL);
                }
<SETMEM>.       {
                 BEGIN(INITIAL);
                }

<*>\n           {
                printf("stepper> ");
                }
.   {;}
%%
