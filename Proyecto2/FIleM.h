#ifndef FILEM_h
#define FILEM_H
using namespace std;
#include <matplotpp/matplotpp.h>
#include <iostream>
#include <fstream>
#include "binario.h"
#include "CRC.h"
#include "rapidcsv.h"
#include <exception>

struct grafico
{
    char Fecha_Inicio[20];
    char Fecha_Final[20];
    


}__attribute((packed));

class FileM:public MatPlot
{
    public:

    static std::vector<double> cum_cases;
    static std::vector<double> new_cases;
    static std::vector<double> cum_deaths;
    static std::vector<double> new_deaths;
    static std::vector<double> dates;
    static int fechas[2];
    FileM();

    int mainF();
    void Filter(std::string pais,std::string fechaI,std::string fechaF,int n_Casos
    ,int n_Casos2,int n_Muertes,int n_Muertes2);
    int  converter(std::string);
    void printFile(char *argv[]);
    bool Country_Filter( registros dat,std::string);
    bool Date_Filter( registros dat, std::string,std::string);
    bool N_Casos_Filter(registros dat, int nCasos1,int nCasos2);
    bool N_Muertes_Filter(registros dat, int nMuertes1,int nMuertes2);

    int string_Cast(std::string,int);

    void DISPLAY();
    void initMatplotpp(int argc, char *argv[]);


    
};






#endif