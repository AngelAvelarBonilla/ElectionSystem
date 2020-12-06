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

void pollUserForInputFileName(char *fileName, int fileNameLength) {
	int hasFile = 0;
	
	printf("Do you have a input file to supply? (1=yes, 0=no): ");
	scanf(" %d", &hasFile);
	
	if (hasFile) {
		printf("Please enter the file name (Up to 64 characters): ");
		scanf(" %s", fileName);
		fileNameLength = strlen(fileName);
	}
}

void commandHelp() {
	puts("Help Menu (Format: Command - Description)");
	puts("----------");
	puts("h - Help Menu");
	puts("e - Exit Program"); //Done
	puts("");
}

int main() {
	char command = 'h'; //Default to 'help' so we can automatically show the user the help menu
	char fileName[65];
	int fileNameLength = 0;
	
	pollUserForInputFileName(fileName, &fileNameLength);
	for (int i = 0; i < fileNameLength; i++) {
		printf("");
	}
	
	//Main loop
	do {
		if (command == 'h') {
			commandHelp();
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
