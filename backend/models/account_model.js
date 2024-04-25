const db=require('../database');
const { getAccountId } = require('./card_model');

const account={
    getAllAccounts(callback) {
        return db.query("SELECT * FROM account", callback);
    },
    getOneAccount(id,callback) {
        return db.query("SELECT * FROM account WHERE account_id=?",[id],callback);
    },
    addAccount(newAccount,callback) {
        return db.query("INSERT INTO account(account_customer_id, account_type, account_balance, account_credit_max, account_credit_current)  VALUES(?,?,?,?,?)",[
            newAccount.account_customer_id,
            newAccount.account_type, 
            newAccount.account_balance, 
            newAccount.account_credit_max,
            newAccount.account_credit_current],
            callback);
    },
    updateAccount(id,updateAccount,callback) {
        return db.query("UPDATE account SET account_customer_id=?, account_type=?, account_balance=?, account_credit_max=?, account_credit_current=? WHERE account_id=?",
        [updateAccount.account_customer_id, 
            updateAccount.account_type, 
            updateAccount.account_balance, 
            updateAccount.account_credit_max, 
            updateAccount.account_credit_current,
            id],
            callback);
    },
    updateBalance(id,updateBalance,callback){
        return db.query("UPDATE account SET account_balance=? WHERE account_id=?",
    [updateBalance.account_balance,
    id],
    callback);
    },
    deleteAccount(id,callback) {
        return db.query("DELETE FROM account WHERE account_id=?", [id], callback);
    },
    getAccountId(cardNumber,callback){
        return db.query("SELECT account_id, account_customer_id, account_type, account_balance, account_credit_max, account_credit_current FROM account inner join accounts_to_cards on account_id=reference_account_id inner join card on reference_card_id=card_id WHERE card_number=?",[cardNumber],callback);
    }
}


module.exports=account;