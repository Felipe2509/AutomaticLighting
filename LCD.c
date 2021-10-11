#include "LDC.h"

/**\brief Actualizar pantalla*/
void Estado_Sis(int count) {// Actualiza la pantalla LCD
    /**
      \details
     Actualiza e imprime en pantalla #personas, nivel de alcohol y fecha
     */
    conf_RS 0;
    conf_EN 0;
    conf_D4 0;
    conf_D5 0;
    conf_D6 0;
    conf_D7 0;
    char aux[5];
    Lcd_Init();
    Lcd_Set_Cursor(1, 1);
    Lcd_Write_String("#Per:");
    Lcd_Set_Cursor(1, 6);
    sprintf(aux, "%d", count);
    Lcd_Write_String(aux); // Imprime el numero de personas desinfectadas
    Lcd_Set_Cursor(1, 10);
    Lcd_Write_String("Niv:"); //Imprimi el nivel de alcohol
    Lcd_Set_Cursor(2, 1);
    Lcd_Write_String("  12/12/2020"); //Imprimi fecha


}
/*F**************************************************************************
 * NAME: Lcd_Port
 *----------------------------------------------------------------------------
 * PARAMS:
 * val: Caracter
 * return:   none
 *----------------------------------------------------------------------------
 * PURPOSE:
 * Actualizar pines del LCD
 *----------------------------------------------------------------------------
 * NOTE:
 *
 *****************************************************************************/

/**\brief Actualiza pines LCD*/
void Lcd_Port(char a) {// Actualiza los pines de la pantalla LCD

    /**
      \details
     Actualiza los pines conectados a la pantalla LCD
     */
    if (a & 1) {
        D4 = 1;
    } else {
        D4 = 0;
    }
    if (a & 2) {
        D5 = 1;
    } else
        D5 = 0;

    if (a & 4)
        D6 = 1;
    else
        D6 = 0;

    if (a & 8)
        D7 = 1;
    else
        D7 = 0;
}
/*F**************************************************************************
 * NAME: Lcd_Cmd
 *----------------------------------------------------------------------------
 * PARAMS:
 * val: a, caracter
 * return:   none
 *----------------------------------------------------------------------------
 * PURPOSE:
 * Manda comandos al LCD
 *----------------------------------------------------------------------------
 * NOTE:
 *
 *****************************************************************************/

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
/*F**************************************************************************
 * NAME: Lcd_Clear
 *----------------------------------------------------------------------------
 * PARAMS:
 * val: none
 * return:   none
 *----------------------------------------------------------------------------
 * PURPOSE:
 * Borra todo en la pantalla LCD
 *----------------------------------------------------------------------------
 * NOTE:
 *
 *****************************************************************************/

/**\brief Clear del LCD*/
void Lcd_Clear(void) {//Borra toda la pantalla LCD

    /**
      \details
     Borra todo lo que hay en la LCD
     */
    Lcd_Cmd(0);
    Lcd_Cmd(1);
}
/*F**************************************************************************
 * NAME: Lcd_Set_Cursor
 *----------------------------------------------------------------------------
 * PARAMS:
 * val: x,y, coordenadas donde poner el cursor
 * return:   none
 *----------------------------------------------------------------------------
 * PURPOSE:
 * Actualiza las coordenadas del cursor LCD
 *----------------------------------------------------------------------------
 * NOTE:
 *
 *****************************************************************************/

/**\brief Obtener cursor*/
void Lcd_Set_Cursor(char a, char b) {//Obtiene la ubicación del cursor en LCD

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
/*F**************************************************************************
 * NAME: Lcd_Init
 *----------------------------------------------------------------------------
 * PARAMS:
 * val: none
 * return:   none
 *----------------------------------------------------------------------------
 * PURPOSE:
 * Inicializa los valores del LCD
 *----------------------------------------------------------------------------
 * NOTE:
 *
 *****************************************************************************/

/**\brief Incializacion del LCD*/
void Lcd_Init(void) {// Inicializ la LCD

    /**
      \details
     Pone los valores inciiales de la Pantalla LCD
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
/*F**************************************************************************
 * NAME: Lcd_Write_Char
 *----------------------------------------------------------------------------
 * PARAMS:
 * val: a, caracter a escribir
 * return:   none
 *----------------------------------------------------------------------------
 * PURPOSE:
 * Escribe un caracter en la pantalla LCD
 *----------------------------------------------------------------------------
 * NOTE:
 *
 *****************************************************************************/

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
/*F**************************************************************************
 * NAME: Lcd_Write_String
 *----------------------------------------------------------------------------
 * PARAMS:
 * val: primera posicion de la cadena
 * return:   none
 *----------------------------------------------------------------------------
 * PURPOSE:
 * Escribe una cadena de caracteres en la pantalla LCD
 *----------------------------------------------------------------------------
 * NOTE:
 *
 *****************************************************************************/

/**\brief Escribir cadena*/
void Lcd_Write_String(char *a) {// Escribe en la LCD una palara

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