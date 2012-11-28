#include "EM_Material.h"

EM_dispMaterial::EM_dispMaterial(std::string name,std::string matfile)   //read data from file (n, Kappa FORMAT)
{
     this-> matname = name;

     std::ifstream infile(matfile.c_str());
     char tempbuff[256];

     while(infile.getline(tempbuff, 256)){
        double tmparr[3];
        std::istringstream iss(tempbuff);
        while (iss)  iss >> tmparr[0] >> tmparr[1] >> tmparr[2];
        ndata.addPoint(1000*tmparr[0], tmparr[1]);
        kapdata.addPoint(1000*tmparr[0], tmparr[2]);
     }
    infile.close();
}



