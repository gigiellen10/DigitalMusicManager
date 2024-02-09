/* Programmer name: Genevieve Kochel
Date: 01/25/2024
Program purpose: This program implements a digital music manager (DMM) with several features that can be
selected from the main menu.
File purpose: This file contains all the function definitions for this program. 
*/

#include "digitalMusic.h"

/* Function: void backToMenu(void)
Description: Prompts and gets input for going back to main menu of DMM.
Accepts: void
Returns: void
Preconditions: none
Postconditions: none
*/
void backToMenu(void)
{
	char buffer[100] = "";

	printf("\nPress enter to go back to the DMM menu! If you would like to exit the program, select option (11) from the menu.\n");
	fgetc(stdin);

}

/* Function: int displayMenuInput(void)
Description: Displays the main menu portion of the program and gets user selection from the options. validates that input.
Accepts: None, void 
Returns: An integer corresponding to the selection from the user.
Preconditions: None
Postconditions: None
*/
int displayMenuInput(void)
{
	int decision = 0;
	char buffer[100] = "";

	do {

		printf("Welcome to your Digital Music Manager!\n\n");
	printf("(1) load\n"
		"(2) store\n"
		"(3) display\n"
		"(4) insert\n"
		"(5) delete\n"
		"(6) edit\n"
		"(7) sort\n"
		"(8) rate\n"
		"(9) play\n"
		"(10) shuffle\n"
		"(11) exit\n");
	
	printf("\nPlease select an option by entering a number (1-11): ");
	fgets(buffer, 100, stdin); // get input from keyboard

	decision = atoi(buffer); // convert the string to an integer and assign to decision

	if (decision < 1 || decision > 11)
	{
		system("cls");
		printf("Sorry, that input is not one of your options. Please try again.\n");
	}

	} while (decision < 1 || decision > 11);

	return decision;
}


/* Function: Node* createNode(Record newData)
Description: Allocates memory for node and initializes it.
Accepts: newData of type Record
Returns: The address to the new node on the heap
Preconditions: <stdlib.h> must be defined in the header file for malloc(). 
Postconditions: None.
*/
Node* createNode(Record newData)
{
	Node* memPtr = NULL; // will stay NULL if memory was not allocated via malloc()

	memPtr = malloc(sizeof(Node)); // get memory on heap for a struct "Record"

	/* set links forward-> and backward<- to NULL initially */
	memPtr->pNext = NULL;
	memPtr->pPrev = NULL;

	/* initialize data portion (for strings, use strcpy()) */
	strcpy(memPtr->data.albumTitle, newData.albumTitle);
	strcpy(memPtr->data.artist, newData.artist);
	strcpy(memPtr->data.songTitle, newData.songTitle);
	strcpy(memPtr->data.genre, newData.genre);

	memPtr->data.songLength.minutes = newData.songLength.minutes;
	memPtr->data.songLength.seconds = newData.songLength.seconds;

	memPtr->data.timesPlayed = newData.timesPlayed;
	memPtr->data.rating = newData.rating;
	
	return memPtr; // returns address of node created if successfull, otherwise returns NULL
}

/* Function: int insertAtFront(Node** listPtr, Record newData)
Description: Function creates a node, initializes it with new data and inserts it in the front of the DOUBLY linked list
Accepts: The address of a pointer to the first node in the linked list, the new data of type Record
Returns: an integer representing if the memory allocation was successful
Preconditions: A pointer to the first node must be defined in main. 
Postconditions: The headPtr in main must contain the address of the new node created and pNext of the new node must contain the previous contents
of headPtr. pLast of the node last contained by headPtr must be set to the address of the new node inserted.
*/
int insertAtFront(Node** listPtr, Record newData)
{
	int success = 0; // indicates if memory was successfully allocated for node 

	Node* memPtr = createNode(newData); // create and initialize node with new data, memPtr now contains address of node created

	if (memPtr != NULL)
	{
		success = 1; // memPtr not NULL means malloc() successfully allocated memory for a node!

		if (*listPtr == NULL) // list empty
		{
			*listPtr = memPtr; // headPtr in main now contains address of first node

		}
		else // list not empty
		{
			(*listPtr)->pPrev = memPtr; // assign the previous ptr at current front node to &node being inserted
			memPtr->pNext = *listPtr; // assign the forward link of new node to current front node in sequence
			*listPtr = memPtr; // update headPtr (== *listPtr) in main to refer to new node being inserted at front

		}

	}

	return success;
}


/* Function: void printList(Node* startPtr, int play)
Description: Prints all records in doubly linked list. Used in play() function.
Accepts: The address of the node to start printing at, an integer indicating if this function is being used in the play() function.
Returns: None
Preconditions: A headPtr must be defined in main. 
Postconditions: All nodes starting from the startPtr must be printed to the screen.
*/
// play == 1 indicates printList() is being used in playMusic function, needs to pause while printing and system(cls)
void printList(Node* startPtr, int play)
{
	while (startPtr != NULL)
	{
		
		if (play == 1) // being used in play() function
		{
			printf("Artist: %s\nAlbum: %s\nSong: %s\nGenre: %s\nSong length: %d mins %d sec\nTimes played: %d\nRating: %d",
				(*startPtr).data.artist, (*startPtr).data.albumTitle, (*startPtr).data.songTitle, (*startPtr).data.genre, (*startPtr).data.songLength.minutes,
				(*startPtr).data.songLength.seconds, (*startPtr).data.timesPlayed, (*startPtr).data.rating);
			
			// loop to delay clearing the screen
			for (int i = 0; i < 1000000000; ++i);
			
			// clear screen for next song
			system("cls");


		}
		else { // ******************not being used for play() function, may need to adjust for display() function**********************
			
			printf("%s, %s, %s, %s, %d:%d, %d, %d",
				(*startPtr).data.artist, (*startPtr).data.albumTitle, (*startPtr).data.songTitle, (*startPtr).data.genre, (*startPtr).data.songLength.minutes,
				(*startPtr).data.songLength.seconds, (*startPtr).data.timesPlayed, (*startPtr).data.rating);
			putchar('\n');
		}

		startPtr = startPtr->pNext;

	}

}


