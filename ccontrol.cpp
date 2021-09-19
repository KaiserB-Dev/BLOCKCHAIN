#include "ccontrol.hpp"

cpos::cpos(){ // Constructor de la clase
    cp=new int[2];
    this->setxy(wherex(),wherey());
}
cpos::cpos(const cpos& c){ // Constructor copia
    cp=new int[2];
    this->setxy(c.WhereX(),c.WhereY());
}
cpos::~cpos(){ // Destructor de la clase
    delete cp;
    //std::cout<<"Soy reptar, oiganme rugir: ROOOAAARRRR\n";
}
cpos::cpos(int position_x,int position_y){ // Constructor de la clase, con argumentos
    this->setxy(position_x,position_y);
}
void cpos::setxy(int position_x,int position_y){ // Modifica la posición según el argumento
    this->cp[0]=position_x;
    this->cp[1]=position_y;
}
void cpos::setxy(){
    this->setxy(wherex(),wherey()); // Modifica la posición, según el actual
}
void cpos::putxy() const{ // Posiciona el cursor según la posición guardada
    gotoxy(cp[0],cp[1]);
}
void cpos::putxy(int xplus,int yplus) const{ // Posiciona el cursor con referencia en los valores guardados
    int* ncp;
    ncp=new int[2];
    ncp[0]=this->WhereX()+xplus;
    ncp[1]=this->WhereY()+yplus;
    if (ncp[0] > -1 && ncp[1] > -1) gotoxy(*this);
    delete ncp;
}
const int cpos::WhereX() const{
    return (const int)cp[0];
}
const int cpos::WhereY() const{
    return (const int)cp[1];
}
std::ostream& operator<<(std::ostream& os, cpos b){
    os<<"("
      <<b.WhereX()
      <<","
      <<b.WhereY()
      <<")";
    return os;
}


void gotoxy(const cpos& position){
    gotoxy(position.WhereX(),position.WhereY());
}

void gotoxy(const int& x,const int& y){
    HANDLE hCon; 
    COORD dwPos; 

    dwPos.X = x; 
    dwPos.Y = y; 
    hCon = GetStdHandle(STD_OUTPUT_HANDLE); 
    SetConsoleCursorPosition(hCon,dwPos); 
}

void gotoxy(const int* x,const int* y){ 
    HANDLE hCon; 
    COORD dwPos; 

    dwPos.X = *(x); 
    dwPos.Y = *(y); 
    hCon = GetStdHandle(STD_OUTPUT_HANDLE); 
    SetConsoleCursorPosition(hCon,dwPos); 
}

int wherex(){ 
    CONSOLE_SCREEN_BUFFER_INFO info; 
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&info); 
    return info.dwCursorPosition.X; 
}

int wherey(){ 
    CONSOLE_SCREEN_BUFFER_INFO info;  
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&info); 
    return info.dwCursorPosition.Y; 
}
