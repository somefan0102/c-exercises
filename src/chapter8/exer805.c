#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

// I renamed `fsize` to `inform` because of its general use case.

#define MAX_PATH 0x400

typedef struct dirent Dirent;
typedef struct stat Stat;

void inform(char *name);
void dirwalk(char *name, void (*f)(char *));

int n_strcmp(char *s, char *t);
int n_strlen(char *s);
char *monthday(int n);

int main(int argc, char *argv[]) {
     if (argc == 1) {
          fprintf(stderr, "Usage: program [file/dir]\n");
     } else {
          for (int i = 1; i < argc; i++) {
               inform(argv[i]);
          }
     }
     return 0;
}

void inform(char *name) {
     Stat stats;
     struct tm *t;

     if (stat(name, &stats) == -1) {
          fprintf(stderr, "Error (inform): Can't access \"%s\"\n", name);
          return;
     } else {
          if ((stats.st_mode & S_IFMT) == S_IFDIR) {
               dirwalk(name, inform);
               return;
          }
          printf(" ____ filename:  %s\n", name);
          printf("| size:          %iB\n", stats.st_size);
          t = localtime(&stats.st_atime);
          printf("| time accessed: %2u %s, %4u (%02u:%02u:%02u)\n", t->tm_mday, monthday(t->tm_mon), 1900+t->tm_year, t->tm_hour, t->tm_min, t->tm_sec);
          t = localtime(&stats.st_mtime);
          printf("| time modified: %2u %s, %4u (%02u:%02u:%02u)\n", t->tm_mday, monthday(t->tm_mon), 1900+t->tm_year, t->tm_hour, t->tm_min, t->tm_sec);
          t = localtime(&stats.st_ctime);
          printf("| time created:  %2u %s, %4u (%02u:%02u:%02u)\n\n", t->tm_mday, monthday(t->tm_mon), 1900+t->tm_year, t->tm_hour, t->tm_min, t->tm_sec);
     }
}

void dirwalk(char *dirname, void (*f)(char *)) {
     char name[MAX_PATH];
     DIR *dir;
     Dirent *entry;
     
     if ((dir = opendir(dirname)) == NULL) {
          fprintf(stderr, "Error (dirwalk): Can't open \"%s\"\n", dirname);
          return;
     }

     while ((entry = readdir(dir)) != NULL) {
          if (!n_strcmp(entry->d_name, ".") || !n_strcmp(entry->d_name, "..")) {
               continue;
          }

          if (n_strlen(dirname) + n_strlen(entry->d_name) + 2 > sizeof(name)) {
               fprintf(stderr, "Error (dirwalk): Name %s/%s too long.\n", dir, entry->d_name);
          } else {
               sprintf(name, "%s/%s", dirname, entry->d_name);
               (*f)(name);
          }
     }

     closedir(dir);
}

int n_strcmp(char *s, char *t) {
    while (*s == *t) {
        if (*s == '\0') {
            return 0;
        }
        s++; t++;
    }

    return *s - *t;
}

int n_strlen(char *s) {
     int i = 0;
     for (; *s; s++, i++);
     return i;
}

char *monthday(int n) {
     static char *months[] = {
          "Illegal month", "January", "February", "March",
          "April", "May", "June", "July", "August", "September",
          "October", "November", "December",
     };

     return (n >= 1 && n <= 12) ? months[n] : months[0];
}

/*
805: Modify the `fsize` program to print the other information contained in
     the inode entry.
*/