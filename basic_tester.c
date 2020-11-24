/**
 * FILE: BASIC_TESTER.C
 *
 * Can be used to run some tests for the Movie Playlist program.
 * This file can be compiled alongside your own file (playlist.c)
 * and it will automatically call and make use of the functions that 
 * you have implemented and which are contained within your
 * playlist.c file.
 *
 * YOU CAN MODIFY THIS FILE IF YOU WISH, E.G. CHANGE OUTPUT MESSAGES
 * OR TO ADD NEW TESTS, ETC. 
 *
 * YOU WON'T BE SUBMITTING THIS FILE TO MY DUNDEE.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "playlist.h"


/**
 * A helper function, to display the contents of the playlist
 * for debugging purposes. The implementation for this is further 
 * below, under main()
 */
void displayPlaylist(Playlist *pList);

/**
 * Implementation of the 'myMalloc' function. Required so that any
 * references to myMalloc within *YOUR* code will be resolved. 
 * Please leave this function here. You don't need to copy or 
 * place it anywhere else.
 */
int mallocFail = 0;
void* myMalloc(size_t size) {
	if (mallocFail) { return NULL; }
	else { return malloc(size); }
}

/**
 * The main function. Run some basic tests on the playlist.
 */
int main()
{
	printf("## BASIC TESTER FOR MOVIE PLAYLIST PROGRAM\n\n");

	// a variable to store (a pointer to) our playlist
	Playlist *pList = NULL;

	// try to create the playlist
	printf("Attempting to create playlist..");
	pList = createPlaylist(); // This calls your implementation of createPlaylist().
							   // It will be found within your playlist.c file.
							   // When you compile your playlist.c file with this file 
							   // (basic_tester.c), gcc will link everything together.

	// if the playlist wasn't created
	if (pList == NULL)
	{
		// display error msg
		printf("ERROR: Unable to create playlist. Exiting...\n");

		// exit / return from the main function - no point in going further
		return 0;
	}
	else
	{
		printf("..success!\n");
	}

	// (attempt to) add a movie BEFORE the current position in the list
	// this should result in a single-item list, with the head, tail,
	// and current fields all pointing to the same single node
	printf("\nAttempting to add Movie 1, 'The Terrible Pointers'..");
	char movieName[] = "The Terrible Pointers";
	int movieLength = 123;
	int result = insertBeforeCurr(pList, movieName, movieLength); // this calls your implementation of insertBeforeCurr()

	// if movie wasn't added successfully
	if (result != SUCCESS)
	{
		// display error msg
		printf("ERROR: Unable to add movie. Exiting...\n");

		// Before exiting, free memory for the list that was created already
		free(pList);

		// exit / return from the main function - no point in going further
		// if we can't get at least one movie onto the list
		return 0;
	}
	else
	{
		// display success msg
		printf("..movie added successfully!\n");

		// display list for confirmation
		displayPlaylist(pList);
	}

	// (attempt to) add a second movie to the list, adding 
	// if AFTER the current position. This should result in
	// a 2-movie list with Movie 1 at the head, Movie 2 at the
	// tail, and the current field pointing to Movie 1
	printf("\nAttempting to add Movie 2, 'Datastructure Armageddon'..");
	char movieName2[] = "Datastructure Armageddon";
	int movieLength2 = 87;
	result = insertAfterCurr(pList, movieName2, movieLength2); // this calls your implementation of insertAfterCurr()

	// if movie 2 wasn't added successfully
	if (result != SUCCESS)
	{
		// display error msg
		printf("ERROR: Unable to add movie to list.\n");
	}
	else
	{
		// display success msg
		printf("..movie added successfully!\n");

		// display list for confirmation and to check that the
		// movies are in the correct order. Movie 1 should
		// be at the head of the list, ahead of Movie 2
		displayPlaylist(pList);
	}


	Movie gMovie;
	printf("\nAttempting to get (the data for) the current movie in the list..");
	result = getCurrentMovie(pList, &gMovie); // this calls your


	// if didn't work
	if (result != SUCCESS)
	{
		// display error msg
		printf("ERROR: getCurrentMovie returns non-SUCCESS.\n");
	}
	else
	{
		// display success msg
		printf("..getCurrentMovie successful!\n");

		// display the movie details for confirmation
		// should be details for movie 3
		printf("Data for movie obtained: Title='%s'; Length=%dmins.\n", gMovie.name, gMovie.length);
	} 


	// (attempt to) add a third movie to the list, AFTER the current position.
	// This should result in a 3-movie list with Movie 1 at the head, Movie 3
	// in the middle, Movie 2 at the tail, and the current field still pointing 
	// to Movie 1
	printf("\nAttempting to add Movie 3, 'A History of NULL'..");
	char movieName3[] = "A History of NULL";
	int movieLength3 = 34;
	result = insertAfterCurr(pList, movieName3, movieLength3); // this calls your implementation of insertAfterCurr() again

	// if movie 3 wasn't added successfully
	if (result != SUCCESS)
	{
		// display error msg
		printf("ERROR: Unable to add movie to list.\n");
	}
	else
	{
		// display success msg
		printf("..movie added successfully!\n");

		// display list for confirmation and to check that the
		// movies are in the correct order. Movie 1 at the top,
		// Movie 3 in the middle, Movie 2 at the tail, and 
		// 'current' still pointing to Movie 1.
		displayPlaylist(pList);
	}

	// (attempt to) skip to the next position in the list. This should shift
	// the 'current' pointer from its current head position (Movie 1), to 
	// point to Movie 3 instead, in the middle.
	printf("\nAttempting to skip to the next movie in the list..");
	result = skipNext(pList); // this calls your implementation of skipNext() again

	// if skip next didn't work
	if (result != SUCCESS)
	{
		// display error msg
		printf("ERROR: skipNext returns non-SUCCESS.\n");
	}
	else
	{
		// display success msg
		printf("..skipNext successful!\n");
	} 

	// (attempt to) get the (data for the) movie at the current position
	Movie aMovie;
	printf("\nAttempting to get (the data for) the current movie in the list..");
	result = getCurrentMovie(pList, &aMovie); // this calls your implementation of getCurrentMovie()

	// if didn't work
	if (result != SUCCESS)
	{
		// display error msg
		printf("ERROR: getCurrentMovie returns non-SUCCESS.\n");
	}
	else
	{
		// display success msg
		printf("..getCurrentMovie successful!\n");

		// display the movie details for confirmation
		// should be details for movie 3
		printf("Data for movie obtained: Title='%s'; Length=%dmins.\n", aMovie.name, aMovie.length);
	} 




	// (attempt to) remove a movie from the current position in the list
	// the current position is Movie 3, which is in the middle of the list
	// between the head and tail. The value for 'moveForward' is set to '1'
	// to instruct the 'current' pointer to be moved forwards after the removal
	printf("\nAttempting to remove a movie from the list..");
	int moveForward = 1;
	result = removeAtCurr(pList, &aMovie, moveForward); // this calls your implementation of removeAtCurr()

	// if movie wasn't removed successfully
	if (result != SUCCESS)
	{
		// display error msg
		printf("ERROR: Unable to remove movie from list.\n");
	}
	else
	{
		// display success msg
		printf("..movie removed successfully!\n");

		// display details of the movie that was removed
		// for confirmation, should be details for movie 3
		printf("Data for movie removed: Title='%s'; Length=%dmins.\n", aMovie.name, aMovie.length);

		// Re-display the remaining list, for confirmation of 
		// the movies remaining. There should be two movies remaining.
		// Movie 1 at the head and Movie 2 at the tail.
		displayPlaylist(pList);
	}

	// try saving the list to a file, if it has been implemented
	printf("\nAttempting to save the playlist to a file..");
	result = savePlaylist(pList, "out.txt");
	if (result != SUCCESS)
	{
		printf("Error: failed to write playlist to file.\n");
	}
	else
	{
		printf("Successfully managed to write playlist to file\n");
	}

	// add more tests here if you wish, e.g. skip back, test different variants
	// of the remove method (removing from the head, removing from the tail),
	// test variants of the insert methods (inserting after the tail), etc.

	// clear the list when finished.
	printf("\nAttempting to clear the list..");
	if (clearPlaylist(pList) != SUCCESS) // this calls your implementation of clearPlaylist()
	{
		// display error msg
		printf("ERROR: Unable to clear the list when finished.\n");
	}
	else
	{
		printf("..list cleared successfully!\n");		
	}

	// a pointer to a second doubly-linked list - this time to 
	// be loaded from a file
	Playlist *pList2 = NULL;

	// attempt to load a playlist from a file
	printf("\nAttempting to load a playlist from a file..");
	pList2 = loadPlaylist("test_playlist.txt");
	if (pList2 == NULL)
	{
		printf("An error occurred when attempting to load a playlist from a file\n");
	}
	else
	{
		printf("Playlist loaded from file successfully\n");

		// display the contents of the list
		displayPlaylist(pList2);

		// free the memory for the playlist loaded from the file
		result = clearPlaylist(pList2);
		if (result != SUCCESS)
		{
			printf("Error: failed to free playlist loaded from file\n");
		}
		else
		{
			printf("Successfully free-d the playlist loaded from file\n");
		}
	}
}

/**
 * Helper function:a function to display the contents of the 
 * playlist, for debugging purposes.
 */
void displayPlaylist(Playlist *pList)
{
	printf("Displaying current status of Playlist...");

	if (pList == NULL)
	{
		printf("ERROR: NULL playlist.\n.");
		return; // break out of function
	}
	else
	{
		printf("\n");
	}

	// start at the head of the playlist
	Movie *pNextMovie = pList->head;

	// while there is movie to display
	while (pNextMovie != NULL)
	{
		// display movie details
		printf("\tNext Movie is %s which is %d mins in length.\n", pNextMovie->name, pNextMovie->length);

		// move to next movie after this one, if there is one there
		pNextMovie = pNextMovie->next;
	}

	// done
}
