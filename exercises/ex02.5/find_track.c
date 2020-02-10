/* Example code for Exercises in C.

Modified version of an example from Chapter 2.5 of Head First C.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define NUM_TRACKS 5

char tracks[][80] = {
    "So What",
    "Freddie Freeloader",
    "Blue in Green",
    "All Blues",
    "Flamenco Sketches"
};


// Finds all tracks that contain the given string.
//
// Prints track number and title.
void find_track(char search_for[])
{
    int i;
    for (i=0; i<NUM_TRACKS; i++) {
        if (strstr(tracks[i], search_for)) {
            printf("Track %i: '%s'\n", i, tracks[i]);
        }
    }
}

/*
Helper function to print out the regular expression error and exit the program
*/
void reportErrAndExit(int status, regex_t *re) {
    char *errbuf = malloc(64); // error buffer
    regerror(status, re, errbuf, 64);
    printf("%s\n", errbuf);
    exit(1);
}

/* Match string against the given regular expression in pattern
Reference: https://pubs.opengroup.org/onlinepubs/7908799/xsh/regexec.html

string: string to search
pattern: regex pattern
return: 0 if no match, 1 otherwise
*/
int match(const char *string, char *pattern)
{
    regex_t re;

    // Compile regular expression contained in pattern
    int status = regcomp(&re, pattern, REG_EXTENDED|REG_NOSUB);
    if (status != 0) {
        reportErrAndExit(status, &re);
    }

    // Compare string with the compiled regular expression
    status = regexec(&re, string, (size_t) 0, NULL, 0);
    regfree(&re);
    if (status != 0) {
        // Repor error
        if (status != REG_NOMATCH) {
            reportErrAndExit(status, &re);
        }
        // No match
        return 0;
    }
    return 1;
}

// Finds all tracks that match the given pattern.
//
// Prints track number and title.
void find_track_regex(char pattern[])
{
    // TODO: fill this in
    int i;
    for (i=0; i<NUM_TRACKS; i++) {
        if (match(tracks[i], pattern)) {
            printf("Track %i: '%s'\n", i, tracks[i]);
        }
    }
}

// Truncates the string at the first newline, if there is one.
void rstrip(char s[])
{
    char *ptr = strchr(s, '\n');
    if (ptr) {
        *ptr = '\0';
    }
}

int main (int argc, char *argv[])
{
    char search_for[80];

    /* take input from the user and search */
    printf("Search for: ");
    fgets(search_for, 80, stdin);
    rstrip(search_for);

    // find_track(search_for);
    find_track_regex(search_for);

    return 0;
}
