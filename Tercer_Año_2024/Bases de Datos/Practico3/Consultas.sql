USE world;

-- Parte I - Consultas

-- 1.
SELECT 
	city.Name,
    country.Name,
    country.Region,
    country.GovernmentForm
FROM city
JOIN country ON city.CountryCode = country.Code
ORDER BY city.Population DESC
LIMIT 10;

-- 2.
SELECT 
	country.Name,
    city.Name,
    country.Population
FROM country
LEFT JOIN city ON country.Capital = city.ID
ORDER BY country.Population ASC
LIMIT 10; 

-- 3.
SELECT 
	country.Name,
    country.Continent,
    countrylanguage.Language
FROM country
JOIN countrylanguage ON country.Code = countrylanguage.CountryCode;

-- 4.
SELECT 
	country.Name,
    city.Name,
    country.SurfaceArea
FROM country
LEFT JOIN city ON country.Capital = city.ID
ORDER BY country.SurfaceArea DESC
LIMIT 20;

-- 5.
SELECT 
	city.Name,
    countrylanguage.Language,
    countrylanguage.Percentage
FROM city
JOIN countrylanguage ON (countrylanguage.CountryCode = city.CountryCode AND countrylanguage.IsOfficial = 'T')
ORDER BY city.Population ASC; 

-- 6.
(SELECT Name, Population FROM country WHERE Population >= 100
ORDER BY country.Population DESC
LIMIT 10
)
UNION
(SELECT Name, Population FROM country WHERE Population >= 100
ORDER BY country.Population ASC
LIMIT 10
);

-- 7.
SELECT DISTINCT country.Name
FROM country
JOIN countrylanguage ON country.Code = countrylanguage.CountryCode
	AND countrylanguage.IsOfficial = 'T'
	AND (
		countrylanguage.Language = "English"
		OR countrylanguage.Language = "France"
	);
    
-- 8.

(
SELECT DISTINCT
	country.Name
FROM country
JOIN countrylanguage ON country.Code = countrylanguage.CountryCode AND countrylanguage.Language = "English"
)
EXCEPT 
(
SELECT DISTINCT country.Name
FROM country
JOIN countrylanguage ON country.Code = countrylanguage.CountryCode AND countrylanguage.Language = "Spanish"
);

-- Parte II - Preguntas
-- 1. Si, ambas consultan devuelven los mismos resultados ya que la única diferencia es en la condición, donde ON del JOIN y el WHERE, en este caso son equivalentes.

-- 2

SELECT city.Name, country.Name
FROM city
INNER JOIN country ON city.CountryCode = country.Code AND country.Name =
'Argentina';
-- Aparecen los nulls

SELECT city.Name, country.Name
FROM city
INNER JOIN country ON city.CountryCode = country.Code
WHERE country.Name = 'Argentina';
-- Borra los nulls