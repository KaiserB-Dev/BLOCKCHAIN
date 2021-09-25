#include <iostream>
#include <string>
#include <WS2tcpip.h>
#pragma comment(lib,"ws2_32.lib")
void leServerSocket();

void main(void){
    leServerSocket();
}

void leServerSocket(){
    //Iniciar servicio
    WSADATA wsDt;
    WORD ver = MAKEWORD(2,2);
    int WsOK = WSAStartup(ver, &wsDt);
    if(WsOK!=0){
        std::cerr<<"No se pudo inicializar el socket :\")"<<std::endl;
        return;
    }

    // Creando el Socket
    SOCKET escucha= socket(AF_INET,SOCK_STREAM,0);
    if(escucha==INVALID_SOCKET){
        std::cerr<<"No se pudo crear el socket :\")"<<std::endl;
        return;
    }

    // Relacionando la ip con el socket
    sockaddr_in linea;
    linea.sin_family = AF_INET; // Configuración tipo TCP/IP
    linea.sin_port = htons(5400); // Convertir los valores al modo del protocolo de la red de trabajo
    linea.sin_addr.S_un.S_addr = INADDR_ANY;

    bind(escucha,(sockaddr*)&linea,sizeof(escucha));

    // Definir el modo listen
    listen(escucha,SOMAXCONN);// Máxima cantidad de conecciones permitidas en el socket escucha

    // Comenzar a esperar por conexiónes externas
    sockaddr_in leCliente;
    int tamannoCliente = sizeof(leCliente);

    SOCKET leSocketClient = accept(escucha,(sockaddr*)&leCliente,&tamannoCliente);
    char leAnfitrion[NI_MAXHOST]; // Nombre remoto del cliente
    char leServicio[NI_MAXSERV]; // El servicio al que se conectó el cliente (el puerto)
    ZeroMemory(leAnfitrion,NI_MAXHOST); // memset(host,0,NI_MAXHOST)
    ZeroMemory(leServicio,NI_MAXSERV);

    if(getnameinfo(
        (sockaddr*)&leCliente,sizeof(leCliente),leAnfitrion,NI_MAXHOST,leServicio,NI_MAXSERV,0 )){
        std::cout<<leAnfitrion<<" Conectado al puerto "<< leServicio<<std::endl;
    }else{
        inet_ntop(AF_INET,&leCliente.sin_addr,leAnfitrion,NI_MAXHOST);
        std::cout<<leAnfitrion<<" conectado al puerto "<<ntohs(leCliente.sin_port)<<std::endl;
    }

    // Cerrar el canal de escucha (listening socket)
    closesocket(escucha);

    // En bucle, acepta y refleja el mensaje al cliente
    char leBuffer[4096];
    while(true){
        ZeroMemory(leBuffer,4096);
        // Esperamos a que el cliente nos envíe los datos
        int ikuRecibido = recv(leSocketClient,leBuffer,4096,0);
        if(ikuRecibido==SOCKET_ERROR){
            std::cerr<<"Error recibiendo, ;\")"<<std::endl;
            break;
        }if(ikuRecibido==0){
            std::cerr<<"Cliente desconectado"<<std::endl;
            break;
        }
        // Reflejar mensaje no cliente y en terminal
        std::cout<<std::string(leBuffer,0,ikuRecibido)<<std::endl;
        send(leSocketClient,leBuffer,ikuRecibido+1,0);
    }

    // Cerrando el canal
    closesocket(leSocketClient);

    // Limpiando el área de trabajo, Bye Winsock uwu
    WSACleanup();
}