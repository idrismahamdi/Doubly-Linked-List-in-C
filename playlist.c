
/* Name: Idris Mahamdi
   Student Number: 2425092
   Module: AC21008.
 */



/**
 * FILE: PLAYLIST.C
 *
 * THIS FILE  CONTAINS EMPTY / DO-NOTHING IMPLEMENTATIONS
 * FOR THE FUNCTIONS REQUIRED FOR THE MOVIE PLAYLIST PROGRAM. 
 *
 * DO NOT RENAME THESE FUNCTIONS OR CHANGE THEIR RETURN
 * TYPES OR INPUT PARAMETERS.
 *
 * YOU NEED TO COMPLETE THE IMPLEMENTATION OF THESE
 * FUNCTIONS BY REPLACING THE CURRENT IMPLEMENTATIONS
 * WITH YOUR OWN. 
 *
 * THESE FUNCTIONS RECEIVE INPUT PARAMETERS THAT WILL
 * PROVIDE THEM WITH THE INFORMATION THAT THEY REQUIRE. YOU
 * DO NOT NEED TO USE USER INPUT FUNCTIONS SUCH AS SCANF
 * ETC, TO READ IN VALUES. THE PLAYLIST FUNCTIONS ARE CALLED
 * FROM A SEPARATE FILE (SEE THE TESTER PROGRAMS) AND THE
 * INPUTS TO THE FUNCTIONS ARE PROVIDED THERE. 
 *
 * THE FUNCTIONS RETURN VALUES TO REPRESENT SUCCESS, ERROR,
 * OR, IN SOME CASES, DATA THAT HAS TO BE RETURNED (e.g. see
 * the createPlaylist() function). THE CALLER OF THESE FUNCTIONS
 * (in the TESTER programs) WILL EXPECT TO RECEIVE THESE
 * RETURN VALUES IN ORDER TO VERIFY THE OUTCOME OF THE 
 * FUNCTION CALL. 
 *
 * IF THERE ARE ANY FUNCTIONS THAT YOU DON'T HAVE TIME TO 
 * IMPLEMENT, PLEASE LEAVE THE EMPTY / DO-NOTHING IMPLEMENTATION
 * FOR THEM IN THIS FILE, OTHERWISE YOUR PROGRAM WON'T COMPILE
 * WHEN IT IS FED INTO OUR TESTER PROGRAM.
 * 
 */
#include <stdlib.h>	// required for some memory allocation functions such as 'free()'
#include <string.h> // you will need this if you use the string helper functions in C
#include "playlist.h" // required, to include the Playlist data structures
#include <stdio.h> // may be required for File input/output functions

/** #### FUNCTION IMPLEMENTATIONS ## */
/**
 * Create a new, empty playlist, returning a pointer to the newly 
 * allocated playlist OR a value of NULL in the event of error.
 *
 * Remember to use 'myMalloc' for memory allocation instead of 'malloc'
 * 
 * NOTE: WHEREAS MOST OF THE FUNCTIONS HERE WILL RETURN AN 'int' VALUE 
 * THAT CORRESPONDS TO ONE OF THE ERROR CODES LISTED ABOVE, THIS FUNCTION
 * CAN RETURN ONLY ONE OF TWO VALUES: (i) A POINTER TO A NEWLY ALLOCATED
 * PLAYLIST; OR (ii) A VALUE OF NULL. A VALUE OF NULL SHOULD BE RETURNED
 * FOR ANY TYPE OF ERROR, EVEN THOSE WHICH WOULD USUALLY FALL WITHIN
 * THE REMIT OF THE ERROR CODES LISTED ABOVE.
 *
 */
Playlist *createPlaylist()
{
	Playlist *newPlaylist = NULL;


	newPlaylist = (Playlist*)myMalloc(sizeof(Playlist));

	if (newPlaylist == NULL)
	{
		return NULL;
	}

	newPlaylist->head = NULL;
	newPlaylist->tail = NULL;
	newPlaylist->curr = NULL;

	
	return newPlaylist;	
}


