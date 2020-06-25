#include<stdio.h>
#include<string.h>

extern void generate_divide_by_zero();
extern void generate_precision_exception();

extern short int read_control_word();
extern void write_control_word(short int x);
extern short int read_status_word();

short int status_word;
double arbit_number1 = 3;
double arbit_number2 = 7;
char binaryNum[17];

char *display_binary(short int exp, int length_int){
    binaryNum[0] = '\0';
    char zero = '0';
    char one = '1';
    for (int i = length_int; i >=0; i--){

	int a = exp >> i;
	if(a & 1) strncat(binaryNum, &one, 1);
	else strncat(binaryNum, &zero, 1);

    }
     
 
    return binaryNum;
}

int main(){

int wybor = 0;

printf("Choose exception type: 1- Divide by zero, 2- Precision exception.\n");
scanf("%d", &wybor);
switch(wybor){
    case 1:
        status_word = read_status_word();
        printf("\nStatus word: %-5u, (binary: %s)\n", status_word, display_binary(status_word, 15));
        printf("\nDividing by zero\n");        
        generate_divide_by_zero();
        status_word = read_status_word();
        printf("\nStatus word: %u, (binary: %s)\n\n", status_word, display_binary(status_word, 15));
        printf("The first two ones, are showing the top of the FPU stack, which is 6 = 110.\n");        
        printf("The other one, is on the third youngest bit, signifying divide by zero exception.\n");
        break;
    case 2:
        status_word = read_status_word();
        printf("\nStatus word: %-5u, (binary: %s)\n", status_word, display_binary(status_word, 15));
        printf("\nDividing to generate precision exception\n");
	generate_precision_exception();
        status_word = read_status_word();
        printf("Status word: %u, (binary: %s)\n", status_word, display_binary(status_word, 15));
	printf("\nThe first two ones, are showing the top of the FPU stack, which is 6 = 110.\n");
        printf("The other one, is on the sixth youngest bit, signifying precision exception.\n");
	break;
    default:
        return 0;

}
return 0;
}
