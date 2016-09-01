#include <iostream>
#include "wmap.h"
#include "vehicle.h"
#include "vfun.h"
#include "gfun.h"
#include <cstdlib>
#include <ctime>
#include <vector>

extern int mapsize;
extern wmap simmap;
using namespace std;


void vmove(vehicle *obj, int mapsize, wmap *cell, vector<vehicle*>& vec, int iter){
if (obj->damaged==true) {obj->roundssinceitansweredthefinalsummons++;}
int it=0;
bool except=false;
cell+=(obj->posx)*mapsize+(obj->posy);
srand(time(0)+iter);

while ((it<obj->speed)&&(obj->damaged==false)){

    except=false;
    int mov=(rand()%6);
    cell->taken=false;

    switch (mov) {
        case 0:
        case 4://DOWN
            if (((obj->posx)+1)<mapsize && (((cell+mapsize)->flag!=true) || except==true))
            {
                (obj->posx)++;
                cell+=mapsize;
                it++;
                obj->moves++;
                obj->moved=true;
            }
            break;
        case 1://UP
            if (((obj->posx)-1)>=0 && (((cell-mapsize)->flag!=true) || except==true))
            {
                (obj->posx)--;
                cell-=mapsize;
                it++;
                obj->moves++;
                obj->moved=true;
            }
            break;
        case 2:
        case 6://RIGHT
            if (((obj->posy)+1)<mapsize && (((cell+1)->flag!=true) || except==true))
            {
                (obj->posy)++;
                cell++;
                it++;
                obj->moves++;
                obj->moved=true;
            }
            break;
        case 3://LEFT
            if (((obj->posy)-1)>=0 && (((cell-1)->flag!=true) || except==true))
            {
                (obj->posy)--;
                cell--;
                it++;
                obj->moves++;
                obj->moved=true;
            }
            break;
        default:
            break;}


    if (((cell+mapsize)->flag==true) && ((cell-mapsize)->flag==true) && ((cell+1)->flag==true) && ((cell-1)->flag==true))
        except=true;

if (obj->type == 1){
    searchv *p = dynamic_cast<searchv *>(obj);
    vsact(p, cell,iter);
    }
else if (obj->type == 2){
    analyzev *p = dynamic_cast<analyzev *>(obj);
    vaact(p, cell, mapsize,iter);}
else if (obj->type == 3){
    rescuev *p = dynamic_cast<rescuev *>(obj);
    vract(p, cell, mapsize, vec,iter);}


    malfunct(obj, cell,iter);
}

    if (obj->type == 1){
        searchv *p = dynamic_cast<searchv *>(obj);
        if(p->tempflags!=0)
            cout << "\nVehicle " << iter+1 << " -> Search Vehicle placed "<<p->tempflags<<" flags.";
            p->tempflags=0;
    }
    if (obj->type == 2){
        analyzev *p = dynamic_cast<analyzev *>(obj);
        if(p->temppal!=0||p->tempplat!=0||p->tempir!=0)
            cout << "\nVehicle " << iter+1 << " -> Analysis Vehicle mined "<<p->temppal<<" paladium units, " << p->tempplat<<" platinum units and "<< p->tempir<<" iridium units.";
            p->tempir=0;
            p->temppal=0;
            p->tempplat=0;
    }
    if (obj->type == 3){
        rescuev *p = dynamic_cast<rescuev *>(obj);
        if(p->temprep!=0)
            cout << "\nVehicle " << iter+1 << " -> Rescue Vehicle repaired "<<p->temprep<<" damaged vehicle(s).";
            p->temprep=0;
    }
}

void vsact (searchv *obj, wmap *cell,int iter){
    if (cell->danger>0.7 && cell->flag==false){
       obj->tempflags++;
       cell->flag=true;
       obj->flags++;
       obj->totalflags++;
    }}

void vaact (analyzev *obj, wmap *cell, int mapsize,int iter){

    int cs=0;
    if ((cell->iridium>0.3 && cell->paladium>0.3 && cell->platinum>0.3)&&(obj->posx!=0 || obj->posy!=0)&&(obj->maxload>=obj->load)){
    while ((obj->maxload>=obj->load)&&(cell->iridium>0 || cell->paladium>0 || cell->platinum>0)){

        ++cs;
        if (cs>3) cs-=3;

if (cs==2){ if (cell->iridium>0){
        cell->iridium--; obj->iridiumload++; obj->load++; obj->totalload++; obj->tempir++;
        }}
else if (cs==1) {if (cell->platinum>0){
        cell->platinum--; obj->platinumload++; obj->load++; obj->totalload++; obj->tempplat++;
        }}
else if (cs==3){  if (cell->paladium>0){
        cell->paladium--; obj->paladiumload++; obj->load++; obj->totalload++; obj->temppal++;
        }}


}
}
    if(obj->load>=obj->maxload){
        cout << "\n=BASE LOAD UPDATED=" << endl;
        cell-=((obj->posx)*mapsize+(obj->posy));


        obj->posx=0;
        obj->posy=0;

        cell->iridium += obj->iridiumload;
        cell->platinum += obj->platinumload;
        cell->paladium += obj->paladiumload;

        obj->iridiumload=0;
        obj->platinumload=0;
        obj->paladiumload=0;
        obj->load=0;

    }

}

