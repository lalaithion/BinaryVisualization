#include "image.h"
#include <string.h>

Image::Image() {
    imageBuffer = (unsigned int*)malloc(sizeof(unsigned int)*IMAGE_BUFFER_SIZE*IMAGE_BUFFER_SIZE);
}

Image::Image(char *filename) {
    imageBuffer = (unsigned int*)malloc(sizeof(unsigned int)*IMAGE_BUFFER_SIZE*IMAGE_BUFFER_SIZE);
    load(filename);
}

Image::~Image() {
    free(imageBuffer);
}

int Image::load(char* filename)
{
    memset(imageBuffer, 0, IMAGE_BUFFER_SIZE*IMAGE_BUFFER_SIZE);
    fflush(stdout);
    FILE* fp = fopen(filename, "rb" ); // "rb" is "read binary"
    if(!fp) {
        printf("File %s not valid\n", filename);
        return 1;
    }

    int length = 0; //  Used to prevent reading from beyond the end of the file
    unsigned char* fileBuffer = (unsigned char*)malloc(FILE_BUFFER_SIZE);
    while( (length = fread(fileBuffer, 1, FILE_BUFFER_SIZE, fp)) )
    {
        int i;
        for (i = 0; i < length - 1; i++)
        {
            int x = fileBuffer[i];
            int y = fileBuffer[i + 1] * IMAGE_BUFFER_SIZE ;
            imageBuffer[x + y] += 1;
        }
    }
    free(fileBuffer);
    fclose(fp);
    return 0;
}

int Image::getMax(){
    unsigned int max = 0;
    for(int i = 0; i < IMAGE_BUFFER_SIZE*IMAGE_BUFFER_SIZE; i++)
    {
        if (imageBuffer[i] > max)
        {
            max = imageBuffer[i];
        }
    }
    return max;
}

void Image::getLinearNormalizedBuffer(float* normalized, float scale){
    float max = (float)getMax() / scale;
    std::cout << max << std::endl;
    for(int i = 0; i < IMAGE_BUFFER_SIZE*IMAGE_BUFFER_SIZE; i++)
    {
        normalized[i] = imageBuffer[i]/max;
    }
}

void Image::getPowNormalizedBuffer(float* normalized, float exponent){
    float max = (float)getMax();
    std::cout << max << std::endl;
    for(int i = 0; i < IMAGE_BUFFER_SIZE*IMAGE_BUFFER_SIZE; i++)
    {
        normalized[i] = pow(imageBuffer[i]/max,exponent);
    }
}

void Image::getLogNormalizedBuffer(float* normalized, float base) {
    memset(normalized, 0, sizeof(float)*IMAGE_BUFFER_SIZE*IMAGE_BUFFER_SIZE);
    float scale = log(base);
    float max = log((float)getMax())/log(base);
    for(int i = 0; i < IMAGE_BUFFER_SIZE*IMAGE_BUFFER_SIZE; i++)
    {
        if(imageBuffer[i]==0) {
            normalized[i] = 0;
        }
        else {
            normalized[i] = log(imageBuffer[i])/(scale*max);
        }
    }
}

