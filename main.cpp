//-------------------
// MAIN.C iRobot

#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include "network.h"

using namespace std;

class Test {
public:
    void outp();
};

void Test::outp() {
    cout << "outp Test\n";
}


bool run = true;
int nShared = 2;

void *network(void *arg)
{
    while(run)
    {
        cout << "From the thread" << nShared << "\n";
        usleep(2*1000000);
        nShared++;
    }
}

void *n2(void *arg)
{
    for(;;)
    {
        cout << "From thread [two]" << nShared << "\n";
        nShared--;
        usleep(2*300000);
    }
}

int main(void)
{
    Network botLink;
    botLink.outp();
    Test testClass;
    testClass.outp();
    pthread_t networkThread, t2;
    cout << " - Robot Control: v1.0.0\n\n";
    pthread_create(&networkThread, NULL, network, (void *)NULL);
    pthread_create(&t2, NULL, n2, (void *)NULL);
    pthread_exit(NULL);
    return 0;
}
