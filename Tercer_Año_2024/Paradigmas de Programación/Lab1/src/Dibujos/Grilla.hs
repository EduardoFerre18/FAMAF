{-# OPTIONS_GHC -Wno-name-shadowing #-}
module Dibujos.Grilla (
    grilla,
    grillaConf,
    interpTupla
) where
import Graphics.Gloss
import Dibujo (Dibujo, juntar, apilar, figura)
import FloatingPic

row :: [Dibujo a] -> Dibujo a
row [] = error "row: no puede ser vacío"
row [d] = d
row (d:ds) = juntar (fromIntegral $ length ds) 1 d (row ds)

column :: [Dibujo a] -> Dibujo a
column [] = error "column: no puede ser vacío"
column [d] = d
column (d:ds) = apilar (fromIntegral $ length ds) 1 d (column ds)

grilla :: [[Dibujo a]] -> Dibujo a
grilla = column . map row

-- Tamaño de la ventana
windowWidth :: Int
windowWidth = 800

-- Separacion entre Coordenadas
cellSize :: Float
cellSize = fromIntegral windowWidth / 8

type Tupla = (Int, Int)

-- Interprete de tipo Tupla que genera todas las coordenadas en el dibujo
interpTupla :: Output Tupla
interpTupla (a,b) x y w = pictures [translate (x - cellSize / 3) (y - cellSize / 3) $ scale 0.1 0.1 $ text (show (i, j))
                       | i <- [0..7], j <- [0..7],
                       let x = fromIntegral j * cellSize + 50
                           y = fromIntegral (7-i) * cellSize + 100]
                           
dibujoTupla :: Dibujo (Int, Int)
dibujoTupla = figura (0,0)

-- Dibujo de la Grilla
grillaConf :: Conf
grillaConf = Conf {
    name = "Grilla"
    , pic = dibujoTupla
    , bas = interpTupla
}
