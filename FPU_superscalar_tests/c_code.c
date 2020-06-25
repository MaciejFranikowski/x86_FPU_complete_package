#include<stdio.h>

extern void prepare_data();
extern void connected_arithmetic();
extern void not_connected_arithmetic();
extern unsigned long long int rdtsc();
unsigned long long int t1,t2;

int main(){

   for(int i =0; i < 10; i++){
	prepare_data();
	t1 = rdtsc();
    // Change the function for different results.
	not_connected_arithmetic();
	t2 = rdtsc();
	printf("%llu\n", t2-t1);
    }
return 0;
}
