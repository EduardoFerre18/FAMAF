.ifndef datos_s
.equ datos_s, 0 

//En este archivo definimos constantes que utilizamos en todas las funciones de los demas archivos.

//DELAY

DELAY : .word 0x05F5E100

//Pantalla

.equ SCREEN_WIDTH,   640
.equ SCREEN_HEIGH,  480
.equ BITS_PER_PIXEL, 32

//Constantes del auto

.equ inicio_auto_x, 240
.equ final_auto_x, 400
.equ inicio_auto_y, 250 
.equ final_auto_y, 330

.equ inicio_techo_auto_x, 280 
.equ final_techo_auto_x, 360 
.equ inicio_techo_auto_y, 180 
.equ final_techo_auto_y,  250 


.equ primera_rueda_x, 260 
.equ primera_rueda_y, 330
.equ segunda_rueda_x, 380 
.equ segunda_rueda_y, 330
.equ radio_ruedas, 30

//Constantes de la calle
    
    //Calle
    .equ inicio_calle_x, 0
    .equ inicio_calle_y, 120
    .equ final_calle_x, 640
    .equ final_calle_y, 360 
    
    //Lineas de la calle
    //Primer linea
    .equ inicio_pr_linea_x, 0
    .equ inicio_pr_linea_y, 238 
    .equ final_pr_linea_x, 640
    .equ final_pr_linea_y, 242
    //Segunda linea
    .equ inicio_sg_linea_x, 0
    .equ inicio_sg_linea_y, 118
    .equ final_sg_linea_x, 640
    .equ final_sg_linea_y, 122
    //Tercera Linea
    .equ inicio_tr_linea_x, 0
    .equ inicio_tr_linea_y, 358
    .equ final_tr_linea_x, 640
    .equ final_tr_linea_y, 362

//Constantes del piso
.equ inicio_piso_x, 0
.equ inicio_piso_y, 360
.equ final_piso_x, 640
.equ final_piso_y, 480

//Colores
azul_claro: .word 0x175be4 
blanco: .word 0xffffff 
negro: .word 0x000000 
gris: .word 0x606060
amarillo: .word 0xffff00
gris_claro: .word 0xa0a0a0    
celeste: .word 0x8ecbff   
rojo : .word 0xe81515
amarillo_anaranjado : .word 0xe6c000
verde : .word 0x00ff00
verde_cesped: .word 0x00994c

.endif

