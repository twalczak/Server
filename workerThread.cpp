/*-------------------------------------
    Name:    Tomasz Walczak
    Date:    Sept. 15, 2012
 
    File:    workerThread.c
    Desc:    Network Control Thread
 Project:    iRobot Server
 --------------------------------------*/

#include "workerThread.h"

bool run = true;

void *netWorker(void *arg)
{
    std::cout << "Starting: netWorker\n";
    while(run)
    {
        std::cout << "netThread\n";
        sleep(1);
    }
}


