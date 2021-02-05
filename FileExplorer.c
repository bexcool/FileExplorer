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

    char directory_url[10] = "";
    char file_url[10] = "";
    char lastDir[10] = "";
    char lastDirFile[10] = "";
    char file_content[10] = "";

    int OpenedDirectory = 0;
    int action = 1;
    int c;

    struct dirent *dir;
    struct stat filestat;

    FILE *file;

    DIR *directory;

    //testing();

    printf("\n-------------------------\nWelcome to File explorer!\n-------------------------");

    while(action!=10) {
        if(OpenedDirectory==0){
        printf("\n\n\n\nWhat do you want to do?\n\n\t1. Open directory\n\t2. Open directory from no root\n\t3. Open file\n\t4. Open file from no root\n\t",lastDir);
        printf("5. Create file\n\t6. Create file from no root\n\t7. Copy file from no root\n\t8. Delete file from no root\n\t9. About\n\t10. Close application\n\nEnter number: ");
        } else {
        printf("\n\n\n\nLast opened directory: %s\n\nWhat do you want to do?\n\n\t1. Open directory\n\t2. Open directory from no root\n\t3. Open file\n\t4. Open file from no root\n\t5. About\n\t6. Close application\n\nEnter number: ",lastDir);
        }
        scanf("%d",&action);

        switch(action){
            case 1:
                printf("\n\n\nOpen directory: %s",lastDir);
                scanf("%s",&directory_url);

                printf("End: %c",directory_url[(sizeof directory_url/sizeof directory_url[0])-1]);

                strcat(lastDir, directory_url);
                strcpy(directory_url, lastDir);

                //strlen

                directory = opendir(directory_url);

                printf("\nOpened directory: %s\nDirectory content:\n",directory_url);
                printf("----------------------------------------------------------\n\n");
                printf("%c%c\n",CONNECT_LEFT_RIGHT,CONNECT_DOWN_LEFT);

                if (directory) {
                    while ((dir = readdir(directory)) != NULL) {

                    printf(" %c %s\n",CONNECT_UP_DOWN_RIGHT,dir->d_name);
                    }
                    closedir(directory);
                }

                printf("\n----------------------------------------------------------");
                printf("\n\nPress any key to continue.");
                getch();
                OpenedDirectory=1;
                break;

            case 2:
                strcpy(lastDir, "");

                printf("\n\n\nOpen directory: %s",lastDir);
                scanf("%s",&directory_url);

                strcat(lastDir, directory_url);
                strcpy(directory_url, lastDir);

                directory = opendir(directory_url);

                printf("\nOpened directory: %s\nDirectory content:\n",directory_url);
                printf("----------------------------------------------------------\n\n");
                printf("%c%c\n",CONNECT_LEFT_RIGHT,CONNECT_DOWN_LEFT);

                if (directory) {
                    while ((dir = readdir(directory)) != NULL) {

                    printf(" %c %s\n",CONNECT_UP_DOWN_RIGHT,dir->d_name);
                    }
                    closedir(directory);
                }

                printf("\n----------------------------------------------------------");
                printf("\n\nPress any key to continue.");
                getch();
                OpenedDirectory=1;
                break;

            case 3:
                printf("\n\n\nOpen file: %s",lastDir);
                scanf("%s",&file_url);

                strcpy(lastDirFile, lastDir);
                strcat(lastDirFile, file_url);
                strcpy(file_url, lastDirFile);

                file = fopen(file_url, "r");

                printf("\nOpened file: %s\nFile content:\n",file_url);
                printf("----------------------------------------------------------\n\n");

                if (file) {
                    while ((c = getc(file)) != EOF)
                    putchar(c);
                    fclose(file);
                }

                printf("\n\n----------------------------------------------------------");
                printf("\n\nPress any key to continue.");
                getch();
                OpenedDirectory=1;
                break;

            case 4:
                strcpy(lastDir, "");

                printf("\n\n\nOpen file: %s",lastDir);
                scanf("%s",&file_url);

                strcpy(lastDirFile, lastDir);
                strcat(lastDirFile, file_url);
                strcpy(file_url, lastDirFile);

                file = fopen(file_url, "r");

                printf("\nOpened file: %s\nFile content:\n",file_url);
                printf("----------------------------------------------------------\n\n");

                if (file) {
                    while ((c = getc(file)) != EOF)
                    putchar(c);
                    fclose(file);
                }

                printf("\n\n----------------------------------------------------------");
                printf("\n\nPress any key to continue.");
                getch();
                OpenedDirectory=0;
                break;

            case 9:
                printf("\n\n\nFile explorer 1.1\nPetr Pavlik 1/2021 - BeXCool\n\nWeb: bexcool.eu\nEmail: bxc@post.cz");
                printf("\n\nPress any key to continue.");
                getch();
                break;

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

    /*FUNCTION - Only testing characters*/
void testing () {
    printf("Char test: %c",191);
}
