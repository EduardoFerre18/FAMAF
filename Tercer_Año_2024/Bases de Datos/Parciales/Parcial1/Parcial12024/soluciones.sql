USE airbnb_like_db;

-- Ejercicio 1

SELECT p.*, COUNT(*) as cant_reviews
FROM `properties` p
JOIN `reviews` r ON r.property_id = p.id
WHERE YEAR(r.created_at) = 2024
GROUP BY p.id
ORDER BY cant_reviews DESC
LIMIT 7;

-- Ejercicio 2

SELECT p.*, SUM(DATEDIFF(b.check_out, b.check_in) * p.price_per_night) AS total_income
FROM `properties` p
JOIN `bookings` b ON b.property_id = p.id
GROUP BY p.id
ORDER BY total_income DESC;


-- Ejercicio 3

SELECT u.*, SUM(p.amount) as total_payment
FROM `users` u 
JOIN `payments` p ON u.id = p.user_id 
GROUP BY u.id 
ORDER BY total_payment DESC
LIMIT 10;

-- Ejercicio 4

DELIMITER //
CREATE TRIGGER `notify_host_after_booking`
AFTER INSERT
ON bookings
FOR EACH ROW
BEGIN
    INSERT INTO messages (sender_id, receiver_id, message)
    VALUES (NEW.user_id, 
            (SELECT p.user_id 
                FROM `properties` p 
                WHERE p.id = NEW.property_id), 
            "Nueva reserva");
END//
DELIMITER ;

-- Ejercicio 5

DELIMITER // 
CREATE PROCEDURE add_new_booking (
    in property_id INT,
    in user_id INT,
    in check_in DATE,
    in check_out DATE
) BEGIN
    DECLARE property_availability INT;
    SELECT COUNT(*) INTO property_availability
    FROM `property_availability` pa
    WHERE pa.property_id = property_id
    AND pa.date BETWEEN check_in AND check_out
    AND pa.status = "available";

    IF property_availability = DATEDIFF(check_out, check_in) THEN
        INSERT INTO bookings (property_id, user_id, check_in, check_out)
        VALUES (property_id, user_id, check_in, check_out);
    END IF;

END//
DELIMITER ; 

-- Ejercicio 6

CREATE ROLE `admin`;
GRANT CREATE ON `properties` to `admin`; 
GRANT UPDATE (`status`) ON `property_availability` TO `admin`;

-- Ejercicio 7

/*
No contradice la propiedad porque la transacción se completa con el COMMIT, esto implica que los cambios en la tabla reviews
se vuelven permanentes. Por lo tanto aunque los datos de la tabla reviews fueron cargados al comienzo,
los cambios realizados en la transacción se mantienen en la base de datos.

*/
