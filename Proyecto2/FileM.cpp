#include "FIleM.h"
namespace csv = rapidcsv;
FileM::FileM() {}

int FileM::mainF()
{
    //Inicio Convertir csv a archivo de texto cjas juas juas
    std::cout << "\n\t\tCSV converter!!!\n";
    std::cout << "Escriba direccion del archivo csv a convertir: \n";
    std::string csv_fileN;
    std::cin >> csv_fileN;
    if (converter(csv_fileN) == 1)
        return 1;

    //Fin Convertir csv a archivo de texto cjas juas juas

    //Inicio Filtros
    std::cout << "\n\t\tFiltracion de datos!!! \n\n";
    std::cout << "Escriba codigo del pais: (Si no desea filtrar por pais escriba -1)\n";
    std::string paisN;
    std::cin >> paisN;

    std::cout << "\nEscriba fecha de inicio(Año-Mes-Dia. Ejem: 2020-09-04): (Si no desea filtrar por fecha -1)\n";
    std::string fechaI;
    std::cin >> fechaI;

    std::string fechaF = "-1";
    if (fechaI != "-1")
    {
        std::cout << "\nEscriba fecha final(Año-Mes-Dia. Ejem: 2020-09-04):\n";

        std::cin >> fechaF;
    }

    std::cout << "\nEscriba por numero de casos inicio: (Si no desea filtrar por numero de casos escriba -1)\n";
    int n_Casos;
    std::cin >> n_Casos;

    int n_Casos2 = -1;
    if (n_Casos != -1)
    {
        std::cout << "\nEscriba por numero de casos final: (Si no desea filtrar por numero de casos escriba -1\n";

        std::cin >> n_Casos2;
    }

    std::cout << "\nEscriba por numero de muertes inicio: (Si no desea filtrar por numero de muertes escriba -1\n";
    int n_Muertes;
    std::cin >> n_Muertes;

    int n_Muertes2 = -1;
    if (n_Muertes != -1)
    {
        std::cout << "\nEscriba por numero de muertes final: (Si no desea filtrar por numero de muertes escriba -1\n";
        std::cin >> n_Muertes2;
    }

    Filter(paisN, fechaI, fechaF, n_Casos, n_Casos2, n_Muertes, n_Muertes2);

    return 0;
}

std::vector<double> FileM::cum_cases;
std::vector<double> FileM::new_cases;
std::vector<double> FileM::cum_deaths;
std::vector<double> FileM::new_deaths;
std::vector<double> FileM::dates;
int FileM::fechas[2];

void FileM::Filter(std::string pais, std::string fechaI, std::string fechaF, int n_Casos, int n_Casos2, int n_Muertes, int n_Muertes2)
{

    std::ifstream iin("out.bin");
    header pop;

    iin.read(reinterpret_cast<char *>(&pop), sizeof(header));

    uint32_t crc = CRC::Calculate(reinterpret_cast<char *>(&pop), sizeof(header) - sizeof(uint32_t), CRC::CRC_32());

    if (crc != pop.crc)
    {
        std::cerr << "Bad header, Wrong CRC\n";
        return;
    }

    std::cout << pop.fecha << "\t\t" << pop.Pais_Codigo << "\t\t" << pop.Pais << "\t\t" << pop.WHO << "\t\t" << pop.Nuevos_Casos << "\t\t" << pop.cumulative << "\t\t" << pop.nuevas_muertes << "\t\t" << pop.cumulative_muertes << "\n\n";

    registros dat;
    double mes;
    int error = 0;

    

    while (!iin.eof())
    {
        iin.read(reinterpret_cast<char *>(&dat), sizeof(registros));
        try
        {
            bool Pais = Country_Filter(dat, pais);
            bool Fecha_Rango = Date_Filter(dat, fechaI, fechaF);
            bool NCasos = N_Casos_Filter(dat, n_Casos, n_Casos2);
            bool NMuertes = N_Muertes_Filter(dat, n_Muertes, n_Muertes2);

            if (Pais == true && Fecha_Rango == true && NCasos == true && NMuertes == true)
            {

                std::cout << "\n"
                          << dat.Date_reported << "\t\t" << dat.Country_code << "\t\t" << dat.Country << "\t\t" << dat.WHO_region << "\t\t" << dat.New_cases << "\t\t" << dat.Cumulative_cases << "\t\t" << dat.New_deaths << "\t\t" << dat.Cumulative_deaths << "\n";

                

                FileM::cum_cases.push_back(dat.Cumulative_cases);
                FileM::new_cases.push_back(dat.New_cases);
                FileM::cum_deaths.push_back(dat.Cumulative_deaths);
                FileM::new_deaths.push_back(dat.New_deaths);
                FileM::dates.push_back(mes);
            }
        }
        catch (std::exception ex)
        {
            if (error == 0)
            {
                std::cout << "\nPorfavor ingrese correctamente los datos!\n";
                error = 1;
            }
        }
    }
}

