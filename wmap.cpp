#include <iostream>
#include "wmap.h"
#include "vehicle.h"
#include "vfun.h"
#include "gfun.h"
#include <vector>

wmap::wmap()
 :flag (false),taken (false)
{
   int x;
   int y;
   int paladium;
   int iridium;
   int platinum;
   float danger;
   bool flag;
   bool taken;


}

wmap::~wmap()
{
    //dtor
}

void wmap::printstuff (){
    std::cout << paladium << "/n" << iridium << "/n" << danger ;}
