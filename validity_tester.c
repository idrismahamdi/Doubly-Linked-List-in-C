/**
 * FILE: VALIDITY_TESTER.C
 *
 * Can be used to run some additional tests for the Movie Playlist program.
 * In this case, focusing on validity of input parameters into functions
 * and valid states for the list after operations.
 *
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
#include <string.h>

/**
 * Implementation of the 'myMalloc' function. Required so that any
 * references to myMalloc within your code will be resolved. 
 * Please leave this function here. You don't need to copy or 
 * place it anywhere else.
 */
int mallocFail = 0;
void* myMalloc(size_t size) {
	if (mallocFail) { return NULL; }
	else { return malloc(size); }
}

/**
 * main function
 */
int main()
{
	printf("## VALIDITY TESTER PROGRAM FOR MOVIE PLAYLIST\n\n");

	// a variable to store the result of calling functions - used later
	int result;

	// a variable to store Movie data which has been removed or obtained at from the list - used later
	Movie movieInfo;

	// variables to create test data for different movies to add to the list
	// movie 1
	char movieName1[] = "A Field of Wandering Iterators";
	int movieLength1 = 123;

	// movie 2
	char movieName2[] = "The NULL-ified Man";
	int movieLength2 = 101;

	// movie 3
	char movieName3[] = "There's Something About Professor Jones";
	int movieLength3 = 94;

	// a pointer to the list, not yet allocated
	Playlist *pList = NULL;

	// ## TEST CREATING THE QUEUE

	// call function to create the list and receive a pointer to it,
	// storing the pointer in our temporary variable
	printf("Attempting to create list..");
	pList = createPlaylist();

	// if list wasn't created
	if (pList == NULL)
	{
		// display error msg
		printf("An error occurred when attempting to create the list\n");

		// exit / return from the main function - no point in going further
		return 0;
	}
	else
	{
		// display success msg
		printf("List created successfully\n");

		// make sure the list has been initialised correctly 
		if ((pList->head != NULL) || (pList->tail != NULL) || (pList->curr != NULL))
		{
			// display error msg
		    printf("FAIL: list has NOT been initialised properly. The head, tail, and curr should ALL be NULL. Rectifying now.\n");
		    pList->head = pList->tail = pList->curr = NULL;
		}
		else
		{	
			printf("PASS: List has been initialised correctly, e.g. head, tail, and curr are NULL\n");
		}
	}

	// ## INSERT AN ITEM ONTO THE LIST
	
	// try inserting a new movie BEFORE the current position in the list
	printf("\nAttempting to insert a movie into the playlist..");
	result = insertBeforeCurr(pList, movieName1, movieLength1); 
	if (result != SUCCESS)
	{
		printf("ERROR: insertBeforeCurr() returns non-SUCCESS code.\n");
	}
	else
	{
		printf("insertBeforeCurr() returns SUCCESS.\n");

		// the movie should now be at the head, tail, and curr of the queue
		// make sure the head isn't empty
		if (pList->head == NULL)
		{
			printf("FAIL: head should NOT be NULL after newly added movie\n");
		}
		else
		{
			printf("PASS: head should be non-NULL after newly added movie\n");
		}

		// make sure the curr isn't empty
		if (pList->curr == NULL)
		{
			printf("FAIL: curr should NOT be NULL after newly added movie\n");
		}
		else
		{
			printf("PASS: curr should be non-NULL after newly added movie\n");
		}

		// make sure the tail isn't empty
		if (pList->tail == NULL)
		{
			printf("FAIL: tail should NOT be NULL after newly added movie\n");
		}
		else
		{
			printf("PASS: tail should  be non-NULL after newly added movie\n");

			// the head, the tail, and curr should all be pointing to the same node in memory
			if ((pList->head != pList->tail) || (pList->curr != pList->tail) || (pList->curr != pList->head))
			{
				printf("FAIL: head, tail, AND curr should all point to the same movie in a single-item list\n");
			}
			else
			{
				printf("PASS: head, tail, AND curr should all point to the same movie in a single-item list\n");
			}

			// tail's next should be null / empty
			if ((pList->tail != NULL) && (pList->tail->next != NULL))
			{
				printf("FAIL: tail's next should be NULL\n");
			}
			else
			{
				printf("PASS: tail's next should be NULL\n");
			}

			// head's prev should be null / empty
			if ((pList->head != NULL) && (pList->head->prev != NULL))
			{
				printf("FAIL: head's prev should be NULL\n");
			}
			else
			{
				printf("PASS: head's prev should be NULL\n");
			}

			// tail OK. Check the movie data in the tail node matches what was added
			if ((pList->tail->length != movieLength1)
				|| (strncmp(pList->tail->name, movieName1, 50)) != 0)
			{
				printf("FAIL: data in newly added node doesn't appear to be as expected\n");
			}
			else
			{
				printf("PASS: data in newly added node is correct.\n");
			}

		}
	}

	// ## INSERT ANOTHER MOVIE INTO THE LIST

	// try inserting movie 2 AFTER the current position
	printf("\nAttempting to insert movie 2 into the list..");
	result = insertAfterCurr(pList, movieName2, movieLength2); 
	if (result != SUCCESS)
	{
		printf("ERROR: insertAfterCurr() returns non-SUCCESS code.\n");
	}
	else
	{
		printf("insertAfterCurr() returns SUCCESS.\n");

		// the newly added movie should now be at the tail of the list
		// make sure the head isn't empty
		if (pList->head == NULL)
		{
			printf("FAIL: head should not be NULL after newly added movie\n");
		}
		else
		{
			printf("PASS: head should be non-NULL after newly added movie\n");

			// the tail of the list shouldn't be NULL either
			if (pList->tail == NULL)
			{
				printf("FAIL: tail should NOT be NULL after newly added movie\n");
			}
			else
			{
				printf("PASS: tail should be non-NULL after newly added movie\n");
			}

			// the head and the tail of the list should NOT be pointing to the same
			// node in a two-item queue
			if ((pList->head != NULL) && (pList->tail != NULL) && (pList->head != pList->tail))
			{
				printf("PASS: head AND tail should NOT point to the same movie in a list with more than one movie\n");
			}
			else
			{
				printf("FAIL: head AND tail should NOT point to the same movie in a list with more than one movie\n");
			}

			// the curr field should still be referring to the head node in the list and
			// NOT the newly added tail. 
			if ((pList->head != NULL) && (pList->tail != NULL) && (pList->curr != NULL) && (pList->head == pList->curr) && (pList->tail != pList->curr))
			{
				printf("PASS: curr should be the same as head and not the same as tail when doing insert AFTER.\n");
			}
			else
			{
				printf("FAIL: curr should be the same as head and not the same as tail when doing insert AFTER.\n");
			}
		
			// check the data in the newly added movie matches what was added (movie 2)
			if ((pList->tail->length != movieLength2)
				|| (strncmp(pList->tail->name, movieName2, 50)) != 0)
			{
				printf("FAIL: data in newly added movie doesn't appear to be as expected\n");
			}
			else
			{
				printf("PASS: data in newly added movie node is correct.\n");
			}

		}
	}

	// ## INSERT ANOTHER MOVIE INTO THE LIST

	// try inserting movie 3 BEFORE the current position
	printf("\nAttempting to insert movie 3 into the list..");
	result = insertBeforeCurr(pList, movieName3, movieLength3); 
	if (result != SUCCESS)
	{
		printf("ERROR: insertBeforeCurr() returns non-SUCCESS code.\n");
	}
	else
	{
		printf("insertBeforeCurr() returns SUCCESS.\n");

		// the movie should now be at the head, tail, and curr of the queue
		// make sure the head isn't empty
		if (pList->head == NULL)
		{
			printf("FAIL: head should NOT be NULL after newly added movie\n");
		}
		else
		{
			printf("PASS: head should be non-NULL after newly added movie\n");
		}

		// make sure the curr isn't empty
		if (pList->curr == NULL)
		{
			printf("FAIL: curr should NOT be NULL after newly added movie\n");
		}
		else
		{
			printf("PASS: curr should be non-NULL after newly added movie\n");
		}

		// make sure the tail isn't empty
		if (pList->tail == NULL)
		{
			printf("FAIL: tail should NOT be NULL after newly added movie\n");
		}
		else
		{
			printf("PASS: tail should  be non-NULL after newly added movie\n");

			// the head, the tail, and curr should all be pointing to the same node in memory
			if ((pList->head != pList->tail) || (pList->curr != pList->tail) || (pList->curr != pList->head))
			{
				printf("FAIL: head, tail, AND curr should all point to the same movie in a single-item list\n");
			}
			else
			{
				printf("PASS: head, tail, AND curr should all point to the same movie in a single-item list\n");
			}

			// tail's next should be null / empty
			if ((pList->tail != NULL) && (pList->tail->next != NULL))
			{
				printf("FAIL: tail's next should be NULL\n");
			}
			else
			{
				printf("PASS: tail's next should be NULL\n");
			}

			// head's prev should be null / empty
			if ((pList->head != NULL) && (pList->head->prev != NULL))
			{
				printf("FAIL: head's prev should be NULL\n");
			}
			else
			{
				printf("PASS: head's prev should be NULL\n");
			}

			// tail OK. Check the movie data in the tail node matches what was added
			if ((pList->tail->length != movieLength1)
				|| (strncmp(pList->tail->name, movieName1, 50)) != 0)
			{
				printf("FAIL: data in newly added node doesn't appear to be as expected\n");
			}
			else
			{
				printf("PASS: data in newly added node is correct.\n");
			}

		}
	}

	// ## TRY REMOVING A MOVIE FROM THE CURRENT POSITION IN THE LIST

	// call remove function - providing it with the memory address
	// of variable 'movieInfo' to receive the movie data. Indicate
	// that the 'curr' pointer should be moved forward after the removal
	int moveForward = 1;
	printf("\nAttempting to remove a movie from the current position..");
	result = removeAtCurr(pList, &movieInfo, moveForward); 
	if (result != SUCCESS)
	{
		printf("ERROR: removeAtCurr() returns non-SUCCESS code.\n");
	}
	else
	{
		printf("removeAtCurr() returns SUCCESS.\n");

		// check that the movie removed matches what it should be - it should contain the data for movie 3
		if ((movieInfo.length != movieLength1)
			|| (strncmp(movieInfo.name, movieName1, 50)) != 0)
		{
			printf("FAIL: data in removed node doesn't appear to be as expected\n");
		}
		else
		{
			printf("PASS: data in removed node is correct.\n");
		}

		// after removal, there should be two movies remaining in the list and
		// with the 'curr' field shifted to the tail node

		// check that the head and tail aren't the same
		if ((pList->head != NULL) && (pList->tail != NULL) && (pList->head != pList->tail))
		{
			printf("PASS: head and tail should NOT point to the same movie in the list after remove.\n");
		}
		else	
		{
			printf("FAIL: head and tail should NOT point to the same movie in the list after remove.\n");
			
		}

		// check that curr is the same as tail and not head
		if ((pList->head != NULL) && (pList->tail != NULL) && (pList->curr != NULL) && (pList->head != pList->curr) && (pList->tail == pList->curr))
		{
			printf("PASS: curr should mow point to tail (and not head) after remove.\n");
		}
		else	
		{
			printf("FAIL: curr should now point to tail (and not head) after remove.\n");
			
		}

		// there should be nothing after the tail and nothing prior to the head
		if ((pList->head != NULL) && (pList->tail != NULL) && (pList->tail->next == NULL) && (pList->head->prev == NULL))
		{
			printf("PASS: tail's next should be NULL and head's prev should be NULL.\n");
		}
		else
		{
			printf("FAIL: tail's next should be NULL and head's prev should be NULL.\n");
		}

		// head's next should be the tail and tail's prev should be the head
		if ((pList->head != NULL) && (pList->tail != NULL) && (pList->head->next == pList->tail) && (pList->tail->prev == pList->head))
		{
			printf("PASS: tail's prev should be head, and head's next should be tail.\n");
		}
		else
		{
			printf("FAIL: tail's prev should be head, and head's next should be tail.\n");
		}
	}

	// you can add more more tests of your own here if you wish... 

	// ## CLEAR THE LIST 

	// call clear function 
	printf("\nAttempting to clear the list..");
	result = clearPlaylist(pList); 
	if (result != SUCCESS)
	{
		printf("ERROR: clearPlaylist() returns non-SUCCESS code.\n");
	}
	else
	{
		printf("clearPlaylist() returns SUCCESS code.\n");
	}

	// ## ADVANCED TESTS
	printf("\nAttempting advanced tests for validation of inputs..\n");

	// create another list 
	pList = createPlaylist();

	// try removing a movie from an empty list
	result = removeAtCurr(pList, &movieInfo, 0);
	if (result != INVALID_LIST_OPERATION)
	{
		printf("FAIL: should have detected attempt to remove Movie from an empty list\n");
	}
	else
	{
		printf("PASS: Correctly identified attempt to remove Movie from an empty list\n");
	}

	// try getting the movie at the current position in the list, when the list is empty
	result = getCurrentMovie(pList, &movieInfo);
	if (result != INVALID_LIST_OPERATION)
	{
		printf("FAIL: should have detected attempt to get movie from an empty list.\n");
	}
	else
	{
		printf("PASS: Correctly identified attempt to get movie from an empty list.\n");
	}

	// try to insert a valid movie to a non-valid (NULL) list
	result = insertAfterCurr(NULL, movieName1, movieLength1);
	if (result != INVALID_INPUT_PARAMETER)
	{
		printf("FAIL: should have detected attempt to insert movie into NULL list\n");
	}
	else
	{
		printf("PASS: Correctly identified attempt to add movie into a NULL list\n");
	}

	// try to add a non-valid movie (NULL movie name) to a valid list
	result = insertBeforeCurr(pList, NULL, movieLength1);
	if (result != INVALID_INPUT_PARAMETER)
	{
		printf("FAIL: should have detected attempt to add non-valid movie name to list\n");
	}
	else
	{
		printf("PASS: Correctly identified attempt to add non-valid movie name to list\n");
	}

	// clear the list when finished
	clearPlaylist(pList);

	// end of tests
	return 0;
}