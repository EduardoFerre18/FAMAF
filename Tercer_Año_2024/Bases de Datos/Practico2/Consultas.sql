use world;
-- Ejercicio 1)
SELECT `Name`, `Region` FROM `country` ORDER BY `name` ASC;

-- Ejercicio 2)
SELECT `Name`, `Population` FROM `city` ORDER BY `Population` DESC LIMIT 10;

-- Ejercicio 3)
SELECT `Name`, `Region`, `SurfaceArea`, `GovernmentForm` FROM `country` ORDER BY `SurfaceArea` ASC LIMIT 10;

-- Ejercicio 4)
SELECT * FROM `country` WHERE `IndepYear` IS NOT NULL; 

-- Ejercicio 5)
SELECT `Language`, `Percentage` FROM `countrylanguage` WHERE `isOfficial` = 'T'; 

-- Ejercicio 6)
UPDATE `countrylanguage` SET `Percentage` = 100.0 WHERE `CountryCode` = 'AIA';

-- Ejercicio 7)
SELECT * FROM `city` WHERE `District` = 'Córdoba' AND `CountryCode` = 'ARG'; 

-- Ejercicio 8)
DELETE FROM `city` WHERE `District` = 'Córdoba' AND `CountryCode` != 'ARG'; 

-- Ejercicio 9)
SELECT * FROM `country`;
SELECT `Name` FROM `country` WHERE `HeadOfState` LIKE '%John%';

-- Ejercicio 10)

SELECT * FROM `country` WHERE `Population` BETWEEN 35000000 AND 45000000;

-- Ejercicio 11)



