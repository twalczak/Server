//
//  serial.h
//  
//
//  Created by Tomasz Walczak on 9/24/12.
//  POSIX SERIAL PORT COMMUNICATION
//

#ifndef ____serial__
#define ____serial__

#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <getopt.h>

class Serial_Controller {
public:
    int fd;
    char serialport[256];
    int baudrate; //iRobot Default
    char buf[256];
    int rc,n;
    
    void Serial(char* port, int baud);
    
    char open();
    char isOpen();
    
    char write_byte(uint8_t data);
    char write_string(char* str);
    uint8_t read_byte();
};

#endif /* defined(____serial__) */
