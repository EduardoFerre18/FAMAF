-- Ejercicio 1)
CREATE DATABASE world;
use world;

-- Ejercicio 2)

-- Country table
CREATE TABLE `country`(
	`Code` varchar(10) NOT NULL ,
    `Name` varchar(50),
    `Continent` varchar(50),
    `Region` varchar(50),
    `SurfaceArea` double,
    `IndepYear` int, 
	`Population` int,
	`LifeExpectancy` int,
	`GNP` int,
	`GNPOld` int,
	`LocalName` varchar(50),
	`GovernmentForm` varchar(50),
	`HeadOfState` varchar(50),
	`Capital` int,
	`Code2` varchar(10),
	PRIMARY KEY (`Code`)
);

-- City table
CREATE TABLE `city` (
  `ID` int NOT NULL AUTO_INCREMENT,
  `Name` varchar(50),
  `CountryCode` varchar(10),
  `District` varchar(20),
  `Population` int,
  PRIMARY KEY (`ID`),
  FOREIGN KEY (`CountryCode`) REFERENCES `country` (`Code`)
);

-- Country language table
CREATE TABLE `countrylanguage` (
  `CountryCode` varchar(10),
  `Language` varchar(50),
  `IsOfficial` varchar(50),
  `Percentage` decimal(4,1),
  PRIMARY KEY (`CountryCode`,`Language`),
  FOREIGN KEY (`CountryCode`) REFERENCES `country` (`Code`)
);

-- Ejercicio 3) Se importo el archivo world-data.sql

-- Ejercicio 4)

CREATE TABLE `continent` (
	`Name` varchar(52),
    `Area` int,
    `LandMassPercentage` decimal(4,1),
    `MostPopulatedCity` varchar(60),
	PRIMARY KEY (`Name`)
); 

-- Ejercicio 5)

INSERT INTO `continent` (`Name`, `Area`, `LandMassPercentage`, `MostPopulatedCity`)
VALUES 
('Africa', 30370000, 20.4, 'Cairo, Egypt'),
('Antarctica', 14000000, 9.2, 'McMurdo Station*'),
('Asia', 44579000, 29.5, 'Mumbai, India'),
('Europe', 10180000, 6.8, 'Instanbul, Turquia'),
('North America', 24709000, 16.5, 'Ciudad de México, Mexico'),
('Oceania', 8600000, 5.9, 'Sydney, Australia'),
('South America', 17840000, 12.0, 'São Paulo, Brazil');

-- Ejercicio 6)

ALTER TABLE `country` ADD FOREIGN KEY (`Continent`) REFERENCES continent (`Name`);