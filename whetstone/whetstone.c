/*
 * {module name} Whetstone
 *
 * {module description}
 *
 * Copyright (C) {YEAR} Texas Instruments Incorporated - http://www.ti.com/
 *
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
*/

/*
 * C Converted Whetstone Double Precision Benchmark
 *		Version 1.2	22 March 1998
 *
 *	(c) Copyright 1998 Painter Engineering, Inc.
 *		All Rights Reserved.
 *
 *		Permission is granted to use, duplicate, and
 *		publish this text and program as long as it
 *		includes this entire comment block and limited
 *		rights reference.
 *
 * Converted by Rich Painter, Painter Engineering, Inc. based on the
 * www.netlib.org benchmark/whetstoned version obtained 16 March 1998.
 *
 * A novel approach was used here to keep the look and feel of the
 * FORTRAN version.  Altering the FORTRAN-based array indices,
 * starting at element 1, to start at element 0 for C, would require
 * numerous changes, including decrementing the variable indices by 1.
 * Instead, the array E1[] was declared 1 element larger in C.  This
 * allows the FORTRAN index range to function without any literal or
 * variable indices changes.  The array element E1[0] is simply never
 * used and does not alter the benchmark results.
 *
 * The major FORTRAN comment blocks were retained to minimize
 * differences between versions.  Modules N5 and N12, like in the
 * FORTRAN version, have been eliminated here.
 *
 * An optional command-line argument has been provided [-c] to
 * offer continuous repetition of the entire benchmark.
 * An optional argument for setting an alternate LOOP count is also
 * provided.  Define PRINTOUT to cause the POUT() function to print
 * outputs at various stages.  Final timing measurements should be
 * made with the PRINTOUT undefined.
 *
 * Questions and comments may be directed to the author at
 *			r.painter@ieee.org
 */
/*
C**********************************************************************
C     Benchmark #2 -- Double  Precision Whetstone (A001)
C
C     o	This is a REAL*8 version of
C	the Whetstone benchmark program.
C
C     o	DO-loop semantics are ANSI-66 compatible.
C
C     o	Final measurements are to be made with all
C	WRITE statements and FORMAT sttements removed.
C
C**********************************************************************   
*/
#ifndef MURMULATOR
/* Compiler and system dependent definitions: */

#ifndef TIME
#undef TIMES

