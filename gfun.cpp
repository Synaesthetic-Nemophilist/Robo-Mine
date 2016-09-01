#include <iostream>
#include "wmap.h"
#include "vehicle.h"
#include "vfun.h"
#include "gfun.h"
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cmath>

using namespace std;


void fillmap (wmap *simulmap, int mapsize){
srand(time(0));

    for(int i=0; i<mapsize; i++){
        for(int j=0; j<mapsize; j++){
            simulmap->x=i;
            simulmap->y=j;
            simulmap->iridium=(1+(rand()%10));
            simulmap->paladium=(1+(rand()%10));
            simulmap->platinum=(1+(rand()%10));
            simulmap->danger=((rand()%9)/(float)10);
            *simulmap++;
        }
    }

cout << "Map succesfully initialized";
};


void nulifycell (wmap *cell){
cell->paladium=0;
cell->iridium=0;
cell->platinum=0;
cell->danger=0;


}


void celledit (wmap* cell){
int  ch;
float x1;
bool x2, re=false;
do{
cout << "Would you like to edit 1.Paladium deposits 2.Iridium Deposits 3.Platinum Deposits 4.Danger Factor 5.Flag Placement" << endl;
do{
cin >> ch;
if (ch<0 || ch>5) cout << "Please insert 1-5 to edit parameters or 0 to exit" << endl;
}while(ch<0 || ch>5);

if ((ch>0)&&(ch<5)){cin >> x1;}
else {cin >> x2;}

if (ch==1){
    cout<<"Insert new paladium value"<<endl;
    cell->paladium=x1;}
else if (ch==2){
    cout<<"Insert new iridium value"<<endl;
    cell->iridium=x1;}
else if (ch==3){
        cout<<"Insert new platinum value"<<endl;
    cell->platinum=x1;}
else if (ch==4){
        cout<<"Insert new danger value"<<endl;
    cell->danger=x1;}
else if (ch==5){
        cout<<"Insert '1' for flag, or '0' for no flag"<<endl;
    cell->flag=x2;}

if (ch!=0){
cout << "Would you like to edit any other values? 1.Yes 0.No" << endl;
cin >> re;}
}
while ((ch!=0)&&(re==true));

}

void vehicleedit (vehicle *obj,int mapsize)
{
    int ch,x1,y1,spd;
    float acc;
    bool dmge,re=false;
    do{
    cout << "Would you like to edit 1.Vehicle position 2.Condition 3.Access 4.Speed"<<endl;
    do{
        cin >> ch;
        if (ch<0 || ch>4) cout << "Please insert 1-5 to edit parameters or 0 to exit" << endl;
    }while(ch<0 || ch>4);
    if (ch==1)
    {
       cout<<"Insert in x-y manner the vehicle's new position"<<endl;
        do{cin>>x1; }while(x1<=0 || x1>=mapsize);
        obj->posx = x1;
        do{cin>>y1;} while(y1<=0 || y1>=mapsize);
        obj->posy = y1;
    }
    if (ch==2)
    {
        cout<<"Insert '1' to damage vehicle, or '0' to make it function"<<endl;
        do{cin>>dmge;} while(dmge!=0 && dmge!=1);
        obj->damaged=dmge;
    }
    if (ch==3)
    {
        cout<<"Insert new access parametre"<<endl;
        do{cin>>acc;} while(acc<=0 || acc>=1);
        obj->access=acc;
    }
    if (ch==4)
    {
        cout<<"Insert new speed parametre"<<endl;
        do{cin>>spd;} while(spd<=0 || spd>=31);
        obj->speed=spd;
    }
    if (ch!=0){
    cout << "Would you like to edit any other values? 1.Yes 0.No" << endl;
    cin >> re;}
    }while ((ch!=0)&&(re==true));
}


void cellinfo (wmap cell){
if (cell.x==0 && cell.y==0) cout << "Base Station";
else cout<< "\nCell [" <<cell.x << ":" << cell.y << "]";
cout << "\nPaladium deposit=" << cell.paladium << "\nIridium deposit=" << cell.iridium << "\nPlatinum deposit=" << cell.platinum << "\nDanger=" << cell.danger << " - Flag Set=" << cell.flag << endl;
}




//TEST FUNCTIONS=======================
void printcell (wmap cell){
cout<< cell.x << " " << cell.y << " ---- " <<  cell.paladium << " " << cell.iridium << " " << cell.platinum << " " << cell.danger<< ".......";
}

