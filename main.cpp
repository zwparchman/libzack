#include <iostream>
#include "Timer.hpp"
#include "Channel.hpp"
#include "utility.hpp"
#include <unistd.h>
#include "Defer.hpp"

#include <gtest/gtest.h>


using namespace std;
using namespace zack;

TEST( normalize, float_test ){
  EXPECT_FLOAT_EQ( 0.5, normalize( 0.5f, std::pair<float,float>(0,1) ) );
  EXPECT_FLOAT_EQ( 0.25, normalize( 0.25f, std::pair<float,float>(0,1) ) );
}

TEST( normalize, int_test){
  EXPECT_FLOAT_EQ( 0.25f, normalize( 25, std::pair<int,int>(0,100) ) );
  EXPECT_FLOAT_EQ( 0.25f, normalize( 26, std::pair<int,int>(1,101) ) );
}

TEST( lerp, int_test){
  EXPECT_EQ( 10, lerp(1.0f , pair<int,int>(0,10)));
  EXPECT_EQ( 5, lerp( 0.5f, pair<int,int>(0,10)));
}

TEST( remap, basic ){
  EXPECT_EQ( 5, remap( 0.5f, pair<float,float>(0,1), pair<int,int>(0,10)));
  EXPECT_EQ( 6, remap( 0.5f, pair<float,float>(0,1), pair<int,int>(1,11)));
  EXPECT_EQ( 6, remap( 1.5f, pair<float,float>(1,2), pair<int,int>(1,11)));
}

TEST( timer, running ){
  Timer t;
  EXPECT_EQ( false, t.running);
  t.start();
  EXPECT_EQ( true, t.running);
  t.stop();
  EXPECT_EQ( false, t.running);
  t._continue();
  EXPECT_EQ( true, t.running);
  t.stop();
  EXPECT_EQ( false, t.running);
}

TEST( timer, timing){
  Timer t;
  t.start();
  usleep(50000);
  t.stop();
  EXPECT_NEAR(0.05f,t.getTime(), 0.001f);
  t._continue();
  usleep(50000);
  t.stop();
  EXPECT_NEAR(0.10f,t.getTime(), 0.001f);

  t.reset();
  EXPECT_NEAR( 0.0f, t.getTime(), 0.001f);
  t.start();
  usleep(50000);
  t.stop();
  EXPECT_NEAR(0.05f,t.getTime(), 0.001f);
  t._continue();
  usleep(50000);
  t.stop();
  EXPECT_NEAR(0.10f,t.getTime(), 0.001f);
}

TEST(channel, retrieve){
  Channel<int> chan;
  chan.put(1);
  int i,j,k;
  chan.get(i);
  EXPECT_EQ( 1, i);

  EXPECT_EQ( false, chan.get(i, false ));

  chan.put(2);
  chan.put(3);


  chan.get(j,false);
  chan.get(k,false);

  EXPECT_EQ( 2, j);
  EXPECT_EQ( 3, k);
}

TEST( channel, size){
  Channel<int> chan;

  EXPECT_EQ( 0, chan.size() );
  chan.put(0);
  EXPECT_EQ( 1, chan.size() );
  chan.put(0);
  EXPECT_EQ( 2, chan.size() );
  chan.put(0);
  EXPECT_EQ( 3, chan.size() );
  chan.put(0);
  EXPECT_EQ( 4, chan.size() );

  int i;
  chan.get(i,false);
  EXPECT_EQ( 3, chan.size() );
  chan.get(i,false);
  EXPECT_EQ( 2, chan.size() );
  chan.get(i,false);
  EXPECT_EQ( 1, chan.size() );
  chan.get(i,false);
  EXPECT_EQ( 0, chan.size() );
  chan.get(i,false);
  EXPECT_EQ( 0, chan.size() );
}

TEST(channel, is_closed){
  Channel<int> chan;

  EXPECT_EQ( false, chan.is_closed());
  chan.close();
  EXPECT_EQ( true, chan.is_closed());
  chan.close();
  EXPECT_EQ( true, chan.is_closed());
}

TEST(channel, late_emplace_fails){
  Channel<int> chan;

  chan.put(1);
  chan.close();

  try{
    chan.put(2);//should fail with exception
  } catch( std::logic_error& l){ 
    return ;
  }

  ADD_FAILURE()<<"Should have thrown an exception";
}

TEST(defer, occurs){
  int i=0;
  {
    Defer ([&](){i++;});
  }
    EXPECT_EQ(i,1);
}

TEST(defer, cancel){
  int i=0;
  {
    Defer d([&](){i++;});
    d.deactivate();
  }
  EXPECT_EQ(i,0);
}

TEST(defer, multiple_runs){
  int i=0;
  int j=0;
  {
    Defer d1([&](){i++;});
    Defer d2([&](){j++;});
  }
  EXPECT_EQ(i,1);
  EXPECT_EQ(j,1);

  {
    Defer d1([&](){i++;});
    Defer d2([&](){j++;});
    d2.deactivate();
  }

  EXPECT_EQ(i,2);
  EXPECT_EQ(j,1);
}

int main(int argc, char ** argv ){
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
