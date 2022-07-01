#ifndef SEGMENTO_H
#define SEGMENTO_H
#include "punto.h"

class segmento
{
    public:
        segmento(const punto p1,const punto p2) {
            this->p1=p1;
            this->p2=p2;
        }

        const punto & devolover_p1()const{
            return p1;
        }

        const punto & devolover_p2()const{
            return p2;
        }

        bool operator== (const segmento & otrosegmento)const
        {
            if((p1==otrosegmento.p1) && (p2==otrosegmento.p2))
                return true;
            else
                return false;
        }

    protected:

    private:
        punto p1, p2 ;
};

#endif // SEGMENTO_H
