#include <iostream>
#include "wmap.h"
#include "vehicle.h"
#include "vfun.h"
#include "gfun.h"
#include <vector>
#include <ctime>

using namespace std;


vehicle::vehicle()
:posx(0),posy(0),moves(0), failures (0), damaged(false),moved(false),access (0.5),speed(30), roundssinceitansweredthefinalsummons(0)
{

}

vehicle::~vehicle()
{
    //dtor
}


searchv::searchv()
//:type (0)
{
type=1;
flags=0;
tempflags=0;
access=0.6;
speed=20;
}


analyzev::analyzev()
//:type (1)
{
type=2;
maxload=200;
paladiumload=0;
iridiumload=0;
platinumload=0;
load=0;
tempplat=0;
tempir=0;
temppal=0;
access=0.4;
speed=10;

}

rescuev::rescuev()
//:type (2)
{
type=3;
repairs=0;
temprep=0;
access=0.4;
speed=20;
}


