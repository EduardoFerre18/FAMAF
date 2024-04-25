module Dibujos.Escher where
import Dibujo
import FloatingPic
import qualified Graphics.Gloss.Data.Point.Arithmetic as V
import Graphics.Gloss (line, blank)

-- Supongamos que eligen.
type Escher = Bool

interpEscher :: Output Escher
interpEscher True x y w = line $ map (x V.+) [(0,0), y V.+ w, w, (0,0)]
interpEscher False _ _ _ = blank

-- El dibujo u.
dibujoU :: Dibujo Escher -> Dibujo Escher
dibujoU p = cuarteto (rotar p) p (r180 p) (r270 p)

-- El dibujo t.
dibujoT :: Dibujo Escher -> Dibujo Escher
dibujoT p = p .-. (r270 p)

-- Esquina con nivel de detalle en base a la figura p.
esquina :: Int -> Dibujo Escher -> Dibujo Escher
esquina n p 
          | n > 1 = cuarteto (esquina (n-1) p) (lado (n-1) p) (rotar (lado (n-1) p)) (dibujoU p)
          | otherwise = cuarteto (figura False) (figura False)  (figura False) (dibujoU p)

-- Lado con nivel de detalle.
lado :: Int -> Dibujo Escher -> Dibujo Escher
lado n p
       | n > 1 = cuarteto (lado (n-1) p) (lado (n-1) p) (rotar p) p
       | otherwise = cuarteto (figura False) (figura False) (rotar(dibujoT p)) (dibujoT p)

-- Por suerte no tenemos que poner el tipo!
noneto p q r s t u v w x =
  apilar
    1
    2
    (juntar 1 2 p (juntar 1 1 q r))
    (apilar 1 1 (juntar 1 2 s (juntar 1 1 t u)) (juntar 1 2 v (juntar 1 1 w x)))

-- El dibujo de Escher:
escher :: Int -> Escher -> Dibujo Escher
escher n f = noneto p q r s t u v w x
  where
    p = esquina n (figura f)
    q = lado n (figura f)
    r = rotar x
    s = rotar q
    t = dibujoU (figura f)
    u = rotar w
    v = rotar p
    w = rotar s
    x = rotar v

escherConf :: Conf
escherConf = Conf {
    name = "Escher"
    , pic = escher 10 True
    , bas = interpEscher
}
