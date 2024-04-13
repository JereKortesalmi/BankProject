#include "withdrawcall.h"

withdrawCall::withdrawCall(QObject *parent)
    : QObject{parent}
{
      qDebug()<<"withdrawCall was constructed.";
}

void withdrawCall::sendTransaction(QByteArray token, int id, double sum)
{


    qDebug()<<"sendRequest from withdrawCall()";
    //Esimerkkidata
    QDateTime current = QDateTime::currentDateTime();
    QJsonObject jsonObj;
    jsonObj.insert("transaction_account_id", id);
    jsonObj.insert("transaction_atm_id","1");           // read from file will be added somewhere else, so will need to add variable here
    jsonObj.insert("transaction_time", current.toString());
    jsonObj.insert("transaction_type","WITHDRAW");
    jsonObj.insert("transaction_amount", QString::number(sum));


    QUrl url("http://localhost:3000/withdraw/" + QString::number(id));
    QNetworkRequest request(url);

    //WEBTOKEN ALKU
    myToken="Bearer "+token;
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU


    w_manager = new QNetworkAccessManager(this);
    w_reply = w_manager->put(request,QJsonDocument(jsonObj).toJson());
    connect(w_manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(onManagerFinished(QNetworkReply*)));
    connect(w_reply, SIGNAL(errorOccurred(QNetworkReply::NetworkError)),
            this, SLOT(onErrorOccurred(QNetworkReply::NetworkError)));
    w_manager->deleteLater();
}

void withdrawCall::getAtmInfo(QByteArray token, int id)
{
    if (token.isEmpty()) {
        return;
    }
    else {
        QUrl url("http://localhost:3000/atm/" + QString::number(id));
        QNetworkRequest request(url);

        //WEBTOKEN ALKU
        myToken="Bearer "+token;
        request.setRawHeader(QByteArray("Authorization"),(myToken));
        //WEBTOKEN LOPPU

        w_manager = new QNetworkAccessManager(this);
        w_reply = w_manager->get(request);
        connect(w_manager, SIGNAL(finished(QNetworkReply*)),this,SLOT(onManagerFinished(QNetworkReply*)));
        connect(w_reply,SIGNAL(errorOccurred(QNetworkReply::NetworkError)),
                this, SLOT(onErrorOccurred(QNetworkReply::NetworkError)));
    }
}

withdrawCall::~withdrawCall()
{
    qDebug()<<"witdrawManager was destroyed";
}

QByteArray withdrawCall::getResponse_data() const
{
    return response_data;
}

void withdrawCall::checkBills(int withdrawal)
{
    qDebug()<<"checkBills()";
    //int original = withdrawal;
    withdrawAmount = withdrawal;
    bool test = checkBillsAvailable();
    if(test==true) {
        removeBills();
    }
    else {
        qDebug()<<"No bills to give";
    }

   /* while(withdrawAmount != 0) {
        if(withdrawAmount>=200 )  {
            if((withdrawAmount % 200)==0) {
                set_200_bills++;
                withdrawAmount = withdrawAmount-200;
            }
            else if((withdrawAmount % 100) == 0) {

            }
            else if((withdrawAmount % 50) != 0) {

            }
            else {
                if((withdrawAmount % 10) == 0 && (withdrawAmount % 20) != 0 && (withdrawAmount % 50) != 0) {
                    set_200_bills++;
                    withdrawAmount = withdrawAmount-200;
                }
                else {
                    set_200_bills++;
                    withdrawAmount = withdrawAmount-200;
                }
            }
        }
        if(withdrawAmount>=100) {
            if((withdrawAmount % 100) == 0 ) {
                set_100_bills++;
                withdrawAmount = withdrawAmount-100;
            }
            else if((withdrawAmount % 50 != 0) && (withdrawAmount %200) != 0) {

            }
            else {
                set_100_bills++;
                withdrawAmount = withdrawAmount-100;

            }
        }
        if(withdrawAmount>=50) {
            if((withdrawAmount % 50) == 0) {
                // jos 50 tulee sopiva lukema
                set_50_bills++;
                withdrawAmount = withdrawAmount-50;
            }
            else if((withdrawAmount % 20) == 0) {
                // jos 20 tulee sopiva lukema
            }
            else {
                if((withdrawAmount % 10) == 0 && (withdrawAmount % 20) != 0) {
                    set_50_bills++;
                    withdrawAmount = withdrawAmount-50;
                }
                else {
                    set_50_bills++;
                    withdrawAmount = withdrawAmount-50;

                }
            }
        }
        if(withdrawAmount>=20) {
            if((withdrawAmount % 20)==0) {
                set_20_bills++;
                withdrawAmount = withdrawAmount-20;
            }
            else if((withdrawAmount % 100) == 0){

            }
            else if((withdrawAmount % 50) == 0) {

            }

            else {
                set_20_bills++;
                withdrawAmount = withdrawAmount-20;
            }
        }
        else {
            withdrawAmount = 0;
        }
    }
    */

    /*
    qDebug()<<"Noston määrä: " << original;
    qDebug()<<"Setelit: ";
    qDebug()<<"200: " << set_200_bills;
    qDebug()<<"100: "<< set_100_bills;
    qDebug()<<"50: " << set_50_bills;
    qDebug()<<"20: " << set_20_bills;
    */
}

