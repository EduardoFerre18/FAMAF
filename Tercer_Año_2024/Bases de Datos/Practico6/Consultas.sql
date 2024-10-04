use classicmodels;

-- Ejercicio 1 Devuelva la oficina con mayor número de empleados.

SELECT o.*, COUNT(o.officeCode) AS cant_empl 
FROM offices AS o
JOIN employees AS e ON e.officeCode = o.officeCode
GROUP BY o.officeCode
ORDER BY cant_empl DESC
LIMIT 1;

-- Ejercicio 2 ¿Cuál es el promedio de órdenes hechas por oficina?, ¿Qué oficina vendió la mayor cantidad de productos?

-- 2.1
SELECT avg(all_offices.cant_orders) AS avg_for_office
FROM
    (
        SELECT o.officeCode, o.city, count(o.officeCode) AS cant_orders
        FROM offices AS o
        JOIN employees AS e ON o.officeCode = e.officeCode
        JOIN customers AS c ON e.employeeNumber = c.salesRepEmployeeNumber
        JOIN orders ON orders.customerNumber = c.customerNumber
        GROUP BY o.officeCode
    ) AS all_offices;

-- 2.2

SELECT
    o.officeCode,
    o.city,
    count(o.officeCode) AS cant_orders
FROM
    offices AS o
    JOIN employees AS e ON o.officeCode = e.officeCode
    JOIN customers AS c ON e.employeeNumber = c.salesRepEmployeeNumber
    JOIN orders ON orders.customerNumber = c.customerNumber
GROUP BY
    o.officeCode
ORDER BY
    cant_orders DESC
LIMIT
    1;

-- Ejercicio 3 Devolver el valor promedio, máximo y mínimo de pagos que se hacen por mes.
SELECT MONTH (p.paymentDate) as month_number, 
            DATE_FORMAT (p.paymentDate, '%M') AS month_name,
            avg(p.amount) as avg_mount,
            max(p.amount) as max_mount,
            min(p.amount) as min_mount
FROM payments as p
GROUP BY month_number, month_name;


-- Ejercicio 4
/*Crear un procedimiento "Update Credit" en donde se modifique el límite de crédito de
un cliente con un valor pasado por parámetro
*/

CREATE PROCEDURE Update_Credit(
    in customer_number int(11),
    in new_limit decimal(10, 2)
)
UPDATE `customer` as c
SET c.creditLimit = new_limit
WHERE c.customerName = customer_number;

-- Test

SELECT
    c.customerNumber,
    c.creditLimit
FROM
    customers AS c
WHERE
    c.customerNumber = 99;

CALL update_credit(103, 10.00);

-- Ejercicio 5

/*Cree una vista "Premium Customers" que devuelva el top 10 de clientes que más
dinero han gastado en la plataforma. La vista deberá devolver el nombre del cliente,
la ciudad y el total gastado por ese cliente en la plataforma.
*/

CREATE VIEW PremiumCustomers AS (
    SELECT c.customerNumber, c.customerName, sum(p.amount) AS total_spent
    FROM customers AS c
    JOIN payments AS p ON c.customerNumber = p.customerNumber
    GROUP BY c.customerNumber
    ORDER BY total_spent DESC
    LIMIT 10
);

-- Prueba

SELECT * FROM PremiumCustomers;
-- Ejercicio 6
/*
Cree una función "employee of the month" que tome un mes y un año y devuelve el
empleado (nombre y apellido) cuyos clientes hayan efectuado la mayor cantidad de
órdenes en ese mes.
*/

DELIMITER //

CREATE FUNCTION employe_of_the_month (mes int, anio int) RETURNS VARCHAR(100) READS SQL DATA BEGIN DECLARE employee_name VARCHAR(100);
    SELECT CONCAT(e.firstName, ' ', e.lastName) INTO employee_name
    FROM employees as e
    JOIN customers as c ON c.salesRepEmployeeNumber = e.employeeNumber
    JOIN orders as o ON o.customerNumber = c.customerNumber
    WHERE
        YEAR(o.requiredDate) = anio
        ANd MONTH(o.requiredDate) = mes
    GROUP BY e.employeeNumber
    ORDER BY COUNT(*) DESC
    LIMIT 1;

    RETURN employee_name;
END//

DELIMITER ;

--Ejercicio 7 

/*Crear una nueva tabla "Product Refillment". Deberá tener una relación varios a uno
con "products" y los campos: `refillmentID`, `productCode`, `orderDate`, `quantity`.
*/

CREATE TABLE `productRefillment` (
    `refillmentID` int PRIMARY KEY AUTO_INCREMENT,
    `productCode` varchar(15) NOT NULL,
    `orderDate` date NOT NULL,
    `quantity` int,
    FOREIGN KEY (`productCode`) REFERENCES `products` (`productCode`) 
);


--Ejercicio 8

/*
Definir un trigger "Restock Product" que esté pendiente de los cambios efectuados
en `orderdetails` y cada vez que se agregue una nueva orden revise la cantidad de
productos pedidos (`quantityOrdered`) y compare con la cantidad en stock
(`quantityInStock`) y si es menor a 10 genere un pedido en la tabla "Product
Refillment" por 10 nuevos productos
*/
DELIMITER //

CREATE TRIGGER `restockProduct` AFTER INSERT ON `orderdetails` FOR EACH ROW BEGIN DECLARE currentStock int;
    SELECT p.quantityInStock INTO currentStock 
    FROM products as p
    WHERE p.productCode = NEW.productCode;
    IF (currentStock - NEW.quantityOrdered) < 10 THEN
        INSERT INTO `product_refillment` (`productCode`, `orderDate`, `quantity`)
        VALUES (NEW.productCode, CURDATE(), 10);
    END IF;
END//
DELIMITER ;

--TEST
select * from productrefillment;
insert into orderdetails values (10205, 'S12_1099', 60, 12, 3); # test trigger (should add refillment)
insert into orderdetails values (10204, 'S12_1099', 12, 12, 3); # test trigger (should not add refillment)

-- Ejercicio 9

/*
Crear un rol "Empleado" en la BD que establezca accesos de lectura a todas las
tablas y accesos de creación de vistas.
*/

CREATE ROLE `Empleado`;
GRANT SELECT 
ON classicmodels.* to `Empleado`;
