const express=require('express');
const router=express.Router();
const transactions_per_account=require('../models/transactions_per_account_model');

router.get('/:id',function(request, response){
    transactions_per_account.getTransactionsPerAccount(request.params.id, function(err, result){
        if(err){
            response.send(err);
        }
        else {
            response.json(result);
        }
    });
});

module.exports=router;