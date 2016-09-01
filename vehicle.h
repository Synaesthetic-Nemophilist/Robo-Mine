#ifndef VEHICLE_H
#define VEHICLE_H
#include <vector>
using namespace std;


class vehicle
{
    public:
        virtual ~vehicle();
        vehicle();
        int posx;
        int posy;
        bool damaged;
        bool moved;
        int failures;
        int type;
        float access;
        int speed;
        int moves;
        int roundssinceitansweredthefinalsummons;

        static int totalfailures;
        static int totalflags;
        static int totalload;
    protected:




    private:
    friend void malfunct(vehicle *obj,wmap *cell,int iter);
    friend void printstuff (vehicle *obj);
    friend void vmove(vehicle *obj, int mapsize, wmap *cell, vector<vehicle*>& vec,  int iter);
    friend void vact();

};



class searchv : public vehicle{
    public:
        searchv();
        int tempflags;
    private:
        int flags;

    friend void vsact (searchv *obj, wmap *cell,int iter);
    friend void vehicleinfo(vehicle* obj);
};


class analyzev : public vehicle{
    public:
        analyzev();
        int temppal;
        int tempir;
        int tempplat;
    private:
        int maxload;
        int paladiumload;
        int iridiumload;
        int platinumload;
        int load;

    friend void vaact (analyzev *obj, wmap *cell, int mapsize,int iter);
    friend void vehicleinfo(vehicle* obj);

};


class rescuev : public vehicle{
    public:
        rescuev();
        int repairs;
        int temprep;
    private:


   friend void vract(rescuev *obj, wmap *cell,int mapsize,vector<vehicle*>& vec,int iter);
   friend void vehicleinfo(vehicle* obj);
};












#endif // VEHICLE_H
