const db=require('../database');

const accounts_to_cards={
    getAllAccounts_To_Cards(callback) {
        return db.query("SELECT * FROM accounts_to_cards", callback);
    },
    getOneAccounts_To_Cards(id,callback) {
        return db.query("SELECT * FROM accounts_to_cards WHERE id=?",[id],callback);
    },
    addAccounts_To_Cards(newAccounts_To_Cards,callback) {
        return db.query("INSERT INTO accounts_to_cards(reference_account_id, reference_card_id) VALUES(?,?)",[
            newAccounts_To_Cards.reference_account_id, 
            newAccounts_To_Cards.reference_card_id],
            callback);
    },
    updateAccounts_To_Cards(id,updateAccounts_To_Cards,callback) {
        return db.query("UPDATE account_to_cards SET reference_account_id=?, reference_card_id=? WHERE reference_id=?",
        [updateAccounts_To_Cards.reference_account_idaccount_id, 
            updateAccounts_To_Cards.reference_card_id,
            id],
            callback);
    },
    deleteAccounts_To_Cards(id,callback) {
        return db.query("DELETE FROM account_to_cards WHERE reference_id=?", [id], callback);
    }
}


module.exports=accounts_to_cards;