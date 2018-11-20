/**
 *  Badjessa(Romeo) B. Bahoumda
 *  CSE 271
 *  Goal: ltimately, develop a C program named bib.c that uses structures (with typedef) and malloc 
 *  (with sizeof) to allow users to build a bibliography reference file. Each bibliographic entry 
 *  should allow the user to enter the author or authors (single entry), title of the article,
 *  publication in which the article was printed, publisher, date of publication, and page or 
 *  pages in which the article appeared.
 *
 *  Current Submission: This submission does the same as the earlier however it allows the user to 
 *  search for a particular bib entry as well as create new entries on the command line
 **/
#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "bibFuncs.h"
#include <ctype.h>

//header node of the file structure
extern struct BibEntry_t *header;

//last element in the linkedlist
extern struct BibEntry_t *tail;
//Bibliography struct, where our bibliography would be stored
int parseArgs(int argc, char **argv);
int is_empty(char *s);
//command line options options table for our input
//Got the idea from StackOverFlow
//https://stackoverflow.com/questions/7489093/getopt-long-proper-way-to-use-it
static struct option long_options[] =
{
  {"s", required_argument, NULL, 's'},
  {"search", required_argument, NULL, 's'},
  {"h", no_argument, NULL, 'h'},
  {"help", no_argument, NULL, 'h'},
  {"v",no_argument, NULL, 'v'},
  {"verbose", no_argument, NULL, 'v'},
  {NULL,0,NULL,0}
};

int isVerbose = 0;
int hasOutput = 0;
int wantSearch = 0;
const char *fileName = "./bib.txt";
char *searchString = NULL;
//Parses the options given on the command
int parseArgs(int argc, char **argv)
{
  int ch;
  //Check for the command line options in the input
  while ((ch = getopt_long(argc, argv, "s:searchh:help:vverbose", long_options, NULL)) != -1)
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
	  searchString = optarg;
	  wantSearch = 1;
	  break;

	default:
	  exitHandler(99);
	  break;
	}

    }
  return 0;
}

//Gets the input and returns an error code of -1
char* getInput(int length, const char *prompt, int flag_required) {
  char *line = NULL;
  size_t size = length;
  fprintf(stdout, "Please Enter the %s: ", prompt);
  if (flag_required == 1) {
    int rc = getline(&line, &size, stdin);
    while (rc == -1 || is_empty(line) == 1) {
      fprintf(stdout, "Try agian, Please Enter the %s: ", prompt);
      rc = getline(&line, &size, stdin);
    }
  } else {
    getline(&line, &size, stdin);
  }
  return line;
}

int is_empty(char *s) {
  while(*s != '\0') {
    if (!isspace((unsigned char)*s)) {
      return 0;
    }
    s++;
  }
  return 1;
}

int main(int argc, char *argv[]){
  int check = 1;
  int mod = 0;
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
	if (wantSearch == 1)
	{
	  searchBib(searchString);
	  exitHandler(0);
	  return 0;
	}
	while(check) {
	  fprintf(stdout, "Commands:\n 1. c or C to create a new Bib Entry\n 2. s or S to search for a specific bib Entry\n 3. x or X to exit\n Input: ");
	  char * secInput = malloc(sizeof(char)*128);
	  scanf("%s", secInput);
	  if (strlen(secInput) > 1) {
	    fprintf(stdout, "Wrong input please enter your query and press Enter");
	    continue;
	  }
	  char input = secInput[0];
	  char finInput = tolower(input);
	  if(finInput == 'c') {
	    //Clearing the buffer before any manipulation
	    while((getchar()) != '\n');
	    
	    fprintf(stdout, "Please add the information below as it is prompted\n");
	    char *title = malloc(sizeof(char)*128);
	    char *author = malloc(sizeof(char)*64);
	    char *publication = malloc(sizeof(char)*32);
	    char *publisher = malloc(sizeof(char)*32);
	    char *date = malloc(sizeof(char)*11);
	    char *pages = malloc(sizeof(char)*32);
	    title = getInput(128, "Title", 1); //Requires some kind of input
	    author = getInput(64, "Author", 1); //Require some kind of input 
	    publication = getInput(32, "Publication", 0);
	    publisher = getInput(32, "Publisher", 0);
	    date = getInput(11, "Date in the format <YYYY-MM-DD>", 0);
	    if (!is_empty(date)) {
	      rc = dateCheck(date, 1);
	      while (rc != 0) {
		date = getInput(11, "Date in the format <YYYY-MM-DD>", 0);
		if (is_empty(date)){
		  break;
		} else {
		  rc = dateCheck(date, 1);
		}
	      }
	    } else {
	      const char * defaultDate = "0000-00-00\n";
	      strcpy(date, defaultDate);
	    } //Default input for dates
	    pages = getInput(16, "Pages", 0);
	    struct BibEntry_t *newEntry = malloc(sizeof(struct BibEntry_t));
	    newEntry = createBib(title, author, publication, publisher, date, pages);
	    tail->next = newEntry;
	    tail = newEntry;
	    mod = 1;
	    free(title);
	    free(author);
	    free(publication);
	    free(publisher);
	    free(pages);
	  }
	  else if (finInput == 's') {
	    //Clearing the buffer before any manipulation
	    while((getchar()) != '\n');
	    
	    fprintf(stdout, "What would you like to search for?\n");
	    char *search = malloc(sizeof(char)*128);
	    scanf("%s", search);
	    searchBib(search);	    
	  }
	  else if (finInput == 'x') {
	    if (mod == 1) {
	      //Printing the list of entry to file
	      printVerbose("Saving the modified version of bib.txt", isVerbose);
	      rc = printBib(header, isVerbose);
	    }
	    if (rc == 0)
	    {
	       //Free the space
	       printVerbose("Freeing the space allocated for the BibEntries...", isVerbose);
	       freeBib(header, isVerbose);
	       printVerbose("Successful operation...", isVerbose);
	    }
	     break;
	  } else {
	    fprintf(stdout, "Wrong input\n");
	  }
	  
	}
      }
    }
  }

  exitHandler(rc);
  return 0;
}

