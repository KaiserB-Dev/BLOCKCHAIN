#ifndef lngCCONTROL_H
#define lngCCONTROL_H
#include <windows.h>
#include <iostream>

// Class by Lang Lovdog Brandon Arthemis Nereo Inu Oókami Marquez Salazar
struct cpos {
    private:
        int* cp;
    public:
        cpos();
        cpos(int position_x,int position_y);
        cpos(const cpos& c);
        ~cpos();
        void setxy();
        void setxy(int position_x,int position_y);
        void putxy() const;
        void putxy(int xplus,int yplus) const;
        const int WhereX() const;
        const int WhereY() const;
        friend std::ostream& operator<<(std::ostream& os, cpos b);
};

int wherey();
int wherex();
void gotoxy(const cpos& position);
void gotoxy(const int& position_x,const int& position_y);
void gotoxy(const int* position_x,const int* position_y);

#endif
