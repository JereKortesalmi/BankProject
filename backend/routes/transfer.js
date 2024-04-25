const express=require('express');
const router=express.Router();
const transfer=require('../models/transfer_model');

router.post('/',function(request, response){
    transfer.makeTransfer(request.body, function(err, result){
        if(err){
            response.json(err.sqlMessage);
        }
        else {
            response.json(result[0]);
        }
    });
});

module.exports=router;