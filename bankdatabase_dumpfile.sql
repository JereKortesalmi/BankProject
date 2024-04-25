-- MySQL dump 10.13  Distrib 8.0.34, for Win64 (x86_64)
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
INSERT INTO `account` VALUES (1,1,'DEBIT',0.00,NULL,NULL),(2,1,'DEBIT',110.00,1000.00,980.00),(3,1,'CREDIT',430.00,1000.00,870.00),(4,2,'DEBIT',1.00,NULL,NULL),(5,3,'ADMIN',60.00,NULL,NULL);
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
INSERT INTO `atm` VALUES (1,6320,36,10,8,4,7),(2,1500,50,10,0,0,0),(3,2000,50,20,0,0,0);
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
) ENGINE=InnoDB AUTO_INCREMENT=27 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `transaction`
--

LOCK TABLES `transaction` WRITE;
/*!40000 ALTER TABLE `transaction` DISABLE KEYS */;
INSERT INTO `transaction` VALUES (1,1,1,'2024-11-11 11:22:33','DEPOSIT',100.00),(2,2,1,'2024-11-11 22:22:22','WITHDRAWAL',-100.00),(3,3,2,'2024-03-14 15:27:00','DEPOSIT',1.00),(4,1,2,'2024-03-26 05:02:05','DEPOSIT',1000.00),(5,4,2,'2024-03-26 05:02:05','DEPOSIT',1.00),(6,5,1,'2024-03-26 05:02:05','ADD MONEY',500.00),(8,2,1,'2024-04-20 23:34:01','WITHDRAW',20.00),(9,1,1,'2024-04-21 00:08:35','WITHDRAW',20.00),(10,1,1,'2024-04-21 00:08:49','WITHDRAW',40.00),(11,1,1,'2024-04-21 00:09:41','WITHDRAW',50.00),(12,1,1,'2024-04-21 00:13:12','WITHDRAW',50.00),(13,1,1,'2024-04-21 00:13:42','WITHDRAW',20.00),(14,1,1,'2024-04-21 00:13:53','WITHDRAW',20.00),(15,1,1,'2024-04-21 00:14:17','WITHDRAW',20.00),(16,1,1,'2024-04-21 10:52:43','WITHDRAW',20.00),(17,1,1,'2024-04-21 10:53:52','WITHDRAW',50.00),(18,1,1,'2024-04-21 10:55:39','WITHDRAW',20.00),(19,1,1,'2024-04-21 10:55:56','WITHDRAW',120.00),(20,1,1,'2024-04-21 11:01:19','WITHDRAW',20.00),(21,1,1,'2024-04-21 11:01:33','WITHDRAW',60.00),(22,2,1,'2024-04-22 11:19:26','WITHDRAW',20.00),(23,2,1,'2024-04-23 10:40:57','WITHDRAW',20.00),(24,1,1,'2024-04-23 16:34:41','WITHDRAW',50.00),(25,1,1,'2024-04-23 20:25:46','WITHDRAW',20.00),(26,1,1,'2024-04-24 10:16:44','WITHDRAW',20.00);
/*!40000 ALTER TABLE `transaction` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping routines for database 'bankdatabase'
--
/*!50003 DROP PROCEDURE IF EXISTS `transfer_procedure` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_0900_ai_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `transfer_procedure`(
	IN sender_id INT,
    IN recipient_id INT,
    IN amount DECIMAL(10, 2)
    )
BEGIN
	DECLARE sender_balance DECIMAL(10, 2);
	DECLARE recipient_balance DECIMAL(10, 2);
    DECLARE sender_type VARCHAR(45);
    DECLARE recipient_type VARCHAR(45);
    DECLARE sender_credit_max DECIMAL(10, 2);
    DECLARE recipient_credit_max DECIMAL(10, 2);
    DECLARE sender_credit_current DECIMAL(10, 2);
    DECLARE recipient_credit_current DECIMAL(10, 2);
    DECLARE available_credit DECIMAL(10, 2);
    DECLARE success INT DEFAULT 0;
    
    START TRANSACTION;
	
    SELECT account_balance, account_type, account_credit_max, account_credit_current 
		INTO sender_balance, sender_type, sender_credit_max, sender_credit_current FROM account WHERE account_id = sender_id FOR UPDATE;
	SELECT account_balance, account_type, account_credit_max, account_credit_current
		INTO recipient_balance, recipient_type, recipient_credit_max, recipient_credit_current FROM account WHERE account_id = recipient_id FOR UPDATE;
    
	IF sender_balance IS NULL THEN
        SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = 'Sender account does not exist';
    ELSEIF recipient_balance IS NULL THEN
        SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = 'Recipient account does not exist';
	ELSEIF sender_balance < amount THEN
		SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = 'Insufficient balance for transfer';
	ELSEIF amount <= 0 THEN
		SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = 'Invalid transfer amount';
	ELSEIF recipient_type = 'CREDIT' AND amount > recipient_credit_current THEN
		SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = 'Transfer amount too big for credit account';
	ELSEIF sender_type = 'ADMIN' OR recipient_type = 'ADMIN' THEN
		SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = 'Cannot send or receive using admin accounts';
	
    ELSEIF sender_type = 'CREDIT' THEN
		UPDATE account SET account_balance = account_balance - amount WHERE account_id = sender_id;
		UPDATE account SET account_credit_current = account_credit_current + amount WHERE account_id = sender_id;
		UPDATE account SET account_balance = account_balance + amount WHERE account_id = recipient_id;
            
		SET success = 1;
	
    ELSEIF sender_type = 'DEBIT' THEN
		UPDATE account SET account_balance = account_balance - amount WHERE account_id = sender_id;
        UPDATE account SET account_balance = account_balance + amount WHERE account_id = recipient_id;
        UPDATE account SET account_credit_current = account_credit_current - amount WHERE account_id = recipient_id;
        
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

-- Dump completed on 2024-04-24 18:53:28
