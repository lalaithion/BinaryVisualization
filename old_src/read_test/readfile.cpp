#include "readfile.h"

fileReader::fileReader(char* myFileName){
    myfile = myFileName;
    for(int i = 0; i < DX*DY; i++) {
        image[i] = 0;
    }
    readFile();
}

int fileReader::readFile()
{
    FILE* fp = fopen(myfile, "rb" ); // "rb" is "read binary"
    if(!fp) {
        printf("File %s not valid\n", myfile);
        exit(0);
    }

    int length = 0; //  Used to prevent reading from beyond the end of the file
    unsigned char* buf = (unsigned char *)malloc(BLOCK_SIZE);
    while( (length = fread(buf, 1, BLOCK_SIZE, fp)) )
    {
        int i;
        for (i = 0; i < length - 1; i++)
        {
            int x = buf[i];
            int y = (buf[i + 1]) * DY ;
            image[(x + y)] += 1;
        }
    }
    free(buf);
    fclose(fp);

    return 0;
}

int fileReader::getImage(unsigned int * returnloc){
    returnloc = image;
    int max = 0;
    for(int i = 0; i < DX*DY; i++)
    {
        if (image[i] > max)
        {
            max = image[i];
        }
    }
    return max;
}
