#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "testmodel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_acSave_triggered();
    void on_acLoad_triggered();

    void on_acSaveToJSON_triggered();

    void on_acOpenFromJSON_triggered();

private:
    Ui::MainWindow *ui;

    TestModel *model;
};
#endif // MAINWINDOW_H
