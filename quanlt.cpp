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
    
    double current_error = -10000; //replace for line center
    double previous_error = 0;
    
    int ln_start;
    int ln_fin;
    
    double kp = 0.25; //maximum proportional gain in speed is 40
    double kd = 0.01; //maximum resist is 32 the other way when it turns too fast; 
    
    double proportional_signal;
    double derivative_signal;
    int total_signal;
    
    // fields for IR sensor loop
    
    int left_IR = 99999;
    int right_IR = 99999;
    int forward_IR;
    
int main()
{
    int i;
    init(1);
    open_screen_stream(); // connect camera to the screen
    for (i = 0; i < 8; i++) // set all didgital outputs to +5V
    {
      // set all digital channels as outputs
      select_IO(i,0);
      write_digital(i,1);
    }
    
    while (1) { //run forever
        take_picture();
        // left_IR = read_analog(0);
        // right_IR = read_analog(1);
        //forward_IR = read_analog (2); 
        // while (left_IR < target value AND right_IR > target value) {}
        //havent plugged in the IR sensors yet so that is just there for future reference
        
        while (1) { //where the IR conditions comes in later 
        
        connect_to_server("192.168.1.2", 1024);
        //sends a message to the connected server
        send_to_server("please");
        //receives message from the connected server
        char message[24];
        
        receive_from_server(message); //this may be buggy!
        printf("%s", message);
        
            int white[320]; //improved accuracy to every single pixel;
            
            for (i = 0; i <320; i++) {
                int w = get_pixel(i+1,55,3); // 1 to 320
                if (w > 127) {w = 1;}; //same thing as jules part but more easy to understand
                else {w = 0;};
                
                white[i] = w;
                
                set_pixel(i+1, 54 ,255,0,0); //creates a redline to show where camera is taking pixels from
            }
            
            update_screen();
            
            for(i = 0; i <320; i++ ) { //separate for loops despite same loop conditions
            //this won't work if it is inside the previous loop because 
            //the array wouldn't have finalized then
            
                if ( //refined to have better chance of dealing with outliers
                    ((white[i-1] == 0) && (white[i] == 1) && (white[i+1] == 1)) || //start of white line 
                    ((white[0] == 1) && (white[1] == 1)) //execption for when line starts at the very edge of the screen
                ) {
                    ln_start = (i-160); //to offset the pixels to -160 to 160
                    //this is very crucial because -(ve) on left side and +(ve) on right side
                    //is needed to calculate the motor speed for left and right using the PID
                    
                }
                
                if ( //refined to have better chance of dealing with outliers
                    ((white[i-1] == 1) && (white[i] == 1) && (white[i+1] == 0)) || //end of white line 
                    ((white[318] == 1) && (white[319] == 0)) //execption for when line ends at the very edge of the screen
                ) {
                    ln_fin = (i-160+1);//so that 160 becomes exclusive instead of inclusive
                }
 
            }
            current_error = (ln_start + ln_fin)/2; //center of the line
            //center of the line is now outside the for loop so that it is only set ONCE 
            
            printf("current_error: %d   ", current_error);
            proportional_signal = current_error*kp;
            printf("proportional_signal: %d   ", proportional_signal);
            Sleep(0,100000); // 1/10th of a second
            
            derivative_signal = ((current_error-previous_error)/0.1)*kd;
            previous_error = current_error;
            printf("derivative_signal: %d   ", derivative_signal);
            printf("\n"); //print format will be "current error: x    proportional signal: x   derivative signal: x   "
            
            total_signal = (int) (current_signal - derivative_signal + 0.5); //0.5 is to counter the rounding error from doubles
            
            if (current_error > -160 && current_error < 160) {//line within picture
            
                set_motor(1,50+total_signal); //the left motor will increase when the line is to the right ( to turn right)
                set_motor(2,50-total_signal); //the right motor will decrease if the line is to the right (to help turn right)
            }
            
            else {
                set_motor(1,-40);
                set_motor(2,-40);
                //reverse the PI so that it doesnt keep going
                //will be refined later
            }
        }
        
    }
    
    return 0;
}

int turnLeft() {
    return 0; //for the maze
    
}

int turnRight() {
    return 0; //for the maze
    
}
    
    
    
    
