const express=require('express');
const router=express.Router();
const card=require('../models/card_model');
const bcrypt=require('bcryptjs');
const jwt=require('jsonwebtoken');
const dotenv=require('dotenv');
dotenv.config();

router.post('/',function(request, response){
    if(request.body.card_number && request.body.card_pin){
        card.login(request.body.card_number, function(err,result){
            if(err){
                console.log(err.errno);
                response.json(err.errno);
            }
            else{
                if(result.length >0){
                   bcrypt.compare(request.body.card_pin, result[0].card_pin, function(err, compareResult){
                        if(compareResult){
                            console.log('Kirjautuminen ok');
                            const token=genToken({card_number: request.body.card_number});
                            response.send(token);
                        }
                        else {
                            console.log("Väärä pinkoodi");
                            response.send(false);
                        }
                    })
                }
                else {
                    console.log("tunnusta ei ole");
                    response.send(false);
                }

            }
        });
    }
    else {
        console.log("Kortin numero tai pinkoodi puuttuu")
        response.send(false);
    }
});

function genToken(value){
    return jwt.sign(value, process.env.MY_TOKEN, {expiresIn: '200s'});
}


module.exports=router;