/*
LITHOGRAPHY SIMULATOR:
LINKER SETTINGS:
-lboost_timer
-lboost_system
-lboost_chrono
-lfftw3
-lm
-lpng
-lboost_filesystem
-lz
*/

#include "lith_utils.h"
#include "EM_Material.h"
#include "layer.h"
#include <vector>
#include <fstream>


const double c         = 299792458;        // velocity of light in vacuum
const double lambda_im =    193e-9;        // imaging wavelength
const double NA_im     =       1.07;        // NA of the imaging system
      double k_0;

//using boost::timer::cpu_timer;
//const int timerbank_cnt = 2;
//cpu_timer timerbank[timerbank_cnt];
//
//boost::random::mt19937 gen;
//boost::random::uniform_int_distribution<> dist(1, 6);


using namespace Eigen;
using namespace std;

int main()
{

//    EM_dispMaterial AG("SILVER", "silver.txt");
//
//   ofstream wikco("silverinterp.txt");
//
//    for (double w = 400; w <=800; w+= 5){
//    cout<<AG.get_n(w)<<endl;
//    wikco << w/1000<<" "<<real(AG.get_n(w))<<" "<<imag(AG.get_n(w))<< endl;
//    }
//
//   wikco.close();
//
//    return 0;
//}

  ofstream wikcor("fullstruct.txt");

   for (double wlength = 300; wlength <= 1600 ; wlength+= 5 ){
     wikcor << wlength<<"   ";

  for (double h = 50; h <= 100; h+=50){

    ////here we decide on the filling fractions/
    double d = 50;
    //double h = 95;
    double Per = 120;
    double g = Per - d;
    double hole_area = M_PI*d*d/4.0;
    double frac = hole_area/(Per*Per);

    vector <EM_Material *> matlist;
    matlist.push_back(new EM_simpMaterial("Vacuum",1.0,0.0));                      //0
    matlist.push_back(new EM_dispMaterial("Silicon", "silicon_crystaline.txt"));   //1
    matlist.push_back(new EM_dispMaterial("Silver", "silver.txt"))  ;              //2
    matlist.push_back(new EM_dispMaterial("Gold", "gold.txt"));                    //3
    matlist.push_back(new EM_simpMaterial("HSQ",1.4,0.0));                         //4

    vector <EM_layer *> laylist;  //substrate side first and on up
    laylist.push_back(new EM_thinfilm(20,matlist[2]));
 //   laylist.push_back(new EM_thinfilm(15,matlist[2]));
 //   laylist.push_back(new EM_thinfilm(5,matlist[3]));
 /*   laylist.push_back(new EM_effmedium_layer(15,matlist[2], 1.0-frac, matlist[4], frac));
    laylist.push_back(new EM_effmedium_layer(5,matlist[3], 1.0-frac, matlist[4], frac));
    laylist.push_back(new EM_effmedium_layer(h-20,matlist[0], 1.0-frac, matlist[4], frac));
    laylist.push_back(new EM_effmedium_layer(15,matlist[0], 1.0-frac, matlist[2], frac));
    laylist.push_back(new EM_effmedium_layer(5,matlist[0], 1.0-frac, matlist[3], frac));  */
    laylist.push_back(new EM_thinfilm(600,matlist[0]));



//// for (int ptype = 0; ptype <1; ptype++){
////
////     polarization_type ptyin;
////
////     if( ptype == 0)
////       ptyin = S;
//       else ptyin = P;



     double theta_inc = deg2rad(0);
    //double wlength = 700;

     complex<double> nsubs = laylist[0] -> get_nval(wlength,subside);
     complex<double> nclad = laylist[laylist.size() -1] -> get_nval(wlength,subside);
     complex<double> nsinthet = nclad*sin(theta_inc);
     complex <double> tsubs = boost::math::asin(nsinthet/nsubs);

     double tfac;
  //   if(ptyin == S)
       tfac = real(nsubs*cos(tsubs))/real(nclad*cos(theta_inc));
  //   else
  //     tfac = real(nsubs*cos(conj(tsubs)))/real(nclad*cos(theta_inc));

     Matrix2cd tot;
     tot(0,0) = 1;  tot(0,1) = 0; tot(1,0) = 0; tot(1,1) = 1;

     for (int i = 0; i  <laylist.size()-1; i++) {
       tot =       calculate_tmat(wlength, nsinthet ,S,laylist[i])* tot;
       tot =  calculate_tmat_intf(wlength, nsinthet, S, laylist[i+1], laylist[i])*tot;
     }
     double T = pow(abs(1.0/tot(0,0)),2);
     double R = pow (abs(tot(1,0)/tot(0,0)),2);



    wikcor<<" "<<R<<" ";
    //cout << wlength<<"   "<<R<<" "<<tfac*T<<endl;




    for(int i=0; i <laylist.size(); i ++)
       delete laylist[i];
    laylist.clear();
    for(int i=0; i <matlist.size(); i ++)
       delete matlist[i];
    matlist.clear();
  }
    wikcor << endl;
}

  wikcor.close();

//
//
//    L.clear();
//    delete l1;
//    delete l2;
//    delete l3;
    return 0;
 }


//bin_grating(double tness, short mind1, short mind2, double cloc, double clen)

/*
    // move all reporting to the report directory
    path path1("./runlog.txt");
    ofstream runlog(path1.leaf().string().c_str());

    runlog << "######################################################################## \n";
    runlog << "LITHOGRAPHY SIMULATOR 1.0     run log                                    \n";
    runlog << "######################################################################## \n";
    runlog <<"\n \n\n\n";

    //get the current time from the clock -- one second resolution
    ptime now = second_clock::local_time();
    cout<<"The program started on "<<now <<endl;
    runlog <<"The program started on "<<now <<"\n";


    timerbank[0].start();

    for (int i = 0; i <10; i++)
       cout << dist(gen)<< " ";
    cout << endl;

    k_0 = 2*M_PI/lambda_im;
    cout << k_0 << endl;
    cout << sin(k_0*1e-9) << endl;

   omp_set_num_threads(8);
   MatrixXd m = MatrixXd::Random(8200,8200);

   timerbank[1].start(); // timer tic
   m = m*m.inverse();
   timerbank[1].stop();  // timer toc

   cout<<m.trace() << endl;
   timerbank[0].stop();


    for(int i=0; i <timerbank_cnt; i++){
       cout   <<"timer #"<<i<<"  "<< timerbank[i].elapsed().wall/1e6<<" msec"<<endl;
       runlog <<"timer #"<<i<<"  "<< timerbank[i].elapsed().wall/1e6<<" msec"<<"\n";
    }
    runlog.close();


    remove_all("./report");
    create_directory("./report");
    rename(path1, "./report"/path1);




   // cout << deg2rad(30.0) << endl;

     Eigen::FFT<double> ffttry;

    VectorXd v1 = VectorXd::Random(8);
    VectorXd v2 = v1;
    v1 /= (v1.array().abs()).maxCoeff();

    VectorXcd v3;

    cout << v1<<endl;
    cout << endl;
//
    ffttry.fwd( v3,v1);
    ffttry.inv( v2,v3);

    cout << v3<<endl;
    cout << endl;
    cout << v2<< endl;  */







