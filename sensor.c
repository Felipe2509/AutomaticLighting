#include <xc.h>
#include <pic18f4550.h>
#include "config.h"
#include "adc_lib.h"
#include "config_puertos.h"
unsigned char password[5] ={'1','1','1','1',0};
unsigned char pass_user[5];

unsigned int value_adc = 0;
unsigned char col_loc, rowloc, temp_col;
unsigned char keypad[4][3] = {'7', '8', '9',
                              '4', '5', '6',
                              '1', '2', '3',
                              '*', '0', '#'};

unsigned char keyfind(); /* function to find pressed key*/
void delay_ms(unsigned int delay_val);
unsigned char idx = 0;
unsigned int bandera=1;
unsigned int control_parental=0;
void main() {

    OSCCON = 0x72; //frec ( Mhz, oscilador interno)
    RBPU = 0;
    CFG_PIR = INPUT; //configuramos el sensor pir en input
    CFG_LAMP = OUTPUT; //configuramos el led en ouput
    adc_init();

    while (1) {

        value_adc = adc_read();
        if (PIR == 1 && value_adc < 25&&control_parental=0) { //si el sensor pir detecta moviento y no hay suficiente luz
            LAMP = ON; //encendemos la lampara 
        } else {
            LAMP = OFF; //apagamos la lampara

        }
        capturarTeclado();

        delay_ms(500);
    }
}
//pausa el tiempo enmilisegundos
void delay_ms(unsigned int delay_val) {
    unsigned int i, j;
    for (i = 0; i < delay_val; i++) {
        for (j = 0; j < 165; j++);
    }
}
//captura la clave digitada en el teclado y la compara con el password para apagar las luces hasta que se digite nuevamente
void capturarTeclado(){
    char key;
    unsigned int i;
    key=keyfind();
    pass_user[idx++] = key;
    for (i = 0; i < 4; i++) {
        if(pass_user[i]!=password[i])
            bandera=0;
                             }
    
    if(bandera==1){
        if(control_parental==0){
            control_parental=1;
        }else{
            control_parental=0;
        }
        idx=0;
    }
    bandera=1;
            
}
//retorna la telca digitada en ese momento
unsigned char keyfind() {

    Direction_Port = 0xf0; //TRISC = 0C 1111 0000
    unsigned char temp1;

    write_port = 0xf0; //Make lower nibble as low(Gnd) and Higher nibble as High(Vcc)
    do {
        do {

            col_loc = read_port & 0xf0; //mask port with f0 and copy it to col_loc variable

        } while (col_loc != 0xf0); //Check initially at the start there is any key pressed
        col_loc = read_port & 0xf0; //mask port with f0 and copy it to col_loc variable
    } while (col_loc != 0xf0);

    delay_ms(50);
    write_port = 0xf0; //Make lower nibble as low(Gnd) and Higher nibble as High(Vcc)
    do {
        do
 {

            col_loc = read_port & 0xf0;
        } while (col_loc == 0xf0); //Wait for key press
        col_loc = read_port & 0xf0;
    } while (col_loc == 0xf0); //Wait for key press

    delay_ms(20);

    col_loc = read_port & 0xf0;



    while (1) {
        write_port = 0xfe; //make Row0(D0) Gnd and keep other row(D1-D3) high
        col_loc = read_port & 0xf0; //Read Status of PORT for finding Row
        temp_col = col_loc;
        if (col_loc != 0xf0) {
            rowloc = 0; //If condition satisfied get Row no. of key pressed
            while (temp_col != 0xf0) //Monitor the status of Port and Wait for key to release
            {
                temp_col = read_port & 0xf0; //Read Status of PORT for checking key release or not
            }
            break;
        }

        write_port = 0xfd; //make Row1(D1) Gnd and keep other row(D0-D2-D3) high
        col_loc = read_port & 0xf0; //Read Status of PORT for finding Row
        temp_col = col_loc;
        if (col_loc != 0xf0) {
            rowloc = 1; //If condition satisfied get Row no. of key pressed
            while (temp_col != 0xf0) //Monitor the status of Port and Wait for key to release
            {
                temp_col = read_port & 0xf0; //Read Status of PORT for checking key release or not
            }
            break;
        }

        write_port = 0xfb; //make Row0(D2) Gnd and keep other row(D0-D1-D3) high
        col_loc = read_port & 0xf0; //Read Status of PORT for finding Row
        temp_col = col_loc;
        if (col_loc != 0xf0) {
            rowloc = 2; //If condition satisfied get Row no. of key pressed
            while (temp_col != 0xf0) //Wait for key to release
            {
                temp_col = read_port & 0xf0; //Read Status of PORT for checking key release or not
            }
            break;
        }

        write_port = 0xf7; //make Row0(D3) Gnd and keep other row(D0-D2) high
        col_loc = read_port & 0xf0; //Read Status of PORT for finding Row*
        temp_col = col_loc;
        if (col_loc != 0xf0) {
            rowloc = 3; //If condition satisfied get Row no. of key pressed
            while (temp_col != 0xf0) //Wait for key to release
            {
                temp_col = read_port & 0xf0; //Read Status of PORT for checking key release or not
            }
            break;
        }

    }



    while (1) {

        if (col_loc == 0xe0) {
            return keypad[rowloc][0]; //Return key pressed value to calling function       
        } else
            if (col_loc == 0xd0) {
            return keypad[rowloc][1]; //Return key pressed value to calling function
        } else
            if (col_loc == 0xb0) {
            return keypad[rowloc][2]; //Return key pressed value to calling function
        } else
 {
            return keypad[rowloc][3]; //Return key pressed value to calling function     
        }
    }

    delay_ms(300);

}