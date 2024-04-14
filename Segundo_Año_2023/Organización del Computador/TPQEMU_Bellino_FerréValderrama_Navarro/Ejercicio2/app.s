.equ GPIO_BASE,    0x3f200000
.equ GPIO_GPFSEL0, 0x00
.equ GPIO_GPLEV0,  0x34
.include "datos.s"
.include "graficos.s"

.globl main

main:
    mov x20, x0
    ldr w23, celeste //REGISTRO QUE GUARDA EL COLOR DEL CIELO
    bl pintar_fondo
    ldr w22, azul_claro //REGISTRO QUE GUARDA EL COLOR DEL AUTO 
    bl dibujar_auto
    
    //Registros que guardan datos del sol/luna
    mov x24, SCREEN_WIDTH - 40 // Centro en x, x2
    mov x25, 40  // Centro en y, x3
    mov x26, 30 // Posicion inicial offset x4
    ldr w27, amarillo // Elijo si sol(amarillo) o luna(blanco)
    mov w1, w27 // Paso el color como parametro
    bl dibujar_sol_o_luna
    
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
    and w11, w10, 0b00100000
    cbz w11, skip
    ldr w23, negro
    bl pintar_fondo
    
    bl dibujar_auto
    
    ldr w27, gris_claro
    mov w1, w27 
    bl dibujar_sol_o_luna
    
    ldr w1, blanco
    mov x21, 40
    bl dibujar_nube
    
    bl dibujar_semaforo
    
    
    ldr w21, DELAY
    L1: 
       sub w21,w21,#1
    cbnz w21, L1
    
skip:
    ldr w10, [x9, GPIO_GPLEV0]
    and w11, w10, 0b00001000
    cbz w11, skip2
    ldr w22, rojo
    bl dibujar_auto
    bl dibujar_semaforo
    ldr w21, DELAY
    L2: 
       sub w21,w21,#1
    cbnz w21, L2
    
skip2:
    ldr w10, [x9, GPIO_GPLEV0]
    and w11, w10, 0b00000010
    cbz w11, skip3
    ldr w22, azul_claro
    bl dibujar_auto
    bl dibujar_semaforo
    ldr w21, DELAY
    L3: 
       sub w21,w21,#1
    cbnz w21, L3

skip3:
    ldr w10, [x9, GPIO_GPLEV0]
    and w11, w10, 0b00000100
    cbz w11, skip4
    //Borro el sol/luna
    mov w1, w23
    bl dibujar_sol_o_luna
    //Lo dibujo trasladado
    mov w1, w27
    add x24, x24,1
    bl dibujar_sol_o_luna
    
    //Borro la nube
    mov w1, w23
    mov x21, 40
    bl dibujar_nube
    //La dibujo trasladada
    ldr w1, blanco
    add x19, x19, 2
    bl dibujar_nube
    
    bl dibujar_auto
    
    //Borro el semaforo
    bl borrar_semaforo
    //Dibujo el semaforo trasladado
    add x17, x17, 5
    bl dibujar_semaforo
    
    ldr w21, DELAY
    L4: 
       sub w21,w21,#5
    cbnz w21, L4
    
skip4:	
    ldr w10, [x9, GPIO_GPLEV0]
    and w11, w10, 0b00010000
    cbz w11, skip5
    //Borro el sol/luna
    mov w1, w23
    bl dibujar_sol_o_luna
    //Lo dibujo trasladado
    mov w1, w27
    sub x24, x24,1
    bl dibujar_sol_o_luna
    
    //Borro la nube
    mov w1, w23
    mov x21, 40
    bl dibujar_nube
    //La dibujo trasladada
    ldr w1, blanco
    sub x19, x19, 2
    bl dibujar_nube
    
    bl dibujar_auto
    
    //Borro el semaforo
    bl borrar_semaforo
    //Dibujo el semaforo trasladado
    sub x17, x17, 5
    bl dibujar_semaforo
    ldr w21, DELAY
    L5: 
       sub w21,w21,#5
    cbnz w21, L5
    
skip5:    
    b readGPIOS   
     
InfLoop:
    b InfLoop


