-- MySQL Workbench Forward Engineering

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION';

-- -----------------------------------------------------
-- Schema db_s7416949_f19
-- -----------------------------------------------------

-- -----------------------------------------------------
-- Schema db_s7416949_f19
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `db_s7416949_f19` DEFAULT CHARACTER SET utf8 ;
USE `db_s7416949_f19` ;

-- -----------------------------------------------------
-- Table `db_s7416949_f19`.`Shelter`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `db_s7416949_f19`.`Shelter` (
  `Location` INT NULL,
  `PhoneNumber` VARCHAR(45) NULL,
  `shelterID` INT NOT NULL,
  PRIMARY KEY (`shelterID`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `db_s7416949_f19`.`Room`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `db_s7416949_f19`.`Room` (
  `RoomNum` INT NOT NULL,
  `Capacity` INT NULL,
  `isFull` TINYINT NOT NULL,
  `Shelter_ShelterID` INT NOT NULL,
  PRIMARY KEY (`RoomNum`),
  INDEX `fk_Room_Shelter1_idx` (`Shelter_ShelterID` ASC),
  CONSTRAINT `fk_Room_Shelter1`
    FOREIGN KEY (`Shelter_ShelterID`)
    REFERENCES `db_s7416949_f19`.`Shelter` (`shelterID`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `db_s7416949_f19`.`Dog`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `db_s7416949_f19`.`Dog` (
  `ID` INT NOT NULL,
  `Name` VARCHAR(45) NULL,
  `DOB` DATETIME NULL,
  `isFixed` VARCHAR(8) NOT NULL,
  `Fee` FLOAT NULL,
  `DateBooked` DATETIME NOT NULL,
  `isAvailable` VARCHAR(45) NOT NULL,
  `RoomNum` INT NOT NULL,
  `isGoodBoy` VARCHAR(8) NOT NULL DEFAULT 1,
  `Breed` VARCHAR(45) NULL,
  PRIMARY KEY (`ID`),
  INDEX `fk_Dog_Room1_idx` (`RoomNum` ASC),
  CONSTRAINT `fk_Dog_Room1`
    FOREIGN KEY (`RoomNum`)
    REFERENCES `db_s7416949_f19`.`Room` (`RoomNum`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `db_s7416949_f19`.`Cat`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `db_s7416949_f19`.`Cat` (
  `ID` INT NOT NULL,
  `Name` VARCHAR(45) NULL,
  `DOB` DATETIME NULL,
  `isFixed` VARCHAR(8) NOT NULL,
  `Color` VARCHAR(45) NULL,
  `Breed` VARCHAR(45) NULL,
  `Fee` FLOAT NULL,
  `DateBooked` DATETIME NULL,
  `isAvailable` VARCHAR(8) NOT NULL,
  `RoomNum` INT NOT NULL,
  PRIMARY KEY (`ID`),
  INDEX `fk_Cat_Room1_idx` (`RoomNum` ASC),
  CONSTRAINT `fk_Cat_Room1`
    FOREIGN KEY (`RoomNum`)
    REFERENCES `db_s7416949_f19`.`Room` (`RoomNum`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `db_s7416949_f19`.`Rabbit`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `db_s7416949_f19`.`Rabbit` (
  `ID` INT NOT NULL,
  `DOB` DATETIME NULL,
  `Breed` VARCHAR(45) NULL,
  `isFixed` VARCHAR(45) NOT NULL,
  `Fee` FLOAT NULL,
  `DateBooked` DATETIME NULL,
  `isAvailable` VARCHAR(8) NULL,
  `RoomNum` INT NOT NULL,
  `Name` VARCHAR(45) NULL,
  PRIMARY KEY (`ID`),
  INDEX `fk_Rabbit_Room1_idx` (`RoomNum` ASC),
  CONSTRAINT `fk_Rabbit_Room1`
    FOREIGN KEY (`RoomNum`)
    REFERENCES `db_s7416949_f19`.`Room` (`RoomNum`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
