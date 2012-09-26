//
//  serial.cpp
//  
//
//  Created by Tomasz Walczak on 9/24/12.
//
//
#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <getopt.h>
#include "serial.h"

Serial_Controller::Serial_Controller(char* port, int baud)
{
    baudrate = baud;
    strcpy(serialport, port);
    _open = false;
}

int Serial_Controller::serial_init()
{
    struct termios toptions;
    int fd;
    
    fd = open(serialport, O_RDWR | O_NOCTTY | O_NDELAY);      // --- OPEN PORT
    if(fd == -1)
    {
        error_msg = "Couldn't open port";
        return -1;
    }
    
    if (tcgetattr(fd, &toptions) < 0)                         // --- GET CURRENT tOPTIONS
    {
        error_msg = "Couldn't get terminal options";
        return -1;
    }
    
    speed_t brate = baudrate;                                   // --- APPLY NEW SETTINGS
    cfsetispeed(&toptions, brate);
    cfsetospeed(&toptions, brate);
    
    toptions.c_cflag &= ~PARENB;    // 8b|NoP|1sb
    toptions.c_cflag &= ~CSTOPB;
    toptions.c_cflag &= ~CSIZE;
    toptions.c_cflag |= CS8;
    toptions.c_cflag &= ~CRTSCTS;
    toptions.c_cflag |= CREAD | CLOCAL; // turn on READ & ignore ctrl lines
    toptions.c_iflag &= ~(IXON | IXOFF | IXANY); // turn off s/w flow ctrl
    toptions.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // make raw
    toptions.c_oflag &= ~OPOST; // make raw
    toptions.c_cc[VMIN]  = 0;
    toptions.c_cc[VTIME] = 20;
    
    if(tcsetattr(fd, TCSANOW, &toptions) < 0) {                 // --- SET NEW tOPTIONS
        error_msg = "Couldn't set terminal options";
        return -1;
    }
    
    _open = true;
    return fd;                                                  // --- RETURN FILE DESCRIPTOR :)
}

char Serial_Controller::write_byte(uint8_t data) {
    if(write(fd,&data,1)!=1)
        return -1;
    return 0;
}

char Serial_Controller::write_string(const char* str) {
    int length = strlen(str);
    if(write(fd, str, length)!=length)
        return -1;
    return 0;
}
