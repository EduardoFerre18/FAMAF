--PARCIAL 1 2022-04-25 (tema A)

--Ejercicio 1

--a)

data Forma = Piedra | Papel | Tijera 

reglas ::Forma->Forma->Bool
reglas Piedra Tijera = True
reglas Piedra  Piedra = False 
reglas Piedra Papel = False 
reglas Papel Piedra = True 
reglas Papel Papel = False
reglas Papel Tijera = False  
reglas Tijera Papel = True 
reglas Tijera Tijera = False
reglas Tijera Piedra = False 

le_gana ::Forma->Forma->Bool
le_gana f g = reglas f g

--b)

type Nombre = String

data Jugador = Mano Nombre Forma


ganador:: Jugador->Jugador->Maybe Nombre
ganador (Mano n f) (Mano m g) | le_gana f g = Just n 
                              | le_gana g f = Just m
                              |otherwise = Nothing

--Ejercicio 2)

mismaForma :: Forma->Forma->Bool
mismaForma Piedra Piedra= True
mismaForma Tijera Tijera = True
mismaForma Papel Papel = True
mismaForma _ _ = False

quien_jugo :: Forma->[Jugador]->[Nombre]
quien_jugo f [] = []
quien_jugo f ((Mano n g):js)| mismaForma f g = n: quien_jugo f js
                            |otherwise = quien_jugo f js

data NotaMusical = Do | Re | Mi | Fa | Sol | La | Si
data Figura = Negra | Corchea
data Melodia = Entonar NotaMusical Figura Melodia | Vacia

figura1 :: Figura->Melodia->Bool
figura1 Corchea (Entonar n Corchea m)= True
figura1 Negra (Entonar n Negra m)= True
figura1 _ _ = False





contar_tiempos :: Melodia -> Int
contar_tiempos Vacia = 0
contar_tiempos (Entonar n f m) |figura1 Corchea (Entonar n f m)  = 1 + contar_tiempos m
                               |figura1 Negra (Entonar n f m) = 2 + contar_tiempos m
                               |otherwise = contar_tiempos m 


--Ejercicio 4)

data Arbol a = Hoja | Rama (Arbol a) a (Arbol a) deriving (Show)

as::Arbol Int
as= (Rama (Rama (Rama Hoja 3 Hoja) 2 (Rama Hoja 4 Hoja)) 1 (Rama (Rama Hoja 6 Hoja) 5 (Rama Hoja 7 Hoja)))
bs:: Arbol Int
bs= (Rama (Rama (Rama Hoja 4 Hoja) 7 (Rama Hoja 8 Hoja)) 1 (Rama (Rama Hoja 3 Hoja) 5 (Rama Hoja 2 Hoja)))

arbol_sum :: Arbol Int->Arbol Int->Arbol Int
arbol_sum Hoja as = as
arbol_sum bs Hoja = bs
arbol_sum (Rama l1 c1 r1) (Rama l2 c2 r2)= Rama (arbol_sum l1 l2) (c1+c2) (arbol_sum r1 r2)





                              