/**
 * Add a new movie into the playlist using the input values provided
 * (the movie name and length). The movie should be inserted immediately 
 * BEFORE the current position. Return SUCCESS or otherwise to signify 
 * success or an error.
 *
 * Remember to use 'myMalloc' for memory allocation instead of 'malloc'
 *
 */
int insertBeforeCurr(Playlist *pList, char name[], int length)
{ 	

	if (pList == NULL)
	{
		return INVALID_INPUT_PARAMETER;
	}

	if ((strlen(name) < 1) || (strlen(name) > 50))
	{
		return INVALID_INPUT_PARAMETER;
	}

	if (length < 1)
	{
		return INVALID_INPUT_PARAMETER;
	}

	Movie *newMovie = (Movie*)myMalloc(sizeof(Movie));

	if (newMovie == NULL)
	{
			return MEMORY_ALLOCATION_ERROR;
	}







	strcpy(newMovie->name, name);
	newMovie->length = length;
	newMovie->next = NULL;

	if (pList->head == NULL) {

		pList->head = newMovie;
		pList->curr = newMovie;
		pList->tail = newMovie;
	
		

		return SUCCESS;

	} 
	else
	{

		pList->curr->prev->next = newMovie;
		pList->curr->next->prev = newMovie;

		if (pList->curr->prev == NULL)
		{
			pList->head = newMovie;

		}
		else
		{
		pList->tail = newMovie;
		}
	}
			

	




	return SUCCESS;


}


/**
 * Add a new movie into the playlist using the input values provided
 * (the movie name and length). The movie should be inserted immediately 
 * AFTER the current position. Return SUCCESS or otherwise to signify 
 * success or an error.
 *
 * Remember to use 'myMalloc' for memory allocation instead of 'malloc'
 *
 */
int insertAfterCurr(Playlist *pList, char name[], int length)
{



	if (pList == NULL)
	{
		return INVALID_INPUT_PARAMETER;
	}

	if ((strlen(name) < 1) || (strlen(name) > 50))
	{
		return INVALID_INPUT_PARAMETER;
	}

	if ((length) < 1)
	{
		return INVALID_INPUT_PARAMETER;
	}

	if (pList->curr == NULL)
	{
		return INVALID_LIST_OPERATION;

	}




	
	Movie *newMovie = (Movie*)myMalloc(sizeof(Movie));

	if (newMovie == NULL)
	{
		return MEMORY_ALLOCATION_ERROR;
	}



	strcpy(newMovie->name, name);
	newMovie->length = length;
	


	newMovie->next = pList->curr->next;


	pList->curr->next = newMovie;

	pList->curr->next = newMovie;

	newMovie->prev = pList->curr;

	

	if ((newMovie->next != NULL) && (newMovie->prev != NULL))
	{
		newMovie->next->prev = newMovie;
		


	}
	else
	{
		pList->tail = newMovie;


	}








	return SUCCESS;
}


/**
 * Skip to the next movie in the playlist, immediately AFTER
 * the current position. 
 */
int skipNext(Playlist *pList)
{    

	if (pList == NULL)
	{
		return INVALID_INPUT_PARAMETER;
	}


	if (pList->curr == NULL)
	{
		return INVALID_LIST_OPERATION;

	}


	pList->curr = pList->curr->next;
	
	return SUCCESS;
}


/**
 * Skip to the previous movie in the playlist, immediately 
 * BEFORE the current position. 
 */
int skipPrev(Playlist *pList)
{

	if (pList == NULL)
	{
		return INVALID_INPUT_PARAMETER;
	}


	if (pList->curr == NULL)
	{
		return INVALID_LIST_OPERATION;

	}

	pList->curr = pList->curr->prev;
	
	return SUCCESS;
}


/**
 * Get the data for the current movie in the playlist. A pointer to a
 * a Movie data structure is received as an input parameter (pMovie)
 * into which the data for the current movie should be copied.
 *
 * The function should return SUCCESS or otherwise.
 *
 */
