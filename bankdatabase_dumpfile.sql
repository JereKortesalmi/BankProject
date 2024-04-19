CREATE DATABASE  IF NOT EXISTS `bankdatabase` /*!40100 DEFAULT CHARACTER SET utf8mb3 */ /*!80016 DEFAULT ENCRYPTION='N' */;
USE `bankdatabase`;
-- MySQL dump 10.13  Distrib 8.0.36, for Win64 (x86_64)
--
-- Host: 127.0.0.1    Database: bankdatabase
-- ------------------------------------------------------
-- Server version	8.2.0

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `account`
--

DROP TABLE IF EXISTS `account`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `account` (
  `account_id` int NOT NULL AUTO_INCREMENT,
  `account_customer_id` int NOT NULL,
  `account_type` varchar(45) NOT NULL,
  `account_balance` decimal(10,2) NOT NULL,
  `account_credit_max` decimal(10,2) DEFAULT NULL,
  `account_credit_current` decimal(10,2) DEFAULT NULL,
  PRIMARY KEY (`account_id`),
  UNIQUE KEY `account_id_UNIQUE` (`account_id`),
  KEY `customer_id_idx` (`account_customer_id`),
  CONSTRAINT `account_owner_id` FOREIGN KEY (`account_customer_id`) REFERENCES `customer` (`customer_id`) ON DELETE RESTRICT ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `account`
--

LOCK TABLES `account` WRITE;
/*!40000 ALTER TABLE `account` DISABLE KEYS */;
INSERT INTO `account` VALUES (1,1,'DEBIT',600.00,NULL,NULL),(2,1,'DEBIT',100.00,1000.00,1000.00),(3,1,'CREDIT',500.00,1000.00,800.00),(4,2,'DEBIT',1.00,NULL,NULL),(5,3,'ADMIN',60.00,NULL,NULL);
/*!40000 ALTER TABLE `account` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `accounts_to_cards`
--

DROP TABLE IF EXISTS `accounts_to_cards`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `accounts_to_cards` (
  `reference_id` int NOT NULL AUTO_INCREMENT,
  `reference_account_id` int NOT NULL,
  `reference_card_id` int NOT NULL,
  PRIMARY KEY (`reference_id`),
  UNIQUE KEY `reference_id_UNIQUE` (`reference_id`),
  KEY `reference_account_id_idx` (`reference_account_id`),
  KEY `reference_card_id_idx` (`reference_card_id`),
  CONSTRAINT `reference_account_id` FOREIGN KEY (`reference_account_id`) REFERENCES `account` (`account_id`) ON DELETE RESTRICT ON UPDATE CASCADE,
  CONSTRAINT `reference_card_id` FOREIGN KEY (`reference_card_id`) REFERENCES `card` (`card_id`) ON DELETE RESTRICT ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `accounts_to_cards`
--

LOCK TABLES `accounts_to_cards` WRITE;
/*!40000 ALTER TABLE `accounts_to_cards` DISABLE KEYS */;
INSERT INTO `accounts_to_cards` VALUES (1,1,1),(2,2,2),(3,3,2),(7,5,3);
/*!40000 ALTER TABLE `accounts_to_cards` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `atm`
--

DROP TABLE IF EXISTS `atm`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `atm` (
  `atm_id` int NOT NULL AUTO_INCREMENT,
  `atm_balance` int NOT NULL,
  `atm_20eur` int DEFAULT NULL,
  `atm_50eur` int DEFAULT NULL,
  `atm_100eur` int DEFAULT NULL,
  `atm_200eur` int DEFAULT NULL,
  `atm_500eur` int DEFAULT NULL,
  PRIMARY KEY (`atm_id`),
  UNIQUE KEY `atm_id_UNIQUE` (`atm_id`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `atm`
--

LOCK TABLES `atm` WRITE;
/*!40000 ALTER TABLE `atm` DISABLE KEYS */;
INSERT INTO `atm` VALUES (1,3480,54,4,4,4,2),(2,1500,50,10,0,0,0),(3,2000,50,20,0,0,0);
/*!40000 ALTER TABLE `atm` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `card`
--

DROP TABLE IF EXISTS `card`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `card` (
  `card_id` int NOT NULL AUTO_INCREMENT,
  `card_customer_id` int NOT NULL,
  `card_number` varchar(20) NOT NULL,
  `card_type` varchar(45) NOT NULL,
  `card_pin` varchar(255) NOT NULL,
  `card_state` int DEFAULT NULL,
  PRIMARY KEY (`card_id`),
  UNIQUE KEY `card_id_UNIQUE` (`card_id`),
  UNIQUE KEY `card_number_UNIQUE` (`card_number`),
  UNIQUE KEY `card_pin_UNIQUE` (`card_pin`),
  KEY `customer_id_idx` (`card_customer_id`),
  CONSTRAINT `card_owner_id` FOREIGN KEY (`card_customer_id`) REFERENCES `customer` (`customer_id`) ON DELETE RESTRICT ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=12 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `card`
--

LOCK TABLES `card` WRITE;
/*!40000 ALTER TABLE `card` DISABLE KEYS */;
INSERT INTO `card` VALUES (1,1,'1234 5678 9012 3456','DEBIT','1234',1),(2,1,'1111','DEBIT/CREDIT','$2a$10$gHK5h4AXZCt1/CtbZVEKr.TGCVrXczd.nJFieWfSLmZpXV70Huydi',1),(3,2,'3456 7890 1234 5678','DEBIT','3456',1),(7,2,'0500CB1EF8','DEBIT','$2a$10$Mz/N1wftx64L7DHm9o/7Qu749ArOXt1Xp1HZD9x4DtsgOyD9PnK/i',1),(8,1,'0500CB1FF3','DEBIT/CREDIT','$2a$10$jbe7e3KtNQS9HcpmXX62rOZDr1KygpwPm2JtehXJSpkNIGddNCwNq',1),(11,3,'0600062211','ADMIN','$2a$10$ZdTjtcSuYtMNnfSYeXgofut4flVZMBklMT2r5BT5CVsi04CATafMa',1);
/*!40000 ALTER TABLE `card` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `customer`
--

DROP TABLE IF EXISTS `customer`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `customer` (
  `customer_id` int NOT NULL AUTO_INCREMENT,
  `customer_firstname` varchar(45) NOT NULL,
  `customer_lastname` varchar(45) NOT NULL,
  PRIMARY KEY (`customer_id`),
  UNIQUE KEY `customer_id_UNIQUE` (`customer_id`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `customer`
--

LOCK TABLES `customer` WRITE;
/*!40000 ALTER TABLE `customer` DISABLE KEYS */;
INSERT INTO `customer` VALUES (1,'Timo','Pesola'),(2,'John','Doe'),(3,'ADMIN','ADMIN');
/*!40000 ALTER TABLE `customer` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `transaction`
--

DROP TABLE IF EXISTS `transaction`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `transaction` (
  `transaction_id` int NOT NULL AUTO_INCREMENT,
  `transaction_account_id` int NOT NULL,
  `transaction_atm_id` int DEFAULT NULL,
  `transaction_time` datetime NOT NULL,
  `transaction_type` varchar(45) NOT NULL,
  `transaction_amount` decimal(10,2) NOT NULL,
  PRIMARY KEY (`transaction_id`),
  UNIQUE KEY `transaction_id_UNIQUE` (`transaction_id`),
  KEY `account_id_idx` (`transaction_account_id`),
  KEY `transaction_atm_id_idx` (`transaction_atm_id`),
  CONSTRAINT `transaction_account_id` FOREIGN KEY (`transaction_account_id`) REFERENCES `account` (`account_id`) ON DELETE RESTRICT ON UPDATE CASCADE,
  CONSTRAINT `transaction_atm_id` FOREIGN KEY (`transaction_atm_id`) REFERENCES `atm` (`atm_id`) ON DELETE RESTRICT ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `transaction`
--

LOCK TABLES `transaction` WRITE;
/*!40000 ALTER TABLE `transaction` DISABLE KEYS */;
INSERT INTO `transaction` VALUES (1,1,1,'2024-11-11 11:22:33','DEPOSIT',100.00),(2,2,1,'2024-11-11 22:22:22','WITHDRAWAL',-100.00),(3,3,2,'2024-03-14 15:27:00','DEPOSIT',1.00),(4,1,2,'2024-03-26 05:02:05','DEPOSIT',1000.00),(5,4,2,'2024-03-26 05:02:05','DEPOSIT',1.00),(6,5,1,'2024-03-26 05:02:05','ADD MONEY',500.00);
/*!40000 ALTER TABLE `transaction` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping routines for database 'bankdatabase'
--
/*!50003 DROP PROCEDURE IF EXISTS `transfer_procedure` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb3 */ ;
/*!50003 SET character_set_results = utf8mb3 */ ;
/*!50003 SET collation_connection  = utf8mb3_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'NO_AUTO_VALUE_ON_ZERO' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `transfer_procedure`(
	IN sender_id INT,
    IN recipient_id INT,
    IN amount DECIMAL(10, 2),
    IN transfer_type VARCHAR(10)
    )
BEGIN
	DECLARE sender_balance DECIMAL(10, 2);
	DECLARE recipient_balance DECIMAL(10, 2);
    DECLARE sender_type VARCHAR(45);
    DECLARE sender_credit_max DECIMAL(10, 2);
    DECLARE sender_credit_current DECIMAL(10, 2);
    DECLARE available_credit DECIMAL(10, 2);
    DECLARE success INT DEFAULT 0;
    
    START TRANSACTION;
	
    SELECT account_balance, account_type, account_credit_max, account_credit_current 
		INTO sender_balance, sender_type, sender_credit_max, sender_credit_current FROM account WHERE account_id = sender_id FOR UPDATE;
	SELECT account_balance 
		INTO recipient_balance FROM account WHERE account_id = recipient_id FOR UPDATE;
    
	IF sender_balance IS NULL THEN
        SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = 'Sender account does not exist';
    ELSEIF recipient_balance IS NULL THEN
        SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = 'Recipient account does not exist';
    ELSEIF sender_type = 'DEBIT' AND transfer_type = 'CREDIT' THEN
		SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = 'Invalid transfer type for debit account';
	ELSEIF sender_balance < amount AND transfer_type = 'DEBIT' THEN
		SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = 'Insufficient balance for debit transfer';
	ELSEIF amount <= 0 THEN
		SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = 'Invalid transfer amount';
	ELSEIF transfer_type = 'CREDIT' THEN
		SET available_credit = sender_credit_max - sender_credit_current;
        
        IF available_credit >= amount THEN
			UPDATE account SET account_credit_current = account_credit_current + amount WHERE account_id = sender_id;
            UPDATE account SET account_balance = account_balance + amount WHERE account_id = recipient_id;
            SET success = 1;
		ELSE
			SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = 'Insufficient remaining credit for credit transfer';
		END IF;
	ELSE
		UPDATE account SET account_balance = account_balance - amount WHERE account_id = sender_id;
        UPDATE account SET account_balance = account_balance + amount WHERE account_id = recipient_id;
        
        SET success = 1;
	END IF;
		
    IF success = 1 THEN
		COMMIT;
        SELECT 'Transaction successful' AS status;
	ELSE
		ROLLBACK;
	END IF;
END ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2024-04-19 12:32:17
