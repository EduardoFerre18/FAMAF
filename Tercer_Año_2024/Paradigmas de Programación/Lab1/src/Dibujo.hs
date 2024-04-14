module Dibujo 
  ( encimar,
    figura,
    apilar,
    juntar, 
    rot45, 
    rotar, 
    espejar,
    figuras,
    (^^^),
    (.-.),
    (///),
    r90,
    r180,
    r270,
    encimar4,
    cuarteto,
    ciclar,
    mapDib,
    change,
    foldDib,
    Dibujo
   ) where


-- nuestro lenguaje 
data Dibujo a 
  = Figura a
  | Rotar (Dibujo a)
  | Espejar (Dibujo a)
  | Rot45 (Dibujo a)
  | Apilar Float Float (Dibujo a) (Dibujo a)
  | Juntar Float Float (Dibujo a) (Dibujo a)
  | Encimar (Dibujo a) (Dibujo a)
  deriving (Eq, Show)

-- combinadores
infixr 6 ^^^

infixr 7 .-.

infixr 8 ///

-- Composición n-veces de una función con sí misma. Componer 0 veces
-- es la función identidad, componer 1 vez es aplicar la función 1 vez, etc.
-- Componer negativamente es un error!
comp :: Int -> (a -> a) -> a -> a
comp n f a 
    | n < 0     = error "Componer negativamente es un error!"
    | n == 0    = a
    | otherwise = f (comp (n - 1) f a)
  


-- Funciones constructoras
figura :: a -> Dibujo a
figura = Figura 

encimar :: Dibujo a -> Dibujo a -> Dibujo a
encimar = Encimar

apilar :: Float -> Float -> Dibujo a -> Dibujo a -> Dibujo a
apilar = Apilar

juntar  :: Float -> Float -> Dibujo a -> Dibujo a -> Dibujo a
juntar = Juntar

rot45 :: Dibujo a -> Dibujo a
rot45 = Rot45

rotar :: Dibujo a -> Dibujo a
rotar = Rotar


espejar :: Dibujo a -> Dibujo a
espejar = Espejar

-- Superpone un dibujo con otro.
(^^^) :: Dibujo a -> Dibujo a -> Dibujo a
(^^^) = Encimar 

-- Pone el primer dibujo arriba del segundo, ambos ocupan el mismo espacio.
(.-.) :: Dibujo a -> Dibujo a -> Dibujo a
(.-.) =  Apilar 1 1 

-- Pone un dibujo al lado del otro, ambos ocupan el mismo espacio.
(///) :: Dibujo a -> Dibujo a -> Dibujo a
(///) = Juntar 1 1

-- rotaciones
r90 :: Dibujo a -> Dibujo a
r90 = comp 2 rot45

r180 :: Dibujo a -> Dibujo a
r180 = comp 2 rotar 

r270 :: Dibujo a -> Dibujo a
r270 = comp 3 rotar 

-- una figura repetida con las cuatro rotaciones, superimpuestas.
encimar4 :: Dibujo a -> Dibujo a
encimar4 p = p ^^^ rotar p ^^^ r180 p ^^^ r270 p

-- cuatro figuras en un cuadrante.
cuarteto :: Dibujo a -> Dibujo a -> Dibujo a -> Dibujo a -> Dibujo a
cuarteto p q r s = (p /// q) .-. (r /// s)  

-- un cuarteto donde se repite la imagen, rotada (¡No confundir con encimar4!)
ciclar :: Dibujo a -> Dibujo a
ciclar p = cuarteto p (rotar p) (r180 p) (r270 p)

-- map para nuestro lenguaje
mapDib :: (a -> b) -> Dibujo a -> Dibujo b
mapDib f (Figura a) = Figura (f a)
mapDib f (Rotar d) = Rotar (mapDib f d)
mapDib f (Espejar d) = Espejar (mapDib f d)
mapDib f (Rot45 d) = Rot45 (mapDib f d)
mapDib f (Apilar x y d1 d2) = Apilar x y (mapDib f d1) (mapDib f d2)
mapDib f (Juntar x y d1 d2) = Juntar x y (mapDib f d1) (mapDib f d2)
mapDib f (Encimar d1 d2) = Encimar (mapDib f d1) (mapDib f d2)
-- verificar que las operaciones satisfagan
-- 1. map figura = id
-- 2. map (g . f) = mapDib g . mapDib f

-- Cambiar todas las básicas de acuerdo a la función.
change :: (a -> Dibujo b) -> Dibujo a -> Dibujo b
change f (Figura a) = f a
change f (Rotar d) = Rotar (change f d)
change f (Espejar d) = Espejar (change f d)
change f (Rot45 d) = Rot45 (change f d)
change f (Apilar x y d1 d2) = Apilar x y (change f d1) (change f d2)
change f (Juntar x y d1 d2) = Juntar x y (change f d1) (change f d2)
change f (Encimar d1 d2) = Encimar (change f d1) (change f d2)

-- Principio de recursión para Dibujos.
foldDib ::
  (a -> b) ->
  (b -> b) ->
  (b -> b) ->
  (b -> b) ->
  (Float -> Float -> b -> b -> b) ->
  (Float -> Float -> b -> b -> b) ->
  (b -> b -> b) ->
  Dibujo a ->
  b
foldDib fFigura fRotar fEspejar fRot45 fApilar fJuntar fEncimar = fun
 where
    fun (Figura a) = fFigura a
    fun (Rotar d) = fRotar (fun d)
    fun (Espejar d) = fEspejar (fun d)
    fun (Rot45 d) = fRot45 (fun d)
    fun (Apilar x y d1 d2) = fApilar x y (fun d1) (fun d2)
    fun (Juntar x y d1 d2) = fJuntar x y (fun d1) (fun d2)
    fun (Encimar d1 d2) = fEncimar (fun d1) (fun d2)

-- Extrae todas las figuras básicas de un dibujo.
figuras :: Dibujo a -> [a]
figuras = foldDib
  (\x -> [x])  -- Para el constructor Figura, devuelvo una lista con la figura.
  id           -- Para Rotar, Espejar, Rot45, y Encimar, no hace nada.
  id           -- Para Rotar, Espejar, Rot45, y Encimar, no hace nada.
  id           -- Para Rotar, Espejar, Rot45, y Encimar, no hace nada.
  (\_ _ l1 l2 -> l1 ++ l2)  -- Para Apilar, concateno las listas de figuras de ambos dibujos.
  (\_ _ l1 l2 -> l1 ++ l2)  -- Para Juntar, concateno las listas de figuras de ambos dibujos.
  (++)         -- Para Encimar, concateno las listas de figuras.


