#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef uint8_t BYTE;
const int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{

    uint8_t buffer[BLOCK_SIZE];
    char *filename = malloc(sizeof(char) * 8);
    FILE *img;
    char *files = calloc(sizeof(char), 8);
    int count_jpg = -1;

    // Your program should accept exactly one command-line argument
    //returns 1 if the ./recover FILENAME is not inputted
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }
    FILE *raw_file = fopen(argv[1], "r");
    //returns 1 if the file could not be open for some reason
    if (raw_file == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }
    while (fread(buffer, 1, BLOCK_SIZE, raw_file) == BLOCK_SIZE)
    {
        //if first 4 bytes equal the start of a jpeg, increase the counter
        if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0){
            count_jpg++;
            //count_jpg starts at -1 to allow for the 000.jpg to be written instead of 001.jpg
            if(count_jpg  == 0){
                //generates files in the 00X.jpg format
                sprintf(filename, "%03i.jpg", count_jpg);
                //copies file names to a char array in order to allow check if the filename already exists when
                //the first 4 bytes don't equal a jpg
                strcpy(files, filename);
                img = fopen(files, "w");
                fwrite(buffer, 1, sizeof(buffer), img);
                fclose(img);
            }
            //after 000.jpg, creates a new file for the rest of the 49 jpg files
            else if (count_jpg > 0){
                sprintf(filename, "%03i.jpg",  count_jpg);
                strcpy(files, filename);
                img = fopen(files, "w");
                fwrite(buffer, 1, sizeof(buffer), img);
                fclose(img);
            }
        }
        //if the first four bytes of buffer don't equal a jpg, check if the file name in the char array already exists
        //if it does, open the file in append mode so it doesnt overwrite the other information and just appends the new bytes to the file
        else {
            sprintf(filename, "%03i.jpg", count_jpg);
            if (strcmp(files, filename) == 0) {
                img = fopen(files, "a");
                fread(buffer, 1, BLOCK_SIZE, img);
                fwrite(buffer, 1, sizeof(buffer), img);
                fclose(img);
            }

        }

    }
    //close and free files/variables
    fclose(raw_file);
    free(filename);
    free(files);
}