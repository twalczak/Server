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
#include <string>

class Serial_Controller {
public:
    int fd;
    char serialport[256];
    int baudrate;
    char buf[256];
    bool _open;
    int rc,n;
    std::string error_msg;
    
    Serial_Controller(char* port, int baud);
    char isOpen();
    char write_byte(uint8_t data);
    char write_string(const char* str);
    uint8_t read_byte();
    uint8_t get_error();
private:
    int serial_init();
};

#endif /* defined(____serial__) */
