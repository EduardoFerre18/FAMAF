--Ejercicio 1

data Color = Rojo | Negro | Azul deriving Show

mismo_color :: Color -> Color -> Bool
mismo_color Rojo Rojo = True
mismo_color Negro Negro = True
mismo_color Azul Azul = True
mismo_color _ _ = False

--Ejercicio 4

data Arbol a = Hoja | Rama (Arbol a) a (Arbol a) deriving Show

arbolBusca :: Arbol (Int, String) -> Int -> Maybe String

arbolBusca Hoja _ = Nothing
arbolBusca (Rama l (clave, valor) r) k 
    | k==clave  = Just valor
    | otherwise = case (arbolBusca l k) of 
        (Just value) -> Just value
        (Nothing) -> arbolBusca r k