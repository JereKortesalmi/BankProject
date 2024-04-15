const db=require('../database');
const bcrypt=require('bcryptjs');

const card={
    getAllCards(callback){
        return db.query("SELECT * FROM card",callback);
    },
    getOneCard(id,callback){
        return db.query("SELECT * FROM card WHERE card_id=?",[id],callback);
    },
    addCard(newCard,callback){
        bcrypt.hash(newCard.card_pin,10,function(err,hashedPassword){
        return db.query("INSERT INTO card(card_customer_id, card_number, card_type, card_pin, card_state) VALUES(?,?,?,?,?)",[
            newCard.card_customer_id,
            newCard.card_number,
            newCard.card_type,
            hashedPassword,
            newCard.card_state],
            callback);
    });
    },
    updateCard(id, updateCard,callback){
        bcrypt.hash(updateCard.card_pin,10,function(err,hashedPassword){
        return db.query("UPDATE card SET card_customer_id=?, card_number=?, card_type=?, card_pin=?, card_state=? WHERE card_id=?",[
            updateCard.card_customer_id,
            updateCard.card_number,
            updateCard.card_type,
            hashedPassword,
            updateCard.card_state,
            id],
            callback);
    });
    },
    deleteCard(id,callback){
        return db.query("DELETE FROM card WHERE card_id=?",[id],callback);
    },
    login(un, callback){
        return db.query("SELECT card_pin, card_state FROM card where card_number=?",[un], callback);
    },
    getAccountId(cardNumber,callback){
        return db.query("select account_id, account_customer_id, account_type, account_balance from account inner join accounts_to_cards on account_id=reference_account_id inner join card on reference_card_id=card_id where card_number=?",[cardNumber],callback);
    },
    loginLock(cardnumber,loginLock,callback){
        return db.query("UPDATE card SET card_state=? WHERE card_number=?",[
            loginLock.card_state,
            cardnumber],
            callback);
        }    
}

module.exports=card;