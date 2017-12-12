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
  int x0, y0, x1, y1;
  int n;
  bool pen;
  display* d;
};

typedef struct state state;

state* newState(char* s) {
  state* new = malloc(sizeof(state));
  new->x0 = 0;
  new->y0 = 0;
  new->x1 = 0;
  new->y1 = 0;
  new->n = 0;
  new->pen = false;
  new->d = newDisplay(s, 200, 200);
  return new;
}

int opcode(int n) {
  return n >> 6;
}

int unsignedOperand(int n) {
  return (n & (0x3F));
}

int signedOperand(int n) {
  return -(n & (0x20)) + (n & (0x1F));
}

void dx(state* c, int n) {
  if (c->pen == true) c->x0=c->x1;
  c->x1+=n;
  if (!c->pen) c->x0=c->x1;
}

void dy(state* c, int n) {
  if (c->pen) c->y0=c->y1;
  c->y1+=n;
  if (!c->pen) c->y0=c->y1;
}

void dt(state* c, int n) {
  printf("pause(d,%i0)\n", n);
  pause(c->d, n*10);
}

void pen(state* c) {
  if (c->pen) {
    c->x0 = c->x1;
    c->y0 = c->y1;
  }
  c->pen = !c->pen;
}

void drawLine(state* c) {
  c->n++;
  printf("-->{%i} line(d,%i,%i,%i,%i)\n",c->n,c->x0,c->y0,c->x1,c->y1);
  line(c->d, c->x0, c->y0, c->x1, c->y1);
  c->x0=c->x1; c->y0=c->y1;
}

void execute(state* c, unsigned char b) {
  int code = opcode(b);
  if (code == 0) {dx(c, signedOperand(b));}
  else if (code == 1) {dy(c, signedOperand(b));}
  else if (code == 2) {dt(c, unsignedOperand(b));}
  else if (code == 3) {pen(c);}
  if ((code == 1) && (c->pen == true)) drawLine(c);
}

void drawFile(char* s) {
  printf("<%s>\n", s);
  FILE *in = fopen(s, "rb");
  unsigned char b = fgetc(in);
  state* c = newState(s);
  while (!feof(in)) {
    execute(c, b);
    b = fgetc(in);
  }
  fclose(in);
  key(c->d);
  printf("------\n");
}

void test() {
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
}

int main() {
  test();
  return 0;
}
