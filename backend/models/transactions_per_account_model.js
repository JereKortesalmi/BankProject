const db=require('../database');

const transactions_per_account={
    getTransactionsPerAccount(id, callback){
        return db.query("SELECT * FROM transaction WHERE transaction_account_id=?",[id],callback);
    }

}

module.exports=transactions_per_account;