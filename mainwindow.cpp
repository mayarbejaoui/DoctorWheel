#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "chatboxconnectiondialog.h"
#include <QMessageBox>
#include <QPdfWriter>
#include <QPainter>
#include <QDesktopServices>
#include <QTcpSocket>
#include <QTextStream>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /******* LOGIN *******/
    ui->Login_line_ID->setValidator( new QIntValidator(0, 99999999, this));
    ui->stackedWidget->setCurrentIndex(0);
    ui->Menu_push_Employees->setDisabled(true);
    ui->Menu_push_Pistes->setDisabled(true);
    ui->Menu_push_Visits->setDisabled(true);
    ui->Menu_push_Vehicules->setDisabled(true);
    ui->Menu_push_Equipements->setDisabled(true);
    ui->Menu_push_Reservations->setDisabled(true);

    /******* GESTION EMPLOYEE *******/
    ui->Empl_line_Salaire->setValidator( new QIntValidator(0, 99999999, this));
    ui->Empl_combo_ID->setModel(E.afficher_id());
    ui->tableView->setModel (E.afficher());
    nSocket=new QTcpSocket(this);
    connect(nSocket,&QTcpSocket::readyRead,[&](){
        QTextStream T(nSocket);
        auto text=T.readAll();
        ui->Empl_text_Chatbox->append(text);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Login_push_Login_clicked()
{
    QString ID = ui->Login_line_ID->text();
    QString PASSWORD = ui->Login_line_MDP->text();
    QSqlQuery query;
    QString poste;
    if(query.exec("SELECT * from EMPLOYEES where ID='"+ID+"' and PASSWORD='"+PASSWORD+"'" ))
    {
        if (query.next())
        {
            poste=query.value(4).toString();

            ui->stackedWidget->setCurrentIndex(1);
            if (poste.compare("Administrateur")==0){
                ui->Menu_push_Employees->setEnabled(true);
                ui->Menu_push_Pistes->setEnabled(true);
                ui->Menu_push_Visits->setEnabled(true);
                ui->Menu_push_Vehicules->setEnabled(true);
                ui->Menu_push_Equipements->setEnabled(true);
                ui->Menu_push_Reservations->setEnabled(true);
            }
            if (poste.compare("Employees")==0){
                ui->Menu_push_Employees->setEnabled(true);
                ui->Menu_push_Pistes->setEnabled(false);
                ui->Menu_push_Visits->setEnabled(false);
                ui->Menu_push_Vehicules->setEnabled(false);
                ui->Menu_push_Equipements->setEnabled(false);
                ui->Menu_push_Reservations->setEnabled(false);
            }
            if (poste.compare("Pistes")==0){
                ui->Menu_push_Employees->setEnabled(false);
                ui->Menu_push_Pistes->setEnabled(true);
                ui->Menu_push_Visits->setEnabled(false);
                ui->Menu_push_Vehicules->setEnabled(false);
                ui->Menu_push_Equipements->setEnabled(false);
                ui->Menu_push_Reservations->setEnabled(false);
            }
            if (poste.compare("Visits")==0){
                ui->Menu_push_Employees->setEnabled(false);
                ui->Menu_push_Pistes->setEnabled(false);
                ui->Menu_push_Visits->setEnabled(true);
                ui->Menu_push_Vehicules->setEnabled(false);
                ui->Menu_push_Equipements->setEnabled(false);
                ui->Menu_push_Reservations->setEnabled(false);
            }
            if (poste.compare("Vehicules")==0){
                ui->Menu_push_Employees->setEnabled(false);
                ui->Menu_push_Pistes->setEnabled(false);
                ui->Menu_push_Visits->setEnabled(false);
                ui->Menu_push_Vehicules->setEnabled(true);
                ui->Menu_push_Equipements->setEnabled(false);
                ui->Menu_push_Reservations->setEnabled(false);
            }
            if (poste.compare("Equipements")==0){
                ui->Menu_push_Employees->setEnabled(false);
                ui->Menu_push_Pistes->setEnabled(false);
                ui->Menu_push_Visits->setEnabled(false);
                ui->Menu_push_Vehicules->setEnabled(false);
                ui->Menu_push_Equipements->setEnabled(true);
                ui->Menu_push_Reservations->setEnabled(false);
            }
            if (poste.compare("Reservations")==0){
                ui->Menu_push_Employees->setEnabled(false);
                ui->Menu_push_Pistes->setEnabled(false);
                ui->Menu_push_Visits->setEnabled(false);
                ui->Menu_push_Vehicules->setEnabled(false);
                ui->Menu_push_Equipements->setEnabled(false);
                ui->Menu_push_Reservations->setEnabled(true);
            }
            QString NOM=query.value(1).toString();
            QString PRENOM=query.value(2).toString();
            ui->Login_lebel_Info->setText("Connecté: "+NOM+" "+PRENOM+"");
            ui->Menu_label_info->setText("Logged in as: "+NOM+" "+PRENOM+"\nGestion: "+poste+"");
        }
        else
        {
            ui->Login_lebel_Info->setText("ID/Mot de passe incorrect");
        }
    }
}

void MainWindow::on_Menu_push_Employees_clicked(){ui->stackedWidget->setCurrentIndex(2);}
void MainWindow::on_Menu_push_Equipements_clicked(){ui->stackedWidget->setCurrentIndex(6);}
void MainWindow::on_Menu_push_Pistes_clicked(){ui->stackedWidget->setCurrentIndex(8);}
void MainWindow::on_Menu_push_Vehicules_clicked(){ui->stackedWidget->setCurrentIndex(3);}
void MainWindow::on_Menu_push_Reservations_clicked(){ui->stackedWidget->setCurrentIndex(5);}
void MainWindow::on_Menu_push_Reture_clicked(){ui->stackedWidget->setCurrentIndex(0);}
void MainWindow::on_Menu_push_Quitter_clicked(){close();}



void MainWindow::on_Empl_push_Ajouter_clicked()
{
    int ID=ui->Empl_line_ID->text().toInt();
    QString NOM=ui->Empl_line_Nom->text();
    QString PRENOM=ui->Empl_line_Prenom->text();
    QString ADRESSE=ui->Empl_line_Adresse->text();
    QString POSTE=ui->Empl_combo_Poste->currentText();
    QString PASSWORD=ui->Empl_line_MDP->text();
    int SALAIRE=ui->Empl_line_Salaire->text().toInt();

    Employee E(ID,NOM,PRENOM,ADRESSE,POSTE,PASSWORD,SALAIRE);
    bool test=E.ajouter();
    if(test)
    {
        ui->Empl_label_GInfo->setText("Ajout Effectué");
        ui->tableView->setModel(E.afficher());
        ui->Empl_combo_ID->setModel (E.afficher_id());
    }
    else
    {
        ui->Empl_label_GInfo->setText("Ajout non effectué");
    }
}

void MainWindow::on_Empl_push_Modifier_clicked()
{
    int ID=ui->Empl_line_ID->text().toInt();
    QString NOM=ui->Empl_line_Nom->text();
    QString PRENOM=ui->Empl_line_Prenom->text();
    QString ADRESSE=ui->Empl_line_Adresse->text();
    QString POSTE=ui->Empl_combo_Poste->currentText();
    QString PASSWORD=ui->Empl_line_MDP->text();
    int SALAIRE=ui->Empl_line_Salaire->text().toInt();

    Employee E(ID,NOM,PRENOM,ADRESSE,POSTE,PASSWORD,SALAIRE);
    bool test=E.modifier();
    if(test)
    {
        ui->Empl_label_GInfo->setText("Modification effectué");
        ui->tableView->setModel(E.afficher());
        ui->Empl_combo_ID->setModel (E.afficher_id());
    }
    else
    {
        ui->Empl_label_GInfo->setText("Modification non effectué");
    }
}

void MainWindow::on_Empl_push_Supprimer_clicked()
{
    Employee E;
    E.setid(ui->Empl_combo_ID->currentText().toInt());
    bool test=E.supprimer(E.getid());
    if(test)
    {
        ui->Empl_label_GInfo->setText("Suppression effectué");
        ui->tableView->setModel(E.afficher());
        ui->Empl_combo_ID->setModel (E.afficher_id());
    }
    else
    {
        ui->Empl_label_GInfo->setText("Suppression non effectué");
    }
}

void MainWindow::on_Empl_combo_ID_currentIndexChanged(int)
{
    int id=ui->Empl_combo_ID->currentText().toInt();
    QString id_1=QString::number(id);
    QSqlQuery query;
    query.prepare("SELECT * FROM EMPLOYEES where ID='"+id_1+"'");
    if(query.exec())
    {
        while (query.next())
        {
            ui->Empl_line_ID->setText(query.value(0).toString()) ;
            ui->Empl_line_Nom->setText(query.value(1).toString()) ;
            ui->Empl_line_Prenom->setText(query.value(2).toString()) ;
            ui->Empl_line_Adresse->setText(query.value(3).toString()) ;
            ui->Empl_combo_Poste->setCurrentText(query.value(4).toString()) ;
            ui->Empl_line_Salaire->setText(query.value(5).toString()) ;
            ui->Empl_line_MDP->setText(query.value(6).toString()) ;
        }
    }
    else
    {
        ui->Empl_label_GInfo->setText("Echec de chargement");
    }
}

void MainWindow::on_Empl_line_Recherche_textChanged(const QString &arg1)
{
    if (ui->Empl_radio_ID->isChecked()==true)
    {
        E.clearTable(ui->tableView);
        E.chercheID(ui->tableView,arg1);
    }
    if (ui->Empl_radio_Nom->isChecked()==true)
    {
        E.clearTable(ui->tableView);
        E.chercheNom(ui->tableView,arg1);
    }
}

void MainWindow::on_Empl_push_TriSalire_clicked()
{
    ui->Empl_label_TInfo->setText("Tri Salaire effectué");
    ui->tableView->setModel(E.tri_salire());
}

void MainWindow::on_Empl_push_TriPoste_clicked()
{
        ui->Empl_label_TInfo->setText("Tri Poste effectué");
        ui->tableView->setModel(E.tri_poste());
}

void MainWindow::on_Empl_push_TriNom_clicked()
{
    ui->Empl_label_TInfo->setText("Tri Nom effectué");
    ui->tableView->setModel(E.tri_nom());
}

void MainWindow::on_Empl_push_ExportPDF_clicked()
{
    QPdfWriter pdf("C:/Users/USER/Desktop/GestionEmployee/Liste.pdf");
    QPainter painter(&pdf);
    int i = 4000;
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 30));
    painter.drawText(3000,1500,"LISTE DES EMPLOYEES");
    painter.setPen(Qt::blue);
    painter.setFont(QFont("Arial", 50));
    //painter.drawRect(2700,200,6300,2600);
    painter.drawRect(0,3000,9600,500);
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 9));
    painter.drawText(300,3300,"ID");
    painter.drawText(1800,3300,"NOM");
    painter.drawText(2800,3300,"PRENOM");
    painter.drawText(3800,3300,"ADRESSE");
    painter.drawText(5000,3300,"POSTE");
    painter.drawText(6900,3300,"SALAIRE");
    QSqlQuery query;
    query.prepare("<SELECT CAST( GETDATE() AS Date ) ");
    time_t tt;
    struct tm* ti;
    time(&tt);
    ti=localtime(&tt);
    asctime(ti);
    painter.drawText(500,300, asctime(ti));
    query.prepare("select ID,NOM,PRENOM,ADRESSE,POSTE,SALAIRE from EMPLOYEES");
    query.exec();
    while (query.next())
    {
        painter.drawText(300,i,query.value(0).toString());
        painter.drawText(1800,i,query.value(1).toString());
        painter.drawText(2800,i,query.value(2).toString());
        painter.drawText(3800,i,query.value(3).toString());
        painter.drawText(4800,i,query.value(4).toString());
        painter.drawText(6700,i,query.value(5).toString());
        i = i +500;
    }
    int reponse = QMessageBox::question(this, "PDF généré", "Afficher le PDF ?", QMessageBox::Yes |  QMessageBox::No);
    if (reponse == QMessageBox::Yes)
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/USER/Desktop/GestionEmployee/Liste.pdf"));
        painter.end();
    }
    if (reponse == QMessageBox::No)
    {
        painter.end();
    }
}

void MainWindow::on_Empl_push_Send_clicked()
{
    QTextStream T(nSocket);
    T << ui->Empl_line_Nickname-> text() << ": " << ui->Empl_line_Message->text();
    nSocket->flush();
    ui->Empl_line_Message->clear();
}

void MainWindow::on_Empl_push_Bind_clicked()
{
    chatboxconnectiondialog D(this);
    if(D.exec()==QDialog::Rejected)
    {return;
    }
    nSocket->connectToHost(D.hostname(),D.port());
}

void MainWindow::on_Empl_push_Statistiques_clicked()
{
    stat = new Employees_Statistiques(this);
    stat->show();
}

void MainWindow::on_Empl_push_reture_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_Menu_push_Visits_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);

}
