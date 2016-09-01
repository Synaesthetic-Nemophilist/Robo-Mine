#include <iostream>
#include "wmap.h"
#include "vehicle.h"
#include "vfun.h"
#include "gfun.h"
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;
int vehicle::totalfailures=0;
int vehicle::totalflags=0;
int vehicle::totalload=0;

int main()
{
    cout << "Please insert desired map size" << endl;
    int mapsize;
    cin >> mapsize;
    wmap simmap[mapsize][mapsize];
    fillmap(&simmap[0][0], mapsize);
    nulifycell(&simmap[0][0]);


//====================================================================


bool done=false, cont=false;
int losevar=0;
vector<vehicle*> vec;
int ch=NULL;
int ch2=NULL;
int bulkr=NULL, bulkr2=0;
int infox,i, infoy,infov;
unsigned int iter, iter2, baseload=0;
bool bulk=false;
int rounditer=0;



do{
        cout <<"\n \t ROUND "<<rounditer;

    for(iter=0; iter<vec.size(); iter++){
        vmove(vec[iter], mapsize, &simmap[0][0], vec, iter);
        if (vec[iter]->roundssinceitansweredthefinalsummons==15){
                cout<<"\nVehicle " << iter << " was destroyed. ANIHILATED!"<<endl;
            vec.erase(vec.begin()+iter);
            iter--;
        }
    }
if (bulk==true) bulkr2++;

if (bulk==false)            {
        bulkr2=0;
        cont=false;
        do{
    cout << "\n\nPlease choose an action or 0 to continue the emulation \n\n1.TotalImage 2.Add Vehicle 3.Cell info 4.Vehicle Info \n5.Edits 6. Bulk 9.End Program\n" << endl;
    cin >> ch;
    cout <<endl;

    if (ch==1)  {    //total image
        baseload=simmap[0][0].iridium+simmap[0][0].paladium+simmap[0][0].platinum;
        cellinfo(simmap[0][0]); //BASE INFO
        cout << "\nTotal Failures: " << vehicle::totalfailures <<"\nTotal Flags: " << vehicle::totalflags << "\nTotal Load: " << vehicle::totalload << "\nBase Load: " << baseload << endl;
        for(iter2=0; iter2<vec.size(); iter2++){
            cout << "\t";
            vehicleinfoshort2(vec[iter2]);
        }
    }

    else if (ch==2) {       //add vehicle ====== done

        cout << "What kind of vehicle would you like to add: 1.Search 2.Analysis 3.Rescue, or press 0 to exit" << endl;
        do{ cin >> ch2;} while ((ch2<0)||(ch2>3));
        if (ch2==1)
            vec.push_back(new searchv());
        else if (ch2==2)
            vec.push_back(new analyzev());
        else if (ch2==3)
            vec.push_back(new rescuev());
        else cout << "No Vehicle added" << endl;
    }

    else if (ch==3){         //cell info ======= done
        cout << "Insert x & y coordinates for the cell you want to get info for" << endl;
        cin >> infox;
        cin >> infoy;
        cellinfo(simmap[infox][infoy]);
    }

    else if (ch==4) {       //vehicle info

    cout << "Choose a vehicle from the list below" << endl;
    for(iter2=0; iter2<vec.size(); iter2++)
    {cout << iter2 << ". ";
    vehicleinfoshort(vec[iter2]);}


    cin >> ch2;
    vehicleinfo(vec[ch2]);

    }

    else if (ch==5){                //edits

        cout << "\nEdit: 1.Base 2.Cell of your choice 3.Vehicle" << endl;
        cin >> ch2;
        if (ch2==1){           //base
            celledit(&simmap[0][0]);
        }
        else if (ch2==2){      //cell
            cout << "Please insert the coordinates of the cell you want to edit (on a x-y manner)" << endl;
            do{
            cin >> infox;
            cin >> infoy;
            if (infox>mapsize || infoy>mapsize) {cout << "Please insert valid values, within the limits of the map: " << mapsize << "x" << mapsize << endl;}
            }while (infox>mapsize || infoy>mapsize);
            celledit(&simmap[infox][infoy]);
        }
        else if (ch2==3){
            if(vec.size()!=0){
            cout<<"Please insert the number of vehicle you want to edit"<<endl;
            for(int i=0;i<vec.size();i++){
            cout<<"\n";
            cout<<"\t"<<"("<<i+1<<")";
            vehicleinfo(vec[i]);}
            do{cin>>infov;}while(infov<1 || infov>vec.size());
            vehicleedit(vec[infov-1],mapsize);
            }
            else
                cout<<"You have not created any vehicles!"<<endl;
        }

    }

    else if (ch==6) {
        cout << "You can set an amount of rounds you can bulk-pass without the menu appearing. The informative messages will still appear. If you changed your mind you can press 0. After you make you choice you will have to wait until the set rounds finish"<<endl;
        cin >> bulkr;
        if (bulkr!=0){
            bulk=true;
        }
        else {
            bulk=false;
        }

    }

    else if (ch==0) {
        cont=true;
    }
    else if (ch==9)
        {cont=true; done=true;}


}while (cont==false);
                            }

    rounditer+=1;

    if (bulk==true && bulkr2>=bulkr){
        bulk=false;
        }
    baseload=simmap[0][0].iridium+simmap[0][0].paladium+simmap[0][0].platinum;
    if (baseload>=(mapsize*mapsize*3)){
        cout << "\n\n\n\n\n\n==========================================================\n\n\n\n\n\n\nThe emulation succesfully terminated with a base load of: " << baseload << "\n\n\n\n\n\n\n=========================================================="<<endl;
        done=true;
    }
    if (vec.size()!=0){
    losevar=0;
    for(int i=0;i<vec.size();i++)
    {
        if(vec[i]->damaged==true)
            losevar++;
            }
    if(losevar==vec.size()){
        cout << "\n\n\n\n\n\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n\n\n\n\n\nAll vehicles are damaged, the emulation has failed.\n\n\n\n\n\n\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
        done=true;
    }}
}while (done==false);

return 0;
}

