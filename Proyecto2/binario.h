#ifndef BINARIO_h
#define BINARIO_H
#include <cstdint>
#include <iostream>

struct header
{
    header()
    : crc(0)
    {
        std::fill(signature,signature + 4,0);
        std::fill(name,name + 4,0);
    }

    void setSignature(char *sign)
    {
        std::copy(sign,sign+4,signature);
    }

    void setName(const std::string& sname)
    {
        std::copy(sname.begin(),sname.end(),name);
    }
    
    void setfecha(const std::string& sfecha)
    {
        std::copy(sfecha.begin(),sfecha.end(),fecha);
    }

    void setP_CODE(const std::string& p_code)
    {
        std::copy(p_code.begin(),p_code.end(),Pais_Codigo);
    }

    void setPais(const std::string& spais)
    {
        std::copy(spais.begin(),spais.end(),Pais);
    }

    void setWHO(const std::string& WHOs)
    {
        std::copy(WHOs.begin(),WHOs.end(),WHO);
    }

    void setNC(const std::string& NC)
    {
        std::copy(NC.begin(),NC.end(),Nuevos_Casos);
    }

    void setCumulativeC(const std::string& cumc)
    {
        std::copy(cumc.begin(),cumc.end(),cumulative);
    }

    void setNew_Deaths(const std::string& n_deahts)
    {
        std::copy(n_deahts.begin(),n_deahts.end(),nuevas_muertes);
    }

    void setCumulativeD(const std::string& cumd)
    {
        std::copy(cumd.begin(),cumd.end(),cumulative_muertes);
    }

    



   char signature[4];
   char name[64];
   char fecha[64];
   char Pais_Codigo[64];
   char Pais[64];
   char WHO[64];
   char Nuevos_Casos[64];
   char cumulative[64];
   char nuevas_muertes[64];
   char cumulative_muertes[64];
   uint32_t crc;

}__attribute((packed));


struct registros
{
    registros()
    : New_cases(0),Cumulative_cases(0),New_deaths(0),Cumulative_deaths(0)
    {
        std::fill(Date_reported,Date_reported +20,0);
        std::fill(Country_code,Country_code +20,0);
        std::fill(Country,Country +20,0);
        std::fill(WHO_region,WHO_region +20,0);
    }

    void setfecha(const std::string& sfecha)
    {
        std::copy(sfecha.begin(),sfecha.end(),Date_reported);
    }

    void setP_CODE(const std::string& p_code)
    {
        std::copy(p_code.begin(),p_code.end(),Country_code);
    }

    void setPais(const std::string& spais)
    {
        std::copy(spais.begin(),spais.end(),Country);
    }

    void setWHO(const std::string& WHOs)
    {
        std::copy(WHOs.begin(),WHOs.end(),WHO_region);
    }


    char Date_reported[20];
    char Country_code[20];
    char Country[64];
    char WHO_region[20];
    int  New_cases;
    int  Cumulative_cases;
    int  New_deaths;
    int  Cumulative_deaths;


}__attribute((packed));


#endif