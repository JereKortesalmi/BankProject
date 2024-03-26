const db=require('../database');

const transaction={
    getAllTransactions(callback){
        return db.query("SELECT * FROM transaction",callback);
    },
    getOneTransaction(id, callback){
        return db.query("SELECT * FROM transaction WHERE transaction_id=?",[id],callback);
    },
    addTransaction(newTransaction,callback){
        return db.query("INSERT INTO transaction(transaction_account_id, transaction_atm_id, transaction_time, transaction_type, transaction_amount) VALUES(?,?,?,?,?)",[newTransaction.transaction_account_id, newTransaction.transaction_atm_id, newTransaction.transaction_time, newTransaction.transaction_type, newTransaction.transaction_amount],callback);
    },
    updateTransaction(id, updateTransaction,callback){
        return db.query("UPDATE transaction SET transaction_account_id=?, transaction_atm_id=?, transaction_time=?, transaction_type=?, transaction_amount=? WHERE transaction_id=?",[updateTransaction.transaction_account_id, updateTransaction.transaction_atm_id, updateTransaction.transaction_time, updateTransaction.transaction_type, updateTransaction.transaction_amount, id],callback);
    },
    deleteTransaction(id,callback){
        return db.query("DELETE FROM transaction WHERE transaction_id=?",[id],callback);
    }
}

module.exports=transaction;