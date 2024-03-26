const express=require('express');
const router=express.Router();
const course=require('../models/account_model');

router.get('/',function(request, response){
    course.getAllAccounts(function(err, result){
       if(err){
           response.send(err);
       }
       else {
           response.json(result);
       }
    });
});
   
router.get('/:id',function(request, response){
    course.getOneAccount(request.params.id, function(err, result){
        if(err){
            response.send(err);
        }
        else {
            response.json(result[0]);
        }
    });
});

router.post('/',function(request, response){
    course.addAccount(request.body, function(err, result){
        if(err){
            response.send(err);
        }
        else {
            response.json(result.affectedRows);
        }
    });
});

router.put('/:id',function(request, response){
    course.updateAccount(request.params.id, request.body, function(err, result){
        if(err){
            response.send(err);
        }
        else {
            response.json(result.affectedRows);
        }
    });
});

router.delete('/:id', function(request, response){
    course.deleteAccount(request.params.id, function(err, result){
        if(err){
            response.send(err);
        }
        else {
            response.json(result.affectedRows);
        }
    });
});
   
   module.exports=router;