/* Function: void reset_array(char arr[], int size)
Description: Resets any array to contain all null characters
Date Created: 01/18/23
* Date Last Modified: 01/18/23
Accepts: An array of characters and the size of that character array
Returns: None, void
Preconditions: The array must be defined in main().
Postconditions: The array must be edited to reflect all '\0' in every index */
void resetArray(char arr[], int size)
{
	int index = 0;

	for (; index < size; ++index)
	{
		arr[index] = '\0'; // reset array to all null characters
	}
}


void clearList(Node** listPtr)
{
	Node* find = *listPtr, *temp = NULL;

	if (find != NULL)
	{
		// find position in list (at end) to start deleting from
		for (; find->pNext != NULL; find = find->pNext);

		while (find != NULL)
		{
			temp = find;

			find = find->pPrev;

			free(temp);

		}

		// set pList back to NULL
		*listPtr = NULL;
	}
	
}

/* Function: int loadMusic(Node** listPtr, FILE* musicListFile)
Description: Opens file for mode "r", reads all records from the file, parses them into thier constituent elements,
stores them into a record and inserts that record into the doubly linked list at the front.
Accepts: A pointer to a pointer containing the address of the first node in the list, a FILE to be opened and read from.
Returns: An integer containing the number of records read from the file. 
Preconditions: All data in the file must be consistently and well-formatted.
Postconditions: headPtr in main() must be updated to contain the address of the first node in the doubly linked list.
*/
int loadMusic(Node** listPtr, FILE* musicListFile)
{
	int recordsRead = 0, success = 0; // indicates how many nodes are in the list
	char buffer[200] = "";
	//Record temp; // will use as newData to create new node

	/* open the file for mode "read" */
	musicListFile = fopen("musicPlayList.csv", "r");

	// free memory in existing list if list not empty, starting at end
	if (*listPtr != NULL)
	{
		clearList(listPtr); // clear list

	}


	// check if file opened successfully
	if (musicListFile != NULL)
	{

		while (fgets(buffer, 200, musicListFile) != NULL) // while not at the end of the file
		{
			Record temp = { {""}, {""}, {""}, {""}, {{-1},{-1}}, {-1}, {-1} }; // initialize at begin of loop so that empty every iteration (for strcpy()),

			// parse data with strtok() and store into temporary record
			strcpy(temp.artist, strtok(buffer, ","));
			if (buffer[0] == '\"') // if double quotes around first and last name, need 2 calls to strtok()
			{
				strcat(temp.artist, strtok(NULL, ","));
			}
			strcpy(temp.albumTitle, strtok(NULL, ","));
			strcpy(temp.songTitle, strtok(NULL, ","));
			strcpy(temp.genre, strtok(NULL, ","));

			temp.songLength.minutes = atoi(strtok(NULL, ":")); // split minutes and seconds with ";" delim.
			temp.songLength.seconds = atoi(strtok(NULL, ","));

			temp.timesPlayed = atoi(strtok(NULL, ","));
			temp.rating = atoi(strtok(NULL, "\n"));

			/* create a node with data stored in temp */
			success = insertAtFront(listPtr, temp);


			resetArray(buffer, 200); // reset buffer to be used for next line read in loop
			// could reset strings in temp here with resetArray, quicker for re-initializing at the top

			if (success == 1) // if node was placed in linked list successfully (memory was allocated via malloc())
			{
				++recordsRead;
			}
		}


	}

	fclose(musicListFile);

	return recordsRead;
}


/* Function: void playMusic(Node* listPtr)
Description: Searches doubly linked list for song entered by user. Starts "playing" songs from the first occurence of that song title in the list.
Accepts: The address of the starting node in the list.
Returns: None, void.
Preconditions: The string entered must be case sensitive and spelled correctly. The list must contain at least one song to be searched for. 
Otherwise won't be able to find a matching song. 
Postconditions: Starting at the song entered by the user, the songs must be played/printed to the screen for a short amount of time, until there
are no more songs to play.
*/
// precondition: selection 1 (load) must have been implemented before this function so elements in list
// searches list for song specified to start at and prints/plays songs from there until end of list...could add feature so not case sensitive for song titles?
void playMusic(Node* listPtr)
{
	char buffer[100] = "", decisionBuff[100] = ""; // buffer will store string with song name
	int decision = 0;

	do {

		decision = 0; // reset decision at every iteration

		printf("Please enter the name of the song you would like to start playing at: ");
		fgets(buffer, 100, stdin);
		strtok(buffer, "\n"); // get rid of newline in string entered by user

		// compare string in buffer to song name in list
		while (listPtr != NULL && strcmp(buffer, listPtr->data.songTitle) != 0)
		{
			listPtr = listPtr->pNext; //update listPtr to next node
		}


		if (listPtr == NULL) // did not find a matching song
		{
			do {
				printf("Sorry, there are no songs matching that name. Would you like to try again?\n");
				printf("Enter 1 for yes, 0 for no: ");

				fgets(decisionBuff, 100, stdin); // get input

				if (!isNumber(decisionBuff) || atoi(decisionBuff) < 0 || atoi(decisionBuff) > 1)
				{
					system("cls");
					printf("You must enter 0 or 1. Please try again.\n");
				}

			} while (!isNumber(decisionBuff) || atoi(decisionBuff) < 0 || atoi(decisionBuff) > 1); // validate input

			decision = atoi(decisionBuff); // convert string to integer
			system("cls");
		}
		else // found song, start playing from here
		{
			system("cls");
			decision = 0;
			printList(listPtr, 1); // start printing from address of node containing target song
			printf("You've reached the end of your playlist!\n");
		}

		resetArray(buffer, 100); // reset both strings to be empty for next possible iteration
		resetArray(decisionBuff, 100);

	} while (decision == 1);


}


