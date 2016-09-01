#ifndef VFUN_H
#define VFUN_H
#include <vector>

using namespace std;


void vmove(vehicle *obj, int mapsize, wmap *cell, vector<vehicle*>& vec,  int iter);

void vsact (searchv *obj, wmap *cell,int iter);
void vaact(analyzev *obj, wmap *cell, int mapsize,int iter);
void vract(rescuev *obj, wmap *cell, int mapsize, std::vector<vehicle*>& vec,int iter);



void malfunct(vehicle *obj, wmap*cell,int iter);
void vehicleinfo(vehicle* obj);
void vehicleinfoshort(vehicle* onj);
void vehicleinfoshort2(vehicle* obj);




void printstuff (vehicle *obj);
void printstuff2(vehicle *obj,wmap *cell);
void printstats (vehicle *obj);















#endif // VFUN_H
