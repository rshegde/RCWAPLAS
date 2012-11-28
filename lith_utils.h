#ifndef LITH_UTILS_H_INCLUDED
#define LITH_UTILS_H_INCLUDED
#include <cmath>    // for fabs( )
#include <math.h>
#include <sstream>
#include <iostream>
#include <string>

//#include <boost/timer/timer.hpp>
//#include "boost/date_time/gregorian/gregorian.hpp"
//#include "boost/date_time/posix_time/posix_time.hpp"
//#include "boost/random/mersenne_twister.hpp"
//#include "boost/random/uniform_int_distribution.hpp"
//#include <boost/filesystem.hpp>
//#include <boost/lexical_cast.hpp>


//using namespace boost::filesystem;
//using namespace boost::gregorian;
//using namespace boost::posix_time;





bool doubleEquals(double , double, double );
bool doubleLess(double , double , double );
bool doubleGreater(double , double , double );

//convert from a string to any numeric type
// usage e.g.  cout<<strToNum<double>("7.0")<<endl;
template<typename T> T strToNum(const std::string& str) {
   std::stringstream ss(str);
   T tmp;
   ss >> tmp;
   if (ss.fail( )) {
      std::string s = "Unable to format ";
      s += str;
      s += " as a number!";
      throw (s);
   }
   return (tmp);
}


//show the machine limits on any numeric type
// usage e.g.    cout << "long:" << endl;
////               showMinMax<long>( );
//template<typename T> void showMinMax( ) {
//   std::cout << "min: " << numeric_limits<T>::min( ) << std::endl;
//   std::cout << "max: " << numeric_limits<T>::max( ) << std::endl;
//   std::cout << endl;
//}

// conversion degrees and radians
inline double deg2rad(const double x) {return (x/180.0)*M_PI;  }
inline double rad2deg(const double x) {return (x*180.0)/M_PI;  }

//conversion between wavelength (nm) and frequency (THz)
inline double wvl2frq(const double x) {return 3e5/x;}
inline double frq2wvl(const double x) {return 3e5/x;}
inline double wvl2omeg(const double x) {return 299792458*2*M_PI/x;}



#endif // LITH_UTILS_H_INCLUDED
