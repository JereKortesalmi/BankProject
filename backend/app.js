var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');

var indexRouter = require('./routes/index');
var usersRouter = require('./routes/users');
//var accountsRouter = require('./routes/account');
var atmRouter = require ('./routes/atm');
var transactionRouter = require ('./routes/transaction');
var cardRouter = require ('./routes/card');
var customerRouter = require ('./routes/customer');

var app = express();

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

app.use('/', indexRouter);
app.use('/users', usersRouter);
app.use('/atm', atmRouter);
app.use('/transaction', transactionRouter);
app.use('/card', cardRouter);
app.use('/customer', customerRouter);

module.exports = app;
