--Parcial 1 - 2022 - Tema B
--Ejercicio 1 a
data Palo = Espada | Basto | Oro | Copa  deriving Show

mismo_palo :: Palo -> Palo -> Bool
mismo_palo Espada Espada = True
mismo_palo Basto Basto = True
mismo_palo Oro Oro = True
mismo_palo Copa Copa = True
mismo_palo _ _ = False 

--Ejercicio 1b
data Figura = Uno | Dos | Tres | Cuatro | Cinco | Seis | Siete | Sota | Caballo | Rey deriving Show

valor_figura :: Figura -> Int
valor_figura Uno = 1
valor_figura Dos = 2
valor_figura Tres = 3
valor_figura Cuatro = 4
valor_figura Cinco = 5
valor_figura Seis = 6 
valor_figura Siete = 7
valor_figura Sota = 8
valor_figura Caballo = 9
valor_figura Rey = 10

data Carta = Naipe Figura Palo deriving Show

suma_cartas :: Carta -> Carta -> Maybe Int
suma_cartas (Naipe a b) (Naipe c d) | mismo_palo b d = Just (valor_figura a + valor_figura c)
                                    | otherwise = Nothing


compatibles :: Carta->[Carta]->[Figura] 
compatibles c [] = []
compatibles (Naipe a b) ((Naipe c d):cs) |(mismo_palo b d) && ((suma_cartas (Naipe a b) (Naipe c d))< Just 15) = c:(compatibles (Naipe a b) cs)
                               |otherwise = compatibles (Naipe a b) cs

--Ejercicio 3

type Duracion = Int 
type Nombre = String 
data Cancion = Tema Nombre Duracion deriving Show
data Estado = Escuchado | NoEscuchado deriving Show
data PlayList = EnLista Cancion Estado PlayList | Vacia deriving Show

esEscuchado :: PlayList->Bool
esEscuchado (EnLista c Escuchado p) = True
esEscuchado (EnLista c NoEscuchado p) = False

tiempo_reproduccion :: PlayList->Int
tiempo_reproduccion Vacia = 0
tiempo_reproduccion (EnLista (Tema n d) e p) | esEscuchado (EnLista (Tema n d) e p) = d + tiempo_reproduccion p
                                             |otherwise = tiempo_reproduccion p

--Ejercicio 4)

data Arbol a = Hoja | Rama (Arbol a) a (Arbol a) deriving (Show)

as::Arbol Int
as= (Rama (Rama (Rama Hoja 3 Hoja) 2 (Rama Hoja 4 Hoja)) 1 (Rama (Rama Hoja 6 Hoja) 5 (Rama Hoja 7 Hoja)))

a_podar :: Arbol a -> Arbol a
a_podar Hoja = Hoja
a_podar (Rama a x b) = 

