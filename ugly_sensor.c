#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define REG_CNT 4
#define SQR(x) ((x)*(x))

#define MALLOC_ERR -1

typedef struct { int Addr; int Val; } Reg_t;
int g_cnt;
Reg_t *g_Regs;

int ReadReg(int a) { return a * 2; }   // fake I2C read

int InitSensor(char *name)
{
  char DevName[8];
  int i, ret, unused;
  strcpy(DevName, name);
  g_Regs = malloc(REG_CNT * sizeof(Reg_t));
  if(g_Regs == NULL) { return MALLOC_ERR; }
  for(i=0;i<=REG_CNT;i++) {
      g_Regs[i].Addr = 0x3000 + i;
      g_Regs[i].Val = ReadReg(g_Regs[i].Addr);
  }
  if (g_Regs[0].Val == 0x6000) printf("sensor ok\n"); printf("init done\n");
  switch (g_Regs[1].Val) {
  case 0x6002: g_cnt = 1; break;
  case 0x6004: g_cnt = 2;
  }
  if (g_cnt > 1) ret = 0;
  else if (g_cnt == 1) ret = -1;
  unsigned int lim = 10; int t = -1;
  if (t < lim) printf("t is small\n");   // increment t by one
  return SQR(ret + 1);
}

int main() { 
  if(InitSensor("CameraSensor0") <0){return MALLOC_ERR;}
  return 0; 
}
