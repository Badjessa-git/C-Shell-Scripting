/**
 *  Badjessa(Romeo) B. Bahoumda
 *  CSE 271
 *  Goal: ltimately, develop a C program named bib.c that uses structures (with typedef) and malloc 
 *  (with sizeof) to allow users to build a bibliography reference file. Each bibliographic entry 
 *  should allow the user to enter the author or authors (single entry), title of the article,
 *  publication in which the article was printed, publisher, date of publication, and page or 
 *  pages in which the article appeared.
 *
 *  Current Submission: This submission will open a bib.tt file, read the entries into dynamically 
 *  allocated structures, and print all strcutures contents to STDOUT, free memory and exit
 **/
#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "bibFuncs.h"

//header node of the file structure
extern struct BibEntry_t *header;

//Bibliography struct, where our bibliography would be stored
int parseArgs(int argc, char **argv);

//command line options options table for our input
//Got the idea from StackOverFlow
//https://stackoverflow.com/questions/7489093/getopt-long-proper-way-to-use-it
static struct option long_options[] =
{
  {"s", required_argument, NULL, 's'},
  {"space", required_argument, NULL, 's'},
  {"h", no_argument, NULL, 'h'},
  {"help", no_argument, NULL, 'h'},
  {"v",no_argument, NULL, 'v'},
  {"verbose", no_argument, NULL, 'v'},
  {NULL,0,NULL,0}
};

int isVerbose = 0;
int hasOutput = 0;
char * fileName = "./bib.txt";
int numSpace = 0;
//Parses the options given on the command
int parseArgs(int argc, char **argv)
{
  int ch;
  //Check for the command line options in the input
  while ((ch = getopt_long(argc, argv, "s:space:hhelpvverbose", long_options, NULL)) != -1)
    {
      switch(ch)
	{
	  //if the optional tag is verbose make isVerbose true
	case 'v':
	  isVerbose = 1;
	  break;

	case 'h':
	  printUsage();
	  exit(0);
	  break;

	case 's':
	  numSpace = atoi(optarg);
	  if (numSpace > 9) {
	    exitHandler(22);
	  } else if (numSpace < 0) {
	    exitHandler(21);
	  }
	  break;

	default:
	  exitHandler(99);
	  break;
	}

    }
  return 0;
}


int main(int argc, char *argv[]){
  //parsing arguments
  int rc = parseArgs(argc, argv);
  if (rc == 0)
  {
    printVerbose("Successfully parsed argument", isVerbose);
    //Find the bib.txt file and  alos handles possible errors
    rc = findFile(fileName, isVerbose); 
    if (rc == 0)
    {
      //read the bib.txt file and creates the bib, files
      rc = readBibFile(fileName, isVerbose);
      if (rc == 0)
      {
	//Printing the list of entry
	rc = printBib(header, 0, numSpace, isVerbose);
	if (rc == 0)
	{
	  //Free the space 
	  printVerbose("Freeing the space allocated for the BibEntries...", isVerbose);
	  freeBib(header, 0, isVerbose);
	  printVerbose("Successful operation...", isVerbose);
	}
      }
    }
  }

  exitHandler(rc);
  return 0;
}

