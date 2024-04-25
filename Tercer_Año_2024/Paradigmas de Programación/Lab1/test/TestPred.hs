module Main (main) where

import Test.HUnit
import System.Exit (exitFailure)
import Control.Monad (when)
import Pred (Pred, cambiar, anyDib, allDib, orP, andP)
import Dibujo (Dibujo, figura)

-- Definir un predicado de prueba y una figura de prueba
esPar :: Pred Int
esPar x = x `mod` 2 == 0

esImpar :: Pred Int
esImpar x = x `mod` 2 /= 0

figuraPrueba :: Dibujo Int
figuraPrueba = figura 2

-- Tests para cambiar
testCambiar :: Test
testCambiar = TestList [
  "cambiar esPar a figura 2 en figuraPrueba" ~: cambiar esPar (const (figura 2)) figuraPrueba ~?= figura 2,
  "cambiar esImpar a figura 2 en figuraPrueba" ~: cambiar esImpar (const (figura 2)) figuraPrueba ~?= figuraPrueba
  ]

-- Tests para anyDib
testAnyDib :: Test
testAnyDib = TestList [
  "anyDib esPar en figuraPrueba" ~: anyDib esPar figuraPrueba ~?= True,
  "anyDib esImpar en figuraPrueba" ~: anyDib esImpar figuraPrueba ~?= False
  ]

-- Tests para allDib
testAllDib :: Test
testAllDib = TestList [
  "allDib esPar en figuraPrueba" ~: allDib esPar figuraPrueba ~?= True,
  "allDib esImpar en figuraPrueba" ~: allDib esImpar figuraPrueba ~?= False
  ]

-- Tests para andP
testAndP :: Test
testAndP = TestList [
  "andP esPar esPar 2" ~: andP esPar esPar 2 ~?= True,
  "andP esPar esImpar 2" ~: andP esPar esImpar 2 ~?= False,
  "andP esPar esPar 3" ~: andP esPar esPar 3 ~?= False
  ]

-- Tests para orP
testOrP :: Test
testOrP = TestList [
  "orP esPar esPar 2" ~: orP esPar esPar 2 ~?= True,
  "orP esPar esImpar 2" ~: orP esPar esImpar 2 ~?= True,
  "orP esPar esPar 3" ~: orP esPar esPar 3 ~?= False
  ]

-- Lista de pruebas
tests :: Test
tests = TestList [testCambiar, testAnyDib, testAllDib, testAndP, testOrP]

main :: IO ()
main = do
    -- Ejecuta las pruebas y muestra los resultados
    results <- runTestTT tests
    when (errors results + failures results /= 0) exitFailure