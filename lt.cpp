#include <stdio.h>

//#include <pthread.h>
#include <time.h>
#include <string.h>

// sudo gcc -Wall
extern "C" int init_hardware();
extern "C" int init(int d_lev);

extern "C" int take_picture();
extern "C" char get_pixel(int row, int col, int color);
extern "C" void set_pixel(int col, int row, char red,char green,char blue);

extern "C" int open_screen_stream();
extern "C" int close_screen_stream();
extern "C" int update_screen();
//extern "C" void GetLine(int row,int threshold);
extern "C" int display_picture(int delay_sec,int delay_usec);
extern "C" int save_picture(char filename[5]);

extern "C" int set_motor(int motor,int speed);

extern "C" int read_analog(int ch_adc);
extern "C" int Sleep(int sec, int usec);
extern "C" int select_IO(int chan, int direct);
extern "C" int write_digital(int chan,char level);
extern "C" int read_digital(int chan);
extern "C" int set_PWM(int chan, int value);

extern "C" int connect_to_server( char server_addr[15],int port);
extern "C" int send_to_server(char message[24]);
extern "C" int receive_from_server(char message[24]);


int v_left = 0;
int v_right = 0;

int main()
{
    int i;
    init(0);
    // connect camera to the screen
    open_screen_stream();
    // set all didgital outputs to +5V
    for (i = 0; i < 8; i++)
    {
      // set all digital channels as outputs
      select_IO(i,0);
      write_digital(i,1);
    }
    while(1)
    {
       take_picture();      // take camera shot
       int white[32]; //creates the array that we'll use to scan 32 pixels accross the camera
       
       //
       for ( i=0; i<32;i++)
       {   
           white[i] = 0; //sets the "i" into 0 to be used by the command below
           white[i] = ( get_pixel(10+10*i,55,3) > 100);  //converts pixels into 1s and 0s thereby distinguishing blacks as 1 and 0 as white
           
           /*Since the camera sensor isn't detecting perfect white pixels consisting of 0,0,0  and perfect black pixels
           containing 255,255,255 
           we assumed from the code above that everything higher than 100 in digit to be classified as 1 and therefore black and
           anything below 100 as white or light coloured */
           
     	   printf("%d ",white[i]); //prints the values of pixels
           // draw some red line,  two dots above the sensor line
           set_pixel(10+i*10, 53 ,255,0,0);
           set_pixel(10+i*10, 54 ,255,0,0);
           set_pixel(10+i*10, 56 ,255,0,0);
           set_pixel(10+i*10, 57 ,255,0,0);
         }
        printf("\n");
       // displays picture
       update_screen();

       // runs the robot FOREVER!!!!! jk just for 10 secs in a straight line
       for(x=0; x<10, x++){
       Lw = 255; //left wheel 
       Rw = 255; //right wheel
       set_motor(1,Rw);
       set_motor(2,Lw);
}
/*The code above is just for testing, it is not to be taken literally*/
   // terminate hardware
    close_screen_stream();
    set_motor(1,0);
    set_motor(2,0);
  
    return 0;


}
