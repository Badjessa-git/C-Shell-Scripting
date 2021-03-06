/**
 *  Badjessa B. Bahoumda
 *  CSE 271
 *  Header File
 */

#ifndef BIBFUNCS_H
#define BIBFUNCS_H "bibFuncs.h"

struct BibEntry_t
{
  char * author;
  char * title;
  char * publication;
  char * publisher;
  char * date;
  char * pages;
  struct BibEntry_t *next;
};

//Check if the file given is valid, nonempty as well as readable
int findFile(char *fileName, int isVerbose);

//Read the bib.txt file and make calls to create bib in order to
//create a new BibEntry_t
int readBibFile(char *fileName, int isVerbose);

//print the current BibEntry_t
int printBib(struct BibEntry_t *curEntry, int mode, int space, int isVerbose);

//Free the allocated space for the cur BibEntry
int freeBib(struct BibEntry_t *curEntry, int mode, int isVerbose);

//PrintVerbose
void printVerbose(char *message, int isVerbose);

//handles the potenetial error for exit
void exitHandler(int code);

//Usage, shows the help for the usesr
void printUsage();

#endif 
