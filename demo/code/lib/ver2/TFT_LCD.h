#ifndef _TFT_LCD_H_
#define _TFT_LCD_H_

#define TFT_SIZE     3
#define TFT_LINE_1   0
#define TFT_LINE_2   40
#define TFT_LINE_3   80

void TFT_Init(void);
void TFT_PrintText(int16_t x, int16_t y, int8_t sizeText, String text);
void TFT_DeleteLine(int16_t line);
void TFT_Clear(void);

#endif /* _TFT_LCD_H_ */
