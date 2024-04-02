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
        return db.query("INSERT INTO card(card_customer_id, card_number, card_type, card_pin) VALUES(?,?,?,?)",[
            newCard.card_customer_id,
            newCard.card_number,
            newCard.card_type,
            hashedPassword],
            callback);
    });
},
    updateCard(id, updateCard,callback){
        bcrypt.hash(updateCard.card_pin,10,function(err,hashedPassword){
        return db.query("UPDATE card SET card_customer_id=?, card_number=?, card_type=?, card_pin=? WHERE card_id=?",[
            updateCard.card_customer_id,
            updateCard.card_number,
            updateCard.card_type,
            hashedPassword,
            id],
            callback);
    });
},
    deleteCard(id,callback){
        return db.query("DELETE FROM card WHERE card_id=?",[id],callback);
    },
    login(un, callback){
        return db.query("SELECT card_pin FROM card where card_number=?",[un], callback);
    }
}

module.exports=card;