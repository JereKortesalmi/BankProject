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
    DECLARE error_status INT DEFAULT 0;
    
    START TRANSACTION;
	
    SELECT account_balance, account_type, account_credit_max, account_credit_current 
		INTO sender_balance, sender_type, sender_credit_max, sender_credit_current FROM account WHERE account_id = sender_id FOR UPDATE;
	SELECT account_balance, account_type, account_credit_max, account_credit_current
		INTO recipient_balance, recipient_type, recipient_credit_max, recipient_credit_current FROM account WHERE account_id = recipient_id FOR UPDATE;
    
	IF sender_balance IS NULL THEN
		SET error_status = 1;
        -- SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = 'Sender account does not exist';
    ELSEIF recipient_balance IS NULL THEN
		SET error_status = 2;
        -- SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = 'Recipient account does not exist';
	ELSEIF sender_balance < amount THEN
		SET error_status = 3;
		-- SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = 'Insufficient balance for transfer';
	ELSEIF amount <= 0 THEN
		SET error_status = 4;
		-- SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = 'Invalid transfer amount';
	ELSEIF recipient_type = 'CREDIT' AND amount > recipient_credit_current THEN
		SET error_status = 5;
		-- SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = 'Transfer amount too big for credit account';
	ELSEIF sender_type = 'ADMIN' OR recipient_type = 'ADMIN' THEN
		SET error_status = 6;
		-- SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = 'Cannot send or receive using admin accounts';
	ELSEIF sender_type = recipient_type THEN
		SET error_status = 7;
        -- SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = 'Account selection error';
	
    ELSEIF sender_type = 'CREDIT' AND error_status = 0 THEN
		UPDATE account SET account_balance = account_balance - amount WHERE account_id = sender_id;
		UPDATE account SET account_credit_current = account_credit_current + amount WHERE account_id = sender_id;
		UPDATE account SET account_balance = account_balance + amount WHERE account_id = recipient_id;
        
        insert into transaction (transaction_account_id, transaction_atm_id, transaction_time, transaction_type, transaction_amount) VALUES (sender_id, 1, current_timestamp(), "WITHDRAW", amount);
        insert into transaction (transaction_account_id, transaction_atm_id, transaction_time, transaction_type, transaction_amount) VALUES (recipient_id, 1, current_timestamp(), "DEPOSIT", amount);
        
		SET success = 1;
	
    ELSEIF sender_type = 'DEBIT' AND error_status = 0 THEN
		UPDATE account SET account_balance = account_balance - amount WHERE account_id = sender_id;
        UPDATE account SET account_balance = account_balance + amount WHERE account_id = recipient_id;
        UPDATE account SET account_credit_current = account_credit_current - amount WHERE account_id = recipient_id;
        
        insert into transaction (transaction_account_id, transaction_atm_id, transaction_time, transaction_type, transaction_amount) VALUES (sender_id, 1, current_timestamp(), "WITHDRAW", amount);
        insert into transaction (transaction_account_id, transaction_atm_id, transaction_time, transaction_type, transaction_amount) VALUES (recipient_id, 1, current_timestamp(), "DEPOSIT", amount);
        
        SET success = 1;
	
    END IF;
		
    IF success = 1 THEN
		COMMIT;
        SELECT 'Transaction successful' AS status;
	ELSE
		ROLLBACK;
        IF error_status = 1 THEN
			SELECT 'Sender account does not exist' AS status;
        ELSEIF error_status = 2 THEN
			SELECT 'Recipient account does not exist' AS status;
        ELSEIF error_status = 3 THEN
			SELECT 'Insufficient balance for transfer' AS status;
        ELSEIF error_status = 4 THEN
			SELECT 'Invalid transfer amount' AS status;
        ELSEIF error_status = 5 THEN
			SELECT 'Transfer amount too big for credit account' AS status;
        ELSEIF error_status = 6 THEN
			SELECT 'Cannot send or receive using admin accounts' AS status;
        ELSEIF error_status = 7 THEN
			SELECT 'Account selection error' AS status;
		END IF;
        
	END IF;
END