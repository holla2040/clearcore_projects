#ifndef _FILE_H_
#define _FILE_H_

void sdInit(void);
void sdSettingsRead(uint8_t *source);
bool sdSettingsWrite(uint8_t *dest);
uint8_t sdSettingsGetByte(uint32_t addr);
void sdSettingsPutByte(uint32_t addr, uint8_t new_value);



#endif
