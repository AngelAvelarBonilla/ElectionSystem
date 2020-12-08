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
#define MAXSTRINGLENGTH 65  
char candidate[TOTALPOSSIBLECAN][MAXSTRINGLENGTH]; // array that contains the string of candidate names
int voteCount[TOTALPOSSIBLECAN]; // array that contains the number of votes for each candidate
char positionName[MAXSTRINGLENGTH]; // name of position to be voted on ex 'President'
int numOfCandidates;  // number of candidates running in election
int totalVotesCast; 
char fileName[MAXSTRINGLENGTH];\


// ------------------------------- File I/O ------------------------------- //

// Prompts user to load previous election results
void pollUserForInputFileName(char userInputNameOfFile[], int* userInputNameLength) {
  int hasFile = 0;

  printf("Do you have a input file to supply? (1 = yes, 0 = no): ");
  scanf(" %d", &hasFile);
  getchar(); // consumes newline from scanf
  if (hasFile) {
    printf("Please enter the file name (Up to 64 characters): ");
    scanf(" %s", userInputNameOfFile);
    getchar();
    (*userInputNameLength) = strlen(userInputNameOfFile);
  }
}

// Write results of election to results.csv
// Information written to csv:
// Name of Position, ARRAY INDEX, Name of Candidate, Candidates Vote Count, Total Votes Casted, Total Num of Candidates
void saveResults() {
  FILE *fp;
  fp = fopen(fileName, "w");
  for (int i = 0; i < numOfCandidates; i++) {
      fprintf(fp, "%s,%d,%s,%d,%d,%d", positionName, i, candidate[i], voteCount[i], totalVotesCast, numOfCandidates);
      //This prints a \n at the end of every line except for the last. 
      //We don't want the file to end with a newline b/c that messes up the processing when the data is read in on program startup
      if (!(i == numOfCandidates -1 )) {
        fprintf(fp, "\n");
      }
  }
  fclose(fp);
}

// Loads results from previous election, can continue election or view results.
void readInResults() {
  FILE *fp;
  fp = fopen(fileName, "r");

  while (!feof(fp)) {
    int readNum, readVote, readTotal, readNumCan;
    char readCandidate[MAXSTRINGLENGTH];
    char readPosition[MAXSTRINGLENGTH];
    fscanf(fp, "%[^,],%d,%[^,],%d,%d,%d", &readPosition, &readNum, &readCandidate, &readVote, &readTotal, &readNumCan);
    strcpy(candidate[readNum], readCandidate);
    strcpy(positionName, readPosition);
    voteCount[readNum] = readVote;
    totalVotesCast = readTotal;
    numOfCandidates = readNumCan;
  }
}

void attemptToImportFile() {
  char userInputNameOfFile[MAXSTRINGLENGTH];
  int fileNameLength;
  int userInputNameLength = 0;

  pollUserForInputFileName(userInputNameOfFile, &userInputNameLength);
  if (userInputNameLength == 0) {
    fileName[0] = 'r';
    fileName[1] = 'e';
    fileName[2] = 's';
    fileName[3] = 'u';
    fileName[4] = 'l';
    fileName[5] = 't';
    fileName[6] = 's';
    fileName[7] = '.';
    fileName[8] = 'c';
    fileName[9] = 's';
    fileName[10] = 'v';
    fileName[11] = '\0';

    fileNameLength = 11;
  } else {
    for (int i = 0; i <= userInputNameLength; i++) {
      fileName[i] = userInputNameOfFile[i];
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
