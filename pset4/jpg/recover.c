/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t BYTE;

struct ELEM
{
    BYTE  element;
};
bool jpg_opened = false;


int main(int argc, char* argv[])
{

    char* infile = "card.raw";
    struct ELEM elements[512];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 1;
    }
    char str[8];

    // read 512 bytes at the time

    int pic_num = 0;
    while(fread(&elements, sizeof(BYTE), 512, inptr) == 512)
    {
        if (elements[0].element == 0xFF && elements[1].element == 0xD8 && elements[2].element == 0xFF && (elements[3].element == 0xE0 || elements[3].element == 0xE1))
        {

                jpg_opened = true;
                sprintf(str, "%03d.jpg", pic_num);
                FILE* outptr = fopen(str, "w");
                if (outptr == NULL)
                {
                    fclose(inptr);
                    fprintf(stderr, "Could not create %s.\n", str);
                    return 2;
                }
                fwrite(&elements, sizeof(BYTE), 512, outptr);
                fclose(outptr);
                pic_num++;
        }

        else
        {
            if (jpg_opened)
            {
                FILE* outptr = fopen(str, "a");
                if (outptr == NULL)
                {
                    fclose(inptr);
                    fprintf(stderr, "Could not create %s.\n", str);
                    return 2;
                }
                fwrite(&elements, sizeof(BYTE), 512, outptr);
                fclose(outptr);
            }
        }
    }
    
    fclose(inptr);
    return 0;
}
