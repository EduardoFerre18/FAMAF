module Pred (
  Pred,
  cambiar, anyDib, allDib, orP, andP, falla
) where

import Dibujo

type Pred a = a -> Bool

-- Dado un predicado sobre básicas, cambiar todas las que satisfacen
-- el predicado por la figura básica indicada por el segundo argumento.
cambiar :: Pred a -> (a -> Dibujo a) -> Dibujo a -> Dibujo a
cambiar predicate f = change (\a -> if predicate a then f a else figura a)


-- Alguna básica satisface el predicado.
anyDib :: Pred a -> Dibujo a -> Bool
anyDib predicate = foldDib (\a -> predicate a) id id id (\_ _ a b -> a || b) (\_ _ a b -> a || b) (\a b -> a || b)


-- Todas las básicas satisfacen el predicado.
allDib :: Pred a -> Dibujo a -> Bool
allDib predicate = foldDib (\a -> predicate a) id id id (\_ _ a b -> a && b) (\_ _ a b -> a && b) (\a b -> a && b)

-- Los dos predicados se cumplen para el elemento recibido.
andP :: Pred a -> Pred a -> Pred a
andP p1 p2 a = p1 a && p2 a

-- Algún predicado se cumple para el elemento recibido.
orP :: Pred a -> Pred a -> Pred a
orP p1 p2 a = p1 a || p2 a

falla :: Bool
falla = True