/* Function: int searchArtist(Node* pList, Node* artistArr[100], char* artistName)
Description: Starting at the node denoted by pList, the function searches for any matching artists within the list. If
a matching artist is found, the address of that node is stored in the array denoted artistArr. 
Accepts: A pointer to the first node in sequence, an array of pointers to nodes, a string containing the artist name to search for.
Returns: An integer, the number of matching artists found. 
Preconditions: The artist string must be well-formated (case sensitive, no extra spaces etc.)
Postconditions: This function must be used in the display() and edit() functions. the artistArr must contain the addresses of 
all matching artist strings. 
*/

int searchArtist(Node* pList, Node* artistArr[100], char* artistName)
{
	Node* tempPtr = pList; // declare temp ptr set to start of list to use in loop 
	int match = 0, index = 0; // match will keep track of matching artist records stored, index is position in node array w match artists

	while (tempPtr != NULL) // loop through till end of list 
	{
		char tempStr[100] = ""; // allows us to put artist in correct format for searching (if enclosed in quotes)
		char compArtistStr[100] = ""; // allows us to copy over string without first set of quotes...will contain final well-formatted string to compare to target artist

		strcpy(tempStr, tempPtr->data.artist); // make a copy of artist name
		
		/* line below assuming tempArtistStr is a well-formed line */
		strcpy(compArtistStr, strtok(tempStr, "\"")); 
		

		if (strcmp(compArtistStr, artistName) == 0) // if artist name matches search
		{
			++match; // increment number of matches
			artistArr[index] = tempPtr; // found a matching record so store into our array of pointers to nodes that match artist
			++index; // increment position in node array

		}

		tempPtr = tempPtr->pNext; // update tempPtr to next node
	}

	return match;


}


/* Function: int displayEditOptions(void)
Description: Displays elements of each record that the user has the ability to edit. Gets input selection from user and 
validates that selection. 
Accepts: None, void.
Returns: An integer, the number corresponding to the selection from the menu made by the user.
Preconditions: None.
Postconditions: The different options available to edit must be displayed to the screen. This selection must be used to indicate 
which part of the data to be edited in the edit() function.
*/
int displayEditOptions(void)
{
	int attributeNum = 0, contEditing = 0;

		do {

			char decision[100] = "";

			printf("\n(1) Artist Name\n"
				"(2) Album Title\n"
				"(3) Song Title\n"
				"(4) Genre\n"
				"(5) Song Length - minutes\n"
				"(6) Song Length - seconds\n"
				"(7) Times Played\n"
				"(8) Rating\n");
			printf("Please choose an atribute to edit by entering the corresponding number (1 - 8): ");
			fgets(decision, 100, stdin);
			attributeNum = atoi(decision);

			if (attributeNum < 1 || attributeNum > 8)
			{
				system("cls");
				printf("Sorry, that is not one of your options. Please try again.\n");
			}

		} while (attributeNum < 1 || attributeNum > 8);

		return attributeNum;


}


/* Function: void printNode(Node* nodeAddress)
Description: Prints a singular node.
Accepts: The address of a node.
Returns: None
Preconditions: The address of the node must refer to valid memory.
Postconditions: The contents of the node pointed to by nodeAddress must be printed to the screen.
*/
void printNode(Node* nodeAddress)
{
	printf("Artist: %s\nAlbum: %s\nSong: %s\nGenre: %s\nSong length: %d mins %d sec\nTimes played: %d\nRating: %d", nodeAddress->data.artist,
		nodeAddress->data.albumTitle, nodeAddress->data.songTitle, nodeAddress->data.genre,
		nodeAddress->data.songLength.minutes, nodeAddress->data.songLength.seconds, nodeAddress->data.timesPlayed, nodeAddress->data.rating);
}


/* Function: int isNumber(char str[])
Description: Determines if a string contains all numbers.
Accepts: A string.
Returns: An integer, 0 or 1, indicating if the string was not all numbers or was composed of all digits, respectively.
Preconditions: str[] must be defined.
Postconditions: Return value must be used to validate user input in several do-while loops throughout the program.
*/

int isNumber(char str[])
{
	int isNum = 0, i = 0, result = -1;

	strtok(str, "\n"); // since being used to validate user input, get rid of newline if present

	for (; str[i] != '\0' && isdigit(str[i]) != 0; ++i); // breaks out of loop when end of string or found non-number in string
	
	if (str[i] == '\0') // did not find non-digit
	{
		isNum = 1;
	}
	else // found non-digit
	{
		isNum = 0;
	}

	return isNum;

}


