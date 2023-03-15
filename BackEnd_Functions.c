// Author of the program - Justas Mileika 2021 Vilnius University, Software Engineering, Bachelor's degree, first year, group 2. E-mail: justasmileika@gmail.com
#include "module.h"
#include "User_Interface.h"
#include "BackEnd_Functions.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int compareName(void *value1, void *value2)
{
    if(strcmp((*(Song*)value1).name, (*(Song*)value2).name) == 0)
    {
        return 1;
    }
    return 0;
}

int compareArtist(void *value1, void *value2)
{
    if(strcmp((*(Song*)value1).artist, (*(Song*)value2).artist) == 0)
    {
        return 1;
    }
    return 0;
}

int compareGenre(void *value1, void *value2)
{
    if(strcmp((*(Song*)value1).genre, (*(Song*)value2).genre) == 0)
    {
        return 1;
    }
    return 0;
}

void modifyPlaylist(List **playlist, char* fileName, int maxIndexSize, int maxLineLength)
{
    if(playlist == NULL || *playlist == NULL || fileName == NULL)
    {
        return;
    }

    int size = getListSize(*playlist);
    if(size < 0)
    {
        printf(MSG_LIST_SIZE_WARNING, maxIndexSize);
        size = maxIndexSize;
    }

    int choice = showMenu(PLAYLIST_MODIFICATION_MENU, modifyOptions, 6, ASKING_CHOICE);
    while(choice != 6)
    {
        if(choice == 1)
        {
            if(size != 0)
            {
                printPlaylist(*playlist);
            }
            else
            {
                printf(EMPTY_PLAYLIST);
            }
        }
        if(choice == 2)
        {
            FILE *database = NULL;
            database = fopen(DATABASE_FILE_NAME, "r");
            if(database == NULL)
            {
                printf(DATABASE_NOT_OPENED);
                return;
            }

            printf(ASKING_FOR_POSITION_INSERT);
            int position = getInteger(ASKING_FOR_INTEGER, 1, size + 1);

            Song song = getSongFromInput(0, maxLineLength);

            char *link = lookupSong(database, song, maxLineLength);

            song.link = calloc(maxLineLength, sizeof(char));
            strcpy(song.link, link);

            if(insertElement(playlist, &song, sizeof(Song), position - 1) == NULL)
            {
                fclose(database);
                notEnoughtMemory();
            }
            else
            {
                printf(MSG_INSERTION_SUCCESSFUL);
            }
            fclose(database);
        }
        else if(choice == 3)
        {
            printf(ASKING_FOR_POSITION_DELETE);
            int position = getInteger(ASKING_FOR_INTEGER, 1, size);

            if(deleteElement(playlist, position - 1) == NULL)
            {
                notEnoughtMemory();
            }
            else
            {
                printf(MSG_DELETION_SUCCESSFUL);
            }
        }
        else if(choice == 4)
        {
            FILE *database = NULL;
            database = fopen(DATABASE_FILE_NAME, "r");
            if(database == NULL)
            {
                printf(DATABASE_NOT_OPENED);
                return;
            }
            printf(ASKING_FOR_POSITION_CHANGE);
            int position = getInteger(ASKING_FOR_INTEGER, 1, size);

            Song song = getSongFromInput(0, maxLineLength);

            char *link = lookupSong(database, song, maxLineLength);

            song.link = calloc(maxLineLength, sizeof(char));
            strcpy(song.link, link);

            if(changeValue(*playlist, &song, sizeof(Song), position - 1) == NULL)
            {
                fclose(database);
                notEnoughtMemory();
            }
            else
            {
                printf(MSG_CHANGE_SUCCESSFUL);
            }
            fclose(database);

        }
        else if(choice == 5)
        {
            int choiceCompress = showMenu(COMPRESSION_MENU, compressingOptions, 4, ASKING_CHOICE);
            switch (choiceCompress)
            {
            case 1:
                removeDuplicates(playlist, sizeof(Song), compareName);
                break;
            case 2:
                removeDuplicates(playlist, sizeof(Song), compareArtist);
                break;
            case 3:
                removeDuplicates(playlist, sizeof(Song), compareGenre);
                break;
            case 4:
                break;
            }
            printf(MSG_COMPRESSION_SUCCESSFUL);
        }
        choice = showMenu(PLAYLIST_MODIFICATION_MENU, modifyOptions, 6, ASKING_CHOICE);
    }
    if(savePlaylistInFile(*playlist, fileName) != NULL)
    {
        printf(MSG_MODIFICATIONS_SUCCESSFUL);
    }
    else
    {
        printf(MSG_MODIFICATIONS_UNSUCCESSFUL);
    }
}

char *lookupSong(FILE *file, Song song, int maxLineLength)
{
    fseek(file, 0, SEEK_SET);

    char *line = (char*) calloc(maxLineLength, sizeof(char));
    if(line == NULL)
    {
        notEnoughtMemory();
    }

    int correctAutor = 0, correctSong = 0;
    while(fgets(line, maxLineLength, file) != NULL)
    {
        if(strncmp(song.name, line, strlen(song.name)) == 0)
        {
            correctSong = 1;
        }
        else if(strncmp(song.artist, line, strlen(song.artist)) == 0 && correctSong == 1)
        {
            correctAutor = 1;
        }
        else if(strncmp(song.genre, line, strlen(song.genre)) == 0 && correctAutor == 1 && correctSong == 1)
        {
            char *link = NULL;
            fgets(line, maxLineLength, file);
            link = (char*) calloc(strlen(line), sizeof(char));
            if(link == NULL)
            {
                notEnoughtMemory();
            }

            strcpy(link, line);
            free(line);
            return link;
        }
        else
        {
            correctAutor = 0;
            correctSong = 0;
        }
    }
    free(line);
    return NULL;
}

char *addSongToDatabase(char *fileName, Song song)
{
    FILE *file = NULL;
    file = fopen(fileName, "a");
    if(file == NULL)
    {
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    printSongToFile(song, file);
    fclose(file);
    return fileName;
}

void printSongToFile(Song song, FILE *file)
{
    if(file == NULL)
    {
        return;
    }
    fwrite(song.name, 1, strlen(song.name), file);
    fwrite("\n", 1, 1, file);

    fwrite(song.artist, 1, strlen(song.artist), file);
    fwrite("\n", 1, 1, file);

    fwrite(song.genre, 1, strlen(song.genre), file);
    fwrite("\n", 1, 1, file);

    fwrite(song.link, 1, strlen(song.link), file);
    fwrite("\n", 1, 1, file);
}

char *savePlaylistInFile(List *playlist, char *playlistName)
{
    FILE *file = NULL;
    file = fopen(playlistName, "w");
    if(file == NULL)
    {
        return NULL;
    }

    while(playlist != NULL)
    {
        if(playlist->value != NULL)
        {
            Song song = *((Song*)playlist->value);
            printSongToFile(song, file);
        }
        playlist = playlist->next;
    }

    fclose(file);
    return playlistName;
}

void notEnoughtMemory()
{
    printf(MSG_NOT_ENOUGH_MEMORY);
    exit(0);
}

List *loadPlaylistFromFile(char *fileName, int maxLineLength)
{
    FILE *file = NULL;
    file = fopen(fileName, "r");
    if(file == NULL)
    {
        return NULL;
    }

    List *playlist = createList(1);
    if(playlist == NULL)
    {
        notEnoughtMemory();
    }

    char *line = (char*) calloc(maxLineLength, sizeof(char));
    if(line == NULL)
    {
        notEnoughtMemory();
    }

    char *songName = NULL;
    char *artist = NULL;
    char *genre = NULL;
    char *link = NULL;

    int firstSong = 1;
    int counter = 1;

    while(fgets(line, maxLineLength, file) != NULL)
    {
        if(songName == NULL)
        {
            songName = (char*) calloc(strlen(line) - 1, sizeof(char));
            if(songName == NULL)
            {
                notEnoughtMemory();
            }

            strncpy(songName, line, strlen(line) - 1);
        }
        else if(artist == NULL)
        {
            artist = (char*) calloc(strlen(line) - 1, sizeof(char));
            if(artist == NULL)
            {
                notEnoughtMemory();
            }

            strncpy(artist, line, strlen(line) - 1);
        }
        else
        {
            genre = (char*) calloc(strlen(line) - 1, sizeof(char));

            if(genre == NULL)
            {
                notEnoughtMemory();
            }

            strncpy(genre, line, strlen(line) - 1);

            fgets(line, maxLineLength, file);

            link = (char*) calloc(strlen(line) - 1, sizeof(char));
            if(link == NULL)
            {
                notEnoughtMemory();
            }
            strncpy(link, line, strlen(line) - 1);

            Song song = {};
            song.name = calloc(strlen(songName), sizeof(char));
            if(song.name == NULL)
            {
                notEnoughtMemory();
            }

            song.artist = calloc(strlen(artist), sizeof(char));
            if(song.artist == NULL)
            {
                notEnoughtMemory();
            }

            song.genre = calloc(strlen(genre), sizeof(char));
            if(song.genre == NULL)
            {
                notEnoughtMemory();
            }

            song.link = calloc(strlen(link), sizeof(char));
            if(song.link == NULL)
            {
                notEnoughtMemory();
            }

            strcpy(song.name, songName);
            strcpy(song.artist, artist);
            strcpy(song.genre, genre);
            strcpy(song.link, link);

            if(firstSong)
            {
                if(changeValue(playlist, &song, sizeof(Song), 0) == NULL)
                {
                    notEnoughtMemory();
                }
                firstSong = 0;
            }
            else
            {
                if(insertElement(&playlist, &song, sizeof(Song), counter) == NULL)
                {
                    notEnoughtMemory();
                }
                ++counter;
            }

            free(songName);
            free(artist);
            free(genre);
            free(link);

            genre = NULL;
            songName = NULL;
            artist = NULL;
            link = NULL;
        }
    }

    free(songName);
    free(artist);
    free(genre);
    free(link);
    free(line);
    fclose(file);

    if(firstSong)
    {
        free(playlist);
        return NULL;
    }
    return playlist;
}

void checkDatabase(int maxLineLength)
{
    FILE *file = NULL;
    file = fopen(DATABASE_FILE_NAME, "r");
    if(file == NULL)
    {
        printf(DATABASE_NOT_OPENED);
        return;
    }

    int choice = showMenu(DATABASE_MENU, databaseOptions, 3, ASKING_CHOICE);
    while(choice != 3)
    {
        if(choice == 1)
        {
            Song song = getSongFromInput(0, maxLineLength);
            char *link = lookupSong(file, song, maxLineLength);
            if(link == NULL)
            {
                printf(MSG_SONG_NOT_FOUND_IN_DATABASE);
            }
            else
            {
                printf(MSG_SONG_FOUND_IN_DATABASE, link);
            }
            free(link);
        }
        if(choice == 2)
        {
            Song song = getSongFromInput(1, maxLineLength);

            if(lookupSong(file, song, maxLineLength) == NULL)
            {
                fclose(file);
                if(addSongToDatabase(DATABASE_FILE_NAME, song) != NULL)
                {
                    printf(DATABASE_UPDATED_SUCCESSFULLY);
                }
                else
                {
                    printf(DATABASE_NOT_OPENED);
                }

                file = NULL;
                file = fopen(DATABASE_FILE_NAME, "r");
                if(file == NULL)
                {
                    printf(DATABASE_NOT_OPENED);
                }
            }
            else
            {
                printf(SONG_ALREADY_IN_DATABASE);
            }
        }
        choice = showMenu(DATABASE_MENU, databaseOptions, 3, ASKING_CHOICE);
    }
    fclose(file);
}

void printHelp()
{
    printf(MSG_HELP);
}

void exitProgram()
{
    printf(PROGRAM_OUTRO);
    exit(0);
}

void modifyExistingPlaylist(int maxLineLength, int maxListIndex)
{
    printf(MSG_ASKING_FOR_PLAYLIST_FILE);
    char *name = getString(maxLineLength);
    if(name == NULL)
    {
        notEnoughtMemory();
    }

    List *playlist = loadPlaylistFromFile(name, maxLineLength);
    if(playlist == NULL)
    {
        printf(FILE_NOT_OPENED);
        free(name);
        return;
    }
    else
    {
        printf(FILE_OPENED_SUCCESSFULY);
    }

    modifyPlaylist(&playlist, name, maxListIndex, maxLineLength);
    free(name);
    destroyList(&playlist);
}

void createNewPlaylist(int maxLineLength)
{
    printf(MSG_ASKING_FOR_PLAYLIST_NAME);
    char *playlistName = getString(maxLineLength);
    if(playlistName == NULL)
    {
        notEnoughtMemory();
    }

    List *playlist = createList(1);
    if(playlist == NULL)
    {
        free(playlistName);
        notEnoughtMemory();
    }

    int size = 0;
    FILE *database = NULL;
    database = fopen(DATABASE_FILE_NAME, "r");
    if(database == NULL)
    {
        free(playlistName);
        free(playlist);
        printf(DATABASE_NOT_OPENED);
        return;
    }

    while(showMenu(PLAYLIST_CREATION_MENU, createPlaylistOptions, 2, ASKING_CHOICE) == 1)
    {
        Song song = getSongFromInput(0, maxLineLength);

        char *link = lookupSong(database, song, maxLineLength);
        if(link != NULL)
        {
            song.link = calloc(strlen(link), sizeof(char));
            if(song.link == NULL)
            {
                free(song.artist);
                free(song.name);
                free(song.link);
                free(song.genre);
                free(link);
                free(playlistName);
                free(playlist);
                fclose(database);

                notEnoughtMemory();
            }
            strncpy(song.link, link, strlen(link) - 1);

            if(size == 0)
            {
                if(changeValue(playlist, &song, sizeof(Song), 0) == NULL)
                {
                    free(song.artist);
                    free(song.name);
                    free(song.link);
                    free(song.genre);
                    free(link);
                    free(playlistName);
                    free(playlist);
                    fclose(database);

                    notEnoughtMemory();
                }
                ++size;
            }
            else
            {
                if(insertElement(&playlist, &song, sizeof(Song), size) == NULL)
                {
                    free(song.artist);
                    free(song.name);
                    free(song.link);
                    free(song.genre);
                    free(link);
                    free(playlistName);
                    free(playlist);
                    fclose(database);

                    notEnoughtMemory();
                }
                ++size;
            }
            printf(MSG_SONG_ADDED_TO_PLAYLIST);

        }
        else
        {
            printf(MSG_SONG_NOT_FOUND_IN_DATABASE);
            int choice = showMenu(SONG_MENU, noSongFoundOptions, 2, ASKING_CHOICE);
            if(choice == 1)
            {
                free(song.artist);
                free(song.name);
                free(song.link);
                free(song.genre);
                free(link);

                continue;
            }
            else
            {
                printf(MSG_ASKING_FOR_LINK);
                link = getString(maxLineLength);
                if(link == NULL)
                {
                    free(song.artist);
                    free(song.name);
                    free(song.link);
                    free(song.genre);
                    free(link);
                    free(playlistName);
                    free(playlist);
                    fclose(database);

                    notEnoughtMemory();
                }
                song.link = calloc(strlen(link), sizeof(char));
                if(song.link == NULL)
                {
                    free(song.artist);
                    free(song.name);
                    free(song.link);
                    free(song.genre);
                    free(link);
                    free(playlistName);
                    free(playlist);
                    fclose(database);

                    notEnoughtMemory();
                }
                strncpy(song.link, link, strlen(link) - 1);
                fclose(database);
                if(addSongToDatabase(DATABASE_FILE_NAME, song) != NULL)
                {
                    printf(DATABASE_UPDATED_SUCCESSFULLY);
                }
                else
                {
                    printf(DATABASE_NOT_OPENED);

                    free(song.artist);
                    free(song.name);
                    free(song.link);
                    free(song.genre);
                    free(link);
                    free(playlistName);
                    free(playlist);
                    fclose(database);

                    return;
                }
                database = NULL;
                database = fopen(DATABASE_FILE_NAME, "r");

                if(database == NULL)
                {
                    printf(DATABASE_NOT_OPENED);

                    free(song.artist);
                    free(song.name);
                    free(song.link);
                    free(song.genre);
                    free(link);
                    free(playlistName);
                    free(playlist);
                    fclose(database);

                    return;
                }

                if(size == 0)
                {
                    if(changeValue(playlist, &song, sizeof(Song), 0) == NULL)
                    {
                        free(song.artist);
                        free(song.name);
                        free(song.link);
                        free(song.genre);
                        free(link);
                        free(playlistName);
                        free(playlist);
                        fclose(database);

                        notEnoughtMemory();
                    }
                    ++size;
                }
                else
                {
                    if(insertElement(&playlist, &song, sizeof(Song), size) == NULL)
                    {
                        free(song.artist);
                        free(song.name);
                        free(song.link);
                        free(song.genre);
                        free(link);
                        free(playlistName);
                        free(playlist);
                        fclose(database);

                        notEnoughtMemory();
                    }
                    ++size;
                }
            }
        }
        free(link);
    }
    int choiceSaving = showMenu(MSG_ASKING_FOR_SAVE_TO_FILE_CHOICE, booleanOptions, 2, ASKING_CHOICE);

    if(choiceSaving == 1)
    {
        int choiceFile = showMenu(MSG_ASKING_FOR_SAVE_WITH_NAME_CHOICE, booleanOptions, 2, ASKING_CHOICE);
        if(choiceFile == 1)
        {
            if(maxLineLength - strlen(playlistName) >= 4)
            {
                strcat(playlistName, ".txt");
                if(savePlaylistInFile(playlist, playlistName) != NULL)
                {
                    printf(PLAYLIST_SAVED_SUCCESSFULLY);
                }
                else
                {
                    printf(FILE_NOT_OPENED);
                }
            }
            else
            {
                printf(MSG_PLAYLIST_NOT_SAVED_INVALID_NAME);
            }
        }
        else
        {
            printf(MSG_ASKING_NEW_PLAYLIST_FILENAME);
            char *fileName = getString(maxLineLength);
            if(fileName == NULL)
            {
                notEnoughtMemory();
            }
            if(savePlaylistInFile(playlist, fileName) != NULL)
            {
                printf(PLAYLIST_SAVED_SUCCESSFULLY);
            }
            else
            {
                printf(FILE_NOT_OPENED);
            }
        }
    }
    int outputChoice = showMenu(OUTPUT_MENU, booleanOptions, 2, MSG_ASKING_FOR_OUTPUT_OPTIONS);

    if(outputChoice == 1)
    {
        if(size == 0)
        {
            printf(EMPTY_PLAYLIST);
        }
        else
        {
            printPlaylist(playlist);
        }
    }

    destroyList(&playlist);
    free(playlistName);
    fclose(database);
}
