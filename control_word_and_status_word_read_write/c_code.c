#include<stdio.h>

extern short int read_control_word();
extern void write_control_word(short int x);
extern short int read_status_word();
short int number;

int main(){
number = read_control_word();
printf("Control word: %u\n",number);

write_control_word(894);
number = read_control_word();
printf("Control word, after setting it to 894: %u\n",number);

number = read_status_word();
printf("Status word: %u\n", number);

return 0;
}
