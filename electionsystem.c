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

#define TOTALPOSSIBLECAN 20 
#define MAXSTRINGLENGTH 65
char candidate[TOTALPOSSIBLECAN][MAXSTRINGLENGTH]; // array that contains the string of candidate names
char positionName[TOTALPOSSIBLECAN][MAXSTRINGLENGTH]; 
int voteCount[TOTALPOSSIBLECAN]; // array that contains the number of votes for each candidate
char name[MAXSTRINGLENGTH]; // name of position to be voted on ex 'President'
int numOfCandidates;  // number of candidates running in election

//int fileNameLength = 0;

// void pollUserForInputFileName(char userInputNameOfFile[], int* userInputNameLength) {
//   int hasFile = 0;

//   printf("Do you have a input file to supply? (1=yes, 0=no): ");
//   scanf(" %d", &hasFile);

//   if (hasFile) {
//     printf("Please enter the file name (Up to 64 characters): ");
//     scanf(" %s", userInputNameOfFile);
//     (*userInputNameLength) = strlen(userInputNameOfFile);
//   }
// }

void commandHelp() {
  puts("Help Menu (Format: Command - Description)");
  puts("----------");
  puts("h - Help Menu");
  puts("c - Create Election");
  puts("v - Cast Your Vote");
  puts("r - Show Results");
  puts("i - Import Results from File");
  puts("e - Exit Program");
  puts("");
}

void createPosition() {
  printf("What is the name of the position for the election? ");
  fgets(name, MAXSTRINGLENGTH, stdin);
  printf("How many candidates are there? ");
  scanf("%d", &numOfCandidates);
  getchar();

  for (int i = 0; i < numOfCandidates; i++) {
    strcpy(positionName[i], name);
  }

  createCandidate();

}

void createCandidate () {
    char candidateName[MAXSTRINGLENGTH]; 
    for (int i = 0; i < numOfCandidates; i++) { 
        printf("Please enter candidate name: "); 
        fgets(candidateName, MAXSTRINGLENGTH, stdin);
        //printf("%s has been entered", candidateName); // test
        strcpy(candidate[i], candidateName); // inserts candidate string name into candidate array
    }
}


// void saveResults() {
//   FILE *fp;
//   fp = fopen(fileName, "w");

//   for (int i = 0; i < 3; i++) {
//     for (int j = 0; j < 3; j++) {
//       fprintf(fp, "%d,%d,%d", i, j, votes[i][j]);

//       //This prints a \n at the end of every line except for the last. We don't want the file to end with a newline b/c that messes up the processing when the data is read in on program startup
//       if (!(i == 2 && j == 2)) {
//         fprintf(fp, "\n");
//       }
//     }
//   }

//   fclose(fp);
// }

void printBallot() {
  puts("----------- BALLOT ----------- ");
  for (int i = 0; i < numOfCandidates; i++) {
    printf("%d\t%s\t%s", i, positionName[i], candidate[i] );
  }
}

void castVote(){
  int totalVotes = 0; // counter to show how many votes have been cast
  int input;
  
  while (input != -1) {

        printBallot();
        printf("\nPress the number to vote for candidate. Press -1 to complete election. -> ");
        scanf("%d", &input);
        voteCount[input]++;
        totalVotes++;
        printf("\nCongrats you voted! \nTotal votes cast: %d", totalVotes);
        puts("\n----------"); 
    }   
    
  //saveResults();
}

void showResults() {
  puts("------- ELECTION RESULTS -------");
  for (int i = 0; i < numOfCandidates; i++) { 
        
        printf("%sVotes: %d\n", candidate[i], voteCount[i]);
  }
}

// void readInResults() {
//   FILE *fp;
//   fp = fopen(fileName, "r");

//   while (!feof(fp)) {
//     int position, candidate, voteCount;
//     fscanf(fp, "%d,%d,%d", &position, &candidate, &voteCount);
//     votes[position][candidate] = voteCount;
//   }
// }

// void attemptToImportFile() {
//   char userInputNameOfFile[65];
//   int userInputNameLength = 0;

//   pollUserForInputFileName(userInputNameOfFile, &userInputNameLength);
//   if (userInputNameLength == 0) {
//     fileName[0] = 'r';
//     fileName[1] = 'e';
//     fileName[2] = 's';
//     fileName[3] = 'u';
//     fileName[4] = 'l';
//     fileName[5] = 't';
//     fileName[6] = 's';
//     fileName[7] = '.';
//     fileName[8] = 'c';
//     fileName[9] = 's';
//     fileName[10] = 'v';
//     fileName[11] = '\0';

//     fileNameLength = 11;
//   } else {
//     for (int i = 0; i <= userInputNameLength; i++) {
//       fileName[i] = userInputNameOfFile[i];
//     }
//     fileNameLength = userInputNameLength;

//     readInResults();
//   }
// }

int main() {
  char command = 'h'; //Default to 'help' so we can automatically show the user the help menu
  //attemptToImportFile();

  //Main loop
  do {
    if (command == 'h') {
      commandHelp();
      } else if (command == 'c'){
        createPosition();
    } else if (command == 'r'){
      showResults();
    } else if (command == 'i') {
      //attemptToImportFile();
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


  return 0;
}
