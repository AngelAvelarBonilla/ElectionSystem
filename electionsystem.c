// electionsystem.c
// CS211 Group Project:
//
// Election System Users can enter choice as per preference and
// can calculate total votes and leading candidate. Useful for
// small scale election projects.
//
// Collaborators:   Angel Avelar-Bonilla
//                  Aidan Murphey
//                  Joanna Santos
//                  David Witte
//

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define TOTALPOSSIBLECAN 20 // total possible candidates in the array
#define MAXSTRINGLENGTH 65  // maximum length of our strings
char candidate[TOTALPOSSIBLECAN][MAXSTRINGLENGTH]; // array that contains the string of candidate names
int voteCount[TOTALPOSSIBLECAN]; // array that contains the number of votes for each candidate
char positionName[MAXSTRINGLENGTH]; // name of position to be voted on ex 'President'
int numOfCandidates;  // number of candidates running in election
int totalVotesCast;   // total number of votes cast
char fileName[MAXSTRINGLENGTH]; // used for storing the name of the file we will be reading and writing to


// ------------------------------- File I/O ------------------------------- //

// Prompts user to load previous election results
// PRE: User has input 'i' and is attempting to import file
// POST:User has either provided an input file or has not
//      If user has input file then the file name is accepted
void pollUserForInputFileName(char userInputNameOfFile[], int* userInputNameLength) {
  int hasFile = 0;

  printf("Do you have a input file to supply? (1 = yes, 0 = no): ");
  scanf(" %d", &hasFile);
  getchar(); // consumes newline from scanf as it will affect our next input
  if (hasFile) {
    printf("Please enter the file name (Up to 64 characters): ");
    scanf(" %s", userInputNameOfFile);//file name is stored
    getchar(); //consumes newline from scanf
    (*userInputNameLength) = strlen(userInputNameOfFile);//Length of the name (0 by default)
                                                         //is set to the length of the input
                                                         //which will be used in the attemptToImportFile function
  }
}

// Write results of election to results.csv
// Information written to csv:
// Name of Position, ARRAY INDEX, Name of Candidate, Candidates Vote Count, Total Votes Casted, Total Num of Candidates
// PRE: User has casted vote
// POST: Current results of election are written to chosen file in format shown above
void saveResults() {
  FILE *fp;
  fp = fopen(fileName, "w");//opening file with only write permissions
  for (int i = 0; i < numOfCandidates; i++) {
      fprintf(fp, "%s,%d,%s,%d,%d,%d", positionName, i, candidate[i], voteCount[i], totalVotesCast, numOfCandidates);//writes to the file
      if (!(i == numOfCandidates -1 )) {//This prints a \n at the end of every line except for the last.
        fprintf(fp, "\n");              //We don't want the file to end with a newline b/c that messes up
      }                                 //the processing when the data is read in on program startup
  }
  fclose(fp);//closes the file
}

// Loads results from previous election, can continue election or view results.
// PRE: User has selected option 'i' and file name has been entered or has been defaulted to results.csv
// POST:File specified is open with read permissions and information from file has been loaded into current election
void readInResults() {
  FILE *fp;
  fp = fopen(fileName, "r");//opened with read permissions

  while (!feof(fp)) {//while we are not at the end of file
    int readNum, readVote, readTotal, readNumCan;
    char readCandidate[MAXSTRINGLENGTH];
    char readPosition[MAXSTRINGLENGTH];
    fscanf(fp, "%[^,],%d,%[^,],%d,%d,%d", &readPosition, &readNum, &readCandidate, &readVote, &readTotal, &readNumCan);
    strcpy(candidate[readNum], readCandidate);//copies candidate that was read in over to the respective index in candidate[]
    strcpy(positionName, readPosition);//copies the position the was read in over to the position name for the election
    voteCount[readNum] = readVote;//number of votes on current line is stored into voteCount[] at the respective index
    totalVotesCast = readTotal;
    numOfCandidates = readNumCan;
  }
}

//PRE: User has run the program and has selected option 'i'
//POST:A user selected file is read in, or the default results.csv is read in
void attemptToImportFile() {
  char userInputNameOfFile[MAXSTRINGLENGTH];
  int fileNameLength;
  int userInputNameLength = 0;

  pollUserForInputFileName(userInputNameOfFile, &userInputNameLength);
  if (userInputNameLength == 0) {//If a file name is not read in the default results.csv will be opened
    fileName[0] = 'r';
    fileName[1] = 'e';
    fileName[2] = 's';
    fileName[3] = 'u';
    fileName[4] = 'l';
    fileName[5] = 't';//C does not have strings, just null terminated char arrays so
    fileName[6] = 's';//we have to change "strings" this way
    fileName[7] = '.';
    fileName[8] = 'c';
    fileName[9] = 's';
    fileName[10] = 'v';
    fileName[11] = '\0';

    fileNameLength = 11;
  } else {
    for (int i = 0; i <= userInputNameLength; i++) {
      fileName[i] = userInputNameOfFile[i];//copy inputted or defaulted into fileName which will be used with readInResults()
    }
    fileNameLength = userInputNameLength;
    readInResults();
  }
}

