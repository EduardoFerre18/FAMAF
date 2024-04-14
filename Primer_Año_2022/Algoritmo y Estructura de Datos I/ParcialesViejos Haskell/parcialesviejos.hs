--PARCIAL 1

--Ejercicio 1)

estaEnDNI :: Int->Bool
estaEnDNI x = (x==4 || x==5 || x==6 || x==9 || x==0 ||x==4 || x==6 || x==7)

--Ejercicio 2)

sumaDNI :: [Int]->Int
sumaDNI [] = 0
sumaDNI (x:xs) |(estaEnDNI x) = x + sumaDNI xs
                | otherwise = sumaDNI xs

--Ejercicio 3)

sumatoria' :: [a]->(a->Int)->Int
sumatoria' [] f = 0
sumatoria' (x:xs) f = f x + sumatoria' xs f

funcaxuiliar :: Int -> Int
funcaxuiliar x | (estaEnDNI x) = x
               | otherwise = funcaxuiliar x

sumaDNI' :: [Int]->Int
sumaDNI' xs = sumatoria' xs (funcaxuiliar)

--Ejercicio 4)

reducir :: [a]->(a->a->a)->a
reducir [x] op = x
reducir (x:y:ys) op = op x (op y (reducir ys op))

--PARCIAL 2

--Ejercicio 1)

data Materia = IntroAlgo | Algo1 | Algo2 | Sistemas | Discreta2 | IngSoft1
type InfoMateria = (String,Int)

datos_de_materia :: Materia->InfoMateria
datos_de_materia IntroAlgo = ("Introducción a los Algoritmos 1er año",1)
datos_de_materia Algo1 = ("Algoritmo y Estructura de Datos I", 1)
datos_de_materia Algo2 = ("Algoritmo y Estructura de Datos II", 2)
datos_de_materia Sistemas = ("Sistemas Operativos", 2)
datos_de_materia Discreta2 = ("Matemática Discreta II", 3)
datos_de_materia IngSoft1 = ("Ingeniería del Software I", 3)

--Ejercicio 2)

type Año = Int
data Cursadas = AgregarCursada Materia Año Cursadas | Ninguna


cantidad_cursadas :: Cursadas->Año->Int
cantidad_cursadas Ninguna a = 0
cantidad_cursadas (AgregarCursada m y c) a | y==a  = 1 + cantidad_cursadas c a
                                            |otherwise = cantidad_cursadas c a

--Ejercicio 3)

data Carrera = Matematica | Fisica | Computacion | Astronomia deriving (Eq,Show)

type Ingreso = Int

data Cargo = Titular | Asociado | Adjunto | Asistente | Auxiliar deriving Show

data Area = Administrativa | Ensenanza | Economica | Postgrado deriving Show

data Persona = Decano | Docente Cargo | NoDocente Area | Estudiante Carrera Ingreso deriving Show

es_est :: Persona->Bool
es_est (Estudiante c i) = True
es_est _ = False

edad_per :: Persona->Int->Int
edad_per x a = 2022 - a

cuantos_est_may :: [Persona]->Int->Int
cuantos_est_may [] a = 0
cuantos_est_may (x:xs) a | (es_est x && edad_per x a >= 18) = 1 + cuantos_est_may xs a
                         | otherwise = cuantos_est_may xs a




