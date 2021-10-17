//Overide printf since no headers are allowed
int printf(const char *format, ...);

int main(int argc, char **argv)
{
    long int i = 5;
    unsigned long int count = 0;
    
    while (i)
    {
        count++;
        i >>= 1;
    }

    printf("Total bits = %lu", count);
    return 0;
}