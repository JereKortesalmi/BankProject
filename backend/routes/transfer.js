const express=require('express');
const router=express.Router();
const transfer=require('../models/transfer_model');

router.post('/',function(request, response){
    transfer.makeTransfer(request.body, function(err, result){
        if(err){
            response.send(err);
        }
        else {
            response.send(result[0]);
        }
    });
});

module.exports=router;