// --------------------------- ELECTION SYSTEM --------------------------- //

// Print menu screen
void commandHelp() {
  puts("Help Menu (Format: Command - Description)");
  puts("----------");
  puts("h - Help Menu");
  puts("c - Create Election");
  puts("v - Cast Your Vote");
  puts("r - Show Results");
  puts("l - Show Leading Candidate");
  puts("i - Import Results from File");
  puts("e - Exit Program");
  puts("");
}

// Creates candidate string to be named.
void createCandidate () {
    char candidateName[MAXSTRINGLENGTH];
    for (int i = 0; i < numOfCandidates; i++) {
        printf("Please enter candidate name: ");
        fgets(candidateName, MAXSTRINGLENGTH, stdin);
        strtok(candidateName, "\n");                  // eliminates newline buffer
        printf("Candidate %s has been entered on the ballot.\n", candidateName);
        strcpy(candidate[i], candidateName); // inserts candidate string name into candidate array
    }
    puts("All candidates created. Ballot is now complete.");
}

// Creates position string to be voted on and how many total candidates there will be.
void createPosition() {
  printf("What is the name of the position for the election? ");
  fgets(positionName, MAXSTRINGLENGTH, stdin);
  strtok(positionName, "\n");                       // eliminates newline buffer
  printf("How many candidates are there? (min 2, max %d): ", TOTALPOSSIBLECAN);
  scanf("%d", &numOfCandidates);
  getchar();
  createCandidate();
}

void printBallot() {
  printf("----------- %s BALLOT ----------- \n", positionName);
  for (int i = 0; i < numOfCandidates; i++) {
    printf("%d\t%s\n", i, candidate[i] );
  }
}

// User to input number to vote for corresponding candidate.
// Keeps track of total votes cast and saves results to results.csv after -1.
void castVote(){
  int input;
  while (input != -1) {
        printBallot();
        printf("Enter the number to vote for candidate. Enter -1 to complete election. -> ");
        scanf("%d", &input);
        getchar();

        if (input != -1) {
          voteCount[input]++;
          totalVotesCast++;
          printf("\nCongrats you voted! \nTotal votes cast: %d", totalVotesCast);
        } else {
          puts("Election Complete!");
        }
        puts("\n----------------------------------------");
    }
  saveResults();
}

// Calculates and declares winner
void showResults() {
  int i;
  int max = voteCount[0]; // variable to keep track of who has highest vote total
  int pos = 0;            // variable to keep track for parallel array index
  float percentage;

  // loop that determines winning candidate
  for (i = 1; i < numOfCandidates; i++) {
    if (voteCount[i] > max) {
      pos = i;
      max = voteCount[i];
    }
  }
  percentage = (float)max / totalVotesCast * 100.0;
  puts("------- ELECTION RESULTS -------");
  printf("%s Candidate %s has won the election with %d votes out of the %d total votes casted. \n", positionName, candidate[pos], max, totalVotesCast);
  printf("They won %0.2f percent of votes.", percentage);

  puts("\n --- Complete Election Results ---");
  // loop that prints entire election results
  for (i = 0; i < numOfCandidates; i++) {
        printf("%s\t\t\tVotes: %d\n", candidate[i], voteCount[i]);
  }
}

// Prints leading candidate of election so far
void showLeadingCandidate()
{
    printf("\nLeading candidates for %s Election: \n", positionName);
    int i;
    int max = voteCount[0];
    int pos = 0;
    // loop that determines leading canidate in race so far (same as above)
    for (i = 1; i < numOfCandidates; i++) {
      if (voteCount[i] > max) {
        pos = i;
        max = voteCount[i];
      }
    }
    printf("%s Candidate %s is leading with %d votes. \n", positionName, candidate[pos], max);
    puts("\n----------");
}

void launchProgram () {
    char command = 'h'; //Default to 'help' so we can automatically show the user the help menu
  attemptToImportFile();

  //Main loop
  do {
    if (command == 'h') {
      commandHelp();
    } else if (command == 'c'){
      createPosition();
    } else if (command == 'r'){
      showResults();
    } else if (command == 'l'){
      showLeadingCandidate();
    } else if (command == 'i') {
      attemptToImportFile();
    } else if (command == 'v') {
      castVote();
    } else if (command == 'e') {
      puts("Have a wonderful day");
      break;
    }

    printf("Please enter a command: ");
    scanf("%c", &command);
    getchar();
    command = tolower(command);
  } while (1); //Never-ending expression in the while here because we want to break out after we process the goodbye message. This procesing happens at the beginning of the loop, not the end
}

int main() {
  launchProgram();
  return 0;
}