int FileM::converter(std::string argv)
{
    std::ifstream in(argv);

    if (!in.is_open())
    {
        std::cerr << "Cannot open file " << argv << '\n';
        return 1;
    }

    csv::Document doc(in);
    std::ofstream out("out.bin");

    header b;

    b.setSignature("CJAS");
    b.setName("Kobee");
    b.setfecha(doc.GetColumnName(0));
    b.setP_CODE(doc.GetColumnName(1));
    b.setPais(doc.GetColumnName(2));
    b.setWHO(doc.GetColumnName(3));
    b.setNC(doc.GetColumnName(4));
    b.setCumulativeC(doc.GetColumnName(5));
    b.setNew_Deaths(doc.GetColumnName(6));
    b.setCumulativeD(doc.GetColumnName(7));
    b.crc = CRC::Calculate(reinterpret_cast<char *>(&b), sizeof(header) - sizeof(uint32_t), CRC::CRC_32());
    out.write(reinterpret_cast<char *>(&b), sizeof(header));

    for (int i = 0; i < doc.GetRowCount(); i++)
    {
        registros lol;
        for (int j = 0; j < doc.GetColumnCount(); j++)
        {
            lol.setfecha(doc.GetCell<std::string>(j++, i));
            lol.setP_CODE(doc.GetCell<std::string>(j++, i));
            lol.setPais(doc.GetCell<std::string>(j++, i));
            lol.setWHO(doc.GetCell<std::string>(j++, i));
            lol.New_cases = doc.GetCell<int>(j++, i);
            lol.Cumulative_cases = doc.GetCell<int>(j++, i);
            lol.New_deaths = doc.GetCell<int>(j++, i);
            lol.Cumulative_deaths = doc.GetCell<int>(j++, i);

            //obja[doc.GetColumnName(j)]=doc.GetCell<std::string>(j,i);
        }
        out.write(reinterpret_cast<char *>(&lol), sizeof(registros));
    }

    out.close();
    return 0;
}

bool FileM::Country_Filter(registros dat, std::string pais)
{
    if (pais == "-1")
    {
        return true;
    }
    else
    {

        std::string Code = pais;

        std::string Code2 = dat.Country_code;

        if (Code2 == Code)
        {

            return true;
        }
    }
    return false;
}

int FileM::string_Cast(std::string coso, int pos)
{
    int num = 0;
    if (pos == 1)
    {
        char temp[2] = {coso.at(5), coso.at(6)};
        num = std::stoi(temp);
    }
    else if (pos == 2)
    {
        char temp[2] = {coso.at(8), coso.at(9)};
        num = std::stoi(temp);
    }

    return num;
}

bool FileM::Date_Filter(registros dat, std::string fechaI, std::string fechaF)
{
    if (fechaI == "-1")
    {

        return true;
    }
    else
    {

        int mesI = string_Cast(fechaI, 1);
        int diaI = string_Cast(fechaI, 2);

        int mes2 = string_Cast(fechaF, 1);
        int dia2 = string_Cast(fechaF, 2);

        std::string Read_Date = dat.Date_reported;

        int mes_read = string_Cast(Read_Date, 1);
        int dia_read = string_Cast(Read_Date, 2);

        int mayor = diaI, menor = dia2;
        bool paso = false;
        if (diaI > dia2)
        {
            mayor = diaI;
            menor = dia2;
        }
        else if (dia2 > diaI)
        {
            mayor = dia2;
            menor = diaI;
            paso = true;
        }
        if (dia_read >= mayor || mes_read > mesI)
        {
            paso = true;

            if (mes_read == mes2 && dia_read > dia2)
                paso = false;
        }

        /* std::cout<<"\nMesI: "<<mesI<<"\nDiaI: "<<diaI<<"\nMes2: "<<mes2<<
                   "\nDia2: "<<dia2<<"\nMes_read: "<<mes_read<<"\nDia_read:"<<dia_read;*/

        if (mes_read >= mesI && mes_read <= mes2)
        {
            if (paso == true)
            {
                return true;
            }
        }
        else
        {
            return false;
        }
    }
    return false;
}

