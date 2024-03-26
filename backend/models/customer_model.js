const db=require('../database');

const customer={
    getAllCustomers(callback){
        return db.query("SELECT * FROM customer", [id],callback);
    },
    getOneCustomer(id,callback){
        return db.query("SELECT * FROM customer WHERE id=?", [id],callback);
    },
    addCustomer(newCustomer,callback){
        return db.query("INSTER INTO customer(customer_firstname, customer_lastname), values(?,?)",[
            newCustomer.customer_firstname,
            newCustomer.customer_lastname],
            callback);
    },
    updateCustomer(id, updateCustomer,callback){
        return db.query("UPDATE customer SET customer_firstname=?, customer_lastname=?",[
            updateCustomer.customer_firstname,
            updateCustomer.customer_lastname,
            id],
            callback);
    },
    deleteCustomer(id,callback){
        return db.query("DELETE FROM customer WHERE customer_id=?",[id],callback);
    }
}

modeule.exports=customer;