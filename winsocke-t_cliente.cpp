#include <iostream>
#include <string>
#include <WS2tcpip.h>
#pragma comment(lib,"ws2_32.lib")

void leClientSocket();

void main (void){
    leClientSocket();
}

void leClientSocket(){
    std::string leIP = "192.168.100.2"; // IP del servidor
    int lePort = 54000; // El puerto de acceso del Servidor

    // Iniciamos servicio de WinSock
    WSAData lesDatos;
    WORD ver = MAKEWORD(2,2);
    int wsResult = WSAStartup(ver,&lesDatos);
    if (wsResult != 0){
        std::cerr<<"Imposible iniciar Winsock ("<<wsResult<<")\n";
        return;
    }
    // Creando Socket
    SOCKET leZocalo = socket(AF_INET,SOCK_STREAM,0);
    if(leZocalo==INVALID_SOCKET){
        std::cerr<<"No se pudo crear el Socket ("<<WSAGetLastError()<<")\n";
        WSACleanup();
        return;
    }
    // Estructura tipo hint
    sockaddr_in linea;
    linea.sin_family = AF_INET;
    linea.sin_port = htons(lePort);
    inet_pton(AF_INET,leIP.c_str(),&linea.sin_addr);

    // Crear conexión a servidor
    int conResult = connect(leZocalo,(sockaddr*)&linea,sizeof(linea));
    if (conResult==SOCKET_ERROR){
        std::cerr<<"Imposible conectar al servidor ("<<WSAGetLastError()<<")\n";
        closesocket(leZocalo);
        WSACleanup();
        return;
    }

    // Ciclo para recepción y envío de datos
    char leBuffer[4096];
    std::string EntradadUsuario;
    do{
        // Pedir dato a enviar a Servidor
        std::cout<<"> ";
        std::getline(std::cin,EntradadUsuario);
        // Enviar el dato
        if(EntradadUsuario.size()>0){
            int leStadodNvio =
                send(leZocalo,EntradadUsuario.c_str(),EntradadUsuario.size()+1,0);
            if(leStadodNvio!=SOCKET_ERROR){
                // Espera a la respuesta del Servidor
                ZeroMemory(leBuffer,4096);
                int ikuRecibido=recv(leZocalo,leBuffer,4096,0);
                if(ikuRecibido>0){
                    //Refleja respuesta en consola
                    std::cout<<"SERVIDOR> "<<std::string(leBuffer,0,ikuRecibido);
                }
            }
        }
    }while(EntradadUsuario.size()>0);

    // Se cierran el canal, la línea y el zocalo
    closesocket(leZocalo);
    WSACleanup();
}// El chat xd