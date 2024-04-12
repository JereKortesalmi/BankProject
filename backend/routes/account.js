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

router.get('/getaccountid/:cardNumber',function(request,response){
    const cardNumber = request.params.cardNumber;
    course.getAccountId(cardNumber, function(err,result){
        if(err){
            response.send(err);
        } else {
            if(result.length>0){
                let accounts = [];

                result.forEach(row => {
                    const accountDetails ={
                        account_id: row.account_id,
                        account_customer_id: row.account_customer_id,
                        account_type: row.account_type,
                        account_balance: row.account_balance                  
                };
                    accounts.push(accountDetails);
                });
            response.json(accounts);
            } else {
            response.send("No account on this card");
            }
        }
    });
});

router.get('/:cardNumber',function(request,response){
    const cardNumber = request.body.card_number;
    course.getByCardNumber(cardNumber, function(err,result){
        if(err){
            response.send(err);
        } else {
            response.send(result);
        }
    });
});
   
   module.exports=router;