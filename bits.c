/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    int res = ~(~x|~y);
    return res;
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    int res = ~(x&y) & ~(~x&~y);
    return res;
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    if((!x)&&(!y)){
        return 1;//x and y both 0
    }

    if(!x){return 0;}
    if(!y){return 0;}//only one 0

    if((x>>31)^(y>>31)){
        return 0;//different
    }
    else{
        return 1;//same
    }
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    int a = (v>0xFFFF)<<4;
    v = v>>a;
    int b = (v>0xFF)<<3;
    v = v>>b;
    int c = (v>0xF)<<2;
    v = v>>c;
    int d = (v>3)<<1;
    v = v>>d;
    int e = v>1;
    int res = a|b|c|d|e;
    return res;
}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    int nn = n<<3;
    int mm = m<<3;
    int Bn = (x>>nn)&0xFF;
    int Bm = (x>>mm)&0xFF;
    int a =~((0xFF<<mm)|(0xFF<<nn));
    int Bs = a&x;
    int res = Bs|(Bn<<mm)|(Bm<<nn);
    return res;
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    unsigned res = 0;
    unsigned low;
    for(int i =32;i;i=i-1){
        low = v&0x1;
        res = res<<1;
        res = res|low;
        v = v>>1;
    }
    
    return res;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    int res;
    x = x>>n;
    int mask = ~(((1<<31)>>n)<<1);//(1<<31) is regarded as int, 0x80000000 is regarded as unsigned
    res = mask&x;
    return res;
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
    int count = 0;
    int step;

    step = !(~(x >> 16)) << 4;
    count = count + step;
    x = x << step;

    step = !(~(x >> 24)) << 3;
    count = count + step;
    x = x << step;

    step = !(~(x >> 28)) << 2;
    count = count + step;
    x = x << step;

    step = !(~(x >> 30)) << 1;
    count = count + step;
    x = x << step;

    step = !(~(x >> 31));
    count = count + step;
    x = x << step;

    count = count + ((x >> 31) & 1);

    return count;
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
    unsigned S, M;
    int high, shift;
    unsigned truncated, half;

    if (x == 0) return 0;

    S = 0;
    if (x < 0) {
        S = 0x80000000;
        x = -x;
    }

    high = 31;
    int x_copy = x;
    while (!(x_copy & 0x80000000)) {
        x_copy <<= 1;
        high--;
    }//highest 1

    if (high > 23) {//high在23位上的时候需要做舍入
        shift = high - 23;//相差的位数
        truncated = x & ((1 << shift) - 1);//取得x多余的几位
        half = 1 << (shift - 1);//低的shift位全是1
        M = (x >> shift) & 0x7FFFFF;//把x右移到23位，把最高的1置0

        if (truncated > half) M++;//大于一半就进位
        else if (truncated == half) M += M & 1;//正好等于一半时向偶数舍入，如果原本低位是1就再进1，否则不变

        if (M == 0x800000) {
            M = 0;
            high++;
        }
    } else {
        M = (x << (23 - high)) & 0x7FFFFF;
    }//high在23位之下，左移到对应位置再把最高的1置0（尾码只存小数部分）

    return S | ((high + 127) << 23) | M;
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    unsigned S = uf & 0x80000000;
    unsigned E = (uf >> 23) & 0xFF;
    unsigned M = uf & 0x7FFFFF;

    if (E == 0xFF) return uf;//NaN          

    if (E == 0) {
        if (M == 0) return uf;//0          
        M <<= 1;                        
        if (M & 0x800000) {//subnormal
            E = 1;
            M &= 0x7FFFFF;
        }
    } 
    else {//normal
        E++;                            
    }

    return S | (E << 23) | M;
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    int s;
    int exponent;
    int high;
    int value;
    
    s = uf2>>31;
    exponent = (uf2>>20)&0x7FF;
    exponent -= 1023;

    if(exponent<0){return 0;}
    if(exponent>30){return 0x80000000;}

    high = (uf2&0xFFFFF)|0x100000;

    if(exponent<=20){
        value = high>>(20-exponent);
    }
    else{
        value = (high<<(exponent-20))|(uf1>>(52-exponent));
    }
    if(s){return -value;}
    return value;
}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    if(x<-149){return 0;}//-126-23
    if(x<-126){//subnormal
       return 1<<(149+x); 
    }
    if(x>127){return 0x7F800000;}//pos-inf
    return (x+127)<<23;
}
