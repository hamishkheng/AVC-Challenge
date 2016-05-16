#include <stdio.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

extern "C" int init(int);
extern "C" int set_motor(int motor,int speed);

int main () {
	init(2);
	while(1) {
		printf("Here\n");
		int n = 0;
		scanf("%d", &n);
		set_motor(1, n);
		set_motor(2, n);
	}
}
