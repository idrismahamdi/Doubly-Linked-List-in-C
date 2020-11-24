/**
 * FILE: PLAYLIST.H
 *
 * Contains definitions of data structures and error codes required for the
 * Movie Playlist Program. It also provides declarations of the functions 
 * that have to be implemented too.
 *
 * NOTE: YOU DO NOT NEED TO MODIFY THIS FILE. IT CAN BE USED AS-IS.
 * THE CODE THAT YOU IMPLEMENT WILL BE IN THE PLAYLIST.C FILE.
 */

#ifndef __MOVIE_PLAYLIST_HEADER__ // this is a 'guard' on the header file, to prevent it's contents from
#define __MOVIE_PLAYLIST_HEADER__ // being redefined more than once during the build process

#include <stddef.h>// header required for myMalloc function

/**
 * ### ERROR codes / SUCCESS codes ###
 * PLEASE USE THESE AS THE RETURN VALUES FOR YOUR FUNCTIONS. 
 *
 * Example:
 * return INVALID_INPUT_PARAMETER;
 *
 */
#define SUCCESS                  100   // Value to be returned if a function is completed successfully
#define INVALID_INPUT_PARAMETER  101   // Value to be returned if you detect that one of the input parameters 
                                       // into your function is invalid, e.g. it is NULL or an unexpected value
#define MEMORY_ALLOCATION_ERROR  102   // Value to be returned if a memory allocation error occurs during your function
#define INVALID_LIST_OPERATION   103   // Value to be returned if your function detects an operation that is being
                                       // attempted on your list data structure isn't valid or your list
                                       // isn't in a ready state to receive. For example, an attempt is made to remove
                                       // an item from an empty list
#define NOT_IMPLEMENTED          104   // Value to be returned if you haven't implemented this function yet
#define FILE_IO_ERROR            105   // May be required for some File IO tasks. E.g. failure to open a file.

/** ### DATA STRUCTURES ### */

/* typedef for movies that may be added to a playlist */
/* DO NOT MODIFY */
typedef struct movie {
	char name[50];       // the name of the movie
	int length;          // the length of the movie in minutes
	struct movie *prev;	// points to the previous movie in the playlist before this one
	struct movie *next;	// points to the next movie in the playlist after this one
} Movie;


/* typedef for a playlist of movies */
/* DO NOT MODIFY */
typedef struct playlist {
	Movie *head;	// points to the movie at the start / head of the playlist
	Movie *tail;	// points to the movie at the end / tail of the playlist
	Movie *curr;	// points to the 'current' movie, i.e. the one that is currently being viewed or last watched
} Playlist;


/** ### FUNCTION DECLARATIONS ### */
/*  DO NOT MODIFY FUNCTION NAMES, RETURN TYPES, OR INPUT PARAMETERS.
 *  YOU WILL IMPLEMENT THESE FUNCTIONS IN THE SEPARATE PLAYLIST.C FILE.
 */

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
Playlist *createPlaylist();


/**
 * Add a new movie into the playlist using the input values provided
 * (the movie name and length). The movie should be inserted immediately 
 * BEFORE the current position. Return SUCCESS or otherwise to signify 
 * success or an error.
 *
 * Remember to use 'myMalloc' for memory allocation instead of 'malloc'
 *
 */
int insertBeforeCurr(Playlist *pList, char name[], int length);


/**
 * Add a new movie into the playlist using the input values provided
 * (the movie name and length). The movie should be inserted immediately 
 * AFTER the current position. Return SUCCESS or otherwise to signify 
 * success or an error.
 *
 * Remember to use 'myMalloc' for memory allocation instead of 'malloc'
 *
 */
int insertAfterCurr(Playlist *pList, char name[], int length);


/**
 * Skip to the next movie in the playlist, immediately AFTER
 * the current position. 
 */
int skipNext(Playlist *pList);


