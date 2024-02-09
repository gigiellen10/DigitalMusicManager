/* Programmer name: Genevieve Kochel
Date: 01/25/2024
Program purpose: This program implements a digital music manager (DMM) with several features that can be
selected from the main menu.
File purpose: This file contains all the struct declarations, #define/#includes, and function 
prototypes for this program.
*/

#define _CRT_SECURE_NO_WARNINGS

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>



typedef struct duration {

	int seconds;
	int minutes;

} Duration;

typedef struct record {

char artist[50];
char albumTitle[100];
char songTitle[50];
char genre[50];
Duration songLength;
int timesPlayed;
int rating;

} Record;

typedef struct node {

	Record data;
	struct node* pPrev; // pointer to the last node in sequence
	struct node* pNext; // pointer to next node in sequence

} Node;

void backToMenu(void);
int displayMenuInput(void);
Node* createNode(Record newData);
int insertAtFront(Node** listPtr, Record newData);
void printList(Node* startPtr, int play); // startPtr is the address of the node to start printing from, used in play() function
void resetArray(char arr[], int size);
int loadMusic(Node** listPtr, FILE* musicListFile);
void playMusic(Node* listPtr);
int searchArtist(Node* pList, Node* artistArr[100], char* artistName); // used in displayMusic() and editMusic()
int displayEditOptions(void);
void printNode(Node* nodeAddress);
int isNumber(char str[]);
void editMusic(Node* pList);
void rateSong(Node* listPtr);
void getValidData(Record *newRecord);
int insertMusic(Node** pList, Record localRec);
void displayMusic(Node* listPtr);
int deleteSong(Node** pList, Record* deletedRec);
int* createRandArr(int recsRead);
void shuffleMusic(Node* pList, int randArr[], int recsRead);
void swap(Node* ptr1, Node* ptr2);
void stringToLower(char str[]);
void formatString(char str[]);
void bubbleSort(Node* pList, int numNodes, int sortType);
int sortMusic(Node* pList, int numNodes);
void storePlaylist(Node* listPtr, FILE* playListFile);
void exitPlaylist(Node* listPtr, FILE* playListFile);