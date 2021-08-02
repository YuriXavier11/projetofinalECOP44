#include "lcdPosition.h"
#include "lcd.h"

void lcdPosition(unsigned char linha, unsigned char coluna){
    char comando=0;
    
    if (coluna > 15) {
        coluna = 0;
    }
    if (coluna < 0) {
        coluna = 15;
    }
    if (linha == 0) {
        comando = 0x80 + coluna;
    }
    if (linha == 1) {
        comando = 0xC0 + coluna;
    }
    lcdCommand(comando);
}