/* Function: void editMusic(Node* pList)
Description: Function searches for a particular artist. If more than one record was found, the program prompts
which record to edit. The user is then able to edit any aspect of that record.
Accepts: The address of the first node in the doubly linked list.
Returns: None.
Preconditions: None.
Postconditions: If the artist name is edited it must be in the following form: "Last First" or First, in order for program to be exited/loaded again correctly.  
The record specified by the user must reflect the changes entered by the user.
*/
void editMusic(Node* pList)
{
	char userInput[100] = "";
	Node* artistArr[100];
	int matchingRecords = 0, decision = 0, attributeNum = 0, artistIndex = 0; // matchingRecords will contain number of matching records found for an artist

	// prompt user which artist they would like to search for

	do {

		decision = 0, artistIndex = 0; // artistIndex controls which index of the array of Node*'s to access to edit

		char decisionStr[100] = "", temp[100] = "";

		printf("Which artist would you like to search for?\n");
		printf("Enter the name here (if your artist has a first and last name, enter it in the form \"Last First\"): ");

		fgets(userInput, 100, stdin); // get input string
		strtok(userInput, "\n"); // get rid of newline at end of input

		matchingRecords = searchArtist(pList, artistArr, userInput);
		system("cls");

		if (matchingRecords == 0) // did not find a matching record
		{
			do {
				
				printf("Sorry that artist was not found in your playlist.\n");
				printf("Would you like to try again? Enter 1 for yes, 0 for no: ");
				fgets(decisionStr, 100, stdin);
				decision = atoi(decisionStr);
				system("cls");

				if (!isNumber(decisionStr) || decision < 0 || decision > 1)
				{
					printf("You must enter a number, 0 or 1. Please try again.\n");
				}

			} while (!isNumber(decisionStr) || decision < 0 || decision > 1);

		}
		else // found at least 1 matching record
		{

			// loop through Node* array print any records that match the artist
			for (int i = 0, label = 1; i < matchingRecords; ++i, ++label)
			{
				printf("\n(%d) ", label);
				printNode(artistArr[i]);
				puts("\n");

			}

			if (matchingRecords > 1) // more than one song under that artist
			{
				
				do {

					printf("You have %d songs saved matching that artist. Enter the record number above that you would like to edit (1 - %d): ", 
						matchingRecords, matchingRecords);

					fgets(decisionStr, 100, stdin);
					artistIndex = atoi(decisionStr);
					system("cls");
					
					if (artistIndex < 1 || artistIndex > matchingRecords)
					{
						printf("Sorry, that is not one of your options. Please try again.\n");
					}

				} while (artistIndex < 1 || artistIndex > matchingRecords); // validate input

			}
			else // only 1 matching record
			{
				artistIndex = matchingRecords;
			}

			int editMore = 0;

			do {

				resetArray(temp, 100);
				attributeNum = displayEditOptions(); // get input 

				// edit that part of the record at artistIndex - 1 position in array
				switch (attributeNum)
				{
				case 1: // artist
					
					printf("\nEnter the string you would like to replace the current artist with: "); // if first and last name must be in "Last First" form
					fgets(temp, 100, stdin);
					strtok(temp, "\n"); // get rid of newline
					resetArray(artistArr[artistIndex - 1]->data.artist, 50); // clear current string in record before replacing
					strcpy(artistArr[artistIndex - 1]->data.artist, temp); // copy over new string

					break;
				case 2: // album title

					printf("\nEnter the string you would like to replace the current album title with: "); // if first and last name must be in "Last First" form
					fgets(temp, 100, stdin);
					strtok(temp, "\n");
					resetArray(artistArr[artistIndex - 1]->data.albumTitle, 100); // clear current string in record before replacing
					strcpy(artistArr[artistIndex - 1]->data.albumTitle, temp); // copy over new string

					break;
				case 3: // song title
					
					printf("\nEnter the string you would like to replace the song title with: "); // if first and last name must be in "Last First" form
					fgets(temp, 100, stdin);
					strtok(temp, "\n");
					resetArray(artistArr[artistIndex - 1]->data.songTitle, 50); // clear current string in record before replacing
					strcpy(artistArr[artistIndex - 1]->data.songTitle, temp); // copy over new string

					break;
				case 4: // genre

					printf("\nEnter the string you would like to replace the genre with: "); // if first and last name must be in "Last First" form
					fgets(temp, 100, stdin);
					strtok(temp, "\n");
					resetArray(artistArr[artistIndex - 1]->data.genre, 50); // clear current string in record before replacing
					strcpy(artistArr[artistIndex - 1]->data.genre, temp); // copy over new string

					break;
				case 5: // song length - mins

					do {

						printf("\nEnter the new number of minutes for this song: ");
						fgets(temp, 100, stdin);

						if (!isNumber(temp) || atoi(temp) < 0)
						{
							system("cls");
							printf("This field cannot be less than 0 and must contain a number. Please try again.\n");
						}

					} while (!isNumber(temp) || atoi(temp) < 0); // validate: if less than 0 or not a string of numbers
					
					artistArr[artistIndex - 1]->data.songLength.minutes = atoi(temp);

					break;
				case 6: // song length - seconds

					do {

						printf("\nEnter the new number of seconds for this song: ");
						fgets(temp, 100, stdin);

						if (!isNumber(temp) || atoi(temp) < 0 || atoi(temp) > 60)
						{
							system("cls");
							printf("This field must be between 0 - 60, and must contain a number. Please try again.\n");
						}

					} while (!isNumber(temp) || atoi(temp) < 0 || atoi(temp) > 60); // validate

					artistArr[artistIndex - 1]->data.songLength.seconds = atoi(temp);

					break;
				case 7: // times played

					do {

						printf("\nEnter the new number of times played for this song: ");
						fgets(temp, 100, stdin);

						if (!isNumber(temp) || atoi(temp) < 0)
						{
							system("cls");
							printf("This field cannot be less than 0 and must contain a number. Please try again.\n");
						}

					} while (!isNumber(temp) || atoi(temp) < 0); // validate

					artistArr[artistIndex - 1]->data.timesPlayed = atoi(temp);
					break;
				case 8: // rating 

					do {

						printf("\nEnter the new rating for this song: ");
						fgets(temp, 100, stdin);

						if (!isNumber(temp) || atoi(temp) < 1 || atoi(temp) > 5)
						{
							system("cls");
							printf("This field must be between 1-5, and must contain a number. Please try again.\n");
						}

					} while (!isNumber(temp) || atoi(temp) < 1 || atoi(temp) > 5); // validate

					artistArr[artistIndex - 1]->data.rating = atoi(temp);
					
					break;
				}

				do {

					printf("Would you like to continue editing this record? Enter 1 for yes, 0 for no: ");
					resetArray(decisionStr, 100);
					fgets(decisionStr, 100, stdin);
					editMore = atoi(decisionStr);

					if (!isNumber(decisionStr) || editMore < 0 || editMore > 1)
					{
						system("cls");
						printf("\nInput must be 1 or 0. Please try again.\n");
					}

				} while (!isNumber(decisionStr) || editMore < 0 || editMore > 1); // validate 

				if (editMore == 1)
				{
					system("cls"); // clear screen for next iteration
				}
				

			} while (editMore == 1);

		}

	} while (decision == 1);

}


