--Ejercicio 1

--a)

data Carrera = Matematica | Fisica | Computacion | Astronomia deriving (Eq,Show)

--b)

titulo :: Carrera -> String
titulo Matematica = "Licenciatura en Matematica"
titulo Fisica = "Licenciatura en Fisica"
titulo Computacion = "Licenciatura en Computacion"
titulo Astronomia = "Licenciatura en Astronomia"

--c)

data NotaBasica = Do | Re | Mi | Fa | Sol | La | Si deriving (Show, Eq, Ord)

--d)

cifradoAmericano :: NotaBasica->Char
cifradoAmericano Do = 'C' 
cifradoAmericano Re = 'D' 
cifradoAmericano Mi = 'E' 
cifradoAmericano Fa = 'F' 
cifradoAmericano Sol = 'G' 
cifradoAmericano La = 'A' 
cifradoAmericano Si = 'B' 

--Ejercicio 2)

-- A NotaBasica le agregamos deriving (Show, Eq, Ord)

--Ejercicio 3

--a)

minimoElemento :: (Ord) a =>[a]->a
minimoElemento [x] = x
minimoElemento (x:xs) = min x (minimoElemento xs)

--b)

minimoElemento' ::  Bounded a =>  Ord a => [a]-> a
minimoElemento' [] = maxBound
minimoElemento' (x:xs) = min x (minimoElemento' xs)

--c)

--Utilizando la función minimoElemento en la lista [Fa, La, Sol, Re, Fa], nos devuelve la nota Re.

--4)

--a)

type Ingreso = Int

data Cargo = Titular | Asociado | Adjunto | Asistente | Auxiliar deriving Show

data Area = Administrativa | Ensenanza | Economica | Postgrado deriving Show

data Persona = Decano | Docente Cargo | NoDocente Area | Estudiante Carrera Ingreso deriving Show

--b)

--El tipo del constructor docente es: Cargo -> Persona

--c)

--Función Auxiliar

mismoCargo :: Cargo->Persona->Bool
mismoCargo Titular (Docente Titular) = True
mismoCargo Asociado (Docente Asociado) = True
mismoCargo Adjunto (Docente Adjunto) = True
mismoCargo Asociado (Docente Asistente) = True
mismoCargo Auxiliar (Docente Auxiliar) = True
mismoCargo _ _ = False

cuantos_doc :: [Persona]->Cargo->Int
cuantos_doc [] d = 0
cuantos_doc (x:xs) d |mismoCargo d x = 1 + cuantos_doc xs d
                     |otherwise = cuantos_doc xs d

--d)

cuantos_doc' :: [Persona]->Cargo->Int
cuantos_doc' xs c = length(filter (mismoCargo c) xs)

--Ejercicio 5

--a)

data Alteracion = Bemol | Sostenido | Natural

data NotaMusical = Nota NotaBasica Alteracion 

sonido :: NotaBasica->Int
sonido Do = 1
sonido Re = 3
sonido Mi = 5
sonido Fa = 6
sonido Sol = 8
sonido La = 10
sonido Si = 12

--b)

sonidoCromatico :: NotaMusical->Int
sonidoCromatico (Nota b Sostenido) = (sonido b) + 1 
sonidoCromatico (Nota b Bemol) = (sonido b) - 1 
sonidoCromatico (Nota b Natural) = (sonido b)


--c)

instance Eq NotaMusical
    where
          (Nota b c) == (Nota e f) = 
            sonidoCromatico (Nota b c) == sonidoCromatico (Nota e f)
            
--d)

instance Ord NotaMusical
    where 
        (Nota b c) <= (Nota e f) =
            sonidoCromatico (Nota b c) <= sonidoCromatico (Nota e f)

--Ejercicio 6)

--a) 

primerElemento :: [a]->Maybe a 
primerElemento [] = Nothing
primerElemento (x:xs) = Just x

--Ejercicio 7)

data Cola = VaciaC | Encolada Persona Cola deriving Show

--a)


--1)

atender :: Cola->Maybe Cola
atender VaciaC = Nothing
atender (Encolada a b) = Just b

--2)

encolar:: Persona->Cola->Cola
encolar a VaciaC = (Encolada a VaciaC)
encolar a (Encolada c b) = Encolada c (encolar a b)

--3)

busca :: Cola->Cargo->Maybe Persona
busca VaciaC c = Nothing
busca (Encolada (a) b) c | mismoCargo c a = Just a
                                 | otherwise = busca b c

--b) 

--El tipo cola se parece al tipo lista.

--Ejercicio 8

data ListaAsoc a b = Vacia | Nodo a b ( ListaAsoc a b ) deriving Show

--a)

type GuiaTelefonica = ListaAsoc String Int

--b)

--1)

la_long :: ListaAsoc a b->Int
la_long Vacia = 0
la_long (Nodo a b (c)) = 1 + la_long c

--2)

la_concat :: ListaAsoc a b-> ListaAsoc a b -> ListaAsoc a b
la_concat Vacia d = d
la_concat (Nodo a b (c)) d = (Nodo a b) (la_concat c d)

--3)

la_agregar :: ListaAsoc a b->a->b->ListaAsoc a b
la_agregar d a b = Nodo a b d

--4)

la_pares :: ListaAsoc a b -> [(a,b)]
la_pares Vacia = []
la_pares (Nodo a b d) = [(a,b)] ++ la_pares d

--5)

la_busca :: Eq a=>ListaAsoc a b->a->Maybe b
la_busca Vacia d = Nothing
la_busca (Nodo a b (c)) d | a==d = Just b
                          | otherwise = la_busca c d
                          
--6)

la_borrar :: Eq a=>a->ListaAsoc a b-> ListaAsoc a b
la_borrar d Vacia = Vacia
la_borrar d (Nodo a b (c))| d == a = c
                          |otherwise = (Nodo a b) (la_borrar d c) 

-- Ejercicio 9
data Arbol a = Hoja | Rama (Arbol a) a (Arbol a) deriving (Show)

-- a)
a_long :: Arbol a -> Int
a_long Hoja = 0
a_long (Rama a _ b) = 1 + a_long a + a_long b

-- b)
a_hojas :: Arbol a -> Int
a_hojas Hoja = 1
a_hojas (Rama a _ b) = a_hojas a + a_hojas b

-- c)
a_inc :: Num a => Arbol a -> Arbol a
a_inc Hoja = Hoja
a_inc (Rama a n b) = Rama (a_inc a) (n + 1) (a_inc b)

-- d)
a_map :: (a -> b) -> Arbol a -> Arbol b
a_map _ Hoja = Hoja
a_map f (Rama a x b) = Rama (a_map f a) (f x) (a_map f b)
