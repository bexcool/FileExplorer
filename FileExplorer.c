
/** File Explorer Application
 *
 * BeXCool 2020
 * Petr Pavlik <bxc@post.cz>
 *
 * [APACHE LICENSE 2.0 - "./LICENSE.md"]
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
    char file_textwrite[1000] = "";
    char file_copyURL[1000] = "";
    char cwd[1000] = ""; //Current working directory
    char newFileName[1000] = ""; //Renaming file variable
    char decision_encrypt[10] = "";

    char DeleteFileDecision; //Decision while deleting file

    int action = 1;
    int c; //Reading file character - using for putchar(c);
    int renameResult; //Result from renaming file

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

    while(action!=17) {
        if(strcmp(lastDir, "") == 0){
        printf("\n\n\nLast opened directory: You do not have any opened directory.\n\nWhat do you want to do?\n\n\t1. Open directory\n\t2. Create directory\n\t3. Copy directory (coming soon)\n\t4. Delete directory\n\t5. Open file\n\t6. Create file\n\t7. Copy file\n\t");
        printf("8. Delete file\n\t9. Cut directory or file\n\t10. Rename directory or file\n\t11. Run file\n\t12. File or directory properties\n\t13. Encrypt text file\n\t14. Decrypt text file\n\t15. About\n\t16. Help\n\t17. Close application\n\nEnter number: ");
        } else {
        printf("\n\n\nLast opened directory: %s\n\nWhat do you want to do?\n\n\t1. Open directory\n\t2. Create directory\n\t3. Copy directory (coming soon)\n\t4. Delete directory\n\t5. Open file\n\t6. Create file\n\t7. Copy file\n\t",lastDir);
        printf("8. Delete file\n\t9. Cut directory or file\n\t10. Rename directory or file\n\t11. Run file\n\t12. File or directory properties\n\t13. Encrypt text file\n\t14. Decrypt text file\n\t15. About\n\t16. Help\n\t17. Close application\n\nEnter number: ");
        }
        scanf("%d",&action);

        switch(action){ //Checks for action
            case 1: //Open directory
                printf("\n\n\nOpen directory: %s",lastDir); //Gets URL from user
                scanf("%c", &directory_url);
                gets(directory_url);

                if(command(directory_url, lastDir) != 0)goto aborting_od; //Check for commands

                strcat(lastDir, directory_url);
                strcpy(directory_url, lastDir); //Copy strings into directory_url

                if(directory_url[strlen(directory_url)-1] != '/' && directory_url[strlen(directory_url)-1] != '\\' && directory_url[strlen(directory_url)-1] != '%') { //Checks if last character from URL is '/' or '\'
                            strcat(directory_url, "/");
                }

                directory = opendir(directory_url); //Opens directory

                if(directory == NULL) { //Error handler
                    text_color(COLOR_RED);
                    printf("\nUnable to find directory '%s'.\n",directory_url);
                    text_color(COLOR_WHITE);
                    strcpy(lastDir, lastDirBackup);
                } else {

                text_color(COLOR_GREEN);
                chdir(directory_url); //Sets current working dir
                printf("\nOpened directory: %s",getcwd(cwd, 1000));
                text_color(COLOR_WHITE);
                printf("\nDirectory content:\n");
                text_color(COLOR_LIGHT_BLUE);
                printf("----------------------------------------------------------\n");
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
                strcpy(lastDir, cwd);

                printf(" %c\n %c%c Amount of directories: %d",CONNECT_UP_DOWN, CONNECT_UP_DOWN_RIGHT, CONNECT_LEFT_RIGHT, dirCount); //Printing amount of directories
                printf("\n %c%c Amount of files: %d",CONNECT_UP_DOWN_RIGHT, CONNECT_LEFT_RIGHT, filesCount); //Printing amount of files
                printf("\n %c%c Total directory content: %d",CONNECT_UP_RIGHT, CONNECT_LEFT_RIGHT, contentCount); //Printing total directory content

                strcpy(lastDirBackup, lastDir); //Copies last directory to last directory backup

                text_color(COLOR_LIGHT_BLUE);
                printf("\n----------------------------------------------------------");
                text_color(COLOR_WHITE);
                }

                text_color(COLOR_YELLOW);
                printf("\n\nPress any key to continue.");
                text_color(COLOR_WHITE);
                getch();

                aborting_od: //Skipping by command

                break;

            case 2: //Create directory
                printf("\n\n\nCreate directory: %s",lastDir); //Gets URL from user
                scanf("%d",&file_url);
                gets(file_url);
                struct stat st = {0};

                if(command(file_url, lastDir) != 0)goto aborting_cd;

                strcpy(lastDirFile, lastDir);
                strcat(lastDirFile, file_url);
                strcpy(file_url, lastDirFile); //Copies strings
                strcpy(lastDir, file_url);

                chdir(lastDir); //Sets current working directory
                getcwd(cwd, 1000);

                if (stat(file_url, &st) == -1) { //Checks if directory exists
                    mkdir(file_url); //Creates new directory if directory does not exist
                    text_color(COLOR_GREEN);
                    printf("\nCreated directory '%s'.",file_url);
                    text_color(COLOR_WHITE);
                } else {
                    text_color(COLOR_RED);
                    printf("\nDirectory '%s' already exists.",file_url);
                    text_color(COLOR_WHITE);
                }

                text_color(COLOR_YELLOW);
                printf("\n\nPress any key to continue.");
                text_color(COLOR_WHITE);
                getch();

                aborting_cd: //Skipping by command

                break;

            case 3: //Copy directory

                text_color(COLOR_RED);
                printf("\n\n\nCopying directory is not available at the moment.");
                text_color(COLOR_WHITE);

                text_color(COLOR_YELLOW);
                printf("\n\nPress any key to continue.");
                text_color(COLOR_WHITE);
                getch();

                break;

            case 4: //Delete directory
                printf("\n\n\nDelete directory: %s",lastDir); //Gets URL from user
                scanf("%d",&file_url);
                gets(file_url);

                if(command(file_url, lastDir) != 0)goto aborting_dd; //Checks for commands

                strcpy(lastDirFile, lastDir);
                strcat(lastDirFile, file_url);
                strcpy(file_url, lastDirFile);

                char decision;
                text_color(COLOR_RED);
                printf("\nAre you sure to delete file '%s'? (Y/N)\n",file_url); //Ask user if he wants to really delete file
                text_color(COLOR_WHITE);
                scanf(" %c",&decision);

                if(decision == 'y' || decision == 'Y') { //Checking users decision
                        int del = remove_directory(file_url); //Deletes file is 'y'
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
                    printf("\nFile '%s' has not deleted.",file_url);
                    text_color(COLOR_WHITE);
                }



                text_color(COLOR_YELLOW);
                printf("\n\nPress any key to continue.");
                text_color(COLOR_WHITE);
                getch();

                aborting_dd: //Skipping by command

                break;

            case 5: //Open file
                printf("\n\n\nOpen file: %s",lastDir); //Gets URL from user
                scanf("%d",&file_url);
                gets(file_url);

                if(command(file_url, lastDir) != 0)goto aborting_of; //Checks for commands

                strcpy(lastDirFile, lastDir);
                strcat(lastDirFile, file_url);
                strcpy(file_url, lastDirFile); //Copies strings

                file = fopen(file_url, "r"); //Opens file

                if(file == NULL) { //Error handler
                    text_color(COLOR_RED);
                    printf("\nUnable to find file '%s'.\n",file_url);
                    text_color(COLOR_WHITE);
                } else {
                text_color(COLOR_GREEN);
                printf("\nOpened file: %s",file_url);
                text_color(COLOR_WHITE);
                printf("\nFile content:\n");
                text_color(COLOR_LIGHT_BLUE);
                printf("----------------------------------------------------------\n\n");
                text_color(COLOR_WHITE);

                char fileText[5000] = "";

                while(fgets(fileText, sizeof(fileText), file) != NULL) { //Prints line by line from file
                fputs(fileText, stdout);
                }

                fclose(file);

                text_color(COLOR_LIGHT_BLUE);
                printf("\n\n----------------------------------------------------------");
                text_color(COLOR_WHITE);
                }

                text_color(COLOR_YELLOW);
                printf("\n\nPress any key to continue.");
                text_color(COLOR_WHITE);
                getch();

                aborting_of: //Skipping by command

                break;

            case 6: //Create file
                printf("\n\n\nCreate file: %s",lastDir); //Gets URL from user
                scanf("%d",&file_url);
                gets(file_url);

                if(command(file_url, lastDir) != 0)goto aborting_cf; //Checks for commands

                strcpy(lastDirFile, lastDir);
                strcat(lastDirFile, file_url);
                strcpy(file_url, lastDirFile); //Copies strings

                file = fopen(file_url, "w"); //Creates file

                if(file == NULL) { //Error handler
                    text_color(COLOR_RED);
                    printf("\nUnable to create file '%s'.\n",file_url);
                    text_color(COLOR_WHITE);
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

                aborting_cf: //Skipping by command

                break;

            case 7: //Copy file
                printf("\n\n\nCopy file: %s",lastDir); //Gets URL from user
                scanf("%d",&file_url);
                gets(file_url);

                char file_url_first[1000] = "";

                strcpy(file_url_first, file_url); //Copies strings

                if(command(file_url, lastDir) != 0)goto aborting_copyf; //Checks for commands

                strcpy(lastDirFile, lastDir);
                strcat(lastDirFile, file_url);
                strcpy(file_url, lastDirFile);

                file = fopen(file_url, "r"); //Reads file

                if(file == NULL) { //Error handler
                    text_color(COLOR_RED);
                    printf("\nUnable to find file '%s'.\n",file_url);
                    text_color(COLOR_WHITE);
                } else {

                strcpy(file_url, "");

                printf("\nCopy file to new file URL: " );
                scanf("%s",&file_url);

                if(command(file_url, lastDir) != 0)goto aborting_copyf; //Checks for commands

                file_copydata = fopen(file_url, "w"); //Creates file

                if(file_copydata == NULL) {
                    text_color(COLOR_RED);
                    printf("\nUnable to copy file '%s' to file '%s'.\n",file_url_first, file_url);
                    text_color(COLOR_WHITE);
                } else {

                char fileText[5000] = "";

                while(fgets(fileText, sizeof(fileText), file) != NULL) { //Prints line by line from file
                fputs(fileText, file_copydata);
                }

                text_color(COLOR_GREEN);
                printf("\nCopied file '%s' to file '%s'",file_url_first, file_url);
                text_color(COLOR_WHITE);

                fclose(file); //Closes old file
                fclose(file_copydata); //Closes new file
                }

                }

                text_color(COLOR_YELLOW);
                printf("\n\nPress any key to continue.");
                text_color(COLOR_WHITE);
                getch();

                aborting_copyf: //Skipping by command

                break;

            case 8: //Delete file
                printf("\n\n\nDelete file: %s",lastDir); //Gets URL from user
                scanf("%d",&file_url);
                gets(file_url);

                if(command(file_url, lastDir) != 0)goto aborting_delf; //Checks for commands

                strcpy(lastDirFile, lastDir);
                strcat(lastDirFile, file_url);
                strcpy(file_url, lastDirFile);

                text_color(COLOR_RED);
                printf("\nAre you sure to delete file '%s'? (Y/N)\n",file_url); //Ask user if he wants to really delete file
                text_color(COLOR_WHITE);
                scanf(" %c",&DeleteFileDecision);

                if(DeleteFileDecision == 'y' || DeleteFileDecision == 'Y') { //Checking users decision
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
                }else if(DeleteFileDecision == 'n' || DeleteFileDecision == 'N') {
                    text_color(COLOR_GREEN);
                    printf("\nFile '%s' has not deleted.",file_url);
                    text_color(COLOR_WHITE);
                }



                text_color(COLOR_YELLOW);
                printf("\n\nPress any key to continue.");
                text_color(COLOR_WHITE);
                getch();

                aborting_delf: //Skipping by command

                break;

            case 9: //Cut directory or file
                printf("\n\n\nCut directory or file: %s",lastDir); //Gets URL from user
                scanf("%d",&file_url);
                gets(file_url);

                if(command(file_url, lastDir) != 0)goto aborting_cutdf; //Checks for commands

                strcpy(lastDirFile, lastDir);
                strcat(lastDirFile, file_url);
                strcpy(file_url, lastDirFile); //Copies strings

                char newFileName[1000] = "";

                printf("\n\nCut to new URL: %s",lastDir); //Gets new file name from user
                scanf("%d",&newFileName);
                gets(newFileName);

                if(command(newFileName, lastDir) != 0)goto aborting_cutdf; //Checks for commands

                int renameResult = rename(file_url, newFileName);

                if(renameResult == 0) {
                    text_color(COLOR_GREEN);
                    printf("File has been moved.");
                    text_color(COLOR_WHITE);
                } else {
                    text_color(COLOR_RED);
                    printf("File has not been moved.");
                    text_color(COLOR_WHITE);
                }

                text_color(COLOR_YELLOW);
                printf("\n\nPress any key to continue.");
                text_color(COLOR_WHITE);
                getch();

                aborting_cutdf: //Skipping by command

                break;

            case 10: //Rename directory or file
                printf("\n\n\nRename directory or file: %s",lastDir); //Gets URL from user
                scanf("%d",&file_url);
                gets(file_url);

                if(command(file_url, lastDir) != 0)goto aborting_renamedf; //Checks for commands

                strcpy(lastDirFile, lastDir);
                strcat(lastDirFile, file_url);
                strcpy(file_url, lastDirFile); //Copies strings

                printf("\n\nNew file name: %s",lastDir); //Gets new file name from user
                scanf("%d",&newFileName);
                gets(newFileName);

                if(command(newFileName, lastDir) != 0)goto aborting_renamedf; //Checks for commands

                char dirRename[1000] = "";
                char dirRenameOld[1000] = "";

                strcpy(dirRenameOld, file_url);

                strcpy(dirRename, dirname(dirRenameOld));
                strcat(dirRename, "/");
                strcat(dirRename, newFileName);
                strcpy(newFileName, dirRename);

                renameResult = rename(file_url, newFileName);

                if(renameResult == 0) {
                    text_color(COLOR_GREEN);
                    printf("File has been renamed.");
                    text_color(COLOR_WHITE);
                } else {
                    text_color(COLOR_RED);
                    printf("File has not been renamed.");
                    text_color(COLOR_WHITE);
                }

                text_color(COLOR_YELLOW);
                printf("\n\nPress any key to continue.");
                text_color(COLOR_WHITE);
                getch();

                aborting_renamedf: //Skipping by command

                break;

            case 11: //Run file
                printf("\n\n\nRun file: %s",lastDir); //Gets URL from user
                scanf("%d",&file_url);
                gets(file_url);

                if(command(file_url, lastDir) != 0)goto aborting_runf; //Checks for commands

                strcpy(lastDirFile, lastDir);
                strcat(lastDirFile, file_url);
                strcpy(file_url, lastDirFile); //Copies strings

                printf("\n");

                text_color(COLOR_RED);

                int result;

                result=system(file_url); //Runs file/program

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

                aborting_runf:

                break;

            case 12: //Properties
                printf("\n\n\nOpen properties from: %s",lastDir); //Gets URL from user
                scanf("%d",&file_url);
                gets(file_url);

                if(command(file_url, lastDir) != 0)goto aborting_propeties; //Checks for commands

                strcpy(lastDirFile, lastDir);
                strcat(lastDirFile, file_url);
                strcpy(file_url, lastDirFile); //Copies strings

                struct stat stats;

                stat(file_url, &stats);

                if(stats.st_mode == 16895 || stats.st_mode == 16749){
                    if(file_url[strlen(file_url)-1] != '/' && file_url[strlen(file_url)-1] != '\\' && file_url[strlen(file_url)-1] != '%') { //Checks if last character from URL is '/' or '\'
                        strcat(file_url, "/");
                    }
                }

                stat(file_url, &stats);

                text_color(COLOR_GREEN);
                printf("\nOpened properties: %s",file_url);
                text_color(COLOR_WHITE);
                printf("\n\nProperties:\n\n");
                text_color(COLOR_LIGHT_BLUE);
                text_color(COLOR_WHITE);

                printf("URL:\t\t\t\t%s\n",file_url);

                char time[100] = "";

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

                if(stats.st_size > 0) { //If is higher than 0, print size
                            printf("\nSize:\t\t\t\t%.2fKb (%d bytes)", (float)stats.st_size/1000, stats.st_size);
                }

                printf("\n");

                strcpy(lastDirBackup, lastDir); //Copies last directory to last directory backup

                text_color(COLOR_YELLOW);
                printf("\n\nPress any key to continue.");
                text_color(COLOR_WHITE);
                getch();

                aborting_propeties:

                break;

            case 13: //Encryption
                printf("\nFile to encrypt: %s",lastDir); //Gets URL from user
                scanf("%d",&file_url);
                gets(file_url);

                if(command(file_url, lastDir) != 0)goto aborting_encrypting; //Checks for commands

                if(file_url[strlen(file_url)-3] != 't' && file_url[strlen(file_url)-2] != 'x' && file_url[strlen(file_url)-1] != 't') {
                    text_color(COLOR_RED);
                    printf("\nFile '%s' is not a text file.\n",file_url);
                    text_color(COLOR_WHITE);
                } else {

                char fileenstr[5000] = "";
                char enstr[5000] = "";

                strcpy(lastDirFile, lastDir);
                strcat(lastDirFile, file_url);
                strcpy(file_url, lastDirFile); //Copies strings

                file = fopen(file_url, "r");

                if(file == NULL) { //Error handler
                    text_color(COLOR_RED);
                    printf("\nUnable to find file '%s'.\n",file_url);
                    text_color(COLOR_WHITE);
                    fclose(file);
                } else {
                    while(fgets(fileenstr, sizeof(fileenstr), file) != NULL) { //Prints line by line from file
                        strcat(enstr, fileenstr);
                    }

                    for(int i = 0; (i < strlen(enstr) && enstr[i] != '\0'); i++) {
                        enstr[i] = enstr[i] + 7; //Added 7 to character
                    }
                    fclose(file);
                    file = fopen(file_url, "w");

                    fputs(enstr, file);
                    fclose(file);

                    text_color(COLOR_GREEN);
                    printf("\nFile '%s' has been encrypted.",file_url);
                    text_color(COLOR_WHITE);

                    char newFileEnName[1000] = "";

                    strcpy(newFileEnName, str_replace(file_url, get_filename_from_path(file_url), ""));
                    strcat(newFileEnName, get_filename_from_path(file_remove_extension(file_url)));
                    strcat(newFileEnName, ".encf");

                    renameResult = rename(file_url, newFileEnName); //Changing file name

                    if(renameResult == 0) {
                    text_color(COLOR_GREEN);
                    printf("\nFile has been renamed to '%s'.",get_filename_from_path(newFileEnName));
                    text_color(COLOR_WHITE);
                    } else {
                    text_color(COLOR_RED);
                    printf("\nFile has not been renamed to '%s'.",get_filename_from_path(newFileEnName));
                    text_color(COLOR_WHITE);
                    }

                }

                }

                text_color(COLOR_YELLOW);
                printf("\n\nPress any key to continue.");
                text_color(COLOR_WHITE);
                getch();

                aborting_encrypting: //Skipping by command

                break;

            case 14: //Decryption
                printf("\nFile to decrypt: %s",lastDir); //Gets URL from user
                scanf("%d",&file_url);
                gets(file_url);

                if(command(file_url, lastDir) != 0)goto aborting_decrypting; //Checks for commands enc

                if(file_url[strlen(file_url)-4] != 'e' && file_url[strlen(file_url)-3] != 'n' && file_url[strlen(file_url)-2] != 'c' && file_url[strlen(file_url)-1] != 'f') {
                    text_color(COLOR_RED);
                    printf("\nFile '%s' is not encrypted.\n",file_url);
                    text_color(COLOR_WHITE);
                } else {

                char filedestr[5000] = "";
                char destr[5000] = "";

                strcpy(lastDirFile, lastDir);
                strcat(lastDirFile, file_url);
                strcpy(file_url, lastDirFile); //Copies strings

                file = fopen(file_url, "r");



                if(file == NULL) { //Error handler
                    text_color(COLOR_RED);
                    printf("\nUnable to find file '%s'.\n",file_url);
                    text_color(COLOR_WHITE);
                    fclose(file);
                } else {
                    while(fgets(filedestr, sizeof(filedestr), file) != NULL) { //Prints line by line from file
                        strcat(destr, filedestr);
                    }

                    for(int i = 0; (i < strlen(destr) && destr[i] != '\0'); i++) {
                        destr[i] = destr[i] - 7; //Removed 7 to character
                    }
                    fclose(file);
                    file = fopen(file_url, "w");

                    fputs(destr, file);
                    fclose(file);

                    text_color(COLOR_GREEN);
                    printf("\nFile '%s' has been decrypted.",file_url);
                    text_color(COLOR_WHITE);

                    char newFileEnName[1000] = "";

                    strcpy(newFileEnName, str_replace(file_url, get_filename_from_path(file_url), ""));
                    strcat(newFileEnName, get_filename_from_path(file_remove_extension(file_url)));
                    strcat(newFileEnName, ".txt");

                    renameResult = rename(file_url, newFileEnName); //Changing file name

                    if(renameResult == 0) {
                    text_color(COLOR_GREEN);
                    printf("\nFile has been renamed to '%s'.",get_filename_from_path(newFileEnName));
                    text_color(COLOR_WHITE);
                    } else {
                    text_color(COLOR_RED);
                    printf("\nFile has not been renamed to '%s'.",get_filename_from_path(newFileEnName));
                    text_color(COLOR_WHITE);
                    }

                }

                }

                text_color(COLOR_YELLOW);
                printf("\n\nPress any key to continue.");
                text_color(COLOR_WHITE);
                getch();

                aborting_decrypting: //Skipping by command

                break;

            case 15: //About
                printf("\n\n\nFile explorer 1.1.1\nThis application is under APACHE LICENSE 2.0 - \"./LICENSE.md\"\nPetr Pavlik 2021 - BeXCool\n\nWeb: bexcool.eu\nEmail: bxc@post.cz");
                text_color(COLOR_YELLOW);
                printf("\n\nPress any key to continue.");
                text_color(COLOR_WHITE);
                getch();
                break;

            case 16: //Help
                printf("\n\n\nList of commands (type them after selecting action by number):\n\t$root - Removes current URL and aborts action.\n\t$abort - Aborts current action.");
                text_color(COLOR_YELLOW);
                printf("\n\nPress any key to continue.");
                text_color(COLOR_WHITE);
                getch();
                break;

            case 17: //Close
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
