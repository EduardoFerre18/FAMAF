module Main (main) where

import Test.HUnit
import System.Exit (exitFailure)
import Control.Monad (when)
import Dibujo

-- Tests para las funciones
testFigura :: Test
testFigura = TestCase $ assertEqual "figura" "Figura 5" (show $ figura 5)

testRotar :: Test
testRotar = TestCase $ assertEqual "rotar" "Rotar (Figura 1)" (show $ rotar (figura 1))

testEspejar :: Test
testEspejar = TestCase $ assertEqual "espejar" "Espejar (Figura 1)" (show $ espejar (figura 1))

testRot45 :: Test
testRot45 = TestCase $ assertEqual "rot45" "Rot45 (Figura 1)" (show $ rot45 (figura 1))

testApilar :: Test
testApilar = TestCase $ assertEqual "apilar" "Apilar 2.0 3.0 (Figura 1) (Figura 2)" (show $ apilar 2.0 3.0 (figura 1) (figura 2))

testJuntar :: Test
testJuntar = TestCase $ assertEqual "juntar" "Juntar 2.0 3.0 (Figura 1) (Figura 2)" (show $ juntar 2.0 3.0 (figura 1) (figura 2))

testEncimar :: Test
testEncimar = TestCase $ assertEqual "encimar" "Encimar (Figura 1) (Figura 2)" (show $ encimar (figura 1) (figura 2))

testR180 :: Test
testR180 = TestCase $ assertEqual "r180" "Rotar (Rotar (Figura 1))" (show $ r180 (figura 1))

testR270 :: Test
testR270 = TestCase $ assertEqual "r270" "Rotar (Rotar (Rotar (Figura 1)))" (show $ r270 (figura 1))

testApilarOp :: Test
testApilarOp = TestCase $ assertEqual "(.-.)" "Apilar 1.0 1.0 (Figura 1) (Figura 2)" (show $ (figura 1) .-. (figura 2))

testJuntarOp :: Test
testJuntarOp = TestCase $ assertEqual "(///)" "Juntar 1.0 1.0 (Figura 1) (Figura 2)" (show $ (figura 1) /// (figura 2))

testEncimarOp :: Test
testEncimarOp = TestCase $ assertEqual "(^^^)" "Encimar (Figura 1) (Figura 2)" (show $ (figura 1) ^^^ (figura 2))

testCuarteto :: Test
testCuarteto = TestCase $ assertEqual "cuarteto" "Apilar 1.0 1.0 (Juntar 1.0 1.0 (Figura 1) (Figura 2)) (Juntar 1.0 1.0 (Figura 1) (Figura 2))" (show $ cuarteto (figura 1) (figura 2) (figura 1) (figura 2))

testEncimar4 :: Test
testEncimar4 = TestCase $ assertEqual "encimar4" "Encimar (Figura 1) (Encimar (Rotar (Figura 1)) (Encimar (Rotar (Rotar (Figura 1))) (Rotar (Rotar (Rotar (Figura 1))))))" (show $ encimar4 (figura 1))

testChange :: Test
testChange = TestCase $ assertEqual "change" "Figura 2" (show $ change (figura . (+1)) (figura 1))

testFoldDib :: Test
testFoldDib = TestCase $ assertEqual "foldDib" 3 (foldDib (const 1) id id id (\_ _ x y -> x + y) (\_ _ x y -> x + y) (+) (encimar (juntar 1.0 1.0 (figura 1) (figura 2)) (rotar (figura 2))))

testMapDib :: Test
testMapDib = TestCase $ assertEqual "mapDib" "Encimar (Juntar 1.0 1.0 (Figura (Figura \"1\")) (Figura (Figura \"2\"))) (Rotar (Figura (Figura \"2\")))" (show $ mapDib (figura . show) (encimar (juntar 1.0 1.0 (figura 1) (figura 2)) (rotar (figura 2))))

testFiguras :: Test
testFiguras = TestCase $ assertEqual "figuras" [1, 2, 2] (figuras (encimar (juntar 1.0 1.0 (figura 1) (figura 2)) (rotar (figura 2))))

-- Lista de pruebas
tests :: Test
tests = TestList [testFigura, testRotar, testEspejar, testRot45, testApilar, testJuntar, testEncimar, testR180, testR270, testApilarOp, testJuntarOp, testEncimarOp, testCuarteto, testEncimar4, testChange, testFoldDib, testMapDib, testFiguras]
main :: IO ()
main = do
    -- Ejecuta las pruebas y muestra los resultados
    results <- runTestTT tests
    when (errors results + failures results /= 0) exitFailure