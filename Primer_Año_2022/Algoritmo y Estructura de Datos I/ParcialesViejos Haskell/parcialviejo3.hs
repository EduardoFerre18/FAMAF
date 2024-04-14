--Ejercicio 1)

data Numeracion = Cero | Uno | Dos | Tres | Cuatro deriving Show

--a)

misma_numeracion :: Numeracion->Numeracion->Bool
misma_numeracion Cero Cero = True
misma_numeracion Uno Uno = True
misma_numeracion Dos Dos = True
misma_numeracion Tres Tres = True
misma_numeracion Cuatro Cuatro = True
misma_numeracion _ _ = False

--b)

data Domino = Ficha Numeracion Numeracion

encajar :: Domino->Domino->Maybe Numeracion
encajar (Ficha n m) (Ficha x y) | misma_numeracion m x = Just y
                                | otherwise = Nothing

--Ejercicio 2)

compatibles :: [Domino]->Numeracion->[Numeracion]
compatibles [] n = []
compatibles ((Ficha x y):ds) n | misma_numeracion x n = y:(compatibles ds n)
                               | otherwise = compatibles ds n

--Ejercicio 3)

type Evento = String
data Categoria = Cumple | Reunion | Otro
data Calendario = SinEventos | Agendar Evento Categoria Calendario 

esReunion :: Categoria->Bool
esReunion Reunion = True
esReunion _ = False


listar_reuniones :: Calendario->[Evento]
listar_reuniones SinEventos = []
listar_reuniones (Agendar e c k)| esReunion c = e:(listar_reuniones k)
                                | otherwise = (listar_reuniones k)

--Ejercicio 4)

data Arbol a = Hoja | Rama (Arbol a) a (Arbol a) deriving (Show)

as::Arbol Int
as= (Rama (Rama (Rama Hoja 3 Hoja) 2 (Rama Hoja 4 Hoja)) 1 (Rama (Rama Hoja 6 Hoja) 5 (Rama Hoja 7 Hoja)))

--a_min ::Ord a =>Arbol a -> a
--a_min (Rama l x r) = min x (min (a_min l) (a_min r))

a_min :: Ord a => Arbol a -> a
a_min (Rama Hoja n1 Hoja) = n1
a_min (Rama a1 n1 Hoja) = min n1 (a_min a1)
a_min (Rama Hoja n1 a2) = min n1 (a_min a2)
a_min (Rama a1 n1 a2) = min n1 (min (a_min a1) (a_min a2))


