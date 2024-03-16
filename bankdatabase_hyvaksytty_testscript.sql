insert into customer values (1, "Timo", "Pesola");
insert into customer values (2, "John", "Doe");

insert into card values (1, 1, "1234 5678 9012 3456", "DEBIT", 1234);
insert into card values (2, 1, "2345 6789 0123 4567", "DEBIT/CREDIT", 2345);
insert into card values (3, 2, "3456 7890 1234 5678", "DEBIT", 3456);

insert into account values (1, 1, "DEBIT", 100, NULL, NULL);
insert into account values (2, 1, "DEBIT", 1000, NULL, NULL);
insert into account values (3, 1, "CREDIT", 500, 1000, 400);
insert into account values (4, 2, "DEBIT", 1, NULL, NULL);

insert into accounts_to_cards values (1, 1, 1);
insert into accounts_to_cards values (2, 2, 2);
insert into accounts_to_cards values (3, 3, 2);
insert into accounts_to_cards values (4, 4, 3);

insert into transaction values (1, 1, "2024-11-11 11:22:33", "DEPOSIT", 100);
insert into transaction values (2, 2, "2024-11-11 22:22:22", "WITHDRAWAL", -100);
insert into transaction values (3, 3, "2024-03-14 15:27:00", "DEPOSIT", 1);
insert into transaction values (4, 1, current_timestamp(), "DEPOSIT", 1000);
insert into transaction values (5, 4, current_timestamp(), "DEPOSIT", 1);

select * from customer
inner join card on customer.customer_id = card.card_customer_id
inner join account on customer.customer_id = account.account_customer_id
inner join transaction on account.account_id = transaction.transaction_account_id;

select * from transaction;

select reference_id, reference_card_id, reference_account_id, account_type from accounts_to_cards
inner join account on accounts_to_cards.reference_account_id=account.account_id;