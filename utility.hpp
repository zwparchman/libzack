
#ifndef  utility_INC
#define  utility_INC

#include <math.h>
#include <utility> 
#include <algorithm>
#include <assert.h>

namespace zack{

template<typename T>
T clamp( T val, std::pair<T,T>range){
  assert( range.first <= range.second);

  return std::max( std::min( val, range.second), range.first);
}

template <typename T>
double normalize( T val, std::pair<T,T> range){
  assert( range.first <= range.second);

  auto diff = abs(range.second - range.first);
  return (val - range.first ) / (double)diff;
}

template <typename T>
T lerp( double val, std::pair<T,T> range){

  T diff = (range.second - range.first);
  T off = diff * val;
  return (range.first) + off;
}

template <typename T, typename R>
R remap( T val, std::pair<T,T> range1, std::pair<R,R> range2){
  assert( range1.first <= range1.second);

  double v = normalize( val, range1);
  return lerp( v, range2);
}

}
#endif   /* ----- #ifndef utility_INC  ----- */
