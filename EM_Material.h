#ifndef EM_MATERIAL_H
#define EM_MATERIAL_H

#include <fstream>
#include <complex>
#include <string>
#include <iostream>
#include "spline.h"


class EM_Material
{
    protected:
       std::string matname;
    public:
       virtual std::complex<double> get_n(double wvlen) = 0;
       std::string get_name(){return matname;}

};

class EM_simpMaterial: public EM_Material
{
    public:
        EM_simpMaterial(std::string name, double nval, double kapval)
             :n(nval), kappa(kapval){this-> matname = name;}
        std::complex<double> get_n(double wvlen){
           std::complex<double> epstmp( n, kappa );
            return epstmp; }
   private:
      double n,kappa;
};

class EM_dispMaterial: public EM_Material
{
    public:
        EM_dispMaterial(std::string name, std::string matfile);
        std::complex<double> get_n(double wvlen){
           std::complex<double> epstmp( ndata(wvlen), kapdata(wvlen) );
            return epstmp; }
   private:
      Spline ndata, kapdata;
};


#endif // EM_MATERIAL_H