//#define TIMES
#define MURMULATOR
#define _u(x) x ## u
#define _REG_(x)
#define TIMER_TIMEHW_OFFSET _u(0x00000000)
#define TIMER_TIMELW_OFFSET _u(0x00000004)
#define TIMER_TIMEHR_OFFSET _u(0x00000008)
#define TIMER_TIMELR_OFFSET _u(0x0000000c)
#define TIMER_ALARM0_OFFSET _u(0x00000010)
#define TIMER_ARMED_OFFSET _u(0x00000020)
#define TIMER_TIMERAWH_OFFSET _u(0x00000024)
#define TIMER_TIMERAWL_OFFSET _u(0x00000028)
#define TIMER_DBGPAUSE_OFFSET _u(0x0000002c)
#define TIMER_PAUSE_OFFSET _u(0x00000030)
#define TIMER_INTR_OFFSET _u(0x00000034)
#define TIMER_INTE_OFFSET _u(0x00000038)
#define TIMER_INTF_OFFSET _u(0x0000003c)
#define TIMER_INTS_OFFSET _u(0x00000040)
typedef volatile unsigned io_rw_32;
typedef const volatile unsigned io_ro_32;
typedef volatile unsigned io_wo_32;
typedef struct {
    _REG_(TIMER_TIMEHW_OFFSET) // TIMER_TIMEHW
    // Write to bits 63:32 of time
    io_wo_32 timehw;

    _REG_(TIMER_TIMELW_OFFSET) // TIMER_TIMELW
    // Write to bits 31:0 of time
    io_wo_32 timelw;

    _REG_(TIMER_TIMEHR_OFFSET) // TIMER_TIMEHR
    // Read from bits 63:32 of time
    io_ro_32 timehr;

    _REG_(TIMER_TIMELR_OFFSET) // TIMER_TIMELR
    // Read from bits 31:0 of time
    io_ro_32 timelr;

    _REG_(TIMER_ALARM0_OFFSET) // TIMER_ALARM0
    // (Description copied from array index 0 register TIMER_ALARM0 applies similarly to other array indexes)
    //
    // Arm alarm 0, and configure the time it will fire
    io_rw_32 alarm[4]; // 4

    _REG_(TIMER_ARMED_OFFSET) // TIMER_ARMED
    // Indicates the armed/disarmed status of each alarm
    // 0x0000000f [3:0]   : ARMED (0)
    io_rw_32 armed;

    _REG_(TIMER_TIMERAWH_OFFSET) // TIMER_TIMERAWH
    // Raw read from bits 63:32 of time (no side effects)
    io_ro_32 timerawh;

    _REG_(TIMER_TIMERAWL_OFFSET) // TIMER_TIMERAWL
    // Raw read from bits 31:0 of time (no side effects)
    io_ro_32 timerawl;

    _REG_(TIMER_DBGPAUSE_OFFSET) // TIMER_DBGPAUSE
    // Set bits high to enable pause when the corresponding debug ports are active
    // 0x00000004 [2]     : DBG1 (1): Pause when processor 1 is in debug mode
    // 0x00000002 [1]     : DBG0 (1): Pause when processor 0 is in debug mode
    io_rw_32 dbgpause;

    _REG_(TIMER_PAUSE_OFFSET) // TIMER_PAUSE
    // Set high to pause the timer
    // 0x00000001 [0]     : PAUSE (0)
    io_rw_32 pause;

    _REG_(TIMER_INTR_OFFSET) // TIMER_INTR
    // Raw Interrupts
    // 0x00000008 [3]     : ALARM_3 (0)
    // 0x00000004 [2]     : ALARM_2 (0)
    // 0x00000002 [1]     : ALARM_1 (0)
    // 0x00000001 [0]     : ALARM_0 (0)
    io_rw_32 intr;

    _REG_(TIMER_INTE_OFFSET) // TIMER_INTE
    // Interrupt Enable
    // 0x00000008 [3]     : ALARM_3 (0)
    // 0x00000004 [2]     : ALARM_2 (0)
    // 0x00000002 [1]     : ALARM_1 (0)
    // 0x00000001 [0]     : ALARM_0 (0)
    io_rw_32 inte;

    _REG_(TIMER_INTF_OFFSET) // TIMER_INTF
    // Interrupt Force
    // 0x00000008 [3]     : ALARM_3 (0)
    // 0x00000004 [2]     : ALARM_2 (0)
    // 0x00000002 [1]     : ALARM_1 (0)
    // 0x00000001 [0]     : ALARM_0 (0)
    io_rw_32 intf;

    _REG_(TIMER_INTS_OFFSET) // TIMER_INTS
    // Interrupt status after masking & forcing
    // 0x00000008 [3]     : ALARM_3 (0)
    // 0x00000004 [2]     : ALARM_2 (0)
    // 0x00000002 [1]     : ALARM_1 (0)
    // 0x00000001 [0]     : ALARM_0 (0)
    io_ro_32 ints;
} timer_hw_t;

#define TIMER_BASE _u(0x40054000)
#define timer_hw ((timer_hw_t *)TIMER_BASE)
static inline unsigned time_us_32(void) {
    return timer_hw->timerawl;
}
#define time(x) (time_us_32() / 1000000)
#include "m-os-api.h"
#include "m-os-api-sdtfn.h"
#include "m-os-api-math.h"

#else

/* standard C library headers required */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

/* the following is optional depending on the timing function used */
#include <time.h>

#endif
#endif

/* map the FORTRAN math functions, etc. to the C versions */
#define DSIN	sin
#define DCOS	cos
#define DATAN	atan
#define DLOG	log
#define DEXP	exp
#define DSQRT	sqrt
#define IF		if

/* function prototypes */
void POUT(long N, long J, long K, double X1, double X2, double X3, double X4);
void PA(double E[]);
void P0(void);
void P3(double X, double Y, double *Z);
#define USAGE	"usage: whetdc [-c] [loops]\n"

/*
	COMMON T,T1,T2,E1(4),J,K,L
*/
double T,T1,T2,E1[5];
int J,K,L;

