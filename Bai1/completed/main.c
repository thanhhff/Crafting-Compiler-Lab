#include <stdio.h>
#include <stdlib.h>

void fileOpenRead(FILE **f, char filename[]);

int main()
{
    FILE *fin;
    fileOpenRead(&fin, "vanban.txt");

    fclose(fin);
    return 0;
}

void fileOpenRead(FILE **f, char filename[])
{
    if ((*f = fopen(filename, "r")) == NULL)
    {
        printf("Can't open file: %s\n", filename);
        exit(1);
    }
}
