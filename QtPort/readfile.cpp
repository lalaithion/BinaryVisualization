#include "readfile.h"

int readfile(char* filename, unsigned int* image)
{
    for(int i = 0; i < IMAGE_SIZE*IMAGE_SIZE; i++) {
        image[i] = 0;
    }
    FILE* fp = fopen(filename, "rb" ); // "rb" is "read binary"
    if(!fp) {
        printf("File %s not valid\n", filename);
        return 1;
    }

    int length = 0; //  Used to prevent reading from beyond the end of the file
    unsigned char* buf = (unsigned char*)malloc(BLOCK_SIZE);
    while( (length = fread(buf, 1, BLOCK_SIZE, fp)) )
    {
        int i;
        for (i = 0; i < length - 1; i++)
        {
            int x = buf[i];
            int y = buf[i + 1] * IMAGE_SIZE ;
            image[x + y] += 1;
        }
    }
    free(buf);
    fclose(fp);

    return 0;
}

int getMax(unsigned int* image){
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

void linearNormalize(unsigned int* image, float* normalized, float scale){
    float max = (float)getMax(image) / scale;
    std::cout << max << std::endl;
    for(int i = 0; i < DX*DY; i++)
    {
        normalized[i] = image[i]/max;
    }
}

void powNormalize(unsigned int* image, float* normalized, float exponent){
    float max = (float)getMax(image);
    std::cout << max << std::endl;
    for(int i = 0; i < DX*DY; i++)
    {
        normalized[i] = pow(image[i]/max,exponent);
    }
}

void logNormalize(unsigned int* image, float* normalized, float base) {
    float scale = log(base);
    float max = log((float)getMax(image))/log(base);
    for(int i = 0; i < DX*DY; i++)
    {
        normalized[i] = log(image[i])/(scale*max);
    }
}

