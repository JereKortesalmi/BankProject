const db=require('../database');

const atm={
    getAllAtms(callback){
        return db.query("SELECT * from atm",callback);
    },
    getOneAtm(id, callback){
        return db.query("SELECT * FROM atm WHERE atm_id=?",[id],callback);
    },
    addAtm(newAtm,callback){
        return db.query("INSERT INTO atm(atm_balance, atm_20eur, atm_50eur, atm_100eur, atm_200eur, atm_500eur) VALUES(?,?,?,?,?,?)",[newAtm.atm_balance, newAtm.atm_20eur, newAtm.atm_50eur, newAtm.atm_100eur, newAtm.atm_200eur, newAtm.atm_500eur],callback);
    },
    updateAtm(id, updateAtm,callback){
        console.log(updateAtm);
        return db.query("UPDATE atm SET atm_balance=?, atm_20eur=?, atm_50eur=?, atm_100eur=?, atm_200eur=?, atm_500eur=? WHERE atm_id=?",[updateAtm.atm_balance, updateAtm.atm_20eur, updateAtm.atm_50eur, updateAtm.atm_100eur, updateAtm.atm_200eur, updateAtm.atm_500eur, id],callback);
    },
    deleteAtm(id,callback){
        return db.query("DELETE FROM atm WHERE atm_id=?",[id],callback);
    }
}

module.exports=atm;