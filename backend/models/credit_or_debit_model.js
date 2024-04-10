const db=require('../database');

const credit_or_debit={
    determineCardType(card_number,callback){
        return db.query("SELECT card_type FROM card WHERE card_number=?",[card_number],callback);
    }
}

module.exports=credit_or_debit;