int main(
#ifndef MURMULATOR
	int argc, char *argv[]
#endif
)
{
#ifdef MURMULATOR
  	cmd_ctx_t* ctx = get_cmd_ctx();
  	int argc = ctx->argc;
  	char **argv = ctx->argv;
	FILE* stderr = ctx->std_err;
#endif
	/* used in the FORTRAN version */
	long I;
	long N1, N2, N3, N4, N6, N7, N8, N9, N10, N11;
	double X1,X2,X3,X4,X,Y,Z;
	long LOOP;
	int II, JJ;

	/* added for this version */
	long loopstart;
	long startsec, finisec;
	float KIPS;
	int continuous;

	loopstart = 1000;		/* see the note about LOOP below */
	continuous = 0;

	II = 1;		/* start at the first arg (temp use of II here) */
	while (II < argc) {
		if (strncmp(argv[II], "-c", 2) == 0 || argv[II][0] == 'c') {
			continuous = 1;
		} else if (atol(argv[II]) > 0) {
			loopstart = atol(argv[II]);
		} else {
			fprintf(stderr, USAGE);
			return(1);
		}
		II++;
	}
	marked_to_exit = false;
LCONT:
	if (marked_to_exit) return 0;
/*
C
C	Start benchmark timing at this point.
C
*/
	startsec = time(0);

/*
C
C	The actual benchmark starts here.
C
*/
	T  = .499975;
	T1 = 0.50025;
	T2 = 2.0;
/*
C
C	With loopcount LOOP=10, one million Whetstone instructions
C	will be executed in EACH MAJOR LOOP..A MAJOR LOOP IS EXECUTED
C	'II' TIMES TO INCREASE WALL-CLOCK TIMING ACCURACY.
C
	LOOP = 1000;
*/
	LOOP = loopstart;
	II   = 1;

	JJ = 1;

IILOOP:
	N1  = 0;
	N2  = 12 * LOOP;
	N3  = 14 * LOOP;
	N4  = 345 * LOOP;
	N6  = 210 * LOOP;
	N7  = 32 * LOOP;
	N8  = 899 * LOOP;
	N9  = 616 * LOOP;
	N10 = 0;
	N11 = 93 * LOOP;
/*
C
C	Module 1: Simple identifiers
C
*/
	X1  =  1.0;
	X2  = -1.0;
	X3  = -1.0;
	X4  = -1.0;

	for (I = 1; I <= N1; I++) {
	    X1 = (X1 + X2 + X3 - X4) * T;
	    X2 = (X1 + X2 - X3 + X4) * T;
	    X3 = (X1 - X2 + X3 + X4) * T;
	    X4 = (-X1+ X2 + X3 + X4) * T;
	}
#ifdef PRINTOUT
	IF (JJ==II)POUT(N1,N1,N1,X1,X2,X3,X4);
#endif

/*
C
C	Module 2: Array elements
C
*/
	E1[1] =  1.0;
	E1[2] = -1.0;
	E1[3] = -1.0;
	E1[4] = -1.0;

	for (I = 1; I <= N2; I++) {
	    E1[1] = ( E1[1] + E1[2] + E1[3] - E1[4]) * T;
	    E1[2] = ( E1[1] + E1[2] - E1[3] + E1[4]) * T;
	    E1[3] = ( E1[1] - E1[2] + E1[3] + E1[4]) * T;
	    E1[4] = (-E1[1] + E1[2] + E1[3] + E1[4]) * T;
	}

#ifdef PRINTOUT
	IF (JJ==II)POUT(N2,N3,N2,E1[1],E1[2],E1[3],E1[4]);
#endif

/*
C
C	Module 3: Array as parameter
C
*/
	for (I = 1; I <= N3; I++)
		PA(E1);

#ifdef PRINTOUT
	IF (JJ==II)POUT(N3,N2,N2,E1[1],E1[2],E1[3],E1[4]);
#endif

/*
C
C	Module 4: Conditional jumps
C
*/
	J = 1;
	for (I = 1; I <= N4; I++) {
		if (J == 1)
			J = 2;
		else
			J = 3;

		if (J > 2)
			J = 0;
		else
			J = 1;

		if (J < 1)
			J = 1;
		else
			J = 0;
	}

#ifdef PRINTOUT
	IF (JJ==II)POUT(N4,J,J,X1,X2,X3,X4);
#endif

/*
C
C	Module 5: Omitted
C 	Module 6: Integer arithmetic
C
*/

	J = 1;
	K = 2;
	L = 3;

	for (I = 1; I <= N6; I++) {
	    J = J * (K-J) * (L-K);
	    K = L * K - (L-J) * K;
	    L = (L-K) * (K+J);
	    E1[L-1] = J + K + L;
	    E1[K-1] = J * K * L;
	}

#ifdef PRINTOUT
	IF (JJ==II)POUT(N6,J,K,E1[1],E1[2],E1[3],E1[4]);
#endif

/*
C
C	Module 7: Trigonometric functions
C
*/
	X = 0.5;
	Y = 0.5;

	for (I = 1; I <= N7; I++) {
		X = T * DATAN(T2*DSIN(X)*DCOS(X)/(DCOS(X+Y)+DCOS(X-Y)-1.0));
		Y = T * DATAN(T2*DSIN(Y)*DCOS(Y)/(DCOS(X+Y)+DCOS(X-Y)-1.0));
	}

#ifdef PRINTOUT
	IF (JJ==II)POUT(N7,J,K,X,X,Y,Y);
#endif

/*
C
C	Module 8: Procedure calls
C
*/
	X = 1.0;
	Y = 1.0;
	Z = 1.0;

	for (I = 1; I <= N8; I++)
		P3(X,Y,&Z);

#ifdef PRINTOUT
	IF (JJ==II)POUT(N8,J,K,X,Y,Z,Z);
#endif

/*
C
C	Module 9: Array references
C
*/
	J = 1;
	K = 2;
	L = 3;
	E1[1] = 1.0;
	E1[2] = 2.0;
	E1[3] = 3.0;

	for (I = 1; I <= N9; I++)
		P0();

#ifdef PRINTOUT
	IF (JJ==II)POUT(N9,J,K,E1[1],E1[2],E1[3],E1[4]);
#endif

/*
C
C	Module 10: Integer arithmetic
C
*/
	J = 2;
	K = 3;

	for (I = 1; I <= N10; I++) {
	    J = J + K;
	    K = J + K;
	    J = K - J;
	    K = K - J - J;
	}

#ifdef PRINTOUT
	IF (JJ==II)POUT(N10,J,K,X1,X2,X3,X4);
#endif

/*
C
C	Module 11: Standard functions
C
*/
	X = 0.75;

	for (I = 1; I <= N11; I++)
		X = DSQRT(DEXP(DLOG(X)/T1));

#ifdef PRINTOUT
	IF (JJ==II)POUT(N11,J,K,X,X,X,X);
#endif

/*
C
C      THIS IS THE END OF THE MAJOR LOOP.
C
*/
	if (++JJ <= II)
		goto IILOOP;

/*
C
C      Stop benchmark timing at this point.
C
*/
	finisec = time(0);

/*
C----------------------------------------------------------------
C      Performance in Whetstone KIP's per second is given by
C
C	(100*LOOP*II)/TIME
C
C      where TIME is in seconds.
C--------------------------------------------------------------------
*/
	printf("\n");
	if (finisec-startsec <= 0) {
		printf("Insufficient duration- Increase the LOOP count\n");
		return(1);
	}

	printf("Loops: %ld, Iterations: %d, Duration: %ld sec.\n",
			LOOP, II, finisec-startsec);

	KIPS = (100.0*LOOP*II)/(float)(finisec-startsec);
	if (KIPS >= 1000.0)
		printf("C Converted Double Precision Whetstones: %.1f MIPS\n", KIPS/1000.0);
	else
		printf("C Converted Double Precision Whetstones: %.1f KIPS\n", KIPS);

	if (continuous)
		goto LCONT;

	return(0);
}

void
PA(double E[])
{
	J = 0;

L10:
	E[1] = ( E[1] + E[2] + E[3] - E[4]) * T;
	E[2] = ( E[1] + E[2] - E[3] + E[4]) * T;
	E[3] = ( E[1] - E[2] + E[3] + E[4]) * T;
	E[4] = (-E[1] + E[2] + E[3] + E[4]) / T2;
	J += 1;

	if (J < 6)
		goto L10;
}

void
P0(void)
{
	E1[J] = E1[K];
	E1[K] = E1[L];
	E1[L] = E1[J];
}

void
P3(double X, double Y, double *Z)
{
	double X1, Y1;

	X1 = X;
	Y1 = Y;
	X1 = T * (X1 + Y1);
	Y1 = T * (X1 + Y1);
	*Z  = (X1 + Y1) / T2;
}

#ifdef PRINTOUT
void
POUT(long N, long J, long K, double X1, double X2, double X3, double X4)
{
	printf("%7ld %7ld %7ld %12.4e %12.4e %12.4e %12.4e\n",
						N, J, K, X1, X2, X3, X4);
}
#endif
