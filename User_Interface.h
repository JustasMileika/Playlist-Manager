// Author of the program - Justas Mileika 2021 Vilnius University, Software Engineering, Bachelor's degree, first year, group 2. E-mail: justasmileika@gmail.com
#ifndef USER_INTERFACE_H_INCLUDED
#define USER_INTERFACE_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>

#define MAIN_MENU "Main Menu:\n"
#define SONG_PARAMETERS "Song parameters:\n"
#define DATABASE_MENU "Database Menu:\n"
#define SONG_MENU "Song Menu:\n"
#define PLAYLIST_MODIFICATION_MENU "Playlist Modification Menu:\n"
#define PLAYLIST_CREATION_MENU "Playlist Creation Menu:\n"
#define OUTPUT_MENU "Output Menu:\n"
#define COMPRESSION_MENU "Compression Menu\n"

#define MSG_ASKING_FOR_SAVE_TO_FILE_CHOICE "Do you wish to save this playlist to a file?\n"
#define MSG_ASKING_FOR_SAVE_WITH_NAME_CHOICE "Do you wish to save this playlist to a text file with the name You specified earlier?\n"
#define MSG_ASKING_FOR_PLAYLIST_NAME "\nPlease choose a name for your playlist: "
#define MSG_ASKING_FOR_OUTPUT_OPTIONS "\nPlease choose whether you wish to see the playlist on the screen: "
#define MSG_ASKING_NEW_PLAYLIST_FILENAME "Please Enter a text file name where you want to save the playlist: "
#define ASKING_FOR_POSITION_INSERT "\nChoose a position where you wish to insert a song:\n"
#define ASKING_FOR_POSITION_DELETE "\nChoose the position of the song you want to delete\n"
#define ASKING_FOR_POSITION_CHANGE "\nChoose the position of the song you want to change\n"
#define ASKING_FOR_INTEGER "Enter an integer in the playlist range ([%d; %d]): \n"
#define ASKING_CHOICE "\nPlease choose what do you wish to do: "
#define MSG_ASKING_FOR_PLAYLIST_FILE "\nEnter a name of the file where the playlist you want to modify is located: "

#define MSG_ASKING_FOR_NAME "\nEnter the song name: "
#define MSG_ASKING_FOR_ARTIST "\nEnter the artist: "
#define MSG_ASKING_FOR_GENRE "\nEnter the genre: "
#define MSG_ASKING_FOR_LINK "\nEnter the link: "

#define MSG_INPUT_IS_TOO_LONG "The input you have entered is too long, please enter an input that is shorter than %d symbols\n"
#define MSG_SONG_ADDED_TO_PLAYLIST "\nSong added to playlist successfully\n"
#define MSG_PLAYLIST_NOT_SAVED_INVALID_NAME "Playlist could not be saved because the name You have entered earlier is not valid\n"
#define MSG_MODIFICATIONS_UNSUCCESSFUL "\nModifications could not be saved in that file\n"
#define MSG_MODIFICATIONS_SUCCESSFUL "\nModifications successfully saved\n"
#define MSG_COMPRESSION_SUCCESSFUL "\nThe playlist has been compressed successfully\n"
#define MSG_SONG_NOT_FOUND_IN_DATABASE "\nSong was not found\n"
#define MSG_SONG_FOUND_IN_DATABASE "\nThe song was found, the link of it is: %s"
#define DATABASE_NOT_OPENED "\nDatabase file could not be opened\n"
#define FILE_NOT_OPENED "\nFile could not be opened\n"
#define DATABASE_UPDATED_SUCCESSFULLY "\nDatabase updated successfully\n"
#define PLAYLIST_SAVED_SUCCESSFULLY "Playlist saved successfully\n"
#define FILE_OPENED_SUCCESSFULY "\nFile opened successfully\n"
#define SONG_ALREADY_IN_DATABASE "The song already exists in the database\n"
#define PROGRAM_OUTRO "\nThank you for using the program!\n"
#define MSG_NOT_ENOUGH_MEMORY "Your system is not able to run this program, sorry...\n"
#define MSG_INVALID_INPUT "\nInvalid input\n"

