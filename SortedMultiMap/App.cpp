#include <iostream>

#include "ShortTest.h"
#include "ExtendedTest.h"

int main(){
    testAll();
    testTrim();
    testAllExtended();

    std::cout<<"Finished SMM Tests!"<<std::endl;
	system("pause");
}
