/*-------------------------------------
       Name:    Tomasz Walczak
       Date:    Sept. 15, 2012
 
       File:    main.c
       Desc:    Main Function
    Project:    iRobot Server
--------------------------------------*/

#include <iostream>
#include <pthread.h>        //POSIX Threads Library

#include "network.h"        //TCP-IP Netowrk Class
#include "serial.h"         //UART Serial Class
#include "workerThread.h"   

using namespace std;

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        cout << "Argument Error\nExiting...\n";
        exit(0);
    }

    pthread_t networkThread;    // Start network worker thread
    pthread_create(&networkThread,
                   NULL, netWorker, (void *)NULL);
    
    pthread_exit(NULL);         // Wait for threads
    return 0;
}
