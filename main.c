/* Programmer name: Genevieve Kochel
Date: 01/25/2024
Program purpose: This program implements a digital music manager (DMM) with several features that can be
selected from the main menu.
File purpose: This file contains the main() function for this program.
*/

#include "testing.h"


int main(void)
{
	int menuSelection = 0, recordsRead = 0, success = 0;
	
	srand((unsigned)time(NULL)); // seed srand()

	Node* headPtr = NULL; // pointer to the first node in doubly linked list
	FILE* infile = NULL; // will refer to musicPlayList.csv when loadMusic() called
	Record localRec;
	
	while (menuSelection != 11) // exit condition
	{
		menuSelection = displayMenuInput();
		success = 0; // reset success variable

		switch (menuSelection) {
		case 1: // load 

			system("cls");
			recordsRead = loadMusic(&headPtr, infile);
			printf("\n%d music records have been successfully loaded into the playlist!\n", recordsRead);
			backToMenu();
			system("cls");

			break;
		case 2: // store 
			system("cls");
			storePlaylist(headPtr, infile);
			printf("Your music has been stored!!\n");
			backToMenu();
			system("cls");

			break;
		case 3: // display

			system("cls");
			displayMusic(headPtr);
			backToMenu();
			system("cls");

			break;
		case 4: // insert 
			system("cls");

			Record localRec = { {""}, {""}, {""}, {""}, {{-1}, {-1}}, {-1}, {-1} };

			getValidData(&localRec);
			success = insertMusic(&headPtr, localRec);

			if (success == 1)
			{
				printf("\nYour record has been inserted into your playlist!\n");
				++recordsRead; // keep track of how many nodes in list
			}
			else
			{
				printf("Oh no! Something went wrong. Your record could not be saved\n");
			}
			backToMenu();
			system("cls");

			break;
		case 5: // delete
			system("cls");

			Record deletedRec = { {""}, {""}, {""}, {""}, {{-1}, {-1}}, {-1}, {-1} };// declare record to hold deleted information
			success = deleteSong(&headPtr, &deletedRec);

			if (success == 1)
			{
				--recordsRead; // update number of records in linked list

				printf("\nThe following record has been deleted:\n");
				printf("Artist: %s\nAlbum: %s\nSong: %s\nGenre: %s\nSong length: %d mins %d sec\nTimes played: %d\nRating: %d", deletedRec.artist,
					deletedRec.albumTitle, deletedRec.songTitle, deletedRec.genre,
					deletedRec.songLength.minutes, deletedRec.songLength.seconds, deletedRec.timesPlayed, deletedRec.rating);

				putchar('\n');
			}
			
			backToMenu();
			system("cls");

			break;
		case 6: // edit
			
			system("cls");
			editMusic(headPtr);
			printf("\nAny edits made have been saved!\n");
			backToMenu();
			system("cls");

			break;
		case 7: // sort
			
			system("cls");
			success = sortMusic(headPtr, recordsRead);
			system("cls");
			if (success == 1)
			{
				printf("\nYour music has been successfully sorted!");

			}
			else
			{
				printf("\nSorry, you cannot sort an empty list! Try loading some music before trying to sort.\n");
			}
			backToMenu();
			system("cls");

			break;
		case 8: // rate 

			system("cls");
			rateSong(headPtr);
			printf("Any changes made have been saved!\n");
			backToMenu();
			system("cls");

			break;
		case 9: // play

			system("cls");
			playMusic(headPtr);
			backToMenu();
			system("cls");

			break;
		case 10: // shuffle
			
			system("cls");

			if (recordsRead != 0) // if list not empty, can shuffle
			{
				int* randomNumArr = createRandArr(recordsRead);

				if (randomNumArr != NULL)
				{
					shuffleMusic(headPtr, randomNumArr, recordsRead);

					free(randomNumArr); // done with randomNumArr at this point, so can free memory
				}
			}
			else
			{
				printf("Sorry, your playlist is empty and cannot be shuffled.\n");
			}

			backToMenu();
			system("cls");

			break;
		case 11: // exit

			system("cls");
			exitPlaylist(headPtr, infile);
			putchar('\n');
			break;
		}
		

	}

	// test functions

	printf("Test functions will now commense!!\n\n");
	system("pause");
	system("cls");
	testInsertFunction();
	puts("\n\n");
	system("pause");
	system("cls");
	testShuffleFunction();
	puts("\n\n");
	system("pause");
	system("cls");
	testDeleteFunction(); // here have to insert the song Chained to the Rhythm through the keyboard, but deletes successfully
	puts("\n\n");

	return 0;
}
