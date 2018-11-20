/**
 *  Badjessa B. Bahoumda
 *  CSE 271
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "bibFuncs.h"
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <ctype.h>

struct BibEntry_t *header;
struct BibEntry_t *tail;
int first = 0;
int lineNum = 1;
int lastBib = 1;
//Planning to use the access functions to check the different
//permsission and return 0 only if the file is present nonempty and readable
int findFile(const char *fileName, int isVerbose)
{
  errno = 0;
  if (access(fileName, R_OK) == 0 && access(fileName, W_OK) == 0)
  {
    FILE *fp;
    if (((fp=fopen(fileName, "r")) != NULL))
      {
	printVerbose("Found bib.txt", isVerbose);

	//Check for the size of File
	fseek(fp, 0, SEEK_END);
	int size = ftell(fp);
	printVerbose("Checking if file is empty...", isVerbose);
	if (0 == size) {
	  fclose(fp);
	  exitHandler(21);
	}
	printVerbose("File is not empty...", isVerbose);
	//retrun to begeining of file
	fseek(fp, 0, SEEK_SET);

	fclose(fp);
      return 0;
      }
    
    else
    {
      exitHandler(10);
    }
	
  }
  else
  {
    switch(errno) {
      case EACCES:
      case EROFS:
	   exitHandler(20);
	   break;

      case ENOENT:
	   exitHandler(20);
           break;
    }
    return -1;
  }
  return 0;
}

//Allocate space for a new BibEntry and set the pointer to the next
//Entry to null
struct BibEntry_t *createBib(char *curTitle, char *curAuthor, char *curPublication, char *curPublisher, char *curDate, char *curPages) {
  struct BibEntry_t *newBib = malloc(sizeof(struct BibEntry_t));
  if (strlen(curTitle) > 0) {
    newBib->title = malloc(strlen(curTitle));
    strcpy(newBib->title, curTitle);
  }

  if (strlen(curAuthor) > 0) {
    newBib->author = malloc(strlen(curAuthor));
    strcpy(newBib->author, curAuthor);
  }

  if (strlen(curPublication) > 0) {
    newBib->publication = malloc(strlen(curPublication));
    strcpy(newBib->publication, curPublication);
  }

  if (strlen(curPublisher) > 0) {
    newBib->publisher = malloc(strlen(curPublisher));
    strcpy(newBib->publisher, curPublisher);
  }

  if (strlen(curDate) > 0) {
    newBib->date = malloc(strlen(curDate));
    strcpy(newBib->date, curDate);
  }
  
  if (strlen(curPages) > 0) {
    newBib->pages = malloc(strlen(curPages));
    strcpy(newBib->pages, curPages);
  }
  
  newBib->next = NULL;
  if (newBib->title == NULL || newBib->author == NULL ) {
    fprintf(stdout, "Missing a Title or Author or Both in the bibliography starting at line %d\n", lastBib);
    freeBib(newBib, 0);
    exitHandler(22);
  }
  return newBib;
}

///Returns the index at which we should start reading the line
int getIndex(int start_index, char* line) {
  int index = start_index;
  while (line[index] == ' ') {
    index++;
  }
  return index;
}

int dateCheck(char *possibleInput, int input) {
  if (strlen(possibleInput) == 11) {//1 more character for the \n
    int i = 0;
    while(i < 10) {
      if (i == 4 || i == 7) {
	if (!(possibleInput[i] == '-')) {
	  if (input == 0) {
	     fprintf(stderr, "Invalid date format at line %d, please input your date as <YYYY-M\
M-DD>\n", lineNum);
	  } else {
	    fprintf(stderr, "Invalid date format\n");
	  }	 
          return 22;
	}
      } else {
	if (!isdigit(possibleInput[i])) {
	  if (input == 0) {
	    fprintf(stderr, "Invalid date format at line %d, please input your date as <YYYY-M\
M-DD>\n", lineNum);
	  } else {
	    fprintf(stderr, "Invalid date format\n");
	  }
	  return 22;
	}
      }
      ++i;
    }
    return 0;
  }
  else {
    if (input == 0) {
      fprintf(stderr, "Invalid date format at line %d, please input your date as <YYYY-MM-DD>\\
n", lineNum);
    } else {
      fprintf(stderr, "Invalid date format\n");
    }
    return 22;
  }

}

//Read the bib file and create BibEntry by calling the bibEntry functions
int readBibFile(const char *fileName, int isVerbose)
{
  int first = 0;
  FILE *fp;
  if (((fp=fopen(fileName, "r")) != NULL))
    {
      size_t len = 140;
      ssize_t read;
      char * line = NULL;

      char *curTitle = malloc(128*sizeof(char));
      char *curAuthor = malloc(64*sizeof(char));
      char *curPublication = malloc(32*sizeof(char));
      char *curPublisher = malloc(32*sizeof(char));
      char *curDate = malloc(11*sizeof(char));
      char *curPages = malloc(16*sizeof(char));
      
      struct BibEntry_t *curEntry;
      while ((read = getline(&line, &len, fp)) != -1)
      {      
	int index = 0;
	if (strstr(line, "Title:") != NULL)
	{
	  lineNum++;
	  index = getIndex(6, line);
	  strncpy(curTitle, line+index, 127);
	}
	else if (strstr(line, "Author:") != NULL)
        {
	  lineNum++;
	  index = getIndex(7, line);
	  strncpy(curAuthor, line+index, 63);
	  
	}
	else if (strstr(line, "Publication:") != NULL)
        {
	  lineNum++;
	  index = getIndex(12, line);
          strncpy(curPublication, line+index, 32);
	    
	}
	else if (strstr(line, "Publisher:") != NULL)
        {
	  lineNum++;
	  index = getIndex(10, line);
	  strncpy(curPublisher, line+index, 16);
	  
	}
	else if (strstr(line, "Date:") != NULL)
        {
	  lineNum++;
	  index = getIndex(5, line);
	  char *possibleInput = malloc(sizeof(char)*11);
	  strncpy(possibleInput, line+index, 11);
	  int rc = dateCheck(possibleInput, 0);
	  if (rc == 0) {
	      strcpy(curDate, possibleInput);
	  } else {
	    exitHandler(rc);
	  }
	  free(possibleInput);
	}
	else if (strstr(line, "Pages:") != NULL)
        {
	  lineNum++;
	  index = getIndex(6, line);
	  strncpy(curPages, line+index, 11);
	  
        }
	else if (strstr(line, ";") != NULL)
        {
	  lastBib = lineNum-1;  	    
	  printVerbose("Creating new BibEntry..." , isVerbose);
	  //if header does not exist, create the first bibEntry
	  if (first == 0) {
	    header = curEntry = malloc(sizeof(struct BibEntry_t));
	    header = createBib(curTitle, curAuthor, curPublication, curPublisher, curDate, curPages);
	    curEntry =  header;
	    first = 1;
	  }
	  //else create a nextNode, assign a point from header(curNode
	  //to it) and move header pointer to that current node
	  else {
	    curEntry->next = malloc(sizeof(struct BibEntry_t));
	    curEntry->next = createBib(curTitle, curAuthor, curPublication, curPublisher, curDate, curPages);
	    curEntry = curEntry->next;
	    tail = curEntry;
	  }
	  strcpy(curTitle, "");
	  strcpy(curAuthor, "");
	  strcpy(curPublication, "");
	  strcpy(curPublisher, "");
	  strcpy(curDate, "");
	  strcpy(curPages, "");
	}
	else
        {
	  exitHandler(22);
	}
      }
      if (line) {
	  free(line);
      }
      free(curTitle);
      free(curAuthor);
      free(curPublication);
      free(curPublisher);
      free(curDate);
      free(curPages);
      return 0;
   }
  exitHandler(22);
  return -1;
}

//turn the string into lowercase
char* toLowerCase(char *str) {
  int i = 0;
  while(str[i] != '\0') {
      str[i] = tolower(str[i]);
      i++;
  }
  str[i+1] = '\0';
  return str;
}

//Search the LinkedList for the possible substring
void searchBib(char *input) {
  int numEntry = 1;
  char *substring = toLowerCase(input);
  struct BibEntry_t* curNode =  header;
  while(curNode != NULL) {
    //Allocate strings which we will then manipulate to get our search
    //results
    //Previous attempts showed that using actuall curNode->* would modify
    //the struct
    char *title = malloc(sizeof(curNode->title));
    strcpy(title, curNode->title);
    title = toLowerCase(title);
    
    char *author = malloc(sizeof(curNode->author));
    strcpy(author, curNode->author);
    author =  toLowerCase(author);

    char *publication = malloc(sizeof(curNode->publication));
    strcpy(publication, curNode->publication);
    publication = toLowerCase(curNode->publication);

    char *publisher = malloc(sizeof(curNode->publisher));
    strcpy(publisher, curNode->publisher);
    publisher =  toLowerCase(curNode->publisher);

    if (strstr(title, substring) != NULL
	|| strstr(author, substring) != NULL
	|| strstr(publication, substring) != NULL
	|| strstr(publisher, substring) != NULL)
    {
      fprintf(stdout, "%d result(s)\n", numEntry);
      fprintf(stdout, "Title: %s", curNode->title);
      fprintf(stdout, "Author: %s", curNode->author);
      fprintf(stdout, "Publication: %s", curNode->publication);
      fprintf(stdout, "Publisher: %s", curNode->publisher);
      fprintf(stdout, "Date: %s", curNode->date);
      fprintf(stdout, "Pages: %s", curNode->pages);
      fprintf(stdout, "\n");
      ++numEntry;
    }

    free(title);
    free(author);
    free(publication);
    free(publisher);
    curNode = curNode->next;
  }

  if (numEntry == 1) {
    fprintf(stdout, "no BibEntry found with the keywords %s\n", substring);
  }
}

//Prints the current bibEntry
//Implemented recursively, print the curEntry, check that there is a
//next entry and go to it to print it out
int printBib(struct BibEntry_t *curEntry, int isVerbose) {
  printVerbose("Printing all the BibEntries...", isVerbose);
  struct stat *fileStat = malloc(sizeof(struct stat)); //check if file exists;
  const char *oldName = "bib.txt";
  const char *newName = "bib.txt.old";
  int rc;
  if ((rc = stat(newName, fileStat)) ==  0) {
    printVerbose("Found existing version of bib.txt.old...deleting", isVerbose);
    int status = remove(newName);
    if (status != 0) {
      printVerbose("Error deleting file", isVerbose);
      exitHandler(99);
    }
    printVerbose("Successfully deleted", isVerbose);
  }
  
  int ret = rename(oldName, newName);

  if (ret) {
    printVerbose("error renaming bib.txt", isVerbose);
    exitHandler(99);
  }
  
  FILE *fp;
  errno = 0;
  printVerbose("Creating a new Bib.txt", isVerbose);
  if ((fp = fopen("bib.txt", "r")) == NULL) {
    fp=fopen("bib.txt", "w+");
    printVerbose("Successfully created a new bib.txt...\n Copying Bib Entries...", isVerbose);
    while (curEntry != NULL)
    {
      if (curEntry->title != NULL)
	fprintf(fp, "Title: %s", curEntry->title);

      if (curEntry->author != NULL)
	fprintf(fp, "Author: %s", curEntry->author);

      if (curEntry->publication != NULL)
	fprintf(fp, "Publication: %s", curEntry->publication);

      if (curEntry->publisher != NULL)
	fprintf(fp, "Publisher: %s", curEntry->publisher);

      if (curEntry->date != NULL)
	fprintf(fp, "Date: %s", curEntry->date);

      if (curEntry->pages != NULL)
	fprintf(fp, "Pages: %s", curEntry->pages);

      fprintf(fp, ";\n");
      curEntry = curEntry->next;
    }
  } else {
    exitHandler(99);
  }
  printVerbose("Successfuly copied the files", isVerbose);
  return 0;
}

//Free the space allocated for the current bibEntry
int freeBib(struct BibEntry_t *curEntry, int isVerbose) {
  if (curEntry != NULL)
  {
  if (isVerbose) {
    fprintf(stdout, "freeing BibEntry %s", curEntry->title);
  }
  free(curEntry->title);
  free(curEntry->author);
  free(curEntry->publication);
  free(curEntry->publisher);
  free(curEntry->date);
  free(curEntry->pages);
  if (curEntry->next != NULL)
    freeBib(curEntry->next, isVerbose);
  free(curEntry);
  }
  return 0;
}

//Check if the flag is set and then print
void printVerbose(const char* message, int isVerbose) {
  if (isVerbose)
    fprintf(stdout, "%s\n", message);

}

void printUsage() {
    printf("Usage: bib <COMMAND_LINE_OPTIONS> <ARGS>\n");
    printf("-s, --search <search_string>      run program searching for the specific string and exit\n");
    printf("-h, --help   <no_argument> shows how to use program\n");
    printf("-v. --verbose <no_argument> shows output\n");
}

//Handles error and exit
void exitHandler(int code) {
  switch(code) {
     case 0:
        fprintf(stdout, "successful execution, no errors\n");
        break;

     case 1:
        printUsage();
        break;

     case 20:
        fprintf(stderr, "bib.txt is present but not readable or accessible\n");
        break;

     case 21:
        fprintf(stderr, "bib.txt is empty\n");
        break;

     case 22:
       fprintf(stderr, "bib.txt is present, but could not be read\n");
       break;
       
     case 10:
        fprintf(stderr, "bib.txt does not exist\n");
	break;
	
     case 99:
        fprintf(stderr, "invalid or missing argument\n");
        break;

     default:
        fprintf(stderr, "Some uninditified error occured\n");
  }

  fprintf(stdout, "Exit Code: %d\n", code);
  exit(code);
}
