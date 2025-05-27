#include <stdio.h>
#include <stdlib.h>

#define MAX_TERMS 100
#define COMPARE(x, y) (x < y ? -1 : (x > y ? 1 : 0))

typedef struct {
  int coef;
  int expon;
} polynomial;

// shared memory for storing polynomials
polynomial terms[MAX_TERMS];
int avail = 0;

void polynomial_add(int, int, int, int, int*, int*);
void polynomial_print(int, int);
void attach(int, int);

void main() {

  // starta and finisha defines polynomial a
  int starta, finisha;
  int startb, finishb;
  int startc, finishc;

  starta = avail;
  terms[avail].expon = 1000; terms[avail].coef = 2; 
  avail++;
  terms[avail].expon = 0; terms[avail].coef = 1;
  finisha = avail;
  avail++;

  startb = avail;
  terms[avail].expon = 4; terms[avail].coef = 1;
  avail++;
  terms[avail].expon = 3; terms[avail].coef = 10;
  avail++;
  terms[avail].expon = 2; terms[avail].coef = 3;
  avail++;
  terms[avail].expon = 0; terms[avail].coef = 1;
  finishb = avail;
  avail++;

  polynomial_add(starta, finisha, startb, finishb, &startc, &finishc);

  polynomial_print(starta, finisha);
  polynomial_print(startb, finishb);
  polynomial_print(startc, finishc);
}

void polynomial_add(int starta, int finisha, int startb, int finishb, int *startd, int *finishd) {

  /* complete this function */

}

void attach(int coefficient, int exponent) {
  /* add a new term to the polynomial */
  if(avail >= MAX_TERMS) {
    fprintf(stderr, "too many terms in the polynomial"); exit(1);
  }
  terms[avail].coef = coefficient;
  terms[avail++].expon = exponent;
}

void polynomial_print(int starta, int finisha) {
  int i;
  for(i = starta; i <= finisha; i++) {
    if(i == starta) printf("%dx^%d", terms[i].coef, terms[i].expon);
    else printf(" + %dx^%d", terms[i].coef, terms[i].expon);
  }
  printf("\n");
}






