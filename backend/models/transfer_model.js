const db=require('../database');

const transfer={
    makeTransfer(transferInfo, callback){
        return db.query("CALL transfer_procedure(?, ?, ?)",[transferInfo.sender_id, transferInfo.recipient_id, transferInfo.amount],callback);
    }
}

module.exports=transfer;