// Author of the program - Justas Mileika 2021 Vilnius University, Software Engineering, Bachelor's degree, first year, group 2. E-mail: justasmileika@gmail.com
#include "module.h"
#include "User_Interface.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *songParameters[] = {"Song name", "Artist", "Genre", "Link"};
char *menuOptions[] = {"Create a new playlist", "View an existing playlist", "Database", "Help", "Exit"};
char *createPlaylistOptions[] = {"Add a song to playlist", "Finish building playlist"};
char *noSongFoundOptions[] = {"Skip this song", "Keep this song and add it to the database(You will need to provide a link to the song)"};
char *booleanOptions[] = {"YES", "NO"};
char *modifyOptions[] = {"View a playlist", "Add a song", "Remove a song", "Change a song", "Compress a playlist", "End modification"};
char *compressingOptions[] = {"Song name", "Artist", "Genre", "Exit compressing"};
char *databaseOptions[] = {"Look up song", "Add song to database", "Exit database"};

void printProgramIntroduction()
{
    printf(MSG_PROGRAM_INTRODUCTION);
}

int getInteger(char *msgAskingForInput, int min, int max)
{
    if(msgAskingForInput == NULL)
    {
        return -1;
    }
    int number = 0;
    int result = 0;
    do{
        printf(msgAskingForInput, min, max);
        result = scanf("%9d", &number);
        if(getchar() != '\n')
        {
            result = 0;
            while(getchar() != '\n');
        }
        if(number < min || number > max)
        {
            result = 0;
        }
        if(result == 0)
        {
            printf(MSG_INVALID_INPUT);
        }
    }
    while(result == 0);
    return number;
}

char *getString(int maxLength)
{
    char *lastChar = (char*) calloc(1, sizeof(char));
    char *input = (char*) calloc(maxLength, sizeof(char));
    if(lastChar == NULL || input == NULL)
    {
        return NULL;
    }
    int notValid = 1;
    while(notValid)
    {
        fgets(input, maxLength + 1, stdin);
        if(*(input + strlen(input) - 1) != '\n')
        {
            printf(MSG_INPUT_IS_TOO_LONG, maxLength);
            do
            {
                fgets(lastChar, 2, stdin);
            }
            while(*lastChar != '\n');
            continue;
        }
        else
        {
            *(input + strlen(input) - 1) = '\0';
            free(lastChar);
            return input;
        }
    }
}

Song getSongFromInput(int linkNeeded, int maxLineLength)
{
    printf(MSG_ASKING_FOR_NAME);
    char *songName = getString(maxLineLength);
    if(songName == NULL)
    {
        notEnoughtMemory();
    }

    printf(MSG_ASKING_FOR_ARTIST);
    char *artist = getString(maxLineLength);
    if(artist == NULL)
    {
        notEnoughtMemory();
    }

    printf(MSG_ASKING_FOR_GENRE);
    char *genre = getString(maxLineLength);
    if(genre == NULL)
    {
        notEnoughtMemory();
    }

    Song song = {calloc(strlen(songName), sizeof(char)), calloc(strlen(artist), sizeof(char)), calloc(strlen(genre), sizeof(char)), NULL};
    if(song.artist == NULL || song.artist == NULL || song.genre == NULL)
    {
        notEnoughtMemory();
    }
    if(linkNeeded)
    {
        printf(MSG_ASKING_FOR_LINK);
        char *link = getString(maxLineLength);
        song.link = calloc(strlen(link), sizeof(char));
        if(song.link == NULL)
        {
            notEnoughtMemory();
        }
        strcpy(song.link, link);
        free(link);
    }

    strcpy(song.name, songName);
    strcpy(song.artist, artist);
    strcpy(song.genre, genre);

    free(songName);
    free(artist);
    free(genre);

    return song;
}

int showMenu(char *menuTitle, char *menuOptions[], int menuSize, char *inputMsg)
{
    if(menuTitle == NULL || menuOptions == NULL || inputMsg == NULL)
    {
        return -1;
    }
    int result = 0;
    int choice = 0;
    do{
        printf("\n%s", menuTitle);
        for(int i = 0; i < menuSize; ++i)
        {
            printf("%d - %s\n", i + 1, menuOptions[i]);
        }
        printf(inputMsg);
        result = scanf("%1d", &choice);

        if(getchar() != '\n')
        {
            result = 0;
            while(getchar() != '\n');
        }
        else if(choice > menuSize || choice <= 0)
        {
            result = 0;
        }
        if(result == 0)
        {
            printf(MSG_INVALID_INPUT);
        }
    } while(result == 0);
    return choice;
}

void printPlaylist(List *playlist)
{
    if(playlist == NULL)
    {
        printf(MSG_NULL);
        return;
    }
    int choice = showMenu(SONG_PARAMETERS, songParameters, 4, "\nPlease choose which one of the song parameters do you wish to see: ");
    printf(PLAYLIST_DISPLAY);
    int size = getListSize(playlist);
    if(size != 0)
    {
        switch (choice)
        {
        case 1:
            printList(playlist, printName);
            break;
        case 2:
            printList(playlist, printArtist);
            break;
        case 3:
            printList(playlist, printGenre);
            break;
        case 4:
            printList(playlist, printLink);
            break;
        }
    }
    else
    {
        printf(EMPTY_PLAYLIST);
    }
}

void printName(void *value)
{
    if(value == NULL)
    {
        printf(MSG_NULL);
        return;
    }
    printf("%s\n", (*(Song*)value).name);
}

void printArtist(void *value)
{
    if(value == NULL)
    {
        printf(MSG_NULL);
        return;
    }
    printf("%s\n", (*(Song*)value).artist);
}

void printGenre(void *value)
{
    if(value == NULL)
    {
        printf(MSG_NULL);
        return;
    }
    printf("%s\n", (*(Song*)value).genre);
}

void printLink(void *value)
{
    if(value == NULL)
    {
        printf(MSG_NULL);
        return;
    }
    printf("%s\n", (*(Song*)value).link);
}
