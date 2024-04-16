const express=require('express');
const router=express.Router();
const card=require('../models/card_model');

router.get('/',function(request, response){
    card.getAllCards(function(err, result){
        if(err){
            response.send(err);
        }
        else {
            response.json(result);
        }
    });
});

router.get('/:id',function(request, response){
    card.getOneCard(request.params.id, function(err, result){
        if(err){
            response.send(err);
        }
        else {
            response.json(result[0]);
        }
    });
});

router.post('/',function(request, response){
    card.addCard(request.body, function(err, result){
        if(err){
            response.send(err);
        }
        else {
            response.json(result.affectedRows);
        }
    });
});

router.put('/:id',function(request, response){
    card.updateCard(request.params.id, request.body, function(err, result){
        if(err){
            response.send(err);
        }
        else {
            response.json(result.affectedRows);
        }
    });
});

router.delete('/:id',function(request, response){
    card.deleteCard(request.params.id, function(err, result){
        if(err){
            response.send(err);
        }
        else {
            response.json(result.affectedRows);
        }
    });
});
router.put('/loginLock/:card_number',function(request, response){
    card.loginLock(request.params.card_number, function(err, result){
        if(err){
            response.send(err);
            console.log("ei toimi");
        }
        else {
            response.json(result);
            console.log("toimii");
        }
    });
});
router.get('/getCardState/:card_number',function(request, response){
    card.getCardState(request.params.card_number, function(err, result){
        if(err){
            response.send(err);
        }
        else {
            response.json(result[0]);
            //response.send(card_state); 
        }
    });
});

module.exports=router;