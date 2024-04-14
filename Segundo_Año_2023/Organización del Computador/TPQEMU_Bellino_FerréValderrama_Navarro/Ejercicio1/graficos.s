.ifndef graficos_s
.equ graficos_s, 0

.include "datos.s"

//En este archivo estan todas las funciones que dibujan la imagen

pintar_por_pixel:
        cmp x2, SCREEN_WIDTH // Chequeo si el x es valido
        b.hs return_pintar_pixel
        cmp x3, SCREEN_HEIGH // Chequeo si si el y es valido
        b.hs return_pintar_pixel 
        mov x9, SCREEN_WIDTH
        madd x9, x3, x9, x2 // x9 = (x3 * x9) + x2
        str w1, [x0, x9, lsl #2] // Guardo w1 en x0 + x9*2^2

    return_pintar_pixel:
        br lr 

linea_vertical:
        sub sp, sp, #16 // Guardo el puntero de retorno en el stack
        stur lr, [sp, #8]
        stur x3, [sp] // Guardo en el stack la coordenada en y del comienzo de la linea

    loop_linea_vertical:
        cmp x3, x4
        b.gt end_loop_linea_vertical
        bl pintar_por_pixel
        add x3, x3, #1
        b loop_linea_vertical

    end_loop_linea_vertical:
        ldur lr, [sp, #8] // Recupero el puntero de retorno del stack
        ldur x3, [sp] // Recupero la coordenada en y del comienzo de la linea
        add sp, sp, #16 

        br lr 

linea_horizontal:
        sub sp, sp, #16 // Guardo el puntero de retorno en el stack
        stur lr, [sp, #8]
        stur x2, [sp] // Guardo en el stack la coordenada en x del comienzo de la linea 

    loop_linea_horizontal:
        cmp x2, x4
        b.gt end_loop_linea_horizontal
        bl pintar_por_pixel
        add x2, x2, #1
        b loop_linea_horizontal

    end_loop_linea_horizontal:
        ldur lr, [sp, #8] // Recupero el puntero de retorno del stack
        ldur x2, [sp] // Recupero la coordenada en x del comienzo de la linea
        add sp, sp, #16 

        br lr 

dibujar_rectangulo:
        sub sp, sp, #16 
        stur lr, [sp, #8] // Guardo el puntero de retorno en el stack
        stur x3, [sp] // Guardo x3 en el stack

    loop_dibujar_rectangulo: // loop para avanzar en y
        cmp x3, x5
        b.gt end_loop_dibujar_rectangulo
        bl linea_horizontal
        add x3, x3, #1
        b loop_dibujar_rectangulo
    
    end_loop_dibujar_rectangulo:
        ldur lr, [sp, #8] // Recupero el puntero de retorno del stack
        ldur x3, [sp] // Recupero x3 del stack
        add sp, sp, #16

        br lr 

dibujar_circulo:
        sub sp, sp, #8 // Guardo el puntero de retorno en el stack
        stur lr, [sp]

        mov x15, x2 // Guardo en x15 la condenada del centro en x
        mov x16, x3 // Guardo en x16 la condenada del centro en y
        add x10, x2, x4 // Guardo en x10 la posición final en x
        add x11, x3, x4 // Guardo en x11 la posición final en y
        mul x12, x4, x4 // x12 = r^2 
        sub x2, x2, x4 // Pongo en x2 la posición inicial en x

    loop0_dibujar_circulo: // Loop para avanzar en x
        cmp x2, x10
        b.gt end_loop0_dibujar_circulo
        sub x3, x11, x4
        sub x3, x3, x4 // Pongo en x3 la posición inicial en y

    loop1_dibujar_circulo: // Loop para avanzar en y
        cmp x3, x11
        b.gt end_loop1_dibujar_circulo // Chequeo si hay que pintar el pixel
        sub x13, x2, x15 // x13 = Distancia en x desde el pixel actual al centro
        smull x13, w13, w13 // x13 = w13 * w13  
        sub x14, x3, x16 // x14 = distancia en y desde el pixel actual al centro
        smaddl x13, w14, w14, x13 // x13 = x14*x14 + x13 
        cmp x13, x12
        b.gt f_dibujar_circulo 
        bl pintar_por_pixel 

    f_dibujar_circulo:
        add x3, x3, #1
        b loop1_dibujar_circulo

    end_loop1_dibujar_circulo:
        add x2, x2, #1
        b loop0_dibujar_circulo

    end_loop0_dibujar_circulo:
        mov x2, x15 
        mov x3, x16 
        ldur lr, [sp] // Recupero el puntero de retorno del stack
        add sp, sp, #8 

        br lr

dibujar_auto:

    sub sp, sp, #8 // Guardo el puntero de retorno en el stack
    stur lr, [sp]

    // Dibuja la carrocería del auto (un rectángulo)
    mov w1, w22
    mov x2, inicio_auto_x 
    mov x3, inicio_auto_y  
    mov x4, final_auto_x  
    mov x5, final_auto_y
    bl dibujar_rectangulo

     // Coordenadas del rectángulo vertical encima de la carrocería
    mov x2, inicio_techo_auto_x   
    mov x3, inicio_techo_auto_y   
    mov x4, final_techo_auto_x    
    mov x5, final_techo_auto_y     

    ldr w1, blanco
    bl dibujar_rectangulo

    // Dibuja las ruedas del auto (dos círculos)
    ldr w1, negro // Color de las ruedas
    mov x2, primera_rueda_x 
    mov x3, primera_rueda_y   
    mov x4, radio_ruedas 
    bl dibujar_circulo

    ldr w1, negro // Color de las ruedas
    mov x2, segunda_rueda_x  
    mov x3, segunda_rueda_y  
    mov x4, radio_ruedas 
    bl dibujar_circulo


    ldur lr, [sp] // Recupero el puntero de retorno del stack
    add sp, sp, #8 

    br lr

pintar_cielo: 
    sub sp, sp, #8 // Guardo el puntero de retorno en el stack
    stur lr, [sp]
    mov w1, w23   
    mov x2, 0 
    mov x3, 0 
    mov x4, SCREEN_WIDTH    
    mov x5, SCREEN_HEIGH / 4 
    bl dibujar_rectangulo

    ldur lr, [sp] // Recupero el puntero de retorno del stack
    add sp, sp, #8 
    br lr

pintar_calle:
    sub sp, sp, #8 // Guardo el puntero de retorno en el stack
    stur lr, [sp]

    mov x1, x20
    mov x2, inicio_calle_x  
    mov x3, inicio_calle_y 
    mov x4, final_calle_x  
    mov x5, final_calle_y 
    ldr w1, gris 
    bl dibujar_rectangulo 

    ldur lr, [sp] // Recupero el puntero de retorno del stack
    add sp, sp, #8 
    br lr

pintar_piso:
    sub sp, sp, #8 // Guardo el puntero de retorno en el stack
    stur lr, [sp]
    
    mov x1, x20
    mov x2, inicio_piso_x  
    mov x3, inicio_piso_y  
    mov x4, final_piso_x  
    mov x5, final_piso_y
    ldr w1, gris_claro
    bl dibujar_rectangulo 

    ldur lr, [sp] // Recupero el puntero de retorno del stack
    add sp, sp, #8 
    br lr

pintar_fondo:
    sub sp, sp, #8 // Guardo el puntero de retorno en el stack
    stur lr, [sp]
    
    bl pintar_cielo
    bl pintar_calle
    bl pintar_piso

    ldur lr, [sp] // Recupero el puntero de retorno del stack
    add sp, sp, #8 
    br lr

dibujar_sol:    
    sub sp, sp, #8 // Guardo el puntero de retorno en el stack
    stur lr, [sp]
    
    mov x2, x24 
    mov x3, x25
    mov x4, x26
    bl dibujar_circulo

    ldur lr, [sp] // Recupero el puntero de retorno del stack
    add sp, sp, #8 
    br lr

dibujar_nube:
    sub sp, sp, #8 // Guardo el puntero de retorno en el stack
    stur lr, [sp]
    mov x2, x19
    mov x3, x21
    mov x4, x18
    bl dibujar_circulo
    
    add x2, x2, 15
    add x3, x3, 20
    mov x4, x18
    bl dibujar_circulo
    
    sub x2, x2, 30
    mov x4, x18
    bl dibujar_circulo
    
    ldur lr, [sp] // Recupero el puntero de retorno del stack
    add sp, sp, #8 
    br lr
    
dibujar_semaforo:
    sub sp, sp, #8 // Guardo el puntero de retorno en el stack
    stur lr, [sp]
    
    // Dibujo el poste del semaforo
    ldr w1, amarillo_anaranjado
    mov x2, x17
    mov x3, 210  
    add x4, x2, 20
    mov x5, 359
    bl dibujar_rectangulo

    //Dibujo la parte superior del semaforo

    ldr w1, amarillo_anaranjado
    sub x2, x17, 20 //Inicio x
    mov x3, 140  //Inicio y
    add x4, x2, 60 //Final x
    mov x5, 260 //Final y
    
    bl dibujar_rectangulo

    //Dibujo el circulo rojo

    ldr w1, rojo
    add x2, x17, 9  
    mov x3, 160
    mov x4, 15 
    bl dibujar_circulo

    //Dibujo el circulo amarillo

    ldr w1, amarillo 
    add x2, x17, 9  
    mov x3, 200
    mov x4, 15 
    bl dibujar_circulo

    //Dibujo el circulo verde
    ldr w1, verde 
    add x2, x17, 9 
    mov x3, 240
    mov x4, 15 
    bl dibujar_circulo
    
    ldur lr, [sp] // Recupero el puntero de retorno del stack
    add sp, sp, #8 
    br lr

.endif


