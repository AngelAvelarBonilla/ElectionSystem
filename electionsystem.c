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

int votes[3][3] = {{0}};

void pollUserForInputFileName(char fileName[], int *fileNameLength) {
	int hasFile = 0;

	printf("Do you have a input file to supply? (1=yes, 0=no): ");
	scanf(" %d", &hasFile);

	if (hasFile) {
		printf("Please enter the file name (Up to 64 characters): ");
		scanf(" %s", fileName);
		(*fileNameLength) = strlen(fileName);
	}
}

void commandHelp() {
	puts("Help Menu (Format: Command - Description)");
	puts("----------");
	puts("h - Help Menu");
	puts("v - Cast your vote");
	puts("r - Show Results");
	puts("e - Exit Program"); //Done
	puts("");
}

void castVote(){
    int i, k;
    char candidateChoice;
    for(i = 0; i<3; i++){
        printf("Cast vote for "); getOfficerPosition(i);
        for(k = 0; k<3; k++){
            printf("\nCandidate %c", k+65);
        }
        printf("\n0 for none of them\nChoice: ");
        scanf(" %c", &candidateChoice);
        candidateChoice = toupper(candidateChoice);
        if (candidateChoice != "0")
            votes[i][candidateChoice - 65]++;
        puts("\n----------");
    }
}

void showResults() {
    int i, j;
    for(i = 0; i<3; i++){
        getOfficerPosition(i);
        for(j=0; j<3; j++){
            printf("\nCandidate %c: %d votes", j+65, votes[i][j]);
        }
        puts("\n----------");
    }
}

void getOfficerPosition(int i){
    switch(i) {
    case 0:
        printf("President");
        break;
    case 1:
        printf("Vice President");
        break;
    case 2:
        printf("Treasurer");
        break;
    }
}

int main() {
	char command = 'h'; //Default to 'help' so we can automatically show the user the help menu

	//Main loop
	do {
		if (command == 'h') {
			commandHelp();
		} else if (command == 'r'){
		    showResults();
		} else if (command == 'v'){
		    castVote();
        } else if (command == 'e') {
			puts("Have a wonderful day");
			break;
		}

		printf("Please enter a command: ");
		scanf(" %c", &command);
		command = tolower(command);
	} while (1); //Never-ending expression in the while here because we want to break out after we process the goodbye message. This procesing happens at the beginning of the loop, not the end


	return 0;
}
