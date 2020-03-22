# CVR_I2C.h
Librería que permite realizar comunicación i2c desde cualquier microcontrolador PIC cuente o no con puerto serial ya que este es realizado por software

# DETALLE DE LAS FUNCIONES

# 1) I2C_INIT()
  Iniciar la comunicacion usando los pines que se desee usando (por default RB1 -> SDA RB0 -> SCL | si se desea cambiar los pines modificar en libreria) --- use la funcion 

# 2) I2C_start()
  Envia condicion de start al esclavo

# 3) I2C_sendAdress(int byte,char wr)
  Envia un byte con la direccion del esclavo, retorna 1 -> si el esclavo envia ack, retorna 0 -> si el esclavo no envia bit de ack

# 4) I2C_sendByte(int byte)
  Envía un Byte de datos al esclavo, normalmente usado despues de enviar la direccion al esclavo
  
# 5) 2C_readByte(int bytes, char MASTER_ACK)
  Lee un Byte de datos desde el esclavo (el parametro MASTER_ACK puede ser configurado con las siguientes opciones  M_ACK -> El maestro     genera la conidcion de ACK, esto cuando no se espera ACK desde el esclavo, NM_ACK -> El maestro no genera la condicion ACK, esto cuando   se espera ACK desde el esclavo.
  
# CONDIGOS DE EJEMPLO 

# ESCRIBIR DATOS
  I2C_start(); // send a start condition 
  if(I2C_sendAdress(adress,I2C_WRITE) == 1){ //send write comand and return 1 if ack or 0 if nack
      I2C_sendByte(val); //send the byte to device 
      I2C_Stop(); // send stop condition
  }
  
 # LEER DATOS
 I2C_start(); // send a start condition
 if(I2C_sendAdress(adress,I2C_READ) == 1){ //send write comand and return 1 if ack or 0 if nack
     I2C_readByte(1,M_ACK); //read 1 byte fron the slave and the master no wait a ack contidion
     I2C_Stop(); // send stop condition
     __delay_ms(1000);
 }
 
 Esta librería es desarrollada por CVR ELECTRONICA y puedes ser usada libremente por cualquier persona que la necesite.
 
 # DATOS DE CONTACTO
 
 WEB: www.cvrelectronica.com
 Email: develop@cvrelectronica.com
 WhatsApp: +57 301 546 8124