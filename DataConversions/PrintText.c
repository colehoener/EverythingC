#include <stdio.h>
#include <string.h>
#define SIZE 128

int main(int argc, char **argv)
{
    //Decalres variables
    char line[SIZE];
    char byte;
    int i;
    int lineLength = 1;
    int done = 0;

    //Opens file and checks if it exists
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL)
        return 0;

    //Make sure size of file is not too large
    long size = ftell(fp);
    if (size > 10000)
    {
        return 0;
    }

    //Finds end of file
    fseek(fp, -1, SEEK_END);
    byte = (char)fgetc(fp);

    //Main loop. Runs until entire file is read.
    do
    {
        //Reads each line backwards. Looks for EOL.
        do
        {
            fseek(fp, -2, SEEK_CUR);
            byte = fgetc(fp);
            lineLength++;

            if (ftell(fp) == 1)
            {
                done = 1;
            }
        } while (byte != '\n' && done != 1);

        //Prints current file line to screen.
        if (done == 0)
        {
            fgets(line, lineLength, fp);
            printf("%s\n", line);
        }
        else
        {
            fseek(fp, -1, SEEK_CUR);
            fgets(line, lineLength + 1, fp);
            printf("%s\n", line);
        }

        //Resets search algorthim variables
        fseek(fp, -(lineLength), SEEK_CUR);
        lineLength = 1;
    } while (done != 1);

    fclose(fp);

    return 0;
}
