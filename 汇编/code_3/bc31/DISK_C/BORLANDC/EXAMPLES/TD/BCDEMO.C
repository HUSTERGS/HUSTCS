/*	file <tcdemo.c>
 *
 *	Demonstration program to show off Turbo Debugger
 *	Reads words from standard input, analyzes letter and word frequency
 *      Copyright (c) 1988, 1989 - Borland Intl.
 */

#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

#define BUFSIZE			128	/* length of line buffer */
#define LETTERSINALPHABET       26      /* number of letters in the alphabet */
#define MAXWORDLENGTH		10      /* maximum word length allowed */
         
static struct linfo {
        unsigned int count;     	/* number of occurrences of this letter */
        unsigned int firstletter;       /* number of times as first letter of a word */
} letterinfo[26];       		/* info for each letter */;

static unsigned int wordcounts[MAXWORDLENGTH];  /* count of words of each length */
static char buffer[BUFSIZE];            /* line buffer */

static int makeintowords(char *bufp);
static long analyzewords(char *bufp);
static void printstatistics(int nlines, int nwords, long charcount);
static int readaline(void);
static void showargs(int argc, char *argv[]);

/* program entry point
 */
int main(int argc, char **argv) {
        unsigned int  nlines, nwords, wordcount;
        unsigned long totalcharacters;

        nlines = 0;
	nwords = 0;
	totalcharacters = 0;
        showargs(argc, argv);
        while (readaline() != 0) {
                wordcount = makeintowords(buffer);
                nwords += wordcount;
                totalcharacters += analyzewords(buffer);
                nlines++;
        }
        printstatistics(nlines, nwords, totalcharacters);
        return(0);
}

/* make the buffer into a list of null-terminated words that end in
 * in two nulls, squish out white space
 */
static int makeintowords(char *bufp) {
        unsigned int nwords;
        char *writep;

        nwords = 0;
        writep = bufp;
        do {
                while (*bufp == ' ')
                        bufp++; /* skip white space between words */
                if (*bufp != 0)
                        nwords++;       /* got the start of a word */
                while (*bufp && *bufp != ' ')
                        *writep++ = *bufp++;
                if (*bufp != 0)
                        bufp++; /* skip over space after word */
                *writep++ = 0;  /* word is null terminated */
        }
        while (*bufp);
        *writep++ = 0;
        return(nwords);
}

/* analyze the words in the buffer
 * there is a null between each word and two nulls at the end
 */
static long analyzewords(char *bufp) {
        unsigned long charcount;
	unsigned int  letterindex;

        charcount = 0;
        while (*bufp != 0) {
                char first = 1;
                int wordlen = 0;
                while (*bufp != 0) {
                        letterindex = toupper(*bufp) - 'A'; /* 0-based index */
                        if (first) {
                                letterinfo[letterindex].firstletter++;
                                first = 0;
                        }
                        letterinfo[letterindex].count++;        /* count the letter */
                        charcount++;
                        wordlen++;
                        bufp++;
                }
                wordcounts[wordlen - 1]++;      /* count a word of this length */
                bufp++; /* skip null at end of word */
        }
        return(charcount);
}

/* display all the statistics
 */
static void printstatistics(int nlines, int nwords, long charcount) {
        unsigned int n, count;
        float    averagelength;

        if (nlines == 0)
                printf("No lines entered\n");
        else {
                averagelength = (float)nwords / nlines;
                printf("Total number of letters = %ld\n", charcount);
                printf("Total number of lines = %d\n", nlines);
                printf("Total word count = %d\n", nwords);
                printf("Average number of words per line = %g\n", averagelength);
                for (n = 0; n < LETTERSINALPHABET; n++) {
                        count = letterinfo[n].count;     
                        if (count > 0)
                                printf("'%c' occurs %u times, %u times at start of a word\n",
                                 'A' + n, count, letterinfo[n].firstletter);
                }
                for (n = 0; n < MAXWORDLENGTH; n++) {
                        count = wordcounts[n];
                        if (count > 0) {
                                if (count == 1)
                                        printf("There is 1 word");
                                else
                                        printf("There are %d words", count);
                                printf(" %d character", n + 1);
                                if (n > 0)
                                        printf("s");    /* make it plural */
                                printf(" long\n");
                        }
                }
        }
}

/* read a line from the standard input into "buffer"
 * returns 1 for ok, 0 for end of file or empty line
 */
static int readaline() {
        printf("Enter a line (empty line to end): ");
        if (gets(buffer) == 0)
                return(0);      /* end of file */
        return(*buffer == 0 ? 0 : 1);   /* empty line is also end */
}

/* display the arguments the program was called with
 */
static void showargs(int argc, char *argv[]) {
        printf("Arguments: ");
        while (--argc)
                printf("%s ", *++argv);
        printf("\n");
}
