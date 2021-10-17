#include "csapp.h"

int main(int argc, char **argv)
{
    int descrpt;
    struct stat stat;
    char *type, *readok;

    //converts a char to int (needed since command line arg is a char)
    descrpt = atoi(argv[1]);

    fstat(descrpt, &stat);
    if (S_ISREG(stat.st_mode)) /* Determine file type */
        type = "regular";
    else if (S_ISDIR(stat.st_mode))
        type = "directory";
    else
        type = "other";
    if ((stat.st_mode & S_IRUSR)) /* Check read access */
        readok = "yes";
    else
        readok = "no";

    printf("type: %s, read: %s\n", type, readok);
    exit(1);
}