#ifndef LAYER_H
#define LAYER_H

#include "lith_utils.h"
#include <iostream>
#include <math.h>
#include "layer.h"
#include <Eigen/Dense>
#include "EM_Material.h"
#include <complex>
#include <boost/math/complex/asin.hpp>

using namespace std;

enum polarization_type {S, P  };
enum interface_type {subside, cladside};  //subside - interface closest to substrate,
                                         //cladside- cladding, wave incidents in the cladding

complex<double> cmplxasin(complex<double> z);

const double Px = 200; //period in nm


class EM_layer{
   protected:
     double thickness;
   public:
     virtual void display_info() = 0;
     virtual complex<double> get_nval(double wvlen, interface_type it) =0;
     double get_thickness( ){return thickness;}
       //add a method called perturb to randomly alter the layer .....
};

class EM_effmedium_layer:public EM_layer{
   private:
    EM_Material *my_mat1;
    EM_Material *my_mat2;
    double fill_frac1;
    double fill_frac2;
  public:
    EM_effmedium_layer(double tness, EM_Material* m1, double f1, EM_Material *m2, double f2)
     :my_mat1(m1), fill_frac1(f1), my_mat2(m2), fill_frac2(f2){
     this-> thickness= tness;}

    complex<double> get_nval(double wvlen, interface_type it){
       return fill_frac1*(my_mat1-> get_n(wvlen)) + fill_frac2*(my_mat2-> get_n(wvlen));}

    void display_info() {
       cout << thickness<<"--"<< my_mat1->get_name() <<"("<<fill_frac1<<")"<<"   "<<my_mat2->get_name() <<"("<<fill_frac2<<")"<<endl;}

};




class EM_thinfilm: public EM_layer{
   private:
      EM_Material* my_mat;   //

   public:
     EM_thinfilm(double tness, EM_Material* mymatp):my_mat(mymatp){
      this-> thickness= tness;}

    // const Eigen::Matrix2cd calculate_tmat (double wlen, complex<double> nsin_theta, polarization_type pt);

     void display_info() {
          cout << thickness<<"--"<< my_mat->get_name() <<endl;}

     complex<double> get_nval(double wvlen, interface_type it){
       return my_mat-> get_n(wvlen);}

};

const Eigen::Matrix2cd calculate_tmat_intf(double wlen, complex<double> nsin_theta, polarization_type pt, EM_layer* llayer, EM_layer* rlayer);
const Eigen::Matrix2cd calculate_tmat (double wlen, complex<double> nsin_theta, polarization_type pt, EM_layer* thislay);








//class periodic_layers: public em_layer{
//   private:
//      unsigned short mat_index1, mat_index2, Nper;   // check pic for details
//      //evernote:///view/27032327/s222/f0b574fa-f30c-4f6f-af1c-96f5cb9d316e/f0b574fa-f30c-4f6f-af1c-96f5cb9d316e/
//      double tsub1, tsub2;           //individual layer thicknesses
//
//   public:
//     periodic_layers(short Np, short mind1, double d1, short mind2, double d2)
//     :Nper(Np), mat_index1(mind1),mat_index2(mind2), tsub1(d1), tsub2(d2){
//      this-> thickness= Np*(d1+d2);
//     }
//
//     const double & calculate_T(double theta_inc, polarization_type pt){
//          double t = 1.0;
//          return t;
//     }
//     virtual void display_info() {
//          cout << thickness<<"--"<<mat_index1<<"-"<<tsub1<<" : "<<mat_index2<<"-"<<tsub2<<"....X"<<Nper<<endl;
//     }
//};
//
//class bin_grating: public em_layer{
//   private:
//      unsigned short mat_index1, mat_index2;   // check pic for details
//      //evernote:///view/27032327/s222/f0b574fa-f30c-4f6f-af1c-96f5cb9d316e/f0b574fa-f30c-4f6f-af1c-96f5cb9d316e/
//      double mid_length;           //fraction of period
//      double center_location;      //fraction of period
//
//
//   public:
//     bin_grating(double tness, short mind1, short mind2, double cloc, double clen)
//     :mat_index1(mind1),mat_index2(mind2), mid_length(clen), center_location(cloc){
//      this-> thickness= tness;
//     }
//
//     const double & calculate_T(double theta_inc, polarization_type pt){
//          double t = 1.0;
//          return t;
//     }
//     virtual void display_info() {
//          cout << thickness<<"--"<<mat_index1<<" : "<<mat_index2<<"-"<<center_location<<","<<mid_length<<endl;
//     }
//};











#endif
