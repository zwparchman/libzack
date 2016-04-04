//defer an action until the defer object is destructed
//the action can be aborted.
//the action is a void returning function or function like object
//that takes no arguments
//the class is constructed in active mode


#ifndef  Defer_INC
#define  Defer_INC

#include <functional>

struct Defer{
  bool active;

  std::function<void()> fun;

  template <typename T>
  Defer( T defered ){
    fun = std::bind( defered );
    active=true;
  }

  void activate(){
    active=true;
  }

  void deactivate(){
    active=false;
  }

  bool is_activated() const {
    return active;
  }

  ~Defer(){
    if( active ){
      fun();
    }
  }
};

#endif   /* ----- #ifndef Defer_INC  ----- */
