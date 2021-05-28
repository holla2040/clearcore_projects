#ifndef _SERIAL_H_
#define _SERIAL_H_

void serialInit(void);
int16_t serialGetC(void);
bool serialPutC(const char c);
void serialWriteS(const char *s);
void serialWriteLn(const char *s);
void serialWrite(const char *s, uint16_t length);
bool serialSuspendInput (bool suspend);
uint16_t serialTxCount(void);
uint16_t serialRxCount(void);
uint16_t serialRxFree(void);
void serialRxFlush(void);
void serialRxCancel(void);


#endif

