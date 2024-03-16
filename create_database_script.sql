-- MySQL Workbench Synchronization
-- Generated: 2024-03-16 11:24
-- Model: New Model
-- Version: 1.0
-- Project: Name of the project
-- Author: timop

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION';

CREATE SCHEMA IF NOT EXISTS `bankdatabase` DEFAULT CHARACTER SET utf8 ;

CREATE TABLE IF NOT EXISTS `bankdatabase`.`customer` (
  `customer_id` INT(11) NOT NULL AUTO_INCREMENT,
  `customer_firstname` VARCHAR(45) NOT NULL,
  `customer_lastname` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`customer_id`),
  UNIQUE INDEX `customer_id_UNIQUE` (`customer_id` ASC) VISIBLE)
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8;

CREATE TABLE IF NOT EXISTS `bankdatabase`.`account` (
  `account_id` INT(11) NOT NULL AUTO_INCREMENT,
  `account_customer_id` INT(11) NOT NULL,
  `account_type` VARCHAR(45) NOT NULL,
  `account_balance` DECIMAL(10,2) NOT NULL,
  `account_credit_max` DECIMAL(10,2) NULL DEFAULT NULL,
  `account_credit_current` DECIMAL(10,2) NULL DEFAULT NULL,
  PRIMARY KEY (`account_id`),
  UNIQUE INDEX `account_id_UNIQUE` (`account_id` ASC) VISIBLE,
  INDEX `customer_id_idx` (`account_customer_id` ASC) VISIBLE,
  CONSTRAINT `account_owner_id`
    FOREIGN KEY (`account_customer_id`)
    REFERENCES `bankdatabase`.`customer` (`customer_id`)
    ON DELETE RESTRICT
    ON UPDATE CASCADE)
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8;

CREATE TABLE IF NOT EXISTS `bankdatabase`.`card` (
  `card_id` INT(11) NOT NULL AUTO_INCREMENT,
  `card_customer_id` INT(11) NOT NULL,
  `card_number` VARCHAR(20) NOT NULL,
  `card_type` VARCHAR(45) NOT NULL,
  `card_pin` VARCHAR(255) NOT NULL,
  PRIMARY KEY (`card_id`),
  UNIQUE INDEX `card_id_UNIQUE` (`card_id` ASC) VISIBLE,
  UNIQUE INDEX `card_number_UNIQUE` (`card_number` ASC) VISIBLE,
  UNIQUE INDEX `card_pin_UNIQUE` (`card_pin` ASC) VISIBLE,
  INDEX `customer_id_idx` (`card_customer_id` ASC) VISIBLE,
  CONSTRAINT `card_owner_id`
    FOREIGN KEY (`card_customer_id`)
    REFERENCES `bankdatabase`.`customer` (`customer_id`)
    ON DELETE RESTRICT
    ON UPDATE CASCADE)
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8;

CREATE TABLE IF NOT EXISTS `bankdatabase`.`transaction` (
  `transaction_id` INT(11) NOT NULL AUTO_INCREMENT,
  `transaction_account_id` INT(11) NOT NULL,
  `transaction_time` DATETIME NOT NULL,
  `transaction_type` VARCHAR(45) NOT NULL,
  `transaction_amount` DECIMAL(10,2) NOT NULL,
  PRIMARY KEY (`transaction_id`),
  UNIQUE INDEX `transaction_id_UNIQUE` (`transaction_id` ASC) VISIBLE,
  INDEX `account_id_idx` (`transaction_account_id` ASC) VISIBLE,
  CONSTRAINT `transaction_account_id`
    FOREIGN KEY (`transaction_account_id`)
    REFERENCES `bankdatabase`.`account` (`account_id`)
    ON DELETE RESTRICT
    ON UPDATE CASCADE)
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8;

CREATE TABLE IF NOT EXISTS `bankdatabase`.`accounts_to_cards` (
  `reference_id` INT(11) NOT NULL AUTO_INCREMENT,
  `reference_account_id` INT(11) NOT NULL,
  `reference_card_id` INT(11) NOT NULL,
  PRIMARY KEY (`reference_id`),
  UNIQUE INDEX `reference_id_UNIQUE` (`reference_id` ASC) VISIBLE,
  INDEX `reference_account_id_idx` (`reference_account_id` ASC) VISIBLE,
  INDEX `reference_card_id_idx` (`reference_card_id` ASC) VISIBLE,
  CONSTRAINT `reference_account_id`
    FOREIGN KEY (`reference_account_id`)
    REFERENCES `bankdatabase`.`account` (`account_id`)
    ON DELETE RESTRICT
    ON UPDATE CASCADE,
  CONSTRAINT `reference_card_id`
    FOREIGN KEY (`reference_card_id`)
    REFERENCES `bankdatabase`.`card` (`card_id`)
    ON DELETE RESTRICT
    ON UPDATE CASCADE)
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
