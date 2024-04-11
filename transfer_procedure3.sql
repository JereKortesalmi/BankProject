CREATE DEFINER=`root`@`localhost` PROCEDURE `transfer_procedure3`(
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
END