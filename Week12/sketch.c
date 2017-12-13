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
 *
 *  EXTENDED OPCODES
 *   0000 - DX
 *   0001 - DY
 *   0010 - DT
 *   0011 - PEN
 *   0100 - CLEAR
 *   0101 - KEY
 *   0110 - COL
 */

#include "display.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct state {
  int x0, y0, x1, y1;
  int n, code, len, pos; // n = number used when executing, code = current opcode, len = length of extended bytes, pos = position in reading extended bytes
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
  new->pen = false;
  new->n = 0;
  new->code = -1;
  new->len = 0;
  new->pos = 0;
  new->d = newDisplay(s, 200, 200);
  return new;
}

void opcode(state* c, int n) {
  c->code = (n & (0xc0)) >> 6;
}

int unsignedOperand(int n) {
  return (n & (0x3F));
}

int signedOperand(int n) {
  return -(n & (0x20)) + (n & (0x1F));
}

void drawLine(state* c) {
  printf("line(d,%i,%i,%i,%i)\n",c->x0,c->y0,c->x1,c->y1);
  line(c->d, c->x0, c->y0, c->x1, c->y1);
  c->x0=c->x1; c->y0=c->y1;
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
  printf("pause(d,%i)\n", n*10);
  pause(c->d, n*10);
}

void pen(state* c) {
  if (c->pen) {
    c->x0 = c->x1;
    c->y0 = c->y1;
  }
  c->pen = !c->pen;
}

void clearDisplay(state* c) {
  clear(c->d);
  printf("clear(d)\n");
}

void keyWait(state* c) { printf("key(d)\n"); key(c->d);}

void changeColour(state*c) { printf("colour(0x%08x)\n", c->n); colour(c->d, c->n);}

void executeExt(state* c) {
  if (c->code == 0) dx(c, c->n);
  else if (c->code == 1) dy(c, c->n);
  else if (c->code == 2) dt(c, c->n);
  else if (c->code == 6) changeColour(c);
  if (c->code == 1 && c->pen == true) {drawLine(c);}
  c->code = -1; c->len = 0; c->pos = 0; c->n = 0;
}

void extendedOpcode(state* c, int n) {
  c->code = n & (0x0F);
}

void extendedLength(state* c, int n) {
  int a = (n & 0x30) >> 4;
  if (a == 0) c->len = 0;
  else {
    int b = 1;
    for (int k = 1; k < a; k++) b=b*2;
    c->len = b;
  }
  c->pos = 0; c->n = 0;
}

void longSignedOperand(state* c, int n) {
  int neg = -(n & (0x80));
  int pos = n & (0x7F);
  for (int k = 1; k < c->len; k++) {neg = neg << 8; pos = pos << 8;}
  c->n = neg + pos;
  c->pos++;
  if (c->len == 1) {executeExt(c);}
}

void longUnsignedOperand(state*c, int n) {
  for (int k = 1; k < (c->len - c->pos); k++) n = n << 8;
  c->n += n;
  c->pos++;
  if (c->pos == c->len) {executeExt(c);}
}

void extended(state* c, unsigned char b) {
  extendedOpcode(c, b);
  if (c->code == 3) pen(c);
  else if (c->code == 4) {clearDisplay(c);}
  else if (c->code == 5) keyWait(c);
  else {
    extendedLength(c, b);
    if (c->len == 0) executeExt(c);
  }
}

void execute(state* c, unsigned char b) {
  if (c->len == 0) {opcode(c, b);}

  if ((c->len != 0) && (c->pos == 0)) {longSignedOperand(c, b);}
  else if (c->pos < c->len) {longUnsignedOperand(c, b);}
  else {
    if (c->code == 0) dx(c, signedOperand(b));
    else if (c->code == 1) dy(c, signedOperand(b));
    else if (c->code == 2) dt(c, unsignedOperand(b));
    else if (c->code == 3) extended(c, b);

    if ((c->code == 1) && (c->pen == true) && (c->len == 0)) drawLine(c);
}}

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
  end(c->d);
  printf("------\n");
}

void test() {
  char* s[11] = {"data/line.sketch", "data/diag.sketch", "data/square.sketch", "data/box.sketch", "data/oxo.sketch", "data/cross.sketch", "data/clear.sketch", "data/key.sketch", "data/field.sketch", "data/lawn.sketch", "data/pauses.sketch"};
  for (int k = 0; k < 11; k++) {
    drawFile(s[k]);
  }
}

int main(int n, char *args[n]) {
  if (n == 1) {
    test();
  } else if (n == 2) {
    drawFile(args[1]);
  } else {
    printf("Enter ./sketch to run tests of ./sketch \"___\" with a file name to draw a particular file");
  }
  return 0;
}
