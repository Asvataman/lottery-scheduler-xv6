/* The following code is added by Asvataman Venkatesan, NetID: axv230014
** This is a Mersenne Twister PRNG (MT19937) implementation.
** It generates high-quality random numbers for the lottery scheduler.
** This code was taken from the internet and modified according to our requirements
*/

#define MT_N 624
#define MT_M 397
#define MT_MATRIX_A 0x9908b0df   /* constant vector a */
#define MT_UPPER_MASK 0x80000000 /* most significant w-r bits */
#define MT_LOWER_MASK 0x7fffffff /* least significant r bits */

static unsigned long mt[MT_N]; /* the array for the state vector */
static int mt_index = MT_N + 1; /* mt_index == MT_N+1 means mt[] is not initialized */

/* Initialize the Mersenne Twister with a seed */
void init_mersenne_twister(unsigned long seed) {
    mt[0] = seed & 0xffffffffUL;
    for (mt_index = 1; mt_index < MT_N; mt_index++) {
        mt[mt_index] = (1812433253UL * (mt[mt_index - 1] ^ (mt[mt_index - 1] >> 30)) + mt_index);
        mt[mt_index] &= 0xffffffffUL; /* for >32 bit machines */
    }
}

/* Generate random numbers from the Mersenne Twister */
unsigned long generate_random_mersenne(void) {
    unsigned long y;
    static unsigned long mag01[2] = { 0x0UL, MT_MATRIX_A };
    
    if (mt_index >= MT_N) { /* Generate N words at one time */
        int kk;

        if (mt_index == MT_N + 1)  /* If init_mersenne_twister() has not been called */
            init_mersenne_twister(5489UL); /* a default initial seed is used */

        for (kk = 0; kk < MT_N - MT_M; kk++) {
            y = (mt[kk] & MT_UPPER_MASK) | (mt[kk + 1] & MT_LOWER_MASK);
            mt[kk] = mt[kk + MT_M] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        for (; kk < MT_N - 1; kk++) {
            y = (mt[kk] & MT_UPPER_MASK) | (mt[kk + 1] & MT_LOWER_MASK);
            mt[kk] = mt[kk + (MT_M - MT_N)] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        y = (mt[MT_N - 1] & MT_UPPER_MASK) | (mt[0] & MT_LOWER_MASK);
        mt[MT_N - 1] = mt[MT_M - 1] ^ (y >> 1) ^ mag01[y & 0x1UL];

        mt_index = 0;
    }
  
    y = mt[mt_index++];

    /* Tempering */
    y ^= (y >> 11);
    y ^= (y << 7) & 0x9d2c5680UL;
    y ^= (y << 15) & 0xefc60000UL;
    y ^= (y >> 18);

    return y;
}

/* Generate a random number between 0 and max */
int random_at_most(int max) {
    return generate_random_mersenne() % (max + 1) ;
}
/* End of code added */
