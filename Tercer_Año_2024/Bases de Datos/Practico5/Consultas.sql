USE sakila;

-- Ejercicio 1 Cree una tabla de `directors` con las columnas: Nombre, Apellido, Número de Películas

CREATE TABLE `directors` (
    `ID` int PRIMARY KEY AUTO_INCREMENT,
    `Nombre` varchar(60) NOT NULL,
    `Apellido` varchar(60) NOT NULL,
    `NumeroDePeliculas` int NOT NULL
);

/* Ejercicio 2 El top 5 de actrices y actores de la tabla `actors` que tienen la mayor experiencia (i.e.
el mayor número de películas filmadas) son también directores de las películas en
las que participaron. Basados en esta información, inserten, utilizando una subquery
los valores correspondientes en la tabla `directors`
*/
--Consulta:
INSERT INTO `directors`
SELECT a.actor_id AS ID,
        a.first_name AS Nombre,
        a.last_name AS Apellido,
        count(fa.actor_id) as NumeroDePeliculas
FROM actor as a
JOIN film_actor as fa ON fa.actor_id = a.actor_id
GROUP BY a.actor_id
ORDER BY NumeroDePeliculas DESC
LIMIT 5;

-- Ejercicio 3
/*
Agregue una columna `premium_customer` que tendrá un valor 'T' o 'F' de acuerdo a
si el cliente es "premium" o no. Por defecto ningún cliente será premium.
*/

ALTER TABLE `customer` 
ADD COLUMN `premium_customer` VARCHAR(5) NOT NULL DEFAULT 'F';

-- Ejercicio 4
/*
Modifique la tabla customer. Marque con 'T' en la columna `premium_customer` de
los 10 clientes con mayor dinero gastado en la plataforma
*/

CREATE VIEW ten_customers_with_most_money_spent AS (
    SELECT c.customer_id
    FROM customer AS c
    JOIN payment AS p ON c.customer_id = p.customer_id
    GROUP BY c.customer_id
    ORDER BY sum(p.amount) DESC
    LIMIT 10
);

UPDATE `customer`
SET `premium_customer` = 'T'
WHERE customer_id IN (
        SELECT customer_id
        FROM ten_customers_with_most_money_spent
    );

-- Ejercicio 5

/*
Listar, ordenados por cantidad de películas (de mayor a menor), los distintos ratings
de las películas existentes (Hint: rating se refiere en este caso a la clasificación
según edad: G, PG, R, etc).
*/

SELECT film.rating
FROM film 
GROUP BY film.rating
ORDER BY count(*) DESC;

-- Ejercicio 6 ¿Cuáles fueron la primera y última fecha donde hubo pagos?

(
    SELECT payment_date 
    FROM payment
    ORDER BY payment_date ASC
    LIMIT 1
)

UNION 

(
    SELECT payment_date 
    FROM payment
    ORDER BY payment_date DESC
    LIMIT 1
);

-- Ejercicio 7 Calcule, por cada mes, el promedio de pagos (Hint: vea la manera de extraer el nombre del mes de una fecha).

USE sakila;

SELECT MONTH (payment.payment_date) as month_number, 
            DATE_FORMAT (payment_date, '%M') AS month_name,
            avg(payment.amount) as avg_mount
FROM payment
GROUP BY month_number, month_name;

-- Ejercicio 8 Listar los 10 distritos que tuvieron mayor cantidad de alquileres (con la cantidad total de alquileres)

SELECT district, count(r.staff_id) as cant_alqu
FROM rental as r
JOIN (
    SELECT a.district, a.address_id, s.staff_id
    FROM address AS a
    JOIN staff AS s ON s.address_id = a.address_id
 ) AS s_d ON s_d.staff_id = r.staff_id
 GROUP BY a.district
 ORDER BY cant_alqu DESC
 LIMIT 10;

 -- Ejercicio 9

 /*Modifique la table `inventory_id` agregando una columna `stock` que sea un número
entero y representa la cantidad de copias de una misma película que tiene
determinada tienda. El número por defecto debería ser 5 copias
*/


ALTER TABLE `inventory` 
ADD COLUMN `stock` INT NOT NULL DEFAULT 5;

-- Ejercicio 10

/*Cree un trigger `update_stock` que, cada vez que se agregue un nuevo registro a la
tabla rental, haga un update en la tabla `inventory` restando una copia al stock de la
película rentada (Hint: revisar que el rental no tiene información directa sobre la
tienda, sino sobre el cliente, que está asociado a una tienda en particular).*/

DELIMITER //

CREATE TRIGGER `update_stock` 
AFTER INSERT 
ON rental 
FOR EACH ROW
BEGIN
    UPDATE `inventory` AS i
    SET i.stock = i.stock - 1
    WHERE i.inventory_id = NEW.inventory_id;
END//

DELIMITER ;

-- Ejercicio 11
/*
Cree una tabla `fines` que tenga dos campos: `rental_id` y `amount`. El primero es
una clave foránea a la tabla rental y el segundo es un valor numérico con dos
decimales.
*/

CREATE TABLE `fines` (
    `rental_id` INT,
    `amount` DECIMAL(5,2),
    FOREIGN KEY (`rental_id`) REFERENCES `rental` (`rental_id`) 
);

-- Ejercicio 12
/*
Cree un procedimiento `check_date_and_fine` que revise la tabla `rental` y cree un
registro en la tabla `fines` por cada `rental` cuya devolución (return_date) haya
tardado más de 3 días (comparación con rental_date). El valor de la multa será el
número de días de retraso multiplicado por 1.5
*/

DELIMITER //

CREATE PROCEDURE check_date_and_fine() BEGIN
INSERT INTO `fines`
SELECT rental_id, ROUND(DATEDIFF(r.return_date, r.rental_date) * 1.5, 2) AS amount
FROM
    rental AS r
WHERE
    DATEDIFF(r.return_date, r.rental_date) > 3;
END//

DELIMITER ;

-- Prueba:
SELECT *
FROM fines;
CALL check_date_and_fine;

-- Ejercicio 13
/*Crear un rol `employee` que tenga acceso de inserción, eliminación y actualización a
la tabla `rental`.
*/

CREATE ROLE `employee`;
GRANT INSERT, UPDATE, DELETE 
ON rental to `employee`;

-- Ejercicio 14
/*
Revocar el acceso de eliminación a `employee` y crear un rol `administrator` que
tenga todos los privilegios sobre la BD `sakila`.
*/

REVOKE DELETE 
ON `rental`
from `employee`;

CREATE ROLE 'administrator';
GRANT ALL PRIVILEGES
ON 'sakila'.*
TO `administrator`;
GRANT ALL PRIVILEGES ON `sakila`.* TO `administrator`;
-- sakila.* todas las tablas, sakila.rental seria solo a la tabla rental.
--Ejercicio 15
/*
Crear dos roles de empleado. A uno asignarle los permisos de `employee` y al otro
de `administrator`.
*/

CREATE USER 'empleado1' @'localhost' IDENTIFIED BY '1234';

CREATE USER 'empleado2' @'localhost' IDENTIFIED BY '1234';

GRANT 'employee' TO 'empleado1' @'localhost';

GRANT 'administrator' TO 'empleado2' @'localhost';

SHOW GRANTS FOR 'empleado1' @'localhost';

SHOW GRANTS FOR 'empleado2' @'localhost';