bool withdrawCall::checkBillsAvailable()
{
    qDebug()<<"checkBillsAvailable()";
    qDebug() << "withdraw Amount = " << withdrawAmount;
    int original = 0;

// WITHDRAW SET BILLS

    if(bills_200 > 0) {
        usable_200 = true;
    }
    else {
        usable_200 = false;
    }
    if(bills_100 > 0) {
        usable_100 = true;
    }
    else {
        usable_100=false;
    }
    if(bills_50 > 0) {
        usable_50 = true;
    }
    else {
        usable_50 = false;
    }
    if(bills_20 > 0) {

        usable_20 = true;
    }
    else {
        usable_20 = false;
    }

    while(withdrawAmount >= 200 && usable_200) {
        qDebug() << "withdraw Amount =" << withdrawAmount << " current=" << original;
        if(bills_200 >= set_200_bills) {
                usable_200 = true;
        }
        else {
            usable_200 = false;
            break;
        }

        if(usable_200==true) {
            if(((withdrawAmount) >= 200)) {
                if((withdrawAmount % 200) == 10) {
                    if(bills_20 >= (set_20_bills + 3)) {
                        set_20_bills = set_20_bills+3;
                        withdrawAmount = withdrawAmount-60;
                    }
                }
                else if(((withdrawAmount) % 200) == 50) {
                    if(bills_50>= set_50_bills+1 && bills_200 >= set_200_bills) {
                        set_50_bills++;
                        set_200_bills++;
                        usable_200=true;
                        usable_50=true;
                        withdrawAmount = withdrawAmount-250;
                    }

                }
                else if(((withdrawAmount) % 200) > 100) {
                    if(bills_200>=set_200_bills) {
                        set_200_bills++;
                        withdrawAmount = withdrawAmount - 200;
                        usable_200 = true;
                    }
                }
                else {
                    set_200_bills++;
                    withdrawAmount = withdrawAmount -200;
                }

            }

            else {

            }

        }
        else {
            break;
        }

    } // while 200


    while(withdrawAmount >= 100 && usable_100) {
        qDebug() << "withdraw Amount =" << withdrawAmount << " current=" << original;

        if(bills_100 >= set_100_bills) {
            usable_100 = true;
        }
         else {
            usable_100 = false;
            break;
        }
        if(usable_100 == true) {
            if(((withdrawAmount) >= 100) && usable_100) {
                if(((withdrawAmount-original) % 100) == 10) {
                    if(bills_20 >= (set_20_bills+3)) {
                        set_20_bills = set_20_bills +3;
                        withdrawAmount = withdrawAmount -60;
                        usable_20=true;
                    }

                }
                 /*
                else if(((withdrawAmount) % 100) == 50){
                    set_50_bills++;
                    set_100_bills++;
                    withdrawAmount = withdrawAmount -150;
                }
                */
                else {
                    if(bills_100 >= (set_100_bills++ )) {
                        set_100_bills++;
                        withdrawAmount = withdrawAmount -100;
                        usable_100 = true;
                    }
            }
            }
            else {
                usable_100 = false;
            }
        }
        else {
            break;
        }
    } // while 100

    while(withdrawAmount >= 50 && usable_50)  {

        qDebug() << "withdraw Amount =" << withdrawAmount << " current=" << original;

        if(bills_50 >= set_50_bills) {
            usable_50 = true;
        }
        else {
            usable_50 = false;
            break;
        }
        if(usable_50 == true) {
            if(((withdrawAmount) >= 50)) {
                if((withdrawAmount % 50) == 10) {
                    if(bills_20 >= (set_20_bills+3)) {
                        if(bills_20 >= set_20_bills+3) {
                            set_20_bills = set_20_bills+3;
                            withdrawAmount=withdrawAmount-60;
                        }
                        else {
                            return false;
                        }
                    }
                }
                else {
                    if(bills_50 >= set_50_bills++) {
                        set_50_bills++;
                        withdrawAmount=withdrawAmount-50;
                        usable_50 = true;
                    }
                    else {
                        usable_50 = false;
                        return false;
                    }
                }

            }
            else {
                usable_50 = false;
            }
        }
        else {
            break;
        }
    } // while 50
    while(withdrawAmount>=20 && usable_20) {

        qDebug() << "withdraw Amount =" << withdrawAmount << " current=" << original;

        if(bills_20 >= set_20_bills) {
            usable_20 = true;
        }
        else {
            usable_20 = false;
            return false;
        }
        if(usable_20 == true) {

            if(((withdrawAmount) >= 20)) {
                if(((withdrawAmount) % 20 ) == 10) {

                    set_20_bills = false;
                    return false;
                    break;
                }
                else {
                    if(bills_20 >= set_20_bills++) {
                        set_20_bills++;
                        withdrawAmount = withdrawAmount-20;
                        usable_20=true;
                    }
                    else {
                        usable_20=false;
                        return false;
                    }
                }
            }
            else {
                usable_20 = false;
            }
        }
        else {
            break;
        }
    } // while 20

    /*
    if(usable_200 && usable_100 && usable_50 && usable_20) {
    return true;
    }
    else {
    return false;
    }
    *
    */

    if(!usable_200 && !usable_100 && usable_50 && usable_20) {
        return false;
    }
    else {
        return true;
    }
}
void withdrawCall::clearBills()
{
    set_20_bills = 0;
    set_50_bills = 0;
    set_100_bills = 0;
    set_200_bills = 0;
}

