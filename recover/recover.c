#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>

 
int main(int argc, char *argv[])
{
    // Check for invalid usage
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    
    FILE *file = fopen(argv[1], "r");
    //check if file exists
    
    if (file == NULL)
    {
        printf("Image cannot be opened\n");
        return 1;
    }
    
    printf("file opened\n");
    
    typedef uint8_t BYTE;
    BYTE buffer[512];
    
    int num = 0;
    
    FILE *img = NULL;
    
    while(fread(&buffer, 512, 1, file))
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            
            if (img != NULL)
            {
                fclose(img);
            }
            //open new img file
            char *filename = malloc(7);
            sprintf(filename, "%03i.jpg", num);
            //printf("filename: %s\n", filename);
            img = fopen(filename, "w");
            free(filename);
            
            fwrite(&buffer, 512, 1, img);
            
            num++;
            printf("num: %i\n", num);
        }
        else
        {
            if (img != NULL)
            {
                fwrite(&buffer, 512, 1, img);
            }
            
        }
        
    }
    
    fclose(img);
    fclose(file);
    
    
}