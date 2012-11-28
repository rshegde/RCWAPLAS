#include "lith_utils.h"

bool doubleEquals(double left, double right, double epsilon) {
   return (fabs(left - right) < epsilon);
}
bool doubleLess(double left, double right, double epsilon) {
   if (fabs(left - right) < epsilon) {
      // Within epsilon, so considered equal
      return (false);
   }
   return (left < right);
}
bool doubleGreater(double left, double right, double epsilon) {
   if (fabs(left - right) < epsilon) {
      // Within epsilon, so considered equal
      return (false);
   }
   return (left > right);
}






