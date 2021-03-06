#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <iostream>
#include <QTableView>
#include <QSqlRecord>
#include <QStandardItemModel>
#include <QString>
#include <QList>


typedef  QString pg_string;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    config_table("table1");

    list_header.append("id");
    list_header.append("only_name");
    list_header.append("first_name");
    list_header.append("last_name");
    list_header.append("email");


    ui->spinBox_index->setMaximum(list_header.size()-1);
    int index =  ui->spinBox_index->value();

   select_colum(list_header[index]);


        db= QSqlDatabase::addDatabase("QPSQL");
            db.setHostName("localhost");
            db.setDatabaseName("eda");
            db.setUserName("postgres");
            //db.setPassword("postgres");
            db.open();

        QSqlQuery query;
        query.exec("SELECT * FROM "+ myTable);


        show_in_table(query,ui->tableViewDB);

}

MainWindow::~MainWindow()
{
    db.close();
    delete ui;
}

void MainWindow::show_in_table(QSqlQuery &q, QTableView *t)
{

    int num_rows=q.size();

    QStandardItemModel *model = new QStandardItemModel(num_rows,1,this);
    QStringList temp;
    temp<<"0"<<"1"<<"2"<<"3"<<"4";
    model->setHorizontalHeaderLabels(temp);


    int i=0;
    while(q.next())
    {
            QList<QStandardItem*> newRow;

            for(int i=0; i<list_header.size(); i++){
                QStandardItem* temp=new QStandardItem(q.record().value(i).toString());
                newRow.append(temp);

            }

            model->insertRow(i,newRow);
            i++;
    }

    t->setModel(model);
}


void MainWindow::clean_table(QTableView *t)
{
    std::cout<< "LIMPIANDO TABLA "<<std::endl;

    t->clearSpans();
    ui->tableViewRespuesta->clearSpans();
}

void MainWindow::on_pushButton_contains_clicked()
{

    ui->spinBox_index->setMaximum(list_header.size()-1);
    int index =  ui->spinBox_index->value();
   select_colum(list_header[index]);


    if(!ui->lineEdit_contains->text().isEmpty())
    {
        std::cout<< "CONTAINS EJECUTANDO "<<std::endl;
        QSqlQuery queryy(db);
        QString entrada=ui->lineEdit_contains->text();
        QString consulta="SELECT * FROM "+ myTable +" WHERE CONTAINS("+myCol+",'"+ entrada +"')";
        std::cout<<consulta.toStdString()<<std::endl;
        queryy.exec(consulta);
        show_in_table(queryy,ui->tableViewRespuesta);
    }
    else
         clean_table(ui->tableViewRespuesta);

}


void MainWindow::on_pushButton_similar_clicked()
{

    ui->spinBox_index->setMaximum(list_header.size()-1);
    int index =  ui->spinBox_index->value();
   select_colum(list_header[index]);



    int distance= ui->spinBox_similar_distance->value()+1;

    if(!ui->lineEdit_similar->text().isEmpty() && distance)
    {
        std::cout<< "SIMILAR EJECUTANDO "<<std::endl;
        QSqlQuery queryy(db);
        QString entrada=ui->lineEdit_similar->text();
        QString consulta="SELECT * FROM "+ myTable +" WHERE SIMILAR_TO("+myCol+",'"+ entrada +"',"+ QString::number(distance) +")";
        std::cout<<consulta.toStdString()<<std::endl;
        queryy.exec(consulta);
        show_in_table(queryy,ui->tableViewRespuesta);
    }
    else
        clean_table(ui->tableViewRespuesta);
}









void MainWindow::config_table(QString t)
{
    myTable = t;
}

void MainWindow::select_colum(QString t)
{
    myCol=t;
}












//query.exec("COPY (SELECT id FROM tabletest ) TO '/tmp/backup.txt' WITH (DELIMITER '|')");
