use olympics;

--Ejercicio 1
ALTER TABLE `person`
ADD COLUMN `total_medals` INT DEFAULT 0;

-- Ejercicio 2
UPDATE person p
JOIN (
    SELECT
        p.id,
        COUNT(*) AS total_medals
    FROM
        person AS p
        JOIN games_competitor AS gc ON gc.person_id = p.id
        JOIN competitor_event AS ce ON gc.id = ce.competitor_id
        JOIN medal AS m ON m.id = ce.medal_id
    WHERE
        m.medal_name != "NA"
    GROUP BY
        p.id
) AS newp ON p.id = newp.id
SET
    p.total_medals = newp.total_medals;

select
    *
from
    person
where
    person.id = 94406;

-- Ejercicio 3
SELECT
    p.full_name,
    p.id,
    m.medal_name,
    COUNT(*) AS `total_medals`
FROM
    person as p
    JOIN games_competitor AS gc ON gc.person_id = p.id
    JOIN competitor_event AS ce ON gc.id = ce.competitor_id
    JOIN medal AS m ON m.id = ce.medal_id
    JOIN person_region AS pr ON p.id = pr.person_id
    JOIN noc_region as nr ON pr.region_id = nr.id
WHERE
    NOT (m.medal_name = "NA")
    AND nr.region_name = 'Argentina'
GROUP BY
    m.medal_name,
    p.id;

-- Ejercicio 4
WITH
    deportistas_argentinos AS (
        SELECT
            p.*,
            nr.region_name
        FROM
            person AS p
            JOIN person_region AS pr ON p.id = pr.person_id
            JOIN noc_region as nr ON pr.region_id = nr.id
        WHERE
            nr.region_name = 'Argentina'
    )
SELECT
    s.sport_name,
    count(*) as total_medals
FROM
    deportistas_argentinos as d_a
    JOIN games_competitor AS gc ON gc.person_id = d_a.id
    JOIN competitor_event AS ce ON gc.id = ce.competitor_id
    JOIN medal AS m ON m.id = ce.medal_id
    JOIN event as e ON e.id = ce.event_id
    JOIN sport as s ON s.id = e.sport_id
WHERE
    NOT (m.medal_name = "NA")
GROUP BY
    s.id;

-- Ejercicio 5
CREATE VIEW
    total_de_medallas_por_pais AS (
        WITH
            deportistas_con_pais AS (
                SELECT
                    p.*,
                    nr.region_name AS pais
                FROM
                    `person` AS p
                    JOIN `person_region` AS pr ON pr.person_id = p.id
                    JOIN `noc_region` AS nr ON nr.id = pr.region_id
            )
        SELECT
            d.pais,
            sum(d.total_medals) AS `total_medals`
        FROM
            deportistas_con_pais AS d
        GROUP BY
            d.pais
    );

-- Ejercicio 6
(
    SELECT
        *
    FROM
        total_de_medallas_por_pais
    ORDER BY
        `total_medals` DESC
    LIMIT
        1
)
UNION
(
    SELECT
        *
    FROM
        total_de_medallas_por_pais
    ORDER BY
        `total_medals` ASC
    LIMIT
        1
);

-- Ejercicio 7
CREATE TRIGGER increase_number_of_medals AFTER INSERT ON `competitor_event` FOR EACH ROW BEGIN
UPDATE `person` AS p
JOIN `games_competitor` AS gc ON p.id = gc.person_id
SET
    p.total_medals = p.total_medals + 1
WHERE
    (gc.person_id = NEW.competitor_id)
    AND (NOT NEW.medal_id = 4);

END;

CREATE TRIGGER decrease_number_of_medals AFTER DELETE ON `competitor_event` FOR EACH ROW BEGIN
UPDATE `person` AS p
JOIN `games_competitor` AS gc ON p.id = gc.person_id
SET
    p.total_medals = p.total_medals - 1
WHERE
    (gc.person_id = OLD.competitor_id)
    AND (NOT OLD.medal_id = 4);

--Ejercicio 8
CREATE PROCEDURE add_new_medalists (
    in event_id INT,
    in g_id INT,
    in s_id INT,
    in b_id INT
) BEGIN
INSERT INTO
    `competitor_event` (`event_id`, `competitor_id`, `medal_id`)
VALUES
    (event_id, g_id, 1),
    (event_id, s_id, 2),
    (event_id, b_id, 3);

END;

-- Ejercicio 9
CREATE ROLE `organizer`;

GRANT DELETE ON `games` to `organizer`;

GRANT
UPDATE (`games_name`) ON `games` TO `organizer`;



/**/

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