
/** File Explorer Application
 *
 * BeXCool 2020
 * Petr Pavlik <bxc@post.cz>
 *
 */

#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "fe_functions.h"


#define CONNECT_UP_DOWN_RIGHT 195
#define CONNECT_DOWN_LEFT 191
#define CONNECT_UP_RIGHT 192
#define CONNECT_LEFT_RIGHT 196
#define CONNECT_UP_DOWN 179

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
    char file_copyURL[1000] = "";

    int action = 1;
    int c;

    struct dirent *dir;
    struct stat filestat;

    FILE *file;
    FILE *file_copydata;

    DIR *directory;

    text_color(COLOR_WHITE);

    text_color(COLOR_INVISIBLE);
    printf("I1C jsou borci");
    text_color(COLOR_WHITE);

    text_color(COLOR_LIGHT_BLUE);
    printf("\n-----------------------------\n");
    text_color(COLOR_WHITE);
    printf("Welcome to the File explorer!");
    text_color(COLOR_LIGHT_BLUE);
    printf("\n-----------------------------");
    text_color(COLOR_WHITE);





    //TODO: ADD COMMENTS, ADD DIR RENAME AND FILE RENAME






    while(action!=13) {
        if(strcmp(lastDir, "") == 0){
        printf("\n\n\n\nLast opened directory: You do not have any opened directory.\n\nWhat do you want to do?\n\n\t1. Open directory\n\t2. Create directory\n\t3. Rename directory\n\t4. Copy directory\n\t5. Delete directory\n\t6. Open file\n\t");
        printf("7. Create file\n\t8. Rename file\n\t9. Copy file\n\t10. Delete file\n\t11. Run file\n\t12. File or directory properties\n\t13. About\n\t14. Help\n\t15. Close application\n\nEnter number: ");
        } else {
        printf("\n\n\n\nLast opened directory: %s\n\nWhat do you want to do?\n\n\t1. Open directory\n\t2. Create directory\n\t3. Rename directory\n\t4. Copy directory\n\t5. Delete directory\n\t6. Open file\n\t",lastDir);
        printf("7. Create file\n\t8. Rename file\n\t9. Copy file\n\t10. Delete file\n\t11. Run file\n\t12. File or directory properties\n\t13. About\n\t14. Help\n\t15. Close application\n\nEnter number: ");
        }
        scanf("%d",&action);

        switch(action){ //Checks for action
            case 1:
                printf("\n\n\nOpen directory: %s",lastDir); //Gets URL from user
                scanf("%d", &directory_url);
                gets(directory_url);

                if(command(directory_url, lastDir) == 0) { //Check for commands

                strcat(lastDir, directory_url);
                strcpy(directory_url, lastDir); //Copy strings into directory_url

                directory = opendir(directory_url); //Opens directory

                if(directory == NULL) { //Error handler
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

                int contentCount = 0, filesCount = 0, dirCount = 0;

                if (directory) {
                    while ((dir = readdir(directory)) != NULL) {    //Reading directories
                        printf(" %c %-40s",CONNECT_UP_DOWN_RIGHT,dir->d_name); //Reading name

                        contentCount++;

                        char time[100] = "";
                        struct stat stats;
                        char fileURL[500] = "";

                        strcat(fileURL, directory_url);
                        strcat(fileURL, dir->d_name);

                        stat(fileURL, &stats);
                        strftime(time, 100, "%d/%m/%Y %H:%M:%S", localtime( &stats.st_mtime)); //Reading time
                        printf("\t<%s>",time);

                        if(stats.st_mode == 16895 || stats.st_mode == 16749){ //Reading type
                            printf("\t  <DIR>");
                            dirCount++;
                        } else if(stats.st_mode == 33206) {
                            printf("\t  <FILE>");
                            filesCount++;
                        } else if(stats.st_mode == 33279) {
                            printf("\t  <EXE>");
                        } else {
                            printf("\t\t");
                        }

                        if(stats.st_size > 0) { //If is higher than 0, print size
                            printf("\t%.2fKb", (float)stats.st_size/1000);
                        }

                        printf("\n");
                    }
                    closedir(directory); //Closing directory
                    }

                printf(" %c\n %c%c Amount of directories: %d",CONNECT_UP_DOWN, CONNECT_UP_DOWN_RIGHT, CONNECT_LEFT_RIGHT, dirCount); //Printing amount of directories
                printf("\n %c%c Amount of files: %d",CONNECT_UP_DOWN_RIGHT, CONNECT_LEFT_RIGHT, filesCount); //Printing amount of files
                printf("\n %c%c Total directory content: %d",CONNECT_UP_RIGHT, CONNECT_LEFT_RIGHT, contentCount); //Printing total directory content

                if(directory_url[strlen(directory_url)-1] == '.') { //Checks if last char from URL is '.'
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

            case 5:
                printf("\n\n\nOpen file: %s",lastDir); //Gets URL from user
                scanf("%d",&file_url);
                gets(file_url);

                if(command(file_url, lastDir) == 0) { //Checks for commands

                strcpy(lastDirFile, lastDir);
                strcat(lastDirFile, file_url);
                strcpy(file_url, lastDirFile); //Copies strings

                file = fopen(file_url, "r"); //Opens file

                if(file == NULL) { //Error handler
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

                if (file) { //Printing file content character by character
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

            case 6:
                printf("\n\n\nCreate file: %s",lastDir); //Gets URL from user
                scanf("%d",&file_url);
                gets(file_url);

                if(command(file_url, lastDir) == 0) { //Checks for commands

                strcpy(lastDirFile, lastDir);
                strcat(lastDirFile, file_url);
                strcpy(file_url, lastDirFile); //Copies strings

                file = fopen(file_url, "w"); //Creates file

                if(file == NULL) { //Error handler
                    text_color(COLOR_RED);
                    printf("\nUnable to create file '%s'.\n",file_url);
                    text_color(COLOR_WHITE);
                    strcpy(lastDir, "");
                } else {
                text_color(COLOR_GREEN);
                printf("\nCreated file: %s",file_url);
                text_color(COLOR_WHITE);
                printf("\nWrite text to file:\n\n");
                scanf("%d\n", &file_textwrite);

                fgets(file_textwrite, 1000, stdin);
                fputs(file_textwrite, file); //Prints data to file
                fclose(file); //Closes file

                text_color(COLOR_GREEN);
                printf("\nText have been written to file.");
                text_color(COLOR_WHITE);
                }

                text_color(COLOR_YELLOW);
                printf("\n\nPress any key to continue.");
                text_color(COLOR_WHITE);
                getch();
                }

                break;

            case 7:
                printf("\n\n\nCopy file: %s",lastDir); //Gets URL from user
                scanf("%d",&file_url);
                gets(file_url);

                char file_url_first[1000] = "";

                strcpy(file_url_first, file_url); //Copies strings

                if(command(file_url, lastDir) == 0) { //Checks for commands

                strcpy(lastDirFile, lastDir);
                strcat(lastDirFile, file_url);
                strcpy(file_url, lastDirFile);

                file = fopen(file_url, "r"); //Reads file

                if(file == NULL) { //Error handler
                    text_color(COLOR_RED);
                    printf("\nUnable to find file '%s'.\n",file_url);
                    text_color(COLOR_WHITE);
                    strcpy(lastDir, "");
                } else {

                strcpy(file_url, "");

                printf("\nCopy file to file: " );
                scanf("%s",&file_url);

                if(command(file_url, lastDir) == 0) { //Checks for commands

                file_copydata = fopen(file_url, "w"); //Creates file

                if(file_copydata == NULL) {
                    text_color(COLOR_RED);
                    printf("\nUnable to copy file '%s' to file '%s'.\n",file_url_first, file_url);
                    text_color(COLOR_WHITE);
                    strcpy(lastDir, "");
                } else {

                fseek(file, 0L, SEEK_END); //File pointer at end of file
                int pos = ftell(file); //Gets file character size
                fseek(file, 0L, SEEK_SET); //File pointer set at start

                while (pos--) {
                    c = fgetc(file);  //Copying file character by character
                    fputc(c, file_copydata);
                }

                text_color(COLOR_GREEN);
                printf("\nCopied file '%s' to file '%s'",file_url_first, file_url);
                text_color(COLOR_WHITE);

                fclose(file); //Closes old file
                fclose(file_copydata); //Closes new file
                }
                } else {
                    break; //Break case if second scan is a command
                    }
                }

                text_color(COLOR_YELLOW);
                printf("\n\nPress any key to continue.");
                text_color(COLOR_WHITE);
                getch();
                }

                break;

            case 8:
                printf("\n\n\nDelete file: %s",lastDir); //Gets URL from user
                scanf("%d",&file_url);
                gets(file_url);

                if(command(file_url, lastDir) == 0) { //Checks for commands

                strcpy(lastDirFile, lastDir);
                strcat(lastDirFile, file_url);
                strcpy(file_url, lastDirFile);

                char decision;
                text_color(COLOR_RED);
                printf("\nAre you sure to delete file '%s'? (YES/NO)\n",file_url); //Ask user if he wants to really delete file
                text_color(COLOR_WHITE);
                scanf(" %c",&decision);

                if(decision == 'y' || decision == 'Y') { //Checking users decision
                        int del = remove(file_url); //Deletes file is 'y'
                        if (!del) {
                            text_color(COLOR_GREEN);
                            printf("\nFile '%s' was deleted.",file_url);
                            text_color(COLOR_WHITE);
                    }else{
                        text_color(COLOR_RED);
                        printf("\nFile '%s' was not deleted.",file_url);
                        text_color(COLOR_WHITE);
                    }
                }else if(decision == 'n' || decision == 'N') {
                    text_color(COLOR_GREEN);
                    printf("\nFile '%s' was not deleted.",file_url);
                    text_color(COLOR_WHITE);
                }



                text_color(COLOR_YELLOW);
                printf("\n\nPress any key to continue.");
                text_color(COLOR_WHITE);
                getch();
                }

                break;

            case 9:
                printf("\n\n\nRun file: %s",lastDir); //Gets URL from user
                scanf("%d",&file_url);
                gets(file_url);

                if(command(file_url, lastDir) == 0) { //Checks for commands

                strcpy(lastDirFile, lastDir);
                strcat(lastDirFile, file_url);
                strcpy(file_url, lastDirFile); //Copies strings

                printf("\n");

                text_color(COLOR_RED);
                int result=system(file_url); //Runs file/program
                text_color(COLOR_WHITE);

                if(result == 1) { //Error handler
                    text_color(COLOR_RED);
                    printf("\nFile '%s' could not be run.",file_url);
                    text_color(COLOR_WHITE);
                }else{
                    text_color(COLOR_GREEN);
                    printf("File '%s' has been run.",file_url);
                    text_color(COLOR_WHITE);
                }

                text_color(COLOR_YELLOW);
                printf("\n\nPress any key to continue.");
                text_color(COLOR_WHITE);
                getch();
                }

                break;

            case 10:
                printf("\n\n\nOpen properties from: %s",lastDir); //Gets URL from user
                scanf("%d",&file_url);
                gets(file_url);

                if(command(file_url, lastDir) == 0) { //Checks for commands

                strcpy(lastDirFile, lastDir);
                strcat(lastDirFile, file_url);
                strcpy(file_url, lastDirFile); //Copies strings

                text_color(COLOR_GREEN);
                printf("\nOpened properties: %s",file_url);
                text_color(COLOR_WHITE);
                printf("\n\nProperties:\n\n");
                text_color(COLOR_LIGHT_BLUE);
                text_color(COLOR_WHITE);

                printf("URL:\t\t\t\t%s\n",file_url);

                char time[100] = "";
                struct stat stats;

                stat(file_url, &stats);
                strftime(time, 100, "%d/%m/%Y %H:%M:%S", localtime(&stats.st_mtime)); //Prints times from file/directory
                printf("Last modified time:\t\t%s\n",time);
                strftime(time, 100, "%d/%m/%Y %H:%M:%S", localtime(&stats.st_atime));
                printf("Last access time:\t\t%s\n",time);
                strftime(time, 100, "%d/%m/%Y %H:%M:%S", localtime(&stats.st_ctime));
                printf("Last status change time:\t%s\n",time);

                if(stats.st_mode == 16895 || stats.st_mode == 16749){ //Prints file type (directory, file, executable file...)
                    printf("Type:\t\t\t\tDIR (%d)", stats.st_mode);
                } else if(stats.st_mode == 33206) {
                    printf("Type:\t\t\t\tFILE (%d)", stats.st_mode);
                } else if(stats.st_mode == 33279) {
                    printf("Type:\t\t\t\tEXE (%d)", stats.st_mode);
                } else {
                    printf("Type:\t\t\t\tUNKNOWN (%d)", stats.st_mode);
                }

                if(stats.st_size > 0) { //Checks if file size is larger than 0
                    printf("\nSize:\t\t\t\t%.2fKb (%d bytes)", (float)stats.st_size/1000, stats.st_size);
                }

                printf("\n");
                }

                if(directory_url[strlen(directory_url)-1] == '.') { //Checks if last character from URL is '.'
                    strcpy(lastDir, lastDirBackup);
                }

                strcpy(lastDirBackup, lastDir); //Copies last directory to last directory backup

                text_color(COLOR_YELLOW);
                printf("\n\nPress any key to continue.");
                text_color(COLOR_WHITE);
                getch();

                break;

            case 11: //About section
                printf("\n\n\nFile explorer 1.2\nPetr Pavlik 1/2021 - BeXCool\n\nWeb: bexcool.eu\nEmail: bxc@post.cz");
                text_color(COLOR_YELLOW);
                printf("\n\nPress any key to continue.");
                text_color(COLOR_WHITE);
                getch();
                break;

            case 12: //Commands section
                printf("\n\n\nList of commands (type them after selecting action by number):\n\t$root - Removes current URL and aborts action.\n\t$abort - Aborts current action.");
                text_color(COLOR_YELLOW);
                printf("\n\nPress any key to continue.");
                text_color(COLOR_WHITE);
                getch();
                break;

            case 13: //Close section
                text_color(COLOR_RED);
                printf("\nClosing application...");
                text_color(COLOR_WHITE);
                return(0);

            default: //Default - error
                text_color(COLOR_RED);
                printf("\nYou have selected invalid action!");
                text_color(COLOR_WHITE);

        }
    }
    return(0);
}
