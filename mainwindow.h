#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QWidget>
#include <QMainWindow>
#include <QSortFilterProxyModel>
#include <QTextTableFormat>
#include <QStandardItemModel>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QDesktopWidget>
#include <QSettings>
#include <QPrinter>
#include <QTextStream>
#include <QFile>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QDataStream>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QDialog>
#include <QSettings>
#include <QDataStream>
#include "employees_statistiques.h"
#include "connection.h"
#include "employee.h"

QT_BEGIN_NAMESPACE
QT_CHARTS_USE_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class QTcpSocket;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Login_push_Login_clicked();

    void on_Menu_push_Employees_clicked();
    void on_Menu_push_Equipements_clicked();
    void on_Menu_push_Pistes_clicked();
    void on_Menu_push_Vehicules_clicked();
    void on_Menu_push_Reservations_clicked();
    void on_Menu_push_Reture_clicked();
    void on_Menu_push_Quitter_clicked();
    void on_Empl_push_Ajouter_clicked();

    void on_Empl_push_Modifier_clicked();

    void on_Empl_push_Supprimer_clicked();

    void on_Empl_combo_ID_currentIndexChanged(int index);

    void on_Empl_line_Recherche_textChanged(const QString &arg1);

    void on_Empl_push_TriSalire_clicked();

    void on_Empl_push_TriPoste_clicked();

    void on_Empl_push_TriNom_clicked();

    void on_Empl_push_ExportPDF_clicked();

    void on_Empl_push_Send_clicked();

    void on_Empl_push_Bind_clicked();

    void on_Empl_push_Statistiques_clicked();

    void on_Empl_push_reture_clicked();

    void on_Menu_push_Visits_clicked();

private:
    Ui::MainWindow *ui;
    QString tmpemail;
    Employee E;
    QTcpSocket *nSocket;
    Employees_Statistiques *stat;
};
#endif // MAINWINDOW_H
