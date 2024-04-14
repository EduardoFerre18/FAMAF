.equ GPIO_BASE,    0x3f200000
.equ GPIO_GPFSEL0, 0x00
.equ GPIO_GPLEV0,  0x34
.include "datos.s"
.include "graficos.s"

.globl main

main:
    mov x20, x0
    
    ldr w23, celeste 
    bl pintar_fondo
    ldr w22, azul_claro 
    bl dibujar_auto

    //Registros que guardan datos del sol/luna
    mov x24, SCREEN_WIDTH - 40 // Centro en x, x2
    mov x25, 40  // Centro en y, x3
    mov x26, 30 // Posicion inicial offset x4
    ldr w27, amarillo 
    mov w1, w27 // Paso el color como parametro
    bl dibujar_sol
    
    //Registros que guardan datos de la nube
    mov x19, SCREEN_WIDTH - 80
    mov x21, 40
    mov x18, 20
    ldr w1, blanco
    bl dibujar_nube
    
    mov x17, 520 //Posicion inicial del semaforo
    bl dibujar_semaforo
  
readGPIOS:
    mov x9, GPIO_BASE
    str wzr, [x9, GPIO_GPFSEL0]
    ldr w10, [x9, GPIO_GPLEV0]
    and w11, w10, 0b00000010
    cbz w11, readGPIOS
    ldr w22, rojo
    bl dibujar_auto

    ldr w22, DELAY
    L1: 
       sub w22,w22,#1
    cbnz w22, L1

    b readGPIOS
    
InfLoop:
    b InfLoop


