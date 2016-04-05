#ifndef TESTSUITE_H
#define TESTSUITE_H
#include "readfile.h"

class testSuite
{
public:
    testSuite();
    void testFileIO(fileReader* reader);
};

#endif // TESTSUITE_H
