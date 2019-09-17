#ifndef DOODLE_H_INCLUDED
#define DOODLE_H_INCLUDED
class Doodle{
public:
    Doodle() {}

    Doodle(int x, int y){
        this->x = x;
        this->y = y;
    }
    setPosition(int x, int y){
        this->x = x;
        this->y = y;
    }
    //static bool isOverlap(Circle*, Circle*);
    int x, y, dx, dy;
};


#endif // DOODLE_H_INCLUDED
