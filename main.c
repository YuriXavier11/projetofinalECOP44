#include <pic18f4520.h>
#include "config.h"
#include "lcd.h"
#include "delay.h"
#include "bits.h"
#include "keypad.h"
#include "valRead.h"
#include "lcdPosition.h"
#include "pwm.h"

unsigned int conta1(int opcao, unsigned int valor);
void  lcdPosition(unsigned char linha, unsigned char coluna);
int   optRead(void);
void  initAcc(int dep);
void  itoa(unsigned int val, char* str );
void  ledLoading(void);
unsigned int saldo;

void main(void) {
    unsigned int tecla = 16, valor;
    int  teclaLida=16,transf;
    char str[4]={};
    
    
    TRISC=0x00;
    
    lcdInit();
    kpInit(); 
    pwmInit();
    initAcc(0);
    
    inicio:
    transf=0;
    lcdPosition(0,0);
    lcd_str("Bem-Vindo aperte");
    lcdPosition(1,1);
    lcd_str("0 para Opcoes");

    for (;;) {
        teclaLida = optRead();

        switch (teclaLida) {
            case 0:
                lcdCommand(0x01); //clr
                lcdPosition(0, 0);
                lcd_str("1-Saldo");
                lcdPosition(0, 9);
                lcd_str("2-Saque");
                lcdPosition(1, 3);
                lcd_str("3-Deposito");
                //shift(4);                    
            break;

            case 1: //saldo
                valor = conta1(2, 0);
                lcdCommand(0x01); //clr
                lcdPosition(0, 2);
                lcd_str("Saldo:");
                lcdPosition(0, 10);
                itoa(valor, str);
                lcd_str(str);
                atraso_s(3);
                goto inicio;
            break;

            case 2: //saque
                lcdCommand(0x01); //clr
                lcdPosition(0, 0);
                lcd_str("5-Soma 6-Subtrai");
                lcdPosition(1, 0);
                lcd_str("#-confirma");
                lcdPosition(1, 12);
                lcd_str("0000");
                break;

            case 3: //Depósito
                lcdCommand(0x01); //clr
                lcdPosition(0, 0);
                lcd_str("5-Soma 6-Subtrai");
                lcdPosition(1, 0);
                lcd_str("*-confirma");
                lcdPosition(1, 12);
                lcd_str("0000");
                break;

            case 5:
                transf += 50;
                itoa(transf, str);
                lcdPosition(1, 12);
                lcd_str(str);
            break;

            case 6:
                transf -= 50;
                itoa(transf, str);
                lcdPosition(1, 12);
                lcd_str(str);
            break;

            case 444:
                ledLoading();
                atraso_s(2);
                if (transf > conta1(2, 0)) {
                    lcdCommand(0x01); //clr
                    lcdPosition(0, 5);
                    lcd_str("Operacao");
                    lcdPosition(1, 5);
                    lcd_str("Invalida");
                    bitSet(TRISC, 1);
                    atraso_s(1);
                    bitClr(TRISC, 1);

                    goto inicio;
                } else {
                    lcdCommand(0x01); //clr
                    lcdPosition(0, 5);
                    lcd_str("Operacao");
                    lcdPosition(1, 5);
                    lcd_str("Realizada");
                    conta1(3, transf);
                    bitSet(TRISC, 1);
                    atraso_s(1);
                    bitClr(TRISC, 1);

                    goto inicio;
                }
            break;

            case 123: //depósito
                lcdCommand(0x01); //clr
                lcdPosition(0, 0);
                lcd_str("Insira as cedulas");
                lcdPosition(1, 5);
                lcd_str("Abaixo");
                pwmSet1(64);
                atraso_s(5);
                pwmSet1(0);
                conta1(4, transf);
                lcdCommand(0x01); //clr
                lcdPosition(0, 5);
                lcd_str("Operacao");
                lcdPosition(1, 5);
                lcd_str("Realizada");
                atraso_s(2);
                goto inicio;
            break;
        }
    }
}

void ledLoading(void) {
    int j, pos;

    TRISD = 0x00;
    PORTD = 0x00;

    for (j = 1; j < 9; j++) {
        switch (j) {
            case 1: 
                pos = 1;
            break; 
            case 2: 
                pos = 2;
            break;
            case 3: 
                pos = 4;
            break;
            case 4: 
                pos = 8;
            break;
            case 5: 
                pos = 16;
            break;
            case 6: 
                pos = 32;
            break;
            case 7: 
                pos = 64;
            break;
            case 8: 
                pos = 128;
            break;
        }
        PORTD = pos;
        atraso_ms(500);
    }
}

int optRead(void){
    unsigned int tecla;
    tecla=kpRead();
    
    for(;;){
        kpDebounce();
        if (kpRead() != tecla) {
            tecla = kpRead();
            if (bitTst(tecla, 4)){return 0;}
            else if (bitTst(tecla, 1)){return 7;}
            else if (bitTst(tecla, 2)){return 4;}
            else if (bitTst(tecla, 3)){return 1;}
            else if (bitTst(tecla, 0)){return 123;}
            else if (bitTst(tecla, 5)){return 8;}
            else if (bitTst(tecla, 6)){return 5;}
            else if (bitTst(tecla, 7)){return 2;}
            else if (bitTst(tecla, 9)){return 9;}
            else if (bitTst(tecla, 10)){return 6;}
            else if (bitTst(tecla, 11)){return 3;} 
            else if (bitTst(tecla, 8)){return 444;} 
        }
    }
}

void initAcc(int dep){

    conta1(2, 0);

}

unsigned int conta1(int opcao, unsigned int valor){
    switch(opcao){
        case 1: 
            saldo = valor;
        break;
        case 2: 
            return saldo;
        break;
        case 3: 
            saldo -= valor;
        break;
        case 4: 
            saldo += valor;
            
        break;
    }
    return 0;
}

void itoa(unsigned int val, char* str ){ 
  str[0]=((val%10000)/1000)+0x30;  
  str[1]=((val%1000)/100)+0x30;  
  str[2]=((val%100)/10)+0x30;
  str[3]=(val%10)+0x30;
}



