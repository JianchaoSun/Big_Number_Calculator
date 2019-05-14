#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "BigNumber.hpp"

#include <algorithm>
#include <sstream>
#include <iterator>

BigNumber  ans("0");
BigNumber one("0");
BigNumber two("0");

bool divT =false;
bool mulT =false;
bool addT =false;
bool modT = false;
bool subT = false;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    std::ostringstream oss;

    if (!ans.v.empty())
    {
      // Convert all but the last element to avoid a trailing ","
      std::copy(ans.v.begin(), ans.v.end()-1,
          std::ostream_iterator<int>(oss));

      // Now add the last element with no delimiter
      oss << ans.v.back();
    }
    std::string copy(oss.str());
    std::reverse(copy.begin(), copy.end());

    ui->setupUi(this);
    ui ->Display->setText(QString::fromStdString(copy));

    QPushButton *numButton[0];
    for(int i=0;i<10;i++){
        QString bName ="b"+QString::number(i);
        numButton[i] = MainWindow::findChild<QPushButton *>(bName);
        connect(numButton[i],SIGNAL(released()),this,SLOT(numPressed()));
    }

    connect(ui->badd,SIGNAL(released()),this,SLOT(mathButtonPressed()));
    connect(ui->bmul,SIGNAL(released()),this,SLOT(mathButtonPressed()));
    connect(ui->bsub,SIGNAL(released()),this,SLOT(mathButtonPressed()));
    connect(ui->bmod,SIGNAL(released()),this,SLOT(mathButtonPressed()));
    connect(ui->bdiv,SIGNAL(released()),this,SLOT(mathButtonPressed()));
    connect(ui->bequ,SIGNAL(released()),this,SLOT(equalButton()));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::numPressed(){
    QPushButton *button = (QPushButton *)sender();
    QString butval = button->text();
    QString displayValue = ui->Display->text();
    if((displayValue.toDouble()==0)||(displayValue.toDouble()==0.0)){
        ui->Display->setText(butval);
    }else{
        QString newVal = displayValue +butval;
        one = BigNumber(newVal.toStdString());

       // double dblNewVal = newVal.toDouble();
        ui->Display->setText(newVal);
    }

}

void MainWindow::mathButtonPressed(){
     divT =false;
     mulT =false;
     addT =false;
     modT = false;
     subT = false;
     QString displayV = ui->Display->text();

     ans = BigNumber(displayV.toStdString());

     QPushButton *button = (QPushButton*)sender();
     QString butVal = button->text();

     if(QString::compare(butVal,"/",Qt::CaseInsensitive)==0){
         divT = true;
     }else if(QString::compare(butVal,"+",Qt::CaseInsensitive)==0){
         addT = true;
     }else if(QString::compare(butVal,"-",Qt::CaseInsensitive)==0){
         subT = true;
     }else if(QString::compare(butVal,"*",Qt::CaseInsensitive)==0){
         mulT = true;
     }else if(QString::compare(butVal,"%",Qt::CaseInsensitive)==0){
         modT = true;
     }
     ui ->Display->setText("");
}
void MainWindow::equalButton(){
    QString curV = ui->Display->text();
    one = BigNumber(curV.toStdString());
    if(addT||subT||mulT||divT||modT){
        if(addT){
            ans = ans+one;
        }else if(subT){
            ans = ans-one;
        }else if(mulT){
            ans = ans*one;
        }else if(divT){
            ans = ans/one;
        }else if(modT){
            ans = ans%one;
        }
    }
    std::ostringstream oss;

    if (!ans.v.empty())
    {
      // Convert all but the last element to avoid a trailing ","
      std::copy(ans.v.begin(), ans.v.end()-1,
          std::ostream_iterator<int>(oss));

      // Now add the last element with no delimiter
      oss << ans.v.back();
    }
    std::string copy(oss.str());
    std::reverse(copy.begin(), copy.end());

    ui->setupUi(this);
    ui ->Display->setText(QString::fromStdString(copy));
}
