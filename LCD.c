#include "LCD.h"


/**\brief Actualiza pines LCD*/
void Lcd_Port(char a) {// Actualiza los pines de la pantalla LCD

    /**
      \details
     Actualiza los pines conectados a la pantalla LCD
     */
    if(a & 1)
       D4 = 1;
    else. 
       D4 = 0;

    if(a & 2)
       D5 = 1;
    else
       D5 = 0;

    if(a & 4)
       D6 = 1;
    else
       D6 = 0;

    if(a & 8)
       D7 = 1;
    else
       D7 = 0;
}



/**\brief Comandos LCD*/
void Lcd_Cmd(char a) {// Envia un comando para la LCD

    /**
      \details
     Envia comandos a la pantalla LCD
     */
    RS = 0; // => RS = 0
    Lcd_Port(a);
    EN = 1; // => E = 1
    delay_ms(4);
    EN = 0; // => E = 0
}


/**\brief Clear del LCD*/
void Lcd_Clear(void) {//Borra toda la pantalla LCD

    /**
      \details
     Borra todo lo que hay en la LCD
     */
    Lcd_Cmd(0);
    Lcd_Cmd(1);
}


/**\brief Obtener cursor*/
void Lcd_Set_Cursor(char a, char b) {//Obtiene la ubicaci?n del cursor en LCD

    /**
      \details
     Asigna las coordenadas del cursor en la pantalla LCD
     */
    char temp, z, y;
    if (a == 1) {
        temp = 0x80 + b - 1;
        z = temp >> 4;
        y = temp & 0x0F;
        Lcd_Cmd(z);
        Lcd_Cmd(y);
    } else if (a == 2) {
        temp = 0xC0 + b - 1;
        z = temp >> 4;
        y = temp & 0x0F;
        Lcd_Cmd(z);
        Lcd_Cmd(y);
    }
}

/**\brief Incializacion del LCD*/
void Lcd_Init(void) {// Inicializ la LCD

    /**
      \details
     Pone los valores inciales de la Pantalla LCD
     */
    Lcd_Port(0x00);
    delay_ms(20);
    Lcd_Cmd(0x03);
    delay_ms(5);
    Lcd_Cmd(0x03);
    delay_ms(11);
    Lcd_Cmd(0x03);

    Lcd_Cmd(0x02);
    Lcd_Cmd(0x02);
    Lcd_Cmd(0x08);
    Lcd_Cmd(0x00);
    Lcd_Cmd(0x0C);
    Lcd_Cmd(0x00);
    Lcd_Cmd(0x06);
}


/**\brief Escribir char*/
void Lcd_Write_Char(char a) {// Escribe en la LCD un caracter

    /**
      \details
     Escribe en pantalla un caracter
     */
    char temp, y;
    temp = a & 0x0F;
    y = a & 0xF0;
    RS = 1; // => RS = 1
    Lcd_Port(y >> 4); //Data transfer
    EN = 1;
    delay_ms(1);
    EN = 0;
    Lcd_Port(temp);
    EN = 1;
    delay_ms(1);
    EN = 0;
}


/**\brief Escribir cadena*/
void Lcd_Write_String(char *a) {// Escribe en la LCD una palabra

    /**
      \details
     Escribe en la pantalla LCD una cadena
     */
    int i;
    for (i = 0; a[i] != '\0'; i++)
        Lcd_Write_Char(a[i]);
}

void delay_ms(unsigned int delay_val) {
    unsigned int i, j;
    for (i = 0; i < delay_val; i++) {
        for (j = 0; j < 165; j++);
    }
}