#define MSG_DELETION_SUCCESSFUL "\nDeletion successful\n"
#define MSG_INSERTION_SUCCESSFUL "\nInsertion successful\n"
#define MSG_CHANGE_SUCCESSFUL "\nChange successful\n"

#define PLAYLIST_DISPLAY "\nYour playlist:\n\n"
#define EMPTY_PLAYLIST "EMPTY PLAYLIST\n"
#define MSG_NULL "NULL\n"

#define MSG_LIST_SIZE_WARNING "\nThe playlist size is bigger than the maximum position the program can hold so the maximum index has been set to %d\n"

#define MSG_HELP "\nHELP: The program lets You create a new playlist, view and modify an existing playlist and browse the database\n\
The database with songs and links to them is located in the text document called \"musicDatabase.txt\" and this file should not be tampered with as every other file created by this program\n\
All playlist management should be done trought this program only!\nIn order to create a new playlist You will need to enter the name of the playlist and choose \
a song to insert into the playlist by providing the program the song name, the artist and the genre of the song. All the song parameters must match with the information of the song\
in the database for it to be found. If no such song was found, You will have a choice to add this song to the database by providing a link to this song\nYou can also save this playlist\
in a file for later usage\nAnother option of the program is to modify existing playlist\nIn there You will find options to view the playlist and then change, delete or insert a song to\
your playlist\nAnother option is to make your playlist more various by compressing a playlist by artist, genre or song name\nLastly, You are able to browse the database for links to a specific song\
and update the database yourself by adding new songs\nIf  you have any questions about this program, please contact me @ justasmileika@gmail.com.\n"

#define MSG_PROGRAM_INTRODUCTION "\nWelcome to Playlist Manager!\n\n"


// Menu options initialized in User_Interface.c
extern char *songParameters[];
extern char *menuOptions[];
extern char *createPlaylistOptions[];
extern char *noSongFoundOptions[];
extern char *booleanOptions[];
extern char *modifyOptions[];
extern char *compressingOptions[];
extern char *databaseOptions[];

// Song structure
typedef struct Song
{
    char *name;
    char *artist;
    char *genre;
    char *link;
} Song;

// function that shows the menu in menuOptions on the screen and prints the message inputMsg until a valid number is received from the user which is returned
// -1 is returned if function is unsuccessfull
int showMenu(char *menuTitle, char *menuOptions[], int menuSize, char *inputMsg);

// function that prints out program introduction messages to the screen
void printProgramIntroduction();

// function that asks the user to choose which of the Song structure parameter to print and prints that parameter value of the whole playlist playlist on the screen
void printPlaylist(List *playlist);

// function that prints the name parameter of the Song structure of the dereferenced pointer value
void printName(void *value);

// function that prints the artist parameter of the Song structure of the dereferenced pointer value
void printArtist(void *value);

// function that prints the genre parameter of the Song structure of the dereferenced pointer value
void printGenre(void *value);

// function that prints the link parameter of the Song structure of the dereferenced pointer value
void printLink(void *value);

// function that takes in a character array from the screen of maximum maxLength size
// returns NULL if function unsuccessfull
char *getString(int maxLength);

// function that prints the message msgAskingForInput and takes in an integer from the screen in the interval [min; max]
// returns -1 if function unsuccessfull
int getInteger(char *msgAskingForInput, int min, int max);

// function that takes in a song with it's parameters from the user from the screen of maximum length maxLineLength and returns a structure with those values
// parameter linkNeeded indicates a boolean which shows whether it is needed to scan a link from the user or not
Song getSongFromInput(int linkNeeded, int maxLineLength);

// function that prints a message MSG_PROGRAM_INTRODUCTION to the screen and ends the program
void notEnoughtMemory();

#endif // USER_INTERFACE_H_INCLUDED