/* Function: void rateSong(Node* listPtr)
Description: This function allows the user to rate a particular song based on the song name. The 
function find the first occurence of this song, and prompts the user for a new rating. The current rating is overwritten.
Accepts: The address of the first node in the list (headPtr in main()).
Returns: None.
Preconditions: The string entered to search for a particular song must be well-formed (no extra spaces, case-sensitive etc).
Postconditions: The rating of the song specified by the user must be overwritten to contain the new rating.
*/
void rateSong(Node* listPtr)
{
	char buffer[100] = "", decisionBuff[100] = ""; // buffer will store string with song name
	int decision = 0;

	do {

		decision = 0;

		printf("Please enter the name of the song you would like to change the rating of: ");
		fgets(buffer, 100, stdin);
		strtok(buffer, "\n"); // get rid of newline in string entered by user

		// compare string in buffer to song name in list
		while (listPtr != NULL && strcmp(buffer, listPtr->data.songTitle) != 0)
		{
			listPtr = listPtr->pNext; //update listPtr to next node
		}


		if (listPtr == NULL) // did not find a matching song
		{
			printf("Sorry, there are no songs matching that name. Would you like to try again?\n");
			printf("Enter 1 for yes, 0 for no: ");

			fgets(decisionBuff, 100, stdin); // get input
			decision = atoi(decisionBuff); // convert string to integer
			system("cls");
		}
		else // found song
		{
			char temp[100] = "";

			do {

				printf("\nEnter the new rating for this song: ");
				fgets(temp, 100, stdin);

				if (atoi(temp) < 1 || atoi(temp) > 5)
				{
					system("cls");
					printf("This field must be between 1-5. Please try again.\n");
				}

			} while (atoi(temp) < 1 || atoi(temp) > 5); // validate

			listPtr->data.rating = atoi(temp);

		}

		resetArray(buffer, 100); // reset both strings to be empty for next possible iteration
		resetArray(decisionBuff, 100);

	} while (decision == 1);


}


/* Function : Record getValidData(void)
Description: prompts the user for the data required to create a struct Record, validates the quality of the data
and creates a record with that validated data
Accepts: None
Returns: a copy of the record that was created inside the function
Preconditions: struct record must be defined in the header file
Postconditions: The record returned must be used in the insertMusic() function as the newData */
void getValidData(Record *newRecord)
{
	
	char buff[100] = "";

	// get artist, don't validate for all characters because some artists have numbers in thier name
	printf("\nPlease enter the name of the artist you would like to input (enter it like so: \"Last First\" or First): ");
	fgets(buff, 100, stdin);

	strtok(buff, "\n");
	strcpy(newRecord->artist, buff);
	resetArray(buff, 100); // reset array to be re-used below
	system("cls");

	// album title
	printf("Please enter the album title for the record you would like to input: ");
	fgets(buff, 100, stdin);

	strtok(buff, "\n"); // get rid of newline in string
	strcpy(newRecord->albumTitle, buff);
	resetArray(buff, 100);
	system("cls");

	// song title
	printf("Please enter the song title for the record you would like to input: ");
	fgets(buff, 100, stdin);

	strtok(buff, "\n"); // get rid of newline in string
	strncpy(newRecord->songTitle, buff, 50);
	resetArray(buff, 100);
	system("cls");

	// genre
	printf("Please enter the genre for the record you would like to input: ");
	fgets(buff, 100, stdin);

	strtok(buff, "\n"); // get rid of newline in string
	strncpy(newRecord->genre, buff, 50);
	resetArray(buff, 100);
	system("cls");

	// song length - mins
	

	do {
		
		resetArray(buff, 100);
		printf("Please enter the minutes field of the song duration for the record you would like to store: ");
		fgets(buff, 100, stdin);
		

		if (atoi(buff) < 0 || isNumber(buff) != 1)
		{
			system("cls");
			printf("Your input cannot be less than 0 and must be a number. Try again.\n");

		}


	} while (atoi(buff) < 0 || isNumber(buff) != 1);

	newRecord->songLength.minutes = atoi(buff);
	resetArray(buff, 100);
	system("cls");

	// song duration - secs
	do {

		resetArray(buff, 100);
		printf("Please enter the seconds field of the song duration for the record you would like to store: ");
		fgets(buff, 100, stdin);


		if ((atoi(buff) < 0 || atoi(buff) > 60) || isNumber(buff) != 1)
		{
			system("cls");
			printf("Your input cannot be less than 0 and must be a number. Try again.\n");

		}


	} while ( (atoi(buff) < 0 || atoi(buff) > 60) || isNumber(buff) != 1);

	newRecord->songLength.seconds = atoi(buff);
	resetArray(buff, 100);
	system("cls");


	// times Played

	do {
		
		resetArray(buff, 100);
		printf("Please enter the number of times played for the new record you would like to store: ");
		fgets(buff, 100, stdin);

		if (isNumber(buff) != 1 || atoi(buff) < 0)
		{
			system("cls");
			printf("Your input cannot be less than 0 and must be a number. Please try again.\n");
			
		}

	} while (isNumber(buff) != 1 || atoi(buff) < 0);

	newRecord->timesPlayed = atoi(buff);

	resetArray(buff, 100);
	system("cls");

	// rating
	do {

		resetArray(buff, 100);
		printf("Please enter the rating for the new record you would like to store (0-5): ");
		fgets(buff, 100, stdin);

		if ( isNumber(buff) != 1 || (atoi(buff) < 0 || atoi(buff) > 5) )
		{
			system("cls");
			printf("Your input must be between 0-5 and must be a number. Please try again.\n");
			
		}

	} while (isNumber(buff) != 1 || (atoi(buff) < 0 || atoi(buff) > 5));

	newRecord->rating = atoi(buff);


}

/* Function: int insertMusic(Node** pList, Record localRec)
Description: This function inserts the record at the front of the doubly linked list. 
Accepts: A pointer to the first node in the linked list, a Record to be inserted (this record must have 
been validated by getValidInput().
Returns: integer success.
Preconditions: getValidInput must have validated the user input. The struct created must be passed into this function.
Postconditions: The list must be updated to reflect the new node inserted.
*/
int insertMusic(Node** pList, Record localRec)
{
	int success = 0;

	success = insertAtFront(pList, localRec);

	return success;
}



