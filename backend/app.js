var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');
const jwt=require('jsonwebtoken');

var indexRouter = require('./routes/index');
var usersRouter = require('./routes/users');
var accountsRouter = require('./routes/account');
var atmRouter = require ('./routes/atm');
var transactionRouter = require ('./routes/transaction');
var accounts_to_cardsRouter = require ('./routes/accounts_to_cards');
var cardRouter = require ('./routes/card');
var customerRouter = require ('./routes/customer');
var loginRouter = require('./routes/login');
var transactions_per_accountRouter = require('./routes/transactions_per_account');
var transferRouter = require('./routes/transfer');

var app = express();

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

app.use('/', indexRouter);
app.use('/login', loginRouter);
//suojaa että eka pitää kirjautua että pääsee muihin
//app.use(authenticateToken);

//app.use('/users', usersRouter);
//app.use('/accounts_to_cards',accounts_to_cardsRouter);
//app.use('/accounts', accountsRouter);
//app.use('/customer', customerRouter);
//app.use('/transactions_per_account',transactions_per_accountRouter);

app.use(authenticateToken);
app.use('/atm', atmRouter);
app.use('/transaction', transactionRouter);
app.use('/card', cardRouter);
app.use('/accounts_to_cards',accounts_to_cardsRouter);
app.use('/accounts', accountsRouter);
app.use('/customer', customerRouter);
app.use('/transactions_per_account',transactions_per_accountRouter);
app.use('/transfer', transferRouter);


function authenticateToken(req, res, next) {
    const authHeader = req.headers['authorization']
    const token = authHeader && authHeader.split(' ')[1]
  
    console.log("token = "+token);
    if (token == null) return res.sendStatus(401)
  
    jwt.verify(token, process.env.MY_TOKEN, function(err, user) {
  
      if (err) return res.sendStatus(403)

      req.user = user
  
      next()
    })
  }


module.exports = app;
