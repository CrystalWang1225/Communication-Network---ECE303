//https://stackoverflow.com/questions/4181784/how-to-set-socket-timeout-in-c-when-making-multiple-connections?fbclid=IwAR2WP1hpFDsV2dqzSBpskCnmdVkQATDU_-EeoPeGNh_RbDcY9ljtKG9CBfo
//http://www.matveev.se/cpp/portscaner.htm
//Also received help from Kevin Jiang, Kevin Kerliu
//Crystal Yuecen Wang's TCP port scanner project
#include<errno.h>
#include<string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <time.h>
#include <fcntl.h>
#ifdef WIN32
#include <winsock2.h>
#else
#include <sys/socket.h>
#endif

void portScanner (char *hostName, int startP, int endP){
    struct hostent *host;
    int sendFd,connection;
    struct  sockaddr_in servAddr;
    if ((host = gethostbyname(hostName)) == NULL){
        fprintf(stderr, "Unable to get the host");
        exit(-1);
    }
    servAddr.sin_family =  AF_INET;
    servAddr.sin_addr = *((struct in_addr *)host -> h_addr);

    fprintf(stderr, "Start scanning...\n");
    //start scanning, for every port to be scanned, tries to connect to it, and if successful
    for (int i = startP; i <= endP; i++){
        if ((sendFd = socket(AF_INET, SOCK_STREAM,0)) <0){ //socket creation
            perror("Socket failed \n");
            exit(-1);
        }
        if (fcntl(sendFd, F_SETFL, O_NONBLOCK) == -1){
            fprintf(stderr, "Unable to set the non-blocking attribute\n" );
            exit(-1);
        }

        servAddr.sin_port = htons(i); // converting the host byte to network byte order

        if ((connection = connect(sendFd, (struct sockaddr *)&servAddr, sizeof(servAddr))) < 0){
            fflush(stdout);
        }
        else if (connection == 0){
         ;
        }
        //by setting up the timeout, it is able to speed up
        struct timeval timeout;

        fd_set fdset;
        FD_ZERO(&fdset);
        FD_SET(sendFd, &fdset);
        timeout.tv_sec = 0;
        timeout.tv_usec =50000;//in msec

        if (select(sendFd +1, NULL, &fdset, NULL, &timeout)) {
            int length, error;
            getsockopt(sendFd, SOL_SOCKET, SO_ERROR, (char *) &error, (socklen_t *)&length);
            if (error == 0)
            {
                    fprintf(stdout, "Active Port Number : %d\n", i);
            }
        }
        close(sendFd);
    }
    fprintf(stderr, "End of the scanning \n");
    fflush(stdout);
}



int main(int argc, char ** argv) {
    if (argc != 4 && argc != 2){
        fprintf(stderr, "Please enter the right format : ./scanner hostname [-p 15:25]\n");
        exit(-1);
    }
    char *hostName = 0;
    int startP, endP;
    int count;
    hostName = argv[1];
    if (argc == 4){
        if (strcmp(argv[2], "-p") == 0) {
            count = sscanf(argv[3], "%d:%d", &startP, &endP);
            if (count < 2 || startP < 0 || startP - endP > 0) {
                fprintf(stderr, "Please enter the correct range.\n");
                exit(-1);
            }
        } else {
            fprintf(stderr, "Please enter the right option -p\n");
            exit(-1);
        }
    }
    else {
        fprintf(stderr, "Using the default port scanning range 0:1024...\n");
        startP = 0;
        endP = 1024;
    }
    fprintf(stderr, "Reading to start TCP port scanning : hostname : %s,\n startPort : %d\n endPort : %d\n", hostName, startP, endP);
    portScanner(hostName, startP, endP);
    return 0;
}

