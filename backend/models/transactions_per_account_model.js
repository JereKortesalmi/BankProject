const db=require('../database');

const transactions_per_account={
    getTransactionsPerAccount(id, callback){
        return db.query("SELECT * FROM transaction WHERE transaction_account_id=?",[id],callback);
    },
    getLimitedTransactionsPerAccount(id, LimitedTransactions, callback){
        const offset = parseInt(LimitedTransactions.offset, 10);
        console.log("Offset:", offset);
        const query = `SELECT * FROM transaction WHERE transaction_account_id=${id} ORDER BY transaction_time DESC LIMIT 5 OFFSET ${offset};`;
        console.log("Constructed Query:", query);
        return db.query(query, callback);
    },
    getTransactionCountPerAccount(id, callback){
        return db.query("SELECT COUNT(*) AS transactionCount FROM transaction WHERE transaction_account_id = ?",[id],callback);
    }

}

module.exports=transactions_per_account;