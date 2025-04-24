USE world;

--Ejercicio 1 Listar el nombre de la ciudad y el nombre del país de todas las ciudades que pertenezcan a países con una población menor a 10000 habitantes.

SELECT city.Name, country.Name, country.Population 
FROM city
JOIN country on country.Code = city.CountryCode
WHERE city.CountryCode in (
    SELECT Code
    FROM country as c
    WHERE c.Population < 10000); 


--Ejercicio 2 Listar todas aquellas ciudades cuya población sea mayor que la población promedio entre todas las ciudades.

SELECT *
FROM city
WHERE city.Population > (
    SELECT avg(city.Population)
    FROM city
);

--Ejercicio 3 Listar todas aquellas ciudades no asiáticas cuya población sea igual o mayor a la población total de algún país de Asia.

SELECT *
FROM city
JOIN country ON city.CountryCode = country.Code
WHERE country.Continent != 'Asia'
  AND city.Population >= SOME (
    SELECT country.Population
    FROM country
    WHERE Continent = 'Asia'
);


--Ejercicio 4 Listar aquellos países junto a sus idiomas no oficiales, que superen en porcentaje de hablantes a cada uno de los idiomas oficiales del país.

SELECT country.Name, cl.Language
FROM country
JOIN countrylanguage as cl ON country.code = cl.CountryCode
WHERE cl.IsOfficial = 'F' 
AND cl.Percentage > ALL (
    SELECT cl.Percentage
    FROM countrylanguage 
    WHERE countrylanguage.CountryCode = country.code AND countrylanguage.IsOfficial = 'T'
);


-- Ejerciio 5. Listar (sin duplicados) aquellas regiones que tengan países con una superficie menor a 1000 km2 y exista (en el país) al menos una ciudad con más de 100000 habitantes.
--(Hint: Esto puede resolverse con o sin una subquery, intenten encontrar ambas respuestas).

--Con una subquery
SELECT DISTINCT country.Region
FROM country
WHERE country.SurfaceArea < 1000
AND EXISTS (
    SELECT * 
    FROM city
    WHERE city.CountryCode = country.Code AND city.Population > 10000 
);

--Sin una subquery

SELECT DISTINCT country.Region
FROM country
JOIN city ON country.Code = city.CountryCode 
WHERE (city.Population > 10000) 
AND (country.SurfaceArea < 1000);

-- Ejercicio 6. Listar el nombre de cada país con la cantidad de habitantes de su ciudad más poblada. 
--(Hint: Hay dos maneras de llegar al mismo resultado. Usando consultas escalares o usando agrupaciones, encontrar ambas).

--Con consultas escalares

SELECT country.Name, (
    SELECT DISTINCT city.Population
    FROM city 
    WHERE city.CountryCode = country.Code
    AND city.Population >= ALL (
        SELECT city.Population
        FROM city
        WHERE city.CountryCode = country.Code
    ) 
) as MaxPopulation
FROM country;

--Usando agrupaciones

SELECT country.Name, MAX(city.Population) AS MaxPopulation
FROM country
LEFT JOIN city ON city.CountryCode = country.Code
GROUP BY country.Name;


-- Ejercicio 7. Listar aquellos países y sus lenguajes no oficiales cuyo porcentaje de hablantes sea mayor al promedio de hablantes de los lenguajes oficiales.

SELECT c.Name, cl.Language 
FROM country as c
LEFT JOIN countrylanguage as cl ON c.Code = cl.CountryCode
WHERE cl.IsOfficial != 'T'
AND cl.Percentage > ALL (
    SELECT avg(cl2.Percentage)
    FROM countrylanguage as cl2
    WHERE cl2.CountryCode = c.Code 
    AND cl2.IsOfficial = 'T' 
); 

--Ejercicio 8. Listar la cantidad de habitantes por continente ordenado en forma descendente.

SELECT DISTINCT c1.Continent, (
    SELECT sum(c2.Population)
    FROM country as c2
    WHERE c1.Continent = c2.Continent
) as TotalPolutation
FROM country as c1
ORDER BY TotalPolutation DESC;

-- Con GROUP BY

SELECT country.Continent, SUM(country.Population) as TotalPolutation
FROM country
GROUP BY country.Continent
ORDER BY TotalPolutation DESC;



--Ejercicio 9. Listar el promedio de esperanza de vida (LifeExpectancy) por continente con una esperanza de vida entre 40 y 70 años.

SELECT country.Continent, AVG(country.LifeExpectancy) as LifeExpectancy
FROM country
WHERE LifeExpectancy >= 40
AND LifeExpectancy <= 70
GROUP BY country.Continent;


--Ejercicio 10. Listar la cantidad máxima, mínima, promedio y suma de habitantes por continente.

SELECT country.Continent, 
        MAX(country.Population) as MaxPopulation, 
        MIN(country.Population) as MinPopulation, 
        AVG(country.Population) as AvgPopulation, 
        SUM(country.Population) as SumPopulation
FROM country
GROUP BY country.Continent