void withdrawCall::removeBills()
{

    qDebug()<<"Remove bills: ";

    bills_200 = bills_200-set_200_bills;
    bills_100 = bills_100-set_100_bills;
    bills_50 = bills_50-set_50_bills;
    bills_20 = bills_20-set_20_bills;

    qDebug() << "Bills removed";



        // can't give out bills


    /*
    else {
        // some bills aren't enough, let's see which one.
        QList<int> test;
        if(bills_200 <= set_200_bills ) {
            test.append(200);
        }
        if(bills_100 <= set_100_bills) {
            test.append(100);
        }
        if(bills_50 <= set_50_bills) {
            test.append(50);
        }
        if(bills_20 <= set_20_bills) {
            test.append(20);
        }

        for(int i=0; i< test.length();i++) {
            if(test[i] == 200) {
                if(bills_100 >= (set_100_bills + (set_200_bills * 2))) {
                    set_100_bills = set_100_bills + set_200_bills * 2;
                    set_200_bills = 0;
                    //test.removeFirst();
                }
                else if(bills_50 >= (set_50_bills+ (set_200_bills *4))) {
                    set_50_bills = set_50_bills + set_200_bills * 4;
                    set_200_bills = 0;
                    //test.removeFirst();
                }
                else if(bills_20 >= (set_20_bills + (set_200_bills * 10))) {
                    set_20_bills = set_20_bills + set_200_bills * 10;
                    set_200_bills = 0;
                    //test.removeFirst();
                }
                else {
                    //impossible so far
                }
            }
            if(test[i] == 100) {
                if(bills_50 >= (set_50_bills + (set_100_bills *2))) {
                    set_50_bills = set_50_bills + set_100_bills * 2;
                    set_100_bills = 0;
                    //test.removeFirst();
                }
                else if(bills_20 >= (set_20_bills + (set_100_bills * 5))) {
                    set_20_bills = set_20_bills + set_100_bills * 5;
                    set_100_bills = 0;
                    //test.removeFirst();
                }
                else {
                    // impossible so far
                }
            }
            if(test[i] == 50) {
                // impossible if value is 50, 110, 190 etc.
            }
            if(test[i] == 20) {
                // impossible for 20, 40, 60, 80, 110 160, 190 but 50 and 100, 200 can be possible.
            }

        }
    }
    */
}

void withdrawCall::onManagerFinished(QNetworkReply *reply)
{
    if(reply->error()) {
        qDebug() << reply->errorString();
        return;
    }
    response_data = reply->readAll();

    emit dataRead();


}

void withdrawCall::onErrorOccurred(QNetworkReply::NetworkError code)
{
    qDebug()<<"Network error:" << code;
}