/* Function: void displayMusic(Node* listPtr)
Description: This function allows the user to display all records in the list 
or search for a record based on a particular artist, displaying all matching records for that artist.
Accepts: A pointer to the first node in the linked list.
Returns: None.
Preconditions: The string enetered to search for an artist must be well-formed. 
Postconditions: The records matching the user input must be displayed to the screen.
*/
void displayMusic(Node* listPtr)
{
	char inputBuff[100] = "", userInput[100] = "";
	int decision = 0, matchingRecords = 0;
	Node* artistArr[100];

	do {
		printf("Please select from the following:\n");
		printf("\n(1) Display all saved music records\n"
			"(2) Display music records for a particular artist\n");
		printf("\nEnter your input here: ");
		fgets(inputBuff, 100, stdin);

		decision = atoi(inputBuff);

		if (decision < 1 || decision > 2)
		{
			system("cls");
			printf("INVALID INPUT: Please enter 0 or 1.\n");
			putchar('\n');

		}

	} while (decision < 1 || decision > 2);

	switch (decision)
	{
	case 1: // print all records

		system("cls");
		printList(listPtr, 0);

		break;

	case 2: // print based on artist

		system("cls");
		printf("Which artist would you like to search for?\n");
		printf("Enter the name here (if your artist has a first and last name, enter it in the form \"Last First\"): ");

		fgets(userInput, 100, stdin); // get input string
		strtok(userInput, "\n"); // get rid of newline at end of input

		matchingRecords = searchArtist(listPtr, artistArr, userInput);
		system("cls");

		if (matchingRecords > 0)
		{
			printf("Records matching that artist name are listed below: ");
			for (int i = 0, label = 1; i < matchingRecords; ++i, ++label)
			{
				printf("\n(%d) ", label);
				printNode(artistArr[i]);
				puts("\n");

			}

		}
		else // did not find matching records
		{

			printf("Sorry, there are no records matching that artist.\n");

		}

		break;
	}


}


/* Function: int deleteSong(Node** pList, Record *deletedRec)
Description: This function searches for a song title, finds the record containing that song 
stores the record information to return and deletes the node. 
Accepts: A pointer to the first node in the linked list, a pointer to an empty record. 
Returns: integer success.
Preconditions: none, list checked for empty inside function.
Postconditions: The list must no longer contain the deleted node and the contents of the deleted node
must be indirectly returned via deleted Rec
*/

int deleteSong(Node** pList, Record *deletedRec)
{
	int success = 0;
	char buffer[100] = ""; // buffer will store string with song name
	Node* pTemp = *pList;

	if (*pList == NULL) // empty list
	{
		return success;
	}
		// search for song title
	
		printf("Please enter the name of the song you would like to delete: ");
		fgets(buffer, 100, stdin);
		strtok(buffer, "\n"); // get rid of newline in string entered by user

		// compare string in buffer to song name in list
		while (pTemp != NULL && strcmp(buffer, pTemp->data.songTitle) != 0)
		{
			pTemp = pTemp->pNext; //update pTemp to next node
		}

		if (pTemp == NULL) // did not find a matching song
		{
				
				printf("Sorry, there are no songs matching that name.\n");
				
				
		}
		else // found song; save record details and delete record
		{
			success = 1;
			strcpy(deletedRec->albumTitle, pTemp->data.albumTitle);
			strcpy(deletedRec->artist, pTemp->data.artist);
			strcpy(deletedRec->songTitle, pTemp->data.songTitle);
			strcpy(deletedRec->genre, pTemp->data.genre);
			deletedRec->songLength.minutes = pTemp->data.songLength.minutes;
			deletedRec->songLength.seconds = pTemp->data.songLength.seconds;
			deletedRec->timesPlayed = pTemp->data.timesPlayed;
			deletedRec->rating = pTemp->data.rating;

			if (pTemp == *pList) 
			{
				// deleting at front, need to modify headPtr
				if (pTemp->pNext != NULL)
				{
					pTemp->pNext->pPrev = pTemp->pPrev; // connect nodes
				}
				*pList = pTemp->pNext;
				free(pTemp);
			}
			else
			{
				// deleting in the middle or at the end
				pTemp->pPrev->pNext = pTemp->pNext;
				pTemp->pNext->pPrev = pTemp->pPrev; // connect links before freeing pTemp
				free(pTemp);
			}

		}

		return success;

}

/* Function: int* createRandArr(int recsRead)
Description: This function creates a randomly generated array with dynamically allocated memory 
based on the number of records contained in the linked list.
Accepts: number of records read up to this point.
Returns: a pointer to an array dynamically allocated via malloc.
Preconditions: recsRead is not 0
Postconditions: Array generated must be used in the shuffle function.
*/

int* createRandArr(int recsRead)
{
	int randNum = 0;
	int* randArr = (int*)malloc(sizeof(int) * (recsRead + 1)); // arr needs to be dynamically sized so allocate memory via malloc()
	int* alreadyGenerated = (int*)malloc(sizeof(int) * (recsRead + 1)); // declare parallel array to keep track of numbers already been generated

	// fill random arr with random numbers 1 - recsRead, # indexes are (recsRead - 1)
	for (int i = 0; i < recsRead; ++i)
	{
		randNum = rand() % recsRead + 1;

		while (alreadyGenerated[randNum] == 1)
		{
			randNum = rand() % recsRead + 1;

			// loop through parallel array to ensure we aren't reusing random numbers
		}

		randArr[i] = randNum;
		alreadyGenerated[randNum] = 1; // indicated that this index number has already been generated and saved
	}

	free(alreadyGenerated);
	return randArr;
}


/* Function: void shuffleMusic(Node* pList, int randArr[], int recsRead)
Description: This function shuffles and plays the music in a randomly generated order specified by 
randArr[]. 
Accepts: number of records read up to this point, an integer array of random numbers 1 - recs read
and a node pointer.
Returns: None
Preconditions: recsRead cannot be 0.
Postconditions: The contents of the list must be printed to the screen for a short amount of time, in the
order specified by randArr.
*/

