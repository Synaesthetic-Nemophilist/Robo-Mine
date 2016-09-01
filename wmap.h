#ifndef WMAP_H
#define WMAP_H


class wmap
{
    public:
        wmap();
        virtual ~wmap();
        void printstuff();
        bool flag;
        float danger;
        int paladium;
        int iridium;
        int platinum;
        int x;
        int y;
        bool taken;
    protected:
    private:
        //int x;
        //int y;


    friend void fillmap (wmap *simulmap, int mapsize);
    friend void printcell (wmap cell);
    friend void nulifycell (wmap *cell);
    friend void celledit (wmap* cell);
//    friend void vsact (searchv *obj, wmap *cell);

};







#endif // WMAP_H
