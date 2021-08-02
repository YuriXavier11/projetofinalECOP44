#include "valRead.h"
#include "pic18f4520.h"
#include "config.h"
#include "bits.h"
#include "keypad.h"
#include "lcd.h"
#include "lcdPosition.h"

int montante(void) {
    unsigned int tecla;
    char valorC[5];
    int valor=0, i, pot[4]={1000,100,10,1};
    tecla = 16;
    
    for(i=0;i<4;i++){
        valorC[i]= 0 + 0x30;
    }
    
    for (i = 0; i < 4; i++) {
        kpDebounce();
        if (kpRead() != tecla) {
            tecla = kpRead();
            if (bitTst(tecla, 4)) {
                valor += tecla * pot[i];
                valorC[i]= tecla + 0x30;
            } else if (bitTst(tecla, 1)) {
                valor += tecla * pot[i];
                valorC[i]= tecla + 0x30;
            } else if (bitTst(tecla, 2)) {
                valor += tecla + 0x30;
                valorC[i]= tecla + 0x30;
            } else if (bitTst(tecla, 3)) {
                valor += tecla * pot[i];
                valorC[i]= tecla + 0x30;
            } else if (bitTst(tecla, 5)) {
                valor += tecla * pot[i];
                valorC[i]= tecla + 0x30;
            } else if (bitTst(tecla, 6)) {
                valor += tecla * pot[i];
                valorC[i]= tecla + 0x30;
            } else if (bitTst(tecla, 7)) {
                valor += tecla * pot[i];
                valorC[i]= tecla + 0x30;
            } else if (bitTst(tecla, 9)) {
                valor += tecla * pot[i];
                valorC[i]= tecla + 0x30;
            } else if (bitTst(tecla, 10)) {
                valor += tecla * pot[i];
                valorC[i]= tecla + 0x30;
            } else if (bitTst(tecla, 11)) {
                valor += tecla * pot[i];
                valorC[i]= tecla + 0x30;
            } 
            lcdPosition(0,7);
            lcd_str(valorC);
        } 
        
        
    }
    return valor;
}