/**
 * Skip to the previous movie in the playlist, immediately 
 * BEFORE the current position. 
 */
int skipPrev(Playlist *pList);


/**
 * Get the data for the current movie in the playlist. A pointer to a
 * a Movie data structure is received as an input parameter (pMovie)
 * into which the data for the current movie should be copied.
 *
 * The function should return SUCCESS or otherwise.
 *
 */
int getCurrentMovie(Playlist *pList, Movie *pMovie);


/**
 * Remove the movie that is at the current position in the playlist and return SUCCESS 
 * or otherwise.
 *
 * An input variable is provided (pMovie) into which the data for the movie being deleted 
 * should be copied - so that the movie data can then be used elsewhere by the caller
 * of the function.
 *
 * The value of the input variable 'moveForward' should be inspected to determine what to
 * do with the 'curr' pointer in the list after the removal has taken place. If ‘moveForward’ 
 * is set to 1, the ‘curr’ pointer should be set to point to the movie in the list which
 * occurs immediately after the one which has just been removed. If 'moveForward' is anything
 * other than 1, the ‘curr’ pointer should be set to point to the movie in the list which 
 * occurs immediately prior to the one which has just been removed. 
 *
 */
int removeAtCurr(Playlist *pList, Movie *pMovie, int moveForward);


/** 
 * Empty the entire contents of the playlist, freeing up any memory that it currently uses. 
 */
int clearPlaylist(Playlist *pList);


/**
 * ADDED EXTRA: save details of all of the movies in the playlist into a file. 
 *
 * The file contents are expected to be formatted in a specific way. Please see 
 * the assignment specification for more details.
 */
int savePlaylist(Playlist *pList, char filename[]);


/**
 * ADDED EXTRA: load a playlist of movies from a file. 
 *
 * This function has similarities to the 'createPlaylist()' function. It should create
 * and return a new Playlist. Instead of returning an empty playlist, it should add
 * movies into the playlist first (based on the file contents which have been read), so
 * that a (pointer to) an already populated playlist is then returned. 
 *
 * In the event of any errors, a value of NULL should be returned instead.
 * 
 * The file from which the movie playlist is read is formatted in a specific way. 
 * Please see the assignment specification for more details.
 *
 * NOTE: WHEREAS MOST OF THE FUNCTIONS HERE WILL RETURN AN 'int' VALUE 
 * THAT CORRESPONDS TO ONE OF THE ERROR CODES LISTED ABOVE, THIS FUNCTION
 * CAN RETURN ONLY ONE OF TWO VALUES: (i) A POINTER TO A NEWLY ALLOCATED
 * PLAYLIST; OR (ii) A VALUE OF NULL. A VALUE OF NULL SHOULD BE RETURNED
 * FOR ANY TYPE OF ERROR, EVEN THOSE WHICH WOULD USUALLY FALL WITHIN
 * THE REMIT OF THE ERROR CODES LISTED ABOVE.
 *
 */
Playlist *loadPlaylist(char filename[]);

/**
 * myMalloc(): a function to allocate memory.
 *
 * DO NOT REMOVE OR MODIFY THIS - PLEASE LEAVE AS IS
 *
 * You will use myMalloc() to allocate memory in your own code. 
 * The implementation of this function is provided to you and
 * has already been placed in the accompanying 'tester' files 
 * where it is ready to use. You simply need to call the
 * function in your code where required. When you compile your
 * own code (playlist.c) with either of the tester files 
 * (basic_tester.c or validity_tester.c) everything will be linked 
 * together. 
 *
 * myMalloc works exactly the same way as malloc. For example, if 
 * you were using malloc to allocate an array of 10 integers, it
 * would be as follows:
 *
 * int *array = (int*)malloc(sizeof(int) * 10);
 * 
 * Using myMalloc will be exactly the same:
 *
 * int *array = (int*)myMalloc(sizeof(int) * 10);
 * 
 */
void *myMalloc(size_t size);

#endif
