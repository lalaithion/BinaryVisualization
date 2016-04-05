#include "readfile.h"


fileReader::fileReader(char* myFileName){
    myfile = myFileName;
    for(int i = 0; i < DX*DY*3; i++) {
        image[i] = 0;
    }
}

int fileReader::readFile()
{
    #define BLOCK_SIZE 32
    FILE* fp = fopen(myfile, "rb" ); // "rb" is "read binary"
    if(!fp) {
        printf("File %s not valid\n", myfile);
        exit(0);
    }
    /*
    //  Find size of file - probably useful later
    fseek(fp, 0, SEEK_END); //  Limited at 2GB
    int size = ftell(fp);
    rewind(fp)              //  Set filestream back to start
    */

    int length = 0; //  Used to prevent reading from beyond the end of the file
    unsigned char* buf = (unsigned char *)malloc(BLOCK_SIZE);
    while( (length = fread(buf, 1, BLOCK_SIZE, fp)) )
    { //  fread( destination, element size, bytes, filestream ) returns the number of bytes read
        int i;
        for (i = 0; i < length - 1; i++)
        {
            //  Converts from 1D character array to 3D RGB array
            int x = buf[i];
            int y = (buf[i + 1]) * DY ;

            if(image[(x + y ) * 3] < 255)
            {
                image[(x + y) * 3] += 100;
            }
        //int color = 2; //  Each location has a RGB componenet: R=0, G=1, B=2
        //image[(x + y) * 3 + color] = 255; //  This is the only blue mode coloring
        }
    }
    free(buf);
    fclose(fp);

    return 0;
}

unsigned char* fileReader::getImage(){
    cout<<"Image size: "<<sizeof(image)/sizeof(unsigned char)<<endl;
    return image;
}
