/* 
 * File:   Libreria I2C
 * Author: CVR ELECTRONINCA 
 * Comments: Version 1.0 del c�digo
 * Revision history: 
 */

#ifndef __CVR_I2C_H
#define __CVR_I2C_H

#define trisSDA TRISBbits.RB1 //Configuracion puerto SDA
#define trisSCL TRISBbits.RB0 //Configuracion puerto SCL

#define sda PORTBbits.RB1 //pin para la se�al SDA 
#define scl PORTBbits.RB0 //pin para la se�al SCL

#define I2C_READ  1
#define I2C_WRITE 0
#define M_ACK  0 //EL MAESTRO ENVIA CONDICION DE ACK,
#define NM_ACK  1 //EL MAESTRO NO ENVIA CONDICION DE ACK, ESTA ES ENVIADA DESDE EL ESCLAVO

#define vel 26 //26 micro segundos 1/velocidad 1/100kbs

void I2C_Init(void); // INICIA EL PUERTO I2C CONFIGURANDO LOS PINES SELECCIONADOS COMO I/O RESPECTIVAMENTE
void I2C_start(void); // ENVIA UNA CONDICION DE START
void I2C_Stop(void); // ENVIA UNA CONSICION DE STOP
unsigned char I2C_sendAdress(int byte,char wr); // ENVIA EL BYTE CON LA DIRECCION DEL DISPOSITIVO MAS LA BIT R/W (I2C_READ/I2C_WRITE)
unsigned char I2C_sendByte(int byte); //ENVIA UN BYTE DE DATOS
unsigned char I2C_readByte(int bytes, char MASTER_ACK); // recibe como paramentro el numero de bytes a leer ( por ahora solo lee un byte de dato)

void I2C_Init()
{
  trisSDA = 0; trisSCL = 0; sda = 1; scl = 1;
}

void I2C_start(){
    scl = 1; sda = 0;__delay_us(26);sda = 1;__delay_us(26);
}
unsigned char I2C_sendAdress(int byte,char wr){
    byte = byte<<1;
    if(wr == I2C_WRITE){
        byte = byte & 0b11111110;
    }else{
        byte = byte | 0b00000001;
    }
    for(int i=0; i<8; i++){
        scl = 0;
        __delay_us(26);
        if((byte & 0x80)==0){
            sda = 0;
        }else{
            sda = 1;
        }
        byte = byte << 1;
        scl = 1;
        __delay_us(26);
    }
    scl = 0;
    __delay_us(26);
    sda = 1;
    scl = 1;
    __delay_us(26);
    scl = 0;
    __delay_us(26);
    if(sda == 1){
        return 0;
    }else{
        return 1;
    }
}

unsigned char I2C_sendByte(int byte){
    for(int i=0; i<8; i++){
        scl = 0;
        __delay_us(26);
        if((byte & 0x80)==0){
            sda = 0;
        }else{
            sda = 1;
        }
        byte = byte << 1;
        scl = 1;
        __delay_us(26);
        
    }
    scl = 0;
    sda = 1;
    __delay_us(26);
    scl = 1;
    __delay_us(26);
    scl = 0;
    __delay_us(26);
    
    if(sda == 1){
        return 0;
    }else{
        return 1;
    }
}
unsigned char I2C_readByte(int bytes, char MASTER_ACK){
    int pulses = bytes*8;
    char byte = 0;
    scl = 0;
    for(int x=0; x<pulses; x++){
        trisSDA = 1;
        scl = 1;
        __delay_us(26);
        if(sda == 1){
            byte = byte | 1;
        }else{
            byte = byte | 0;
        }
        byte = byte << 1;
        scl = 0;
        __delay_us(26);
    }
    scl = 0;
    if(MASTER_ACK == 1){
        sda = 0;
    }else{
        sda = 1;
    }
    __delay_us(26);
    scl = 1;
    __delay_us(26);
    scl = 0;
    __delay_us(26);
    trisSDA = 0;
    return byte;
}

void I2C_Stop()
{
 sda = 0;__delay_us(26); scl = 1;__delay_us(26);sda = 1;__delay_us(26);
}

#endif