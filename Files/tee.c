#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

static int mode = 0;

int parse_args(int argc, char *argv[])
{
    char arg;

    while ((arg = getopt(argc, argv, "a")) != -1)
    {
        switch (arg)
        {

        case 'a':
            mode = 1;
            break;

        default:
            abort();
            break;
        }
    }

    return 0;
}

int main(int argc, char *argv[])
{
    char buf[100];
    size_t length;
    char *append;
    int i;
    FILE *files[10];
    int num_files;

    num_files = argc - optind;
    append = (mode ? "a" : "w");

    for (i = optind; i < argc; i++)
    {
        FILE *pFile = fopen(argv[i], append);

        if (pFile == NULL)
        {

            fprintf(stderr, "File was null");
        }
        files[i - optind] = pFile;
    }

    FILE *tee = fopen("tee.c", "r");
    while ((length = fread(&buf[0], 1, sizeof(buf), tee)) > 0)
    {

        fwrite(&buf[0], 1, length, stdout);

        for (i = 0; i < num_files; i++)
        {
            fwrite(&buf[0], 1, length, files[i]);
        }
    }

    printf("\n");
}