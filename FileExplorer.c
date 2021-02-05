#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "fe_functions.h"

#define CONNECT_UP_DOWN_RIGHT 195
#define CONNECT_DOWN_LEFT 191
#define CONNECT_LEFT_RIGHT 196

    /*MAIN FUNCTION*/
int main(void) {

    char directory_url[1000] = "";
    char file_url[1000] = "";
    char lastDir[1000] = "";
    char lastDirBackup[1000] = "";
    char lastDirFile[1000] = "";
    char file_content[1000] = "";
    char root[1000] = "$root";
    char abort[1000] = "$abort";
    char file_textwrite[1000] = "";

    int action = 1;
    int c;

    struct dirent *dir;
    struct stat filestat;

    FILE *file;

    DIR *directory;

    text_color(COLOR_WHITE);

    text_color(COLOR_LIGHT_BLUE);
    printf("\n-------------------------\n");
    text_color(COLOR_WHITE);
    printf("Welcome to File explorer!");
    text_color(COLOR_LIGHT_BLUE);
    printf("\n-------------------------");
    text_color(COLOR_WHITE);

    while(action!=8) {
        if(strcmp(lastDir, "") == 0){
        printf("\n\n\n\nLast opened directory: You do not have any opened directory.\n\nWhat do you want to do?\n\n\t1. Open directory\n\t2. Open file\n\t");
        printf("3. Create file\n\t4. Copy file\n\t5. Delete file\n\t6. About\n\t7. Help\n\t8. Close application\n\nEnter number: ");
        } else {
        printf("\n\n\n\nLast opened directory: %s\n\nWhat do you want to do?\n\n\t1. Open directory\n\t2. Open file\n\t",lastDir);
        printf("3. Create file\n\t4. Copy file\n\t5. Delete file\n\t6. About\n\t7. Help\n\t8. Close application\n\nEnter number: ");
        }
        scanf("%d",&action);

        switch(action){
            case 1:
                text_color(7);
                printf("\n\n\nOpen directory: %s",lastDir);
                scanf("%s",&directory_url);

                //Check for commands
                if(command(directory_url, lastDir) == 0) {

                strcat(lastDir, directory_url);
                strcpy(directory_url, lastDir);

                directory = opendir(directory_url);

                if(directory == NULL) {
                    text_color(COLOR_RED);
                    printf("\nUnable to find directory '%s'.\n",directory_url);
                    text_color(COLOR_WHITE);
                    strcpy(lastDir, "");
                } else {

                text_color(COLOR_GREEN);
                printf("\nOpened directory: %s",directory_url);
                text_color(COLOR_WHITE);
                printf("\nDirectory content:\n");
                text_color(COLOR_LIGHT_BLUE);
                printf("----------------------------------------------------------\n\n");
                text_color(COLOR_WHITE);
                printf("%c%c\n",CONNECT_LEFT_RIGHT,CONNECT_DOWN_LEFT);

                if (directory) {
                    while ((dir = readdir(directory)) != NULL) {
                    printf(" %c %s\n",CONNECT_UP_DOWN_RIGHT,dir->d_name);
                    }
                    closedir(directory);
                    }

                if(directory_url[strlen(directory_url)-1] == '.') {
                    strcpy(lastDir, lastDirBackup);
                }

                strcpy(lastDirBackup, lastDir); //Copies last directory to last directory backup

                text_color(COLOR_LIGHT_BLUE);
                printf("\n----------------------------------------------------------");
                text_color(COLOR_WHITE);
                }

                text_color(COLOR_YELLOW);
                printf("\n\nPress any key to continue.");
                text_color(COLOR_WHITE);
                getch();
                }

                break;

            case 2:
                printf("\n\n\nOpen file: %s",lastDir);
                scanf("%s",&file_url);

                if(command(file_url, lastDir) == 0) {

                strcpy(lastDirFile, lastDir);
                strcat(lastDirFile, file_url);
                strcpy(file_url, lastDirFile);

                file = fopen(file_url, "r");

                if(file == NULL) {
                    text_color(COLOR_RED);
                    printf("\nUnable to find file '%s'.\n",file_url);
                    text_color(COLOR_WHITE);
                    strcpy(lastDir, "");
                } else {
                text_color(COLOR_GREEN);
                printf("\nOpened file: %s",file_url);
                text_color(COLOR_WHITE);
                printf("\nFile content:\n");
                text_color(COLOR_LIGHT_BLUE);
                printf("----------------------------------------------------------\n\n");
                text_color(COLOR_WHITE);

                if (file) {
                    while ((c = getc(file)) != EOF)
                    putchar(c);
                    fclose(file);
                }

                text_color(COLOR_LIGHT_BLUE);
                printf("\n\n----------------------------------------------------------");
                text_color(COLOR_WHITE);
                }

                text_color(COLOR_YELLOW);
                printf("\n\nPress any key to continue.");
                text_color(COLOR_WHITE);
                getch();
                }

                break;

            case 3:
                printf("\n\n\nCreate file: %s",lastDir);
                scanf("%s",&file_url);

                if(command(file_url, lastDir) == 0) {

                strcpy(lastDirFile, lastDir);
                strcat(lastDirFile, file_url);
                strcpy(file_url, lastDirFile);

                file = fopen(file_url, "w");

                if(file == NULL) {
                    text_color(COLOR_RED);
                    printf("\nUnable to create file '%s'.\n",file_url);
                    text_color(COLOR_WHITE);
                    strcpy(lastDir, "");
                } else {
                text_color(COLOR_GREEN);
                printf("\nCreated file: %s",file_url);
                text_color(COLOR_WHITE);
                printf("\nWrite text to file:\n\n");
                scanf("%s",&file_textwrite);
                printf("\na do nooo");

                fputs(file_textwrite, file);
                fclose(file);

                text_color(COLOR_GREEN);
                printf("\nText have been written to file.");
                text_color(COLOR_WHITE);
                    }

                }

                text_color(COLOR_YELLOW);
                printf("\n\nPress any key to continue.");
                text_color(COLOR_WHITE);
                getch();


                break;

            case 6:
                printf("\n\n\nFile explorer 1.2\nPetr Pavlik 1/2021 - BeXCool\n\nWeb: bexcool.eu\nEmail: bxc@post.cz");
                text_color(COLOR_YELLOW);
                printf("\n\nPress any key to continue.");
                text_color(COLOR_WHITE);
                getch();
                break;

            case 7:
                printf("\n\n\nList of commands (type them after selecting action by number):\n\t$root - Removes current URL and aborts action.\n\t$abort - Aborts current action.");
                text_color(COLOR_YELLOW);
                printf("\n\nPress any key to continue.");
                text_color(COLOR_WHITE);
                getch();
                break;

            case 8:
                text_color(COLOR_RED);
                printf("\nClosing application...");
                text_color(COLOR_WHITE);
                return(0);

            default:
                text_color(COLOR_RED);
                printf("\nYou have selected invalid action!");
                text_color(COLOR_WHITE);

        }
    }
    /*
                --- Wanted to add last changed date to directories, but they use \n after %s. ---

                printf("\nOpen directory: %s",lastDir);
                scanf("%s",&directory_url);
                printf("\n");

                strcat(lastDir, directory_url);
                strcpy(directory_url, lastDir);

                struct dirent *dir;
                directory = opendir(directory_url);

                struct stat filestat;

                printf("\nOpened directory: %s\nDirectory content:\n",directory_url);
                printf("----------------------------------------------------------\n\n");

                if (directory) {
                    while ((dir = readdir(directory)) != NULL) {
                    char fileModifyTime[10000] = "";

                    strcpy(fileModifyTime,directory_url);
                    strcat(fileModifyTime,"/");
                    strcat(fileModifyTime,dir->d_name);

                    stat(fileModifyTime,&filestat);

                    printf("%s\t\t%c%s%c",dir->d_name,60,ctime(&filestat.st_mtime),62);
                    }
                    closedir(directory);
                }

                printf("\n----------------------------------------------------------");
                printf("\n\nPress any key to continue.");
                getch();
                OpenedDirectory=1;
                break;
    */
    return(0);
}
