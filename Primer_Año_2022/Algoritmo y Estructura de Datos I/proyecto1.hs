--Ejercicio 1

--a)

esCero :: Int->Bool
esCero x = (x == 0)

--b)

--esPositivo Eq a => :: Int->Bool
--esPositivo x = (x > 0)

--c)

esVocal :: Char->Bool
esVocal x = (x=='a')||(x=='e')||(x=='i')||(x=='o')||(x=='u')

--Ejercicio 2

--a)

paraTodo :: [Bool]->Bool
paraTodo [] = True
paraTodo (x:xs) = x && paraTodo xs

--b)

sumatoria :: [Int]->Int
sumatoria [] = 0
sumatoria (x:xs)= x + sumatoria xs

--c)

productoria :: [Int]->Int
productoria [] = 1
productoria (x:xs) = x * productoria xs

--d)

factorial :: Int->Int
factorial 0 = 1
factorial n = n * factorial (n-1)

--e)

promedio :: [Int]->Int
promedio (x:xs) = div (sumatoria (x:xs)) (length (x:xs))

--Ejercicio 3

pertenece :: Int->[Int]->Bool
pertenece y [] = False
pertenece y (x:xs)= (y==x) || (pertenece y xs)

--Ejercicio 4

--a)

paraTodo' :: [a]->(a->Bool)->Bool
paraTodo' [] f = True
paraTodo' (x:xs) f = f x && paraTodo' xs f

--b)

existe' :: [a]->(a->Bool)->Bool
existe' [] f = False
existe' (x:xs) f = f x || existe' xs f

--c)

sumatoria' :: [a]->(a->Int)->Int
sumatoria' [] f = 0
sumatoria' (x:xs) f = f x + sumatoria' xs f

--d)

productoria' :: [a]->(a->Int)->Int
productoria' [] f = 1
productoria' (x:xs) f = f x * productoria' xs f

--Ejercicio 5

paraTodo5 :: [Bool]->Bool
paraTodo5 x = paraTodo' x (==True) 

--Ejercicio 6

--a)

todosPares :: [Int]->Bool
todosPares xs= paraTodo' xs (even) 

--b)

--Funcion Auxiliar
esMultiplo :: Int->Int->Bool
esMultiplo y x = mod x y == 0

hayMultiplo :: Int->[Int]->Bool
hayMultiplo x xs = existe' xs (esMultiplo x)

--c)

sumaCuadrados :: Int->Int
sumaCuadrados x = sumatoria' [0..x-1] ( ^2)

--d)

factorial' :: Int->Int
factorial' x = productoria' [1..x] (1*)

--e)

--FuncionAuxiliar

esPar :: [Int]->[Int]
esPar []=[]
esPar (x:xs)| even x = x:(esPar xs) 
            | otherwise = esPar xs

multiplicaPares :: [Int]->Int
multiplicaPares xs = productoria' (esPar xs) (1*)

--Ejercicio 7

--a) 
-- Map: Una función Map, dada una lista devuelve otra, cuyos elementos son los que se obtienen de aplicarles una funcion a cada elemento de la primera en el mismo orden y conlas mismas repeticiones.
-- Filter: Una funcion Filter toma una lista y un predicado y devuelve otra lista con los elementos de la primera que cumplan el predicado, en el mismo orden y con las mismas repeticiones.

--b) La expresión equivale a [2,-3,7,3,-7], es decir a cada elemento lo reemplaza por su sucesor.

--c) La expresión equivale a [1,6,2], es decir filtra los elementos de la lista que son positivos.

--Ejercicio 8

--a)

duplica :: [Int]->[Int]
duplica [] = []
duplica (x:xs)= (x*2):duplica xs

--b)

duplicaMap :: [Int]->[Int]
duplicaMap xs = map ( *2) xs

--Ejercicio 9

--a)

soloPares :: [Int]->[Int]
soloPares []=[]
soloPares (x:xs)| even x = x:(soloPares xs) 
                | otherwise = soloPares xs
                
--b)

soloParesFilter :: [Int]->[Int]
soloParesFilter xs = filter even xs

--c)

multiplicaPares' :: [Int]->Int
multiplicaPares' xs = productoria' (filter even xs) (1*)

--Ejercicio 10)

--a)

primIgualesA :: Eq a => a->[a]->[a]
primIgualesA y [] = []
primIgualesA y (x:xs)|(y==x) = x:(primIgualesA y xs)
                     |otherwise = []
                     
--b)

primIgualesAtake :: Eq a => a->[a]->[a]
primIgualesAtake y xs = takeWhile ( == y) xs

--Ejercicio 11

--a)

primIguales :: Eq a => [a]->[a]
primIguales [] = []
primIguales (x:xs)| x == xs!!0 = x:(primIguales xs)
                  | otherwise = [x] 
                  
--b)

primIguales' :: Eq a => [a]->[a] 
primIguales' xs = primIgualesAtake (xs!!0) (xs) 

--Ejercicio 12

cuantGen :: (b->b->b)->b->[a]->(a->b)->b
cuantGen op z [] t = z 
cuantGen op z (x:xs) t = op (t x) (cuantGen op z xs t)

paraTodo'' :: [Bool]->Bool
paraTodo'' xs = cuantGen (&&) (True) (xs) (id)

existe'' :: [Bool]->Bool
existe'' xs = cuantGen (||) (False) (xs) (id)

sumatoria'' :: [Int]->Int
sumatoria'' xs = cuantGen (+) (0) (xs) (id)

productoria'' :: [Int]->Int
productoria'' xs = cuantGen (*) (1) (xs) (id)  





