#include <stdio.h>
#include <time.h>
#include <string.h>

// sudo gcc -Wall
extern "C" int init_hardware();
extern "C" int init(int d_lev);

// Starting line of methods for camera
extern "C" int take_picture();
extern "C" char get_pixel(int row, int col, int color);
extern "C" void set_pixel(int col, int row, char red,char green,char blue);

extern "C" int open_screen_stream();
extern "C" int close_screen_stream();
extern "C" int update_screen();
//extern "C" void GetLine(int row,int threshold);
extern "C" int display_picture(int delay_sec,int delay_usec);
extern "C" int save_picture(char filename[5]);

//End of methods for camera

//Start of methods for motor
extern "C" int set_motor(int motor,int speed);

extern "C" int read_analog(int ch_adc);
extern "C" int Sleep(int sec, int usec);
extern "C" int select_IO(int chan, int direct);
extern "C" int write_digital(int chan,char level);
extern "C" int read_digital(int chan);
extern "C" int set_PWM(int chan, int value);

//End of methods for motor

//Start of network methods 
extern "C" int connect_to_server( char server_addr[15],int port);
extern "C" int send_to_server(char message[24]);
extern "C" int receive_from_server(char message[24]);
//End of network methods
    
    //fields for PID loop
    
    int current_error = 0;
    int previous_error = 0;
    
    int kp = 0.5;
    int kd = 0.1;
    
    int proportional_signal;
    int derivative_signal;
    
    // fields for IR sensor loop
    
    int left_IR = 99999;
    int right_IR = 99999;
    int forward_IR;
    
    
    
    
