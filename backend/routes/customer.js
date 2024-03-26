const express=require('express');
const router=express.Router();
const customer=require('../models/customer_model');

router.get('/',function(request, response){
    customer.getAllCustomers(function(err, result){
        if(err){
            response.send(err);
        }
        else {
            response.json(result);
        }
    });
});

router.get('/:id',function(request, response){
    customer.getOneCustomer(request.params.id, function(err, result){
        if(err){
            response.send(err);
        }
        else {
            response.json(result[0]);
        }
    });
});

router.post('/',function(request, response){
    customer.addCustomer(request.body, function(err, result){
        if(err){
            response.send(err);
        }
        else {
            response.json(result.affectedRows);
        }
    });
});

router.put('/:id',function(request, response){
    customer.updateCustomer(request.params.id, request.body, function(err, result){
        if(err){
            response.send(err);
        }
        else {
            response.json(result.affectedRows);
        }
    });
});

router.delete('/:id',function(request, response){
    customer.deleteCustomer(request.params.id, function(err, result){
        if(err){
            response.send(err);
        }
        else {
            response.json(result.affectedRows);
        }
    });
});