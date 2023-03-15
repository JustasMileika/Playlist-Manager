// Author of the program - Justas Mileika 2021 Vilnius University, Software Engineering, Bachelor's degree, first year, group 2. E-mail: justasmileika@gmail.com
#ifndef BACKEND_FUNCTIONS_H_INCLUDED
#define BACKEND_FUNCTIONS_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>

#define DATABASE_FILE_NAME "musicDatabase.txt"

#define MAX_LINE_LENGTH 255
#define MAX_LIST_INDEX 999999999

// function that creates a new playlist with user input. Parameter maxLineLength shows the maximum length of the input the user can give
void createNewPlaylist(int maxLineLength);

// function that modifies an existing playlist and the name of it is received from the user from the screen
// Parameter maxLineLength shows the maximum length of the input the user can give and maxListIndex indicates the maximum position of the list the user can choose
void modifyExistingPlaylist(int maxLineLength, int maxListIndex);

// function that allows the user to browse the database file "musicDatabase.txt". Parameter maxLineLength shows the maximum length of the input the user can give
void checkDatabase(int maxLineLength);

// function that prints the message MSG_HELP on the screen
void printHelp();

// function that prints the message PROGRAM_OUTRO to the screen and ends the program
void exitProgram();

// function that returns the character array containing the link of the passed parameter song if an exact match of all three structure Song parameters was found in the passed parameter file
// Parameter maxLineLength shows the maximum length of the input the user can give
// NULL is returned if no such song was found
char *lookupSong(FILE *file, Song song, int maxLineLength);

// function that prints all four structure Song parameters of the parameter song to a file with the name fileName one parameter in each line in the order: name, artist, genre, link
// NULL is returned if function unsuccessful
char *addSongToDatabase(char *fileName, Song song);

// function that returns a linked list filled with pointers to Song type objects loaded from the file with a name fileName
// NULL is returned if function unsuccessful
List *loadPlaylistFromFile(char *fileName, int maxLineLength);

// function that writes out a playlist in a file with the name playlitName
// NULL is returned if function unsuccessful
char *savePlaylistInFile(List *playlist, char *playlistName);

// function that modifies a linked list filled with pointers to Song type objects according to user input
// parameter fileName specifies the file name where the playlist is located, maxIndexSize indicates the maximum value the user can choose as a position of the list
// Parameter maxLineLength shows the maximum length of the input the user can give
void modifyPlaylist(List **playlist, char* fileName, int maxIndexSize, int maxLineLength);

// function that returns 1 if the pointers x and y are equal when dereferenced as Song type structures and compared on the name parameter of the Song structure and 0 otherwise
int compareName(void *x, void *y);

// function that returns 1 if the pointers x and y are equal when dereferenced as Song type structures and compared on the artist parameter of the Song structure and 0 otherwise
int compareArtist(void *x, void *y);

// function that returns 1 if the pointers x and y are equal when dereferenced as Song type structures and compared on the genre parameter of the Song structure and 0 otherwise
int compareGenre(void *x, void *y);

// function that prints a Song type object with all Song structure parameters to a passed file
void printSongToFile(Song song, FILE *file);

#endif // BACKEND_FUNCTIONS_H_INCLUDED
