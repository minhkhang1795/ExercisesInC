/* Example from Head First C.

Downloaded from https://github.com/twcamper/head-first-c

Modified by Allen Downey.
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <wait.h>

/*The program only prints out the first feed because execle() function will
* terminate the program once it's done.
*
*/
void error(char *msg)
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(1);
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <search phrase>\n", argv[0]);
        return 1;
    }
    const char *PYTHON = "/usr/bin/python2";
    const char *SCRIPT = "rssgossip.py";
    char *feeds[] = {
        "http://www.nytimes.com/services/xml/rss/nyt/Africa.xml",
        "http://www.nytimes.com/services/xml/rss/nyt/Americas.xml",
        "http://www.nytimes.com/services/xml/rss/nyt/MiddleEast.xml",
        "http://www.nytimes.com/services/xml/rss/nyt/Europe.xml",
        "http://www.nytimes.com/services/xml/rss/nyt/AsiaPacific.xml"
    };
    int num_feeds = 5;
    int i;
    int status;
    char *search_phrase = argv[1];
    char var[255];
    pid_t pid;

    for (int i=0; i<num_feeds; i++) {
      pid = fork();

      /* check for an error */
      if (pid == -1) {
          fprintf(stderr, "fork failed: %s\n", strerror(errno));
          perror(argv[0]);
          exit(1);
      }
      if (!pid) {
        sprintf(var, "RSS_FEED=%s", feeds[i]);
        char *vars[] = {var, NULL};

        int res = execle(PYTHON, PYTHON, SCRIPT, search_phrase, NULL, vars);
        if (res == -1) {
            error("Can't run script.");
        }
      }
    }

    // Wait for child processes
    for (i=0; i<num_feeds; i++) {
        pid = wait(&status);

        if (pid == -1) {
            fprintf(stderr, "wait failed: %s\n", strerror(errno));
            perror(argv[0]);
            exit(1);
        }
    }
    return 0;
}
