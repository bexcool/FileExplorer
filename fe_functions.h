
/** Functions for File Explorer
 *
 * BeXCool 2020
 * Petr Pavlik <bxc@post.cz>
 *
 * [APACHE LICENSE 2.0 - "./LICENSE.md"]
 *
 */


#ifndef FE_FUNCTIONS_H_INCLUDED
#define FE_FUNCTIONS_H_INCLUDED
#endif // FE_FUNCTIONS_H_INCLUDED

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include "colors.h"

void delay(int number_of_seconds) {
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;

    // Storing start time
    clock_t start_time = clock();

    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds);
}

int command(char url[1000], char lastDir[1000]) {

    if(strcmp(url, "$root") == 0){
        strcpy(lastDir, "");
        text_color(COLOR_YELLOW);
        printf("\nRemoved current URL.");
        text_color(COLOR_WHITE);
        return(lastDir);
        }else if(strcmp(url, "$abort") == 0) {
                    text_color(COLOR_YELLOW);
                    printf("\nAborted current action.");
                    text_color(COLOR_WHITE);
                    return(1);
        } else {
            return(0);
        }
}

int remove_directory(const char *path) {
   DIR *d = opendir(path);
   size_t path_len = strlen(path);
   int r = -1;

   if (d) {
      struct dirent *p;

      r = 0;
      while (!r && (p=readdir(d))) {
          int r2 = -1;
          char *buf;
          size_t len;

          /* Skip the names "." and ".." as we don't want to recurse on them. */
          if (!strcmp(p->d_name, ".") || !strcmp(p->d_name, ".."))
             continue;

          len = path_len + strlen(p->d_name) + 2;
          buf = malloc(len);

          if (buf) {
             struct stat statbuf;

             snprintf(buf, len, "%s/%s", path, p->d_name);
             if (!stat(buf, &statbuf)) {
                if (S_ISDIR(statbuf.st_mode))
                   r2 = remove_directory(buf);
                else
                   r2 = unlink(buf);
             }
             free(buf);
          }
          r = r2;
      }
      closedir(d);
   }

   if (!r)
      r = rmdir(path);

   return r;
}

char* get_fileextension_from_path(char* filepath)	{

	char *filename = (char*)calloc(1, sizeof(filepath));
	filename = (strrchr(filepath, '.'))+1;
	//printf("fileextension: %s\n", filename);

	return filename;

}

char* get_filename_from_path(char* filepath)	{

	char *filename = (char*)calloc(1, sizeof(filepath));
	filename = (strrchr(filepath, '/'))+1;
	//printf("filename: %s\n", filename);

	return filename;

}

char *file_remove_extension(char* myStr) {
    char *retStr;
    char *lastExt;
    if (myStr == NULL) return NULL;
    if ((retStr = malloc (strlen (myStr) + 1)) == NULL) return NULL;
    strcpy (retStr, myStr);
    lastExt = strrchr (retStr, '.');
    if (lastExt != NULL)
        *lastExt = '\0';
    return retStr;
}

char *str_replace(char *orig, char *rep, char *with) {
    char *result; // the return string
    char *ins;    // the next insert point
    char *tmp;    // varies
    int len_rep;  // length of rep (the string to remove)
    int len_with; // length of with (the string to replace rep with)
    int len_front; // distance between rep and end of last rep
    int count;    // number of replacements

    // sanity checks and initialization
    if (!orig || !rep)
        return NULL;
    len_rep = strlen(rep);
    if (len_rep == 0)
        return NULL; // empty rep causes infinite loop during count
    if (!with)
        with = "";
    len_with = strlen(with);

    // count the number of replacements needed
    ins = orig;
    for (count = 0; tmp = strstr(ins, rep); ++count) {
        ins = tmp + len_rep;
    }

    tmp = result = malloc(strlen(orig) + (len_with - len_rep) * count + 1);

    if (!result)
        return NULL;

    while (count--) {
        ins = strstr(orig, rep);
        len_front = ins - orig;
        tmp = strncpy(tmp, orig, len_front) + len_front;
        tmp = strcpy(tmp, with) + len_with;
        orig += len_front + len_rep; // move to next "end of rep"
    }
    strcpy(tmp, orig);
    return result;
}
