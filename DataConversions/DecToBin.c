#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    //Variable declaration
    int decimal = atoi(argv[1]);
    int binary[32];
    int i = 0;
    int length = 0;

    //Calculates binary from decimal
    do
    {
        binary[i] = decimal % 2;
        decimal = decimal / 2;
        i++;
        length++;
    } while (decimal != 0);

    //Prints binary to screen
    for (int j = 31; j > -1; j--)
    {
        if (j < length)
        {
            printf("%d", binary[j]);
        }
        else
        {
            printf("%d", 0);
        }
    }

    return 0;
}