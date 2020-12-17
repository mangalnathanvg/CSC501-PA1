#ifndef _MATH_H_
#define _MATH_H_

/* RAND_MAX default value according to official documentation must be at least 32767 */
#define RAND_MAX 32767

/* LAMBDA Value as specified in PA1 */
#define LAMBDA 0.1

/* Math Functions */
double log(double x);
double pow(double x, int y);
double expdev(double lambda);

#endif
