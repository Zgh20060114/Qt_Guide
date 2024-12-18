//
// Created by zgh on 2024/12/17.
//
#include <QApplication>
#include <QPushButton>
#include <QMainWindow>
#include <QLineEdit>
#include <QTextEdit>
#include <QMenuBar>
#include <QDebug>
#include <QEvent> //zgh 2024/12/18 上午7:26: 信号机制是单向的，事件机制是双向的


#ifndef INC_003NOTEPAD_MAINWINDOW_H
#define INC_003NOTEPAD_MAINWINDOW_H

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    QTextEdit *textEdit;
    QString currentPath;
    bool hasUnsavedModify = false;

protected:
    void closeEvent(QCloseEvent *closeEvent) override;

public Q_SLOTS:
    //zgh 2024/12/17 上午9:43: 槽函数命名： on_name_signal
    void on_open_triggered();
    void on_save_triggered();
    void on_saveAs_triggered();
    void on_autoNewLine_triggered(bool checked);
};


#endif //INC_003NOTEPAD_MAINWINDOW_H
