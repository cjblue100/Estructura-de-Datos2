#include <iostream>
#include <stdexcept>
#include "FIleM.h"




int main(int argc, char *argv[])
{
    FileM bina;
    
    int coso=bina.mainF();
    if (coso!=1)
        bina.initMatplotpp(argc,argv);
   
   
    //coso.DISPLAY();
    
    
    //bina.converter(argv);

    //bina.printFile(argv);
    
    //bina.Country_Filter(argv);

    //bina.Date_Filter(argv);
    return 0;

}