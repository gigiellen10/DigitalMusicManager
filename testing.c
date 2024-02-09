/* Programmer name: Genevieve Kochel
Date: 02/05/2024
Program purpose: This program implements a digital music manager (DMM) with several features that can be
selected from the main menu.
File purpose: This file contains all the function definitions for three test functions.
*/

#include "testing.h"


/* Function: void testInsertFunction(void)
Description: This function tests the insertMusic() function with an invalid test point. this test case will 
allow the record to be inserted because a seperate function getValidData() is used to get and validate and validate 
user input via do-while loops, rather than having checks in the actual insert() function itself
this way, the user has multiple trys to input valid data. the function getValidData() only stores the information once it has 
been found to be within specified ranges (ex: cannot be negative) and if input for a number, is in fact, a number
if this test point were to be inserted via user input into getValidData(), it would not pass the test.
Accepts: Void.
Returns: Void.
Preconditions: insertMusic() must be defined in digitalmusic.c.
Postconditions: A success or fail message must be printed.
*/
void testInsertFunction(void)
{
	Node* headPtr = NULL;
	int success = -1;

	//  Test point: artist name = “Perry, Katy”, album title = “Witness”, song title = 
	// “Chained to the Rhythm”, genre = “pop”, song length = “4:36”, times
	// 	played = -1, rating = 6.

	Record rec = { {"\"Perry, Katy\""}, {"Witness"}, {"Chained to the Rhythm"}, {"pop"}, {{4}, {36}}, {-1}, {6} };

	success = insertMusic(&headPtr, rec);

	if (success == 1)
	{
		printf("The record has been inserted successfully!\n");

	}
	else
	{
		printf("The record has not passed the test, and has not been inserted!\n");
	}
	
	if (headPtr != NULL)
	{
		printf("\nThe value of headPtr has been updated to: %p", headPtr);
	}
	else
	{
		printf("\nHeadptr has not been updated.\n");
	}
	
	
}

/* Function: void testDeleteFunction(void)
Description: This function tests the deleteMusic() function using a test list containing a single node. The node
is deleted from the list and a success message is printed.
Accepts: Void.
Returns: Void.
Preconditions: deleteMusic() must be defined in digitalmusic.c.
Postconditions: A success or fail message must be printed.
*/
void testDeleteFunction(void)
{
	Node* headPtr = NULL;
	int success = 0;

	Record rec = { {"\"Perry, Katy\""}, {"Witness"}, {"Chained to the Rhythm"}, {"pop"}, {{4}, {36}}, {3}, {5} };
	Record deletedData = { {""}, {""}, {""}, {""}, {{-1}, {-1}}, {-1}, {-1} };

	// create a node for the new record

	Node* memPtr = createNode(rec);

	if (memPtr != NULL)
	{
		headPtr = memPtr; // set to only node in list

		success = deleteSong(&headPtr, &deletedData);

	}

	if (success == 1)
	{
		printf("\nThe song was deleted successfully and headPtr is now: %p", headPtr);

	}
	else
	{
		printf("Your data was not deleted successfully. The value of headPtr is still: %p", headPtr);
	}

}

/* Function: void testShuffleFunction(void)
Description: This function tests the shuffleMusic() function using a test list containing 3 nodes. The list is 
printed in the order: 3, 1, 2 specified by the array passed into the shuffle function.
Accepts: Void.
Returns: Void.
Preconditions: shuffleMusic() must be defined in digitalmusic.c.
Postconditions: The records must be printed to the screen in the order: 3, 1, 2.
*/
void testShuffleFunction(void)
{
	Node* headPtr = NULL;
	int randArr[100] = { 3, 1, 2 };
	Record data1 = { {"\"Perry, Katy\""}, {"Witness"}, {"Chained to the Rhythm"}, {"pop"}, {{4}, {36}}, {-1}, {6} };
	Record data2 = { {"The Weeknd"}, {"After Hours"}, {"Nothing Compares"}, {"R&B"}, {{3}, {40}}, {50}, {5} };
	Record data3 = { {"Suicide Boys"}, {"Under the Moon"}, {"Paris"}, {"Dark Trap"}, {{1}, {50}}, {30}, {5} };

	insertAtFront(&headPtr, data1);
	insertAtFront(&headPtr, data2);
	insertAtFront(&headPtr, data3);

	shuffleMusic(headPtr, randArr, 3); // shuffle music prints the order in which the songs were played.


}


