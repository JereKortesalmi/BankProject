const express=require('express');
const router=express.Router();
const transaction=require('../models/transaction_model');

router.get('/',function(request, response){
    transaction.getAllTransactions(function(err, result){
        if(err){
            response.send(err);
        }
        else {
            response.json(result);
        }
    });
});

router.get('/:id',function(request, response){
    transaction.getOneTransaction(request.params.id, function(err, result){
        if(err){
            response.send(err);
        }
        else {
            response.json(result[0]);
        }
    });
});

router.post('/',function(request, response){
    transaction.addTransaction(request.body, function(err, result){
        if(err){
            response.send(err);
        }
        else {
            response.json(result.affectedRows);
        }
    });
});

router.put('/:id',function(request, response){
    transaction.updateTransaction(request.params.id, request.body, function(err, result){
        if(err){
            response.send(err);
        }
        else {
            response.json(result.affectedRows);
        }
    });
});

router.delete('/:id',function(request, response){
    transaction.deleteTransaction(request.params.id, function(err, result){
        if(err){
            response.send(err);
        }
        else {
            response.json(result.affectedRows);
        }
    });
});

module.exports=router;