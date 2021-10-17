#include "csapp.h"

int main(int argc, char **argv)
{
    int infile;
    int n;
    rio_t rio;
    char buf[MAXLINE];

    if (argc > 1)
    {
        infile = open(argv[1], O_RDONLY, 0);
        dup2(infile, STDIN_FILENO);
    }

    Rio_readinitb(&rio, STDIN_FILENO);
    while ((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0)
        Rio_writen(STDOUT_FILENO, buf, n);

    if (argc > 1)
    {
        close(infile);
    }

    exit(1);
}