#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 *

3. Reflect: what worked, what slowed you down? What would you do differently next time?
- Learning how to use an array of *FILE took me a while to figure out. Pointer of pointer is hard!
- Understanding how the function tee() works also slowed me down. I had to make sure how -append works
together with printing out the content via stdout.
- Refactoring code and putting things into functions was also time-consuming because of pointers.

4. Compare your solution to this professional implementation or this one.
 What do you see in professional code that is not in your solution?
- One of the files does not break their main() code into smaller, modular functions.
- They put the function add() after main() and call it in main().
However, they declare add() before main() on the top
- The getopt to get the options looks similar to mine. However, they initialize `int ch`,
 but then cast `ch` to char later on. Not sure why they did that.
- They define a struct _list that looks like a linked list. We haven't learned about struct yet.
 */

/**
 * Take command line argument and return read/write mode
 * @param argc: argument count
 * @param argv: argument values
 * @return: a string designates read "r" or write "w" mode
 */
char *getMode(int argc, char *argv[]) {
    char ch;
    char *mode = "w";
    while ((ch = getopt(argc, argv, "a")) != EOF) {
        switch (ch) {
            case 'a':
                mode = "a";
                break;
            default:
                exit(1);
        }
    }
    return mode;
}

/**
 * Open files given the number of files, argc.
 * @param files: array of files
 * @param argc: number of files
 * @param argv: file names
 * @param mode: read or write mode
 */
void openFiles(FILE **files, int argc, char *argv[], char *mode) {
    for (int i = 0; i < argc; i++) {
        files[i] = fopen(argv[i], mode);
    }
}

/**
 * Close opened files
 * @param files: array of files
 * @param argc: number of files
 */
void closeFiles(FILE **files, int argc) {
    for (int i = 0; i < argc; i++) {
        fclose(files[i]);
    }
}

/**
 * Implement the tee function to print out
 * file content to files and stdout
 * @param files: array of files
 * @param argc: number of files
 * @param line: current line from the input
 */
void tee(FILE **files, int argc, char *line) {
    while (fgets(line, 1024, stdin)) {
        if (argc > 0) {
            for (int i = 0; i < argc; i++) {
                fprintf(files[i], "%s", line);
            }
        }
        fprintf(stdout, "%s", line);
    }
}

int main(int argc, char *argv[]) {
    char *line = malloc(1024);
    char *mode = getMode(argc, argv);
    argc -= optind;
    argv += optind;
    FILE **files = malloc(argc);
    openFiles(files, argc, argv, mode);
    tee(files, argc, line);
    closeFiles(files, argc);
    return 0;
}
