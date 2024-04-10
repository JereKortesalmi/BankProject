const express=require('express');
const router=express.Router();
const credit_or_debit=require('../models/credit_or_debit_model');

router.get('/:card_number',function(request, response){
    credit_or_debit.determineCardType(request.params.card_number, function(err, result){
        if(err){
            response.send(err);
        }
        else {
            response.json(result);
        }
    });
});

module.exports=router;