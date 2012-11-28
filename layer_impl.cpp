#include "layer.h"

//const Eigen::Matrix2cd EM_thinfilm::calculate_tmat (double wlen, complex<double> nsin_theta, polarization_type pt){
//          Eigen::Matrix2cd temp;
//          complex<double> n1 = get_nval(wlen,subside);
//          complex <double> t1 = boost::math::asin(nsin_theta/n1);
//          complex<double> J(0.0,1.0);
//          complex<double> phi = (thickness)*(2.0*M_PI*n1)/(wlen*cos(t1));
//          temp(0,0) = exp(-J*phi);
//          temp(0,1) = 0;
//          temp(1,0) = 0;
//          temp(1,1) = exp(J*phi);
//          //cout<<temp <<endl;
//          return temp ;
//     }


const Eigen::Matrix2cd calculate_tmat (double wlen, complex<double> nsin_theta, polarization_type pt, EM_layer* thislay){
          Eigen::Matrix2cd temp;
          complex<double> n1 = thislay-> get_nval(wlen,subside);
          complex <double> t1 = boost::math::asin(nsin_theta/n1);
          complex<double> J(0.0,1.0);
          complex<double> phi = (thislay->get_thickness())*(2.0*M_PI*n1)/(wlen*cos(t1));
          temp(0,0) = exp(-J*phi);
          temp(0,1) = 0;
          temp(1,0) = 0;
          temp(1,1) = exp(J*phi);
         // cout<<temp <<endl;
          return temp ;
     }


const Eigen::Matrix2cd calculate_tmat_intf(double wlen, complex<double> nsin_theta, polarization_type pt, EM_layer* llayer, EM_layer* rlayer){
          Eigen::Matrix2cd temp;



          complex<double> n1 = llayer-> get_nval(wlen,subside);
          complex <double> t1 = boost::math::asin(nsin_theta/n1);
          complex<double> n2 = rlayer-> get_nval(wlen,cladside);
          complex <double> t2 = boost::math::asin(nsin_theta/n2);

          complex<double> rlr, tlr;

      //  cout << n1 << "  "<<n2<<"  "<< t1<<"  "<<t2<<"  "<<endl;

        if (pt == S){
         rlr = (n1*cos(t1) - n2*cos(t2))/ (n1*cos(t1) + n2*cos(t2));
         tlr =          (2.0*n1*cos(t1))/ (n1*cos(t1) + n2*cos(t2));}
        else {
                 rlr = (n1*cos(t2) - n2*cos(t1))/ (n2*cos(t1) + n1*cos(t2));
                 tlr =          (2.0*n1*cos(t1))/ (n2*cos(t1) + n1*cos(t2)); }

       //  cout << rlr <<" "<<tlr<<endl;

          temp(0,0) = 1.0/tlr;
          temp(0,1) = rlr/tlr;
          temp(1,0) = temp(0,1);
          temp(1,1) = temp(0,0);


          return temp ;
}




