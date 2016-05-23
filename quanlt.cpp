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
    
    double current_error = 0; //replace for line center
    double previous_error = 0;
    
    int ln_start;
    int ln_fin;
    
    double kp = 1.140; //maximum proportional gain in speed is 32 and -32 (a 64 speed difference between the two wheels)
    double kd = 0.015; //maximum resist is 32 the other way when it turns too fast; 
    
    double proportional_signal;
    double derivative_signal;
    int total_signal;
    
    // fields for IR sensor loop
    int sum;
    int left_IR;
    int right_IR;
    int forward_IR;
    bool mazeMode = false;
int turnLeft() {


	set_motor(2,0);
	set_motor(1,60);
	Sleep(0,350000);
	
    return 0; //for the maze
    
}

int turnRight() {
	
	set_motor(2,60);
	set_motor(1,0);
	Sleep(0,350000);
	
    return 0; 
    
}

    
int main()
{
    int i;
    init(0);
    open_screen_stream(); // connect camera to the screen
    for (i = 0; i < 8; i++) // set all didgital outputs to +5V
    {
      // set all digital channels as outputs
      select_IO(i,0);
      write_digital(i,1);
    }
    
    	//connect_to_server("130.195.6.196", 1024); //IP ADDRESS NEEDS TO BE CHANGED
        //sends a message to the connected server
        //send_to_server("Please");
        //receives message from the connected server
        //char message[24];
        
        //receive_from_server(message); //this may be buggy!
        //printf("%s", message);
    
    while (1) { //run forever
        
        // left_IR = read_analog(0);
        // right_IR = read_analog(1);
        //forward_IR = read_analog (2); 
        // while (left_IR < target value AND right_IR > target value) {}
        //havent plugged in the IR sensors yet so that is just there for future reference
        
        while (1) { //where the IR conditions comes in later 
            take_picture();
        
        
            int white[64]; //improved accuracy to every single pixel;
            sum = 0;
            for (i = 0; i <64; i++) {
                int w = get_pixel(i*5,130,3); // 1 to 320
                if (w > 120) {w = 1;} //same thing as jules part but more easy to understand
                else {w = 0;}
                
                white[i] = w;
                
                set_pixel(i, 54 ,255,0,0); //creates a redline to show where camera is taking pixels from
		printf("%d ", white[i]);
		sum = sum + white[i];

		if (sum > 54) {
		 mazeMode = true;
		}
            }
            
            update_screen();
            
            for(i = 1; i <64; i++ ) { //separate for loops despite same loop conditions
            //this won't work if it is inside the previous loop because 
            //the array wouldn't have finalized then
            
                if  ((white[i-1] == 0) && (white[i] == 1)) {
                    ln_start = (i-32); //to offset the pixels to -32 to 32
                    //this is very crucial because -(ve) on left side and +(ve) on right side
                    //is needed to calculate the motor speed for left and right using the PID
                    
                }
                
                if  ((white[i] == 1) && (white[i+1] == 0)) {
                    ln_fin = (i-32);
                }
 
            }
            if ((ln_fin - ln_start) < 20) { //if the width of the whiteness is small enougn
		current_error = (ln_start + ln_fin)/2; //center of the line 
		}

	    else {current_error  =  0;}           //center of the line is now outside the for loop so that it is only set ONCE 
            
            printf("current_error & previous error: %f %f", current_error, previous_error);
            printf (" sum : %d \n", sum);
            proportional_signal = current_error*kp;
	    derivative_signal = (current_error - previous_error)/0.01*kd;
            //printf("proportional_signal: %f   ", proportional_signal);
            Sleep(0,10000); // 1/100th of a second
            if (sum != 0) {
            previous_error = current_error;
}	
	
            //printf("derivative_signal: %f   ", derivative_signal);
            //printf("\n"); //print format will be "current error: x    proportional signal: x   derivative signal: x   "
            
            total_signal = (int) (proportional_signal + derivative_signal); //0.5 is to counter the rounding error from doubles
            
		

            if (sum != 0) {//linewithin picture
		set_motor(1, -50 - total_signal); //the left motor will increase when the line is to the right ( to turn right)
                set_motor(2, -50 + total_signal); //the right motor will decrease if the line is to the right (to help turn right)		 
            }

            
            else if (sum == 0 && mazeMode == true && previous_error < 0){	
         
		//reverse the PI so that it doesnt keep going
                //will be refined later
	
		turnLeft(); //ninty degrees
            }


            else if (sum == 0 && mazeMode == true && previous_error > 0){	
         
		//reverse the PI so that it doesnt keep going
                //will be refined later
	
		turnRight(); //ninty degrees
            }


	    //else if (sum == 0 && mazeMode == true && previous_error > 0) {
		//turnRight(); //ninty degrees
	    //}

	    else if (sum == 0 && mazeMode == false){
            set_motor(1,60);
	    set_motor(2,60);
 
	}
        }
}        
    
    //terminate hardware;
    //close_screen_stream();
    //set_motor(1,0);
    //set_motor(2,0);
    return 0;
}

    
    
    
    