int getCurrentMovie(Playlist *pList, Movie *pMovie){

	if (pList == NULL)
	{
		return INVALID_INPUT_PARAMETER;
	}


	if (pList->curr == NULL)
	{
		return INVALID_LIST_OPERATION;

	}


	strcpy(pMovie->name, pList->curr->name);
	pMovie->length = pList->curr->length;

	return SUCCESS;
}



int removeAtCurr(Playlist *pList, Movie *pMovie, int moveForward)
{
	if (pList == NULL)
	{
		return INVALID_INPUT_PARAMETER;
	}


	if (pList->curr == NULL)
	{
		return INVALID_LIST_OPERATION;

	}

	//Filling in the data to pMovie
	strcpy(pMovie->name, pList->curr->name);
	pMovie->length = pList->curr->length;
	pMovie->next = pList->curr->next;
	pMovie->prev = pList->curr->prev;


	//Linking pMovie previous with the
	pList->curr->prev->next = pMovie->next;
	pList->curr->next->prev = pMovie->prev;
	

	free(pList->curr);

	if (moveForward == 1) 
    {
    	pList->curr = pList->curr->prev->next;
    }
    else 
    {
    	pList->curr = pList->curr->next->prev;
    }

    free(pList->curr);

	return SUCCESS;	
}


/** 
 * Empty the entire contents of the playlist, freeing up any memory that it currently uses. 
 */
int clearPlaylist(Playlist *pList)
{
	if (pList == NULL)
	{
		return INVALID_INPUT_PARAMETER;
	}


	if (pList->head == NULL)
	{
		return INVALID_LIST_OPERATION;

	}

	free(pList);
	return SUCCESS;
}



int savePlaylist(Playlist *pList, char filename[])
{

	if ((pList == NULL) || (filename == NULL)) 
	{
		return INVALID_LIST_OPERATION; 
	}

	Movie *newMovie = (Movie*)myMalloc(sizeof(Movie));

	newMovie = pList->head;
	FILE *saveFile;




	saveFile = fopen(filename, "w");



	while (newMovie != NULL) 
	{
		fprintf(saveFile, "%s#%d#\n",newMovie->name,newMovie->length);

		newMovie = newMovie->next;
	}


	fclose(saveFile);

	return SUCCESS;
}


Playlist *loadPlaylist(char filename[])
{
	//create playlist
	Playlist *newList = NULL;
	newList = createPlaylist();
	
	//valid playlist and filename has got data within it.
	if ((newList == NULL) || (filename == NULL)) 
	{
		return NULL; 
	}


	//File
	FILE *loadFile;
	loadFile = fopen(filename, "r");


	//Initialising variables for reading in movie
	char name[50];
	int length;

	//Initialising variables to allow file to be read, max character for  a line is 256 chacracters
	char line[256];
	char *str;
	const char delimiter[] = "#";

	//This is to check if the first iteration has been, adding it to the head.
	int first = 1;



	while (fgets(line, 256, loadFile) != NULL) 
	{
		//reads in line until first '#'
		str = strtok(line, delimiter);
		strcpy(name, str);


		//contuinues to read the line to the next '#'
		
		str = strtok(NULL, delimiter);
		printf("%s", str );

		//changes from string to int
		length = atoi(str);

		if (first == 1) 
		{
			insertBeforeCurr(newList, name, length);
			first = 0;
		}
		else
		{
			insertAfterCurr(newList, name, length);
		}
	}

	while (fgets(line, 256, loadFile) != NULL) 
	{
		//reads in line until first '#'
		str = strtok(line, delimiter);
		strcpy(name, str);


		//contuinues to read the line to the next '#'
		
		str = strtok(line, delimiter);
		printf("%s", str );

		//changes from string to int
		length = atoi(str);

		if (first == 1) 
		{
			insertBeforeCurr(newList, name, length);
			first = 0;
		}
		else
		{
			insertAfterCurr(newList, name, length);
		}
	}
	
	
	
	fclose(loadFile);

	// //reopening file to start at beggeing to check it is not an empty file
	// loadFile = fopen(filename, "r");

	// if (fgets(line, 256, loadFile) == NULL)
	// {
	// 	return NULL;
	// }
	//  fclose(loadFile);

	

	return newList;

}