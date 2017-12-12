/*
 *  Reads in a custom binary file <.sketch>
 *  These files contain graphic instructions (Recording a sketch & timings)
 *  This program then translates these instructions into calls of a graphics module
 *
 *  OPCODES
 *   00 - DX, change x position
 *   01 - DY, change y position
 *   10 - DT, pause for n * 10 milliseconds
 *   11 - PEN, toggle pen up & pen down
 */

#include "display.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct state {
  int x0, y0, x1, y1, n;
  bool pen;
  display* d;
};

typedef struct state state;

int getOpcode(int n) {return n >> 6;}

int getUnsignedOperand(int n) {
  return (n & (0x3F));
}

int getSignedOperand(int n) {
  return -(n & (0x20)) + (n & (0x1F));
}

state* newState(char* s) {
  state* new = malloc(sizeof(state));
  new->x0 = 0;
  new->y0 = 0;
  new->x1 = 0;
  new->y1 = 0;
  new->n  = 0;
  new->pen = false;
  new->d = newDisplay(s, 200, 200);
  return new;
}

void drawLine(state* c) {
  printf("line(d,%i,%i,%i,%i)\n",c->x0,c->y0,c->x1,c->y1);
  line(c->d, c->x0, c->y0, c->x1, c->y1);
  c->x0=c->x1;
  c->y0=c->y1;
  c->n = 0;
}

void increasex0(state* c, int val) {c->x0 += val;}

void increasex1(state* c, int val) {c->x0 = c->x1; c->x1 += val; c->n++;}

void increasey0(state* c, int val) {c->y0 += val;}

void increasey1(state* c, int val) {c->y0 = c->y1; c->y1 += val;c->n++;}

void penDown(state* c) {
  c->x1 = c->x0;
  c->y1 = c->y0;
}

void execute(state* c, unsigned char b) {
  int code = getOpcode(b);
  if ((code == 0) && (c->pen == false)) {increasex0(c, getSignedOperand(b));}
  else if ((code == 0) && (c->pen == true))  {increasex1(c, getSignedOperand(b));}
  else if ((code == 1) && (c->pen == false))  {increasey0(c, getSignedOperand(b));}
  else if ((code == 1) && (c->pen == true))  {increasey1(c, getSignedOperand(b));}
  else if (code == 2)  {printf("pause(d,%i0)\n", getUnsignedOperand(b)); drawLine(c); pause(c->d, getUnsignedOperand(b));}
  else if ((code == 3) && (c->pen == false)) {penDown(c); c->pen = true;}
  else if ((code == 3) && (c->pen == true))  {drawLine(c); c->pen = false; printf("Pen up\n");}
}

void drawFile(char* s) {
  FILE *in = fopen(s, "rb");
  unsigned char b = fgetc(in);
  state* c = newState(s);
  while (!feof(in)) {
    execute(c, b);
    //printf("%i\n", getOpcode(b));
    if (c->pen == true && c->n == 2) {drawLine(c); printf("Double\n");}
    if (c->n == 2) c->n = 0;
    b = fgetc(in);
  }
  fclose(in);
  key(c->d);
  printf("-------\n");
}

int main() {
  char* s = "line.sketch";
  drawFile(s);
  s = "diag.sketch";
  drawFile(s);
  s = "square.sketch";
  drawFile(s);
  s = "box.sketch";
  drawFile(s);
  s = "oxo.sketch";
  drawFile(s);
  s = "cross.sketch";
  drawFile(s);
  return 0;
}