void shuffleMusic(Node* pList, int randArr[], int recsRead)
{
	Node* searchNode = pList;
	int i = 0, currCount = 0, lastCount = 1;

	// set searchNode to front of list again; loop while haven't gotten to end of random number array
	while (i < recsRead)
	{
		currCount = randArr[i];

		while (lastCount != currCount)
		{
			if (lastCount > currCount)
			{
				searchNode = searchNode->pPrev;
				--lastCount;
			}
			else // lastCount > currCount, go forward in list
			{
				searchNode = searchNode->pNext;
				++lastCount;
			}
		}

		printNode(searchNode);

		for (int i = 0; i < 1000000000; ++i); // delay the time until clear screen

		system("cls");
		 ++i;

		lastCount = currCount;

		/* another solution not traversing the list back and forth (only forward) */

		//searchNode = pList; // reset searchNode

		//count = randArr[i]; // count contains number of nodes from front of list we should move to, to play song

		//for (; count != 1; --count, searchNode = searchNode->pNext); // find position of record to "play" in list

		//printNode(searchNode); // play that record

		//for (int i = 0; i < 1000000000; ++i); // delay the time until clear screen

		//system("cls");
		//++i;
	}

	printf("Your music was played in the following order:");
	for (int i = 0; i < recsRead; ++i)
	{
		printf(" %d", randArr[i]);

		if (i != recsRead - 1)
		{
			putchar(',');
		}
	}

}


/* Function: void swap(Node* ptr1, Node* ptr2)
Description: This function swaps the nodes pointed to by pt1 and ptr2 by exchanging data. Links are not 
modified.
Accepts: Two node pointers who's data is to be swappped.
Returns: None
Preconditions: The pointers passed in may not be null.
Postconditions: The contents the pointers must be edited to reflect the contents of eachother, ex: ptr1 has the data of ptr2 
vice versa.
*/
void swap(Node* ptr1, Node* ptr2)
{
	// could do struct assignment here, airing on safe side since strings
	Record pTemp = { {""}, {""}, {""}, {""}, {{-1}, {-1}}, {-1}, {-1} }; // init temp

	// first store all information from ptr1 in temp Node

	strcpy(pTemp.albumTitle, ptr1->data.albumTitle);
	strcpy(pTemp.artist, ptr1->data.artist);
	strcpy(pTemp.songTitle, ptr1->data.songTitle);
	strcpy(pTemp.genre, ptr1->data.genre);
	pTemp.songLength.minutes = ptr1->data.songLength.minutes;
	pTemp.songLength.seconds = ptr1->data.songLength.seconds;
	pTemp.rating = ptr1->data.rating;
	pTemp.timesPlayed = ptr1->data.timesPlayed;

	// clear and overwrite contents of ptr1 with ptr2 information
	resetArray(ptr1->data.albumTitle, 100);
	resetArray(ptr1->data.genre, 50);
	resetArray(ptr1->data.songTitle, 50);
	resetArray(ptr1->data.artist, 50);

	strcpy(ptr1->data.albumTitle, ptr2->data.albumTitle);
	strcpy(ptr1->data.artist, ptr2->data.artist);
	strcpy(ptr1->data.songTitle, ptr2->data.songTitle);
	strcpy(ptr1->data.genre, ptr2->data.genre);
	ptr1->data.songLength.minutes = ptr2->data.songLength.minutes;
	ptr1->data.songLength.seconds = ptr2->data.songLength.seconds;
	ptr1->data.rating = ptr2->data.rating;
	ptr1->data.timesPlayed = ptr2->data.timesPlayed;

	// clear and overwrite data of ptr2 with contents of tempPtr
	resetArray(ptr2->data.albumTitle, 100);
	resetArray(ptr2->data.genre, 50);
	resetArray(ptr2->data.songTitle, 50);
	resetArray(ptr2->data.artist, 50);

	strcpy(ptr2->data.albumTitle, pTemp.albumTitle);
	strcpy(ptr2->data.artist, pTemp.artist);
	strcpy(ptr2->data.songTitle, pTemp.songTitle);
	strcpy(ptr2->data.genre, pTemp.genre);
	ptr2->data.songLength.minutes = pTemp.songLength.minutes;
	ptr2->data.songLength.seconds = pTemp.songLength.seconds;
	ptr2->data.rating = pTemp.rating;
	ptr2->data.timesPlayed = pTemp.timesPlayed;



}

/* Function: void stringToLower(char str[])
Description: This function converts the string passed in to all lowercase values of the existing letters.
Accepts: A pointer to a string.
Returns: None
Preconditions: The string must contain the null character.
Postconditions: The letters contained in str must be reflected to be all lowercase.
*/
void stringToLower(char str[])
{
	
	for (int i = 0; str[i] != '\0'; ++i)
	{
		str[i] = tolower(str[i]);
	}
}

/* Function: void formatString(char str[])
Description: This function removes all existing quotes, whitespace and converts the characters to lowercase.
Accepts: A pointer to a string.
Returns: None
Preconditions: The string must contain the null character.
Postconditions: The string must be void of whitespace, quotes, and uppercase characters. The results of this function
must be used to compare strings alphabetically in the sort() function.
*/
void formatString(char str[])
{
	if (str[0] == '\"')
	{
		// get rid of first quotes by shifting all characters over
		for (int i = 0; str[i] != '\0'; ++i)
		{
			str[i] = str[i + 1];
		}

		strtok(str, "\""); // get rid of last quote at the end
	}

	// get rid of any whitespace
	for (int i = 0; str[i] != '\0'; ++i)
	{
		if (str[i] == ' ')
		{
			// shift elements over if found whitespace

			for (int j = i; str[j] != '\0'; ++j)
			{
				str[j] = str[j + 1];
			}
		}
	}

	// convert the string to lowercase
	stringToLower(str);

}