void vract(rescuev *obj, wmap *cell,int mapsize,vector<vehicle*>& vec,int iter){
    int x1=(cell+mapsize)->x;
    int x2=(cell-mapsize)->x;
    int y1=(cell++)->y;
    int y2=(cell--)->y;


    if (((cell++)->taken=true)||((cell--)->taken=true)||((cell+mapsize)->taken=true)||((cell-mapsize)->taken=true))
        {
            for (int it=0; it<vec.size(); it++)
            {
                if (vec[it]->posy==cell->y)
                {
                    if ((vec[it]->posx==x1)||(vec[it]->posx==x2))
                    {
                        if(vec[it]->damaged==true)
                        {
                            vec[it]->damaged=false;
                            obj->repairs++;
                            obj->temprep++;
                            obj->roundssinceitansweredthefinalsummons=0;
                        }
                    }
                }
                else if (vec[it]->posx==cell->x)
                {
                    if ((vec[it]->posy==y1)||(vec[it]->posy==y2))
                    {
                        if(vec[it]->damaged==true)
                        {
                            vec[it]->damaged=false;
                            obj->repairs++;
                            obj->temprep++;
                            obj->roundssinceitansweredthefinalsummons=0;
                        }
                    }
                }
            }
        }
}

void malfunct(vehicle *obj, wmap*cell ,int iter){
   if ((cell->danger*(1-obj->access))>0.45){
        obj->damaged=true;
        obj->failures++;
        obj->totalfailures++;
        cout<<"\n Vehicle "<<iter+1<<" damaged on cell: "<<obj->posx<<"-"<<obj->posy<<endl;
        }


}

void vehicleinfo(vehicle* obj){
if (obj->type==1) cout << "\nSearch Vehicle";
else if (obj->type==2) cout << "\nAnalysis Vehicle";
else if (obj->type==3) cout << "\nRescue Vehicle";

cout << "\nPosition " << obj->posx << ":" << obj->posy << "\nCondition: ";

if (obj->damaged==true) cout << "DAMAGED";
else cout << "Functioning";
cout << "\nSpeed: " << obj->speed;
cout << "\nAccess rate: "  << obj->access;
cout << "\nTotal moves: " << obj->moves;
cout << "\nFailures: " << obj->failures << "\n" <<endl;


if (obj->type==1) {
    searchv *p = dynamic_cast<searchv *>(obj);
    cout << "Flags Placed: " << p->flags << endl;
}
else if (obj->type==2) {
    analyzev *p = dynamic_cast<analyzev *>(obj);
    cout << "Paladium Load: " << p->paladiumload << "\nIridium Load: " << p->iridiumload << "\nPlatinum Load: " << p->platinumload << endl;
}
else if (obj->type==3) {
    rescuev *p = dynamic_cast<rescuev *>(obj);
    cout << "Repairs Conducted: " << p->repairs << endl;
    }


}

void vehicleinfoshort(vehicle* obj){
    if (obj->type==1) cout << "Search";
else if (obj->type==2) cout << "Analysis";
else if (obj->type==3) cout << "Rescue";

cout << " == " << obj->posx << ":" << obj->posy <<endl;

}

void vehicleinfoshort2(vehicle* obj){
    if (obj->type==1) cout << "Search";
else if (obj->type==2) cout << "Analysis";
else if (obj->type==3) cout << "Rescue";

cout << " == " << obj->posx << ":" << obj->posy;

if (obj->damaged==0) cout << " -> Functioning" << endl;
else cout << " -> Damaged for " <<obj->roundssinceitansweredthefinalsummons<<" rounds."<< endl;

}




void printstuff2(vehicle *obj,wmap *cell){cout << "posx=" << obj->posx << " posy=" << obj->posy << " Danger="<<cell->danger<<endl;
                                        cout<<"flag:"<<cell->flag<<endl;
                                        cout<<endl;
}

void printstuff (vehicle *obj){
    switch(obj->type)
    {
        case 1: cout <<"Search Robot~Position: "<< obj->posx << "-" << obj->posy << endl; break;
        case 2: cout <<"Analyze Robot~Position: "<< obj->posx << "-" << obj->posy << endl; break;
        case 3: cout <<"Rescue Robot~Position: "<< obj->posx << "-" << obj->posy << endl; break;
    }
}