bool FileM::N_Casos_Filter(registros dat, int nCasos1, int nCasos2)
{

    if (nCasos1 == -1)
    {
        return true;
    }
    else
    {
        int case_Read = dat.Cumulative_cases;

        if (case_Read >= nCasos1 && case_Read <= nCasos2)
        {

            return true;
        }
    }
    return false;
}

bool FileM::N_Muertes_Filter(registros dat, int nMuertes, int nMuertes2)
{
    if (nMuertes == -1)
        return true;
    else
    {
        int case_Read = dat.Cumulative_deaths;

        if (case_Read >= nMuertes && case_Read <= nMuertes2)
        {

            return true;
        }
    }

    return false;
}

void FileM::printFile(char *argv[])
{
    std::ifstream iin(argv[1]);
    header pop;

    iin.read(reinterpret_cast<char *>(&pop), sizeof(header));

    uint32_t crc = CRC::Calculate(reinterpret_cast<char *>(&pop), sizeof(header) - sizeof(uint32_t), CRC::CRC_32());

    std::cout << crc << "   /" << pop.crc << "\n";
    if (crc != pop.crc)
    {
        std::cerr << "Bad header, Wrong CRC\n";
        return;
    }

    std::cout << pop.fecha << "\t\t" << pop.Pais_Codigo << "\t\t" << pop.Pais << "\t\t" << pop.WHO << "\t\t" << pop.Nuevos_Casos << "\t\t" << pop.cumulative << "\t\t" << pop.nuevas_muertes << "\t\t" << pop.cumulative_muertes << "\n\n";

    registros dat;

    while (!iin.eof())
    {
        iin.read(reinterpret_cast<char *>(&dat), sizeof(registros));
        std::cout << dat.Date_reported << "\t\t\t\t" << dat.Country_code << "\t\t\t\t" << dat.Country << "\t\t\t\t" << dat.WHO_region << "\t\t\t\t" << dat.New_cases << "\t\t\t\t" << dat.Cumulative_cases << "\t\t\t\t" << dat.New_deaths << "\t\t\t\t" << dat.Cumulative_deaths << "\n";
    }
}

void FileM::DISPLAY()
{
    int n = cum_cases.size();
    vector<double> x(n);

    // Create test data
    for (int i = 0; i < n; ++i)
    {
        x[i] = i;
    }

    // To create a layer

    // To create multiple lines in one graph

    layer("Cumulative cases", 0);
    subplot(1, 1, 1);
    plot(x, cum_cases);

    xlabel("Cumulative cases");

    layer("New cases", 0);
    subplot(1, 1, 1);
    plot(x, new_cases);

    xlabel("New cases");

    layer("Cumulative deaths", 0);
    subplot(1, 1, 1);
    plot(x, cum_deaths);

    xlabel("Cumulative deaths");

    layer("New deaths", 0);
    subplot(1, 1, 1);
    plot(x, new_deaths);

    xlabel("new deaths");
}

FileM mp;
void Display() { mp.display(); }
void Reshape(int w, int h) { mp.reshape(w, h); }
void idle(void)
{
    glutPostRedisplay();
    usleep(10000);
}
void Mouse(int button, int state, int x, int y) { mp.mouse(button, state, x, y); }
void Motion(int x, int y) { mp.motion(x, y); }
void passive(int x, int y) { mp.passivemotion(x, y); }
void Keyboard(unsigned char key, int x, int y) { mp.keyboard(key, x, y); }

void FileM::initMatplotpp(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutCreateWindow(100, 100, 500, 400);
    glutDisplayFunc(Display);
    glutReshapeFunc(Reshape);
    glutIdleFunc(idle);
    glutMotionFunc(Motion);
    glutMouseFunc(Mouse);
    glutPassiveMotionFunc(passive);
    glutKeyboardFunc(Keyboard);

    glutMainLoop();
}