/* Function: void bubbleSort(Node* pList, int numNodes, int sortType)
Description: This function sorts a doubly linked list in ascending order by artist name, album title, 
rating and timesplayed (descending).
Accepts: A pointer to the front of the doubly linked list, the number of nodes contained in the list, 
and an integer representing the field to sort based on user input. 
Returns: None
Preconditions: The list must not be empty.
Postconditions: The list must be sorted based on the field specified by the user.
*/
void bubbleSort(Node* pList, int numNodes, int sortType)
{

	int i = 0; // controls number of passes
	Node* pStart = pList; 
	char startStr[100] = "", nextStr[100] = "";
	// make num Nodes - 1 # passes and swap nodes if not in ascending order

	for (; i < numNodes; ++i) // controlls number of passes
	{
		pStart = pList;
		
		while (pStart->pNext != NULL)
		{
			Node* ptr1 = pStart;
			Node* ptr2 = pStart->pNext;

			switch (sortType)
			{
			case 1:
				// compare artist, write a function to turn all letters to lower case so compares equally, < 0
				resetArray(startStr, 100);
				resetArray(nextStr, 100);
				strcpy(startStr, ptr1->data.artist);
				strcpy(nextStr, ptr2->data.artist);
				
				
				formatString(startStr); // manipulate string to be in same form for comparison
				formatString(nextStr);

				if(strcmp(startStr, nextStr) > 0)
				{
					swap(ptr1, ptr2); // check if swap function works
				}
					break;
			case 2:
				// compare album title strings, write a function to turn all letters to lower case so compares equally < 0
				resetArray(startStr, 100);
				resetArray(nextStr, 100);
				strcpy(startStr, ptr1->data.albumTitle);
				strcpy(nextStr, ptr2->data.albumTitle);
				
				formatString(startStr); // manipulate string to be in same form for comparison
				formatString(nextStr);

				if (strcmp(startStr, nextStr) > 0)
				{
					swap(ptr1, ptr2);
				}

				break;
			case 3: // compare rating, ascending <

				if (ptr1->data.rating > ptr2->data.rating)
				{
					swap(ptr1, ptr2);
				}

				break;
			case 4: // compare timesPlayed, decending >

				if (ptr1->data.timesPlayed < ptr2->data.timesPlayed)
				{
					swap(ptr1, ptr2);
				}
				break;
			}

			pStart = pStart->pNext; // increment position in the list

		}
		
	}

}


/* Function: int sortMusic(Node* pList, int numNodes)
Description: This function prompts the user to enter a field to sort the doubly linked list by, and 
sorts the linked list in ascending order by artist name, album title,
rating or timesplayed (descending).
Accepts: A pointer to the front of the doubly linked list, the number of nodes contained in the list.
Returns: An integer indicating if the sort was successful. 
Preconditions: None. 
Postconditions: The list must be sorted based on the field specified by the user.
*/
int sortMusic(Node* pList, int numNodes)
{
	char decisionBuff[100] = "";
	int decision = 0;

	do {

		resetArray(decisionBuff, 100);

		printf("Please select from the following options:\n");
		printf("(1) Sort based on artist name (A - Z)\n"
			"(2) Sort based on album title (A - Z)\n"
			"(3) Sort based on rating (1 - 5)\n"
			"(4) Sort based on times played (descending order)\n");
		printf("Enter your selection here: ");

		fgets(decisionBuff, 100, stdin);

		if (isNumber(decisionBuff) != 1 || atoi(decisionBuff) < 1 || atoi(decisionBuff) > 4)
		{
			system("cls");
			printf("Your input must be a number (1 - 4). Please try again.\n");
		}

	} while (isNumber(decisionBuff) != 1 || atoi(decisionBuff) < 1 || atoi(decisionBuff) > 4);

	decision = atoi(decisionBuff); // decision indicates what field to sort based off of

	bubbleSort(pList, numNodes, decision);

	if (numNodes == 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}

}

/* Function: void storePlaylist(Node* listPtr, FILE* playListFile)
Description: This function opens the file denoted by playlistFile for mode "w" and overwrites the 
previous contents of that file with the current contents of the linked list.
Accepts: A pointer to the first node in the list, the file that is to be opened and written to with the contents of the linked list.
Returns: None.
Preconditions: IF ANY RECORDS EDITED: data currently contained in the list must be correctly fomatted...any data loaded using the load function must have been
inputted in the same form as the sample musicPlaylist.csv file.
Postconditions: The file denoted by playListFile must be overwritten to contain the contents of the list.
*/
void storePlaylist(Node* listPtr, FILE* playListFile)
{
	playListFile = fopen("musicPlayList.csv", "w"); // open musicPlaylist for mode "write"

	if (playListFile != NULL) // opened successfully for mode w
	{
		while (listPtr != NULL) // iterate through list until at end, printing to outfile
		{
			if (listPtr->data.artist[0] == '\"') // add comma in between first and last name if name in quotes " ", so correct file formatting
			{
				int space = 0, end = 0;

				// find whitespace
				for (space = 0; listPtr->data.artist[space] != ' '; ++space);
				end = (int)strlen(listPtr->data.artist);
				// shift elements over from end
					for (; end > space - 1; --end)
					{
						listPtr->data.artist[end + 1] = listPtr->data.artist[end];

					}
				// overwrite space with a comma
				listPtr->data.artist[space] = ',';
			}

			fprintf(playListFile, "%s,%s,%s,%s,%d:%d,%d,%d",
				listPtr->data.artist, listPtr->data.albumTitle, listPtr->data.songTitle, listPtr->data.genre, listPtr->data.songLength.minutes,
				listPtr->data.songLength.seconds, listPtr->data.timesPlayed, listPtr->data.rating);

			fputc('\n', playListFile);

			listPtr = listPtr->pNext; // update to go to next node
		}
	}

	fclose(playListFile); // close file
}


/* Function: void exitPlaylist(Node* listPtr, FILE* playListFile)
Description: This function calls storePlaylist() and prints confirmation and exit messages to the screen.
Accepts: A pointer to the first node in the list, the file that is to be opened and written to with the contents of the linked list.
Returns: None.
Preconditions: IF ANY RECORDS EDITED: data currently contained in the list must be correctly fomatted...any data loaded using the load function must have been
inputted in the same form as the sample musicPlaylist.csv file.
Postconditions: The file denoted by playListFile must be overwritten to contain the contents of the list. The main menu loop must be broken after this function exits.
*/

void exitPlaylist(Node* listPtr, FILE* playListFile)
{
	storePlaylist(listPtr, playListFile);

	printf("Playlist successfully outputted to musicPlaylist.csv\n");
	printf("\nThank you for using Digital Music Manager! Goodbye.");

}


