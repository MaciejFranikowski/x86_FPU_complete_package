#include<stdio.h>
#include<string.h>


extern short int read_control_word();
extern void write_control_word(short int x);
extern short int read_status_word();
extern double long calculate();

double number3 = 3;
double number2 = 7;

char binaryNum[65];

// Unions are used in order to properly access the data stored in floats.

union u_double
{
    double  dbl;
    char    data[sizeof(double)];
};

union u_float
{
    float   flt;
    char    data[sizeof(float)];
};

union u_long_double
{
    long double dbl;
    char data[sizeof(long double)];
};

// Returns a string of the given number, converting it to a 
// binary representation.

char *display_binary(long long exp, int length_int){
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

// Each of the "dump" functions work in a similar manner. To extract a portion
// of the IEEE coded number, a bitwise AND is used with an appropriate
// number. The IEEE number is accessed through the union's char array,
// in which the numbers are saved in little endian. 
// 
// EXAMPLE: Trying to extract the exponent portion of a 64 bit float- a double.
// The first byte of char array is d.data[7], which contains one bit- the sign
// and 7 bits of exponent. Using 0x7F - 0111 1111, we extract the exponent part.
// And then we shift the result 4 bits to the left, to make space for the rest
// of the exponent. Then from the next byte, we extract (using 0xF0 - 1111 0000)
// the other part of exponent, which is then shifted 4 bits to the left.
// Finally we connect these parts, using OR.
//
// The rest of the operations is conducted in a very similar manner, always
// taking in account the IEEE representation (f.e. the number of bits of an
// exponent of a 80 bit IEEE number).

static void dump_float(union u_float f)
{
    int exp;
    long mant;

    printf("32-bit float: sign: %d, ", (f.data[3] & 0x80) >> 7);
    exp = ((f.data[3] & 0x7F) << 1) | ((f.data[2] & 0x80) >> 7);
    printf("expt: %6d (unbiased %7d) (binary %-15s), ", exp, exp - 127, display_binary(exp, 7));
    mant = ((((f.data[2] & 0x7F) << 8) | (f.data[1] & 0xFF)) << 8) | (f.data[0] & 0xFF);
    printf("mant: %21ld (0x%017lX) (%s)\n", mant, mant, display_binary(mant, 22));
}


static void dump_double(union u_double d)
{
    int exp;
    long long mant;

    printf("64-bit float: sign: %d, ", (d.data[7] & 0x80) >> 7);
    exp = ((d.data[7] & 0x7F) << 4) | ((d.data[6] & 0xF0) >> 4);
    printf("expt: %6d (unbiased %7d) (binary %-15s), ", exp, exp - 1023, display_binary(exp, 10));

    // The commented out part does not work, sometimes the first 32 bits of the mantissa become ones for no reason.
    // It's the same code, that's under it. No apparent cause found after lots of debugging.
    //
    // mant = ((((d.data[6] & 0x0F) << 8) | (d.data[5] & 0xFF)) << 8) | (d.data[4] & 0xFF);
    // mant = (mant << 32) | (((((((d.data[3] & 0xFF) << 8) | (d.data[2] & 0xFF)) << 8) | (d.data[1] & 0xFF)) << 8) | (d.data[0] & 0xFF));
    mant = d.data[6] & 0x0F;
    mant = (mant << 8);
    mant = mant | (d.data[5] & 0xFF);
    mant = mant << 8;
    mant = mant | (d.data[4] & 0xFF);
    mant = mant << 8;
    mant = mant | (d.data[3] & 0xFF);
    mant = mant << 8;
    mant = mant | (d.data[2] & 0xFF);
    mant = mant << 8;
    mant = mant | (d.data[1] & 0xFF);
    mant = mant << 8;
    mant = mant | (d.data[0] & 0xFF);

    printf("mant: %21lld (0x%017llX) (%s)\n", mant, mant, display_binary(mant, 51));

}

static void dump_double_ext(union u_long_double l)
{
    int exp;
    unsigned long long mant;


    printf("80-bit float: sign: %d, ", (l.data[9] & 0x80) >> 7);
    exp = ((l.data[9] & 0x7F) << 8) | (l.data[8] & 0xFF) ;
    printf("expt: %6d (unbiased %7d) (binary %-15s), ", exp, exp - 16383, display_binary(exp, 14));
    mant = l.data[7] & 0xFF;
    mant = mant << 8;
    mant = mant | (l.data[6] & 0xFF);
    mant = mant << 8;
    mant = mant | (l.data[5] & 0xFF);
    mant = mant << 8;
    mant = mant | (l.data[4] & 0xFF);
    mant = mant << 8;
    mant = mant | (l.data[3] & 0xFF);
    mant = mant << 8;
    mant = mant | (l.data[2] & 0xFF);
    mant = mant << 8;
    mant = mant | (l.data[1] & 0xFF);
    mant = mant << 8;
    mant = mant | (l.data[0] & 0xFF);

    printf("mant: %21llu (0x%017llX) (%s)\n", mant, mant, display_binary(mant, 63));

}

static void print_value(long double v)
{
    union u_double d;
    union u_float  f;
    union u_long_double l;

    f.flt = v;
    d.dbl = v;
    l.dbl = v;

    printf("float/double/double_ext of %Lg\n", v);

    dump_float(f);
    dump_double(d);
    dump_double_ext(l);
}

int main(){
   short int word = 0;

   word = read_control_word();
   printf("\nRead control word: %u, binary: %s\n", word, display_binary(word, 15));
   word = word & 0xF3FF; // 1111 0011 1111 1111
   printf("Control word with zeroed rounding bits: %u, binary: %s\n", word, display_binary(word, 15));
   word = word ^ 0x400; // 0000 0100 0000 0000
   printf("Control word with rounding bits set to round down: %u, binary: %s\n",word, display_binary(word, 15));
   write_control_word(word);
   printf("\nResult of 3/7 division in 3 different precisions with rounding down\n");
   print_value(calculate());

   word = read_control_word();
   printf("\nRead control word: %u, binary: %s\n",word, display_binary(word,15));
   word = word & 0xF3FF; // 1111 0011 1111 1111
   printf("Control word with zeroed rounding bits: %u, binary: %s\n",word, display_binary(word,15));
   word = word ^ 0x800; // 0000 1000 0000 0000
   printf("Control word with rounding bits set to round up: %u, binary: %s\n",word, display_binary(word,15));
   write_control_word(word);
   printf("\nResult of 3/7 division in 3 different precisions with rounding up\n");
   print_value(calculate());

return 0;
}
