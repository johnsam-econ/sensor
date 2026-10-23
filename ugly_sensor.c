#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define REG_CNT 4
#define SQR(x) ((x)*(x))

#define REG_BASE_ADDR 0x3000
#define SENSOR_OK_VAL 0x6000
#define REG_VAL_1 0x6002
#define REG_VAL_2 0x6004

#define MALLOC_ERR -1

typedef struct { int Addr; int Val; } Reg_t;
int g_cnt;
Reg_t *g_Regs;

int ReadReg(int a) { return a * 2; }   // fake I2C read

// Initialize the sensor by reading its registers and evaluating the returned values.
int InitSensor(char *name)
{
  char DevName[32];
  int i, ret = -1;
  snprintf(DevName, sizeof(DevName), "%s", name);
  g_Regs = malloc(REG_CNT * sizeof(Reg_t));
  if(g_Regs == NULL) { return MALLOC_ERR; }

  // Read the sensor's consecutive registers starting from the base address.
  for(i=0;i<REG_CNT;i++) {
      g_Regs[i].Addr = REG_BASE_ADDR + i;
      g_Regs[i].Val = ReadReg(g_Regs[i].Addr);
  }

  // Verify the sensor's expected identification value before reporting initialization success.
  if (g_Regs[0].Val == SENSOR_OK_VAL) { 
    printf("sensor ok\n"); 
    printf("init done\n");
  }

  // Interpret the second register's value to determine the sensor's detected state.
  switch (g_Regs[1].Val) {
  case REG_VAL_1: 
    g_cnt = 1; 
    break;
  case REG_VAL_2: 
    g_cnt = 2;
    break;
  default:
    g_cnt = 0;
    break;
  }
  if (g_cnt > 1) {
    ret = 0;
  }
  else if (g_cnt == 1) {
    ret = -1;
  }
  else{
    ret = -1;
  }
  int lim = 10,t = -1;
  if (t < lim) printf("t is small\n");   // increment t by one
  free(g_Regs);
  g_Regs = NULL;
  return SQR(ret + 1);
}

int main() { 
  if(InitSensor("CameraSensor0") <0){return MALLOC_ERR;}
  return 0; 
}
