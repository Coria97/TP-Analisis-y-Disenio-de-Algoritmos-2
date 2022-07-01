#ifndef PUNTO_H
#define PUNTO_H

class punto
{
    public:
        punto(){}
        punto(int x, int y) {
            this->x=x;
            this->y=y;
        }
        int coordx()const{
            return x;
        }
        int coordy()const{
            return y;
        }
        bool operator==(const punto & otropunto)const
        {
            if((this->x==otropunto.coordx())&&(this->y==otropunto.coordy()))
                return true;
            else
                return false;
        }
        bool operator!=(const punto & otropunto)const
        {
            if((this->x!=otropunto.coordx())||(this->y!=otropunto.coordy()))
                return true;
            else
                return false;
        }
        punto operator-(const punto & p2)
        {
            this->x-=p2.coordx();
            this->y-=p2.coordy();
        }
        float prod_cruzado(const punto & p2)
        {
            return((x*p2.coordy())-(y*p2.coordx()));
        }

    private:
        int x;
        int y;
};

#endif // PUNTO_H
