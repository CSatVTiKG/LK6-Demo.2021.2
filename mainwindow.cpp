#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    model = new TestModel(this);

    ui->tableView->setModel(model);
}

MainWindow::~MainWindow()
{
    delete ui;

    delete model;
}


void MainWindow::on_acSave_triggered()
{
    QString fileName =
                QFileDialog::getSaveFileName(this, tr("Save XML File"),
                                             QDir::currentPath(),
                                             tr("XML Files (*.xml)"));
        if (fileName.isEmpty())
            return;

        QFile file(fileName);
        if (!file.open(QFile::WriteOnly | QFile::Text)) {
            QMessageBox::warning(this, tr("XML demo"),
                                 tr("Cannot write file %1:\n%2.")
                                 .arg(QDir::toNativeSeparators(fileName),
                                      file.errorString()));
            return;
        }

        if (model->writeToXML(&file))
            statusBar()->showMessage(tr("File saved"), 2000);
}

void MainWindow::on_acLoad_triggered()
{
    QString fileName =
                QFileDialog::getOpenFileName(this, tr("Open XML File"),
                                             QDir::currentPath(),
                                             tr("XML Files (*.xml)"));
        if (fileName.isEmpty())
            return;

        QFile file(fileName);
        if (!file.open(QFile::ReadOnly | QFile::Text)) {
            QMessageBox::warning(this, tr("XML demo"),
                                 tr("Cannot read file %1:\n%2.")
                                 .arg(QDir::toNativeSeparators(fileName),
                                      file.errorString()));
            return;
        }

        if (!model->readFromXML(&file)) {
            QMessageBox::warning(this, tr("XML demo"),
                                 tr("Parse error in file %1")
                                 .arg(QDir::toNativeSeparators(fileName)
                                      ));
        } else {
            statusBar()->showMessage(tr("File loaded"), 2000);
        }
}

void MainWindow::on_acSaveToJSON_triggered()
{
    QString fileName =
                QFileDialog::getSaveFileName(this, tr("Save JSON File"),
                                             QDir::currentPath(),
                                             tr("JSON Files (*.json)"));
        if (fileName.isEmpty())
            return;

        QFile file(fileName);
        if (!file.open(QFile::WriteOnly | QFile::Text)) {
            QMessageBox::warning(this, tr("JSON demo"),
                                 tr("Cannot write file %1:\n%2.")
                                 .arg(QDir::toNativeSeparators(fileName),
                                      file.errorString()));
            return;
        }

        model->writeToJSON(&file);
            statusBar()->showMessage(tr("File saved"), 2000);
}

void MainWindow::on_acOpenFromJSON_triggered()
{
    QString fileName =
                QFileDialog::getOpenFileName(this, tr("Open JSON File"),
                                             QDir::currentPath(),
                                             tr("JSON Files (*.json)"));
        if (fileName.isEmpty())
            return;

        QFile file(fileName);
        if (!file.open(QFile::ReadOnly | QFile::Text)) {
            QMessageBox::warning(this, tr("JSON demo"),
                                 tr("Cannot read file %1:\n%2.")
                                 .arg(QDir::toNativeSeparators(fileName),
                                      file.errorString()));
            return;
        }

        QString str = file.readAll();

        if (!model->readFromJSON(str)) {
            QMessageBox::warning(this, tr("JSON demo"),
                                 tr("Parse error in file %1")
                                 .arg(QDir::toNativeSeparators(fileName)
                                      ));
        } else {
            statusBar()->showMessage(tr("File loaded"), 2000);
        }
}
