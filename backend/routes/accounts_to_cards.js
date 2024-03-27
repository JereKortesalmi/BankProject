const express=require('express');
const router=express.Router();
const accounts_to_cards=require('../models/accounts_to_cards_model');

router.get('/',function(request, response){
    accounts_to_cards.getAllAccounts_To_Cards(function(err, result){
        if(err){
            response.send(err);
        }
        else {
            response.json(result);
        }
    });
});

router.get('/:id',function(request, response){
    accounts_to_cards.getOneAccounts_To_Cards(request.params.id, function(err, result){
        if(err){
            response.send(err);
        }
        else {
            response.json(result[0]);
        }
    });
});

router.post('/',function(request, response){
    accounts_to_cards.addAccounts_To_Cards(request.body, function(err, result){
        if(err){
            response.send(err);
        }
        else {
            response.json(result.affectedRows);
        }
    });
});

router.put('/:id',function(request, response){
    accounts_to_cards.updateAccounts_To_Cards(request.params.id, request.body, function(err, result){
        if(err){
            response.send(err);
        }
        else {
            response.json(result.affectedRows);
        }
    });
});

router.delete('/:id',function(request, response){
    accounts_to_cards.deleteAccounts_To_Cards(request.params.id, function(err, result){
        if(err){
            response.send(err);
        }
        else {
            response.json(result.affectedRows);
        }
    });
});

module.exports=router;