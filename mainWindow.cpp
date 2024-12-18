//
// Created by zgh on 2024/12/17.
//
#include "mainWindow.h"
#include <QSettings> //zgh 2024/12/17 上午10:37: 储存用户设置
#include <QFile>
#include <QFileDialog>
#include <QMessageBox> //zgh 2024/12/17 下午8:20: 消息弹窗
#include <QCloseEvent>

//zgh 2024/12/17 上午9:19: 默认参数还要删掉才能分离
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
//        QLineEdit *lineEdit = new QLineEdit;
    textEdit = new QTextEdit;
    setCentralWidget(textEdit);
    QMenuBar *menuBar1 = new QMenuBar;
    setMenuBar(menuBar1);
    QMenu *menu = menuBar1->addMenu("文件");
//        QAction *open = menu->addAction("打开");
//        connect(open,&QAction::triggered, this,&MainWindow::onOpen);  //zgh 2024/12/17 上午8:25: 动词的过去分词是信号
//        menu->addSeparator();
//        QAction *save = menu->addAction("保存");
//        connect(save,&QAction::triggered, this,&MainWindow::onSave);
//        QAction *saveAs = menu->addAction("另存为");
//        connect(saveAs,&QAction::triggered, this,&MainWindow::onSaveAs);

    //zgh 2024/12/17 上午8:17: 使用Qt的反射机制，action不用麻烦connect了
    QAction *open = menu->addAction("打开");
    open->setObjectName("open");
    QAction *save = menu->addAction("保存");
    save->setObjectName("save");
    QAction *saveAs = menu->addAction("另存为");
    saveAs->setObjectName("saveAs");

    QMenu *menu1 = menuBar1->addMenu("编辑");
    QAction *AutoNewLine = menu1->addAction("自动换行");
    AutoNewLine->setCheckable(true);

    AutoNewLine->setObjectName("autoNewLine");
    QMetaObject::connectSlotsByName(this); //zgh 2024/12/17 上午10:29: 在最后应

    QSettings settings("zgh","003notePad");
    bool enableAutoNewLine = settings.value("enableAutoNewLine", true).toBool();
    connect(textEdit,&QTextEdit::textChanged, this,[this] {
        hasUnsavedModify = true;
    });
    AutoNewLine->setChecked(enableAutoNewLine);
//        on_autoNewLine_triggered(enableAutoNewLine);
}

//zgh 2024/12/17 上午10:57: 槽函数不是只能在信号里调用，还可以在代码里手动调用
void MainWindow::on_open_triggered(){
//    qDebug()<<"open";
//    QFile file("CMakeCache.txt");
    QString path = QFileDialog::getOpenFileName(this,"选择要打开的文件","","文本文件 (*.txt *.log);;所有文件 (*.*)");
    if (path==""){  //zgh 2024/12/17 下午1:05: 选择取消会返回空
        return;
    }
    QFile file(path);
    if (!file.open(QFile::ReadOnly)){
        qWarning()<< "file open failed";
        return;
    }
    QString text = QString::fromUtf8(file.readAll());
    textEdit->setPlainText(text);  //zgh 2024/12/17 下午12:39: setText是富文本，setPlainText是平凡文本
    currentPath = path;

}
void MainWindow::on_saveAs_triggered(){
    QString path = QFileDialog::getSaveFileName(this,"选择要打开的文件","","");
    if (path==""){
        return;
    }
    QFile file(path);
    if (!file.open(QFile::WriteOnly)){
        qWarning()<< "file save failed";
        return;
    }
    QString text = textEdit->toPlainText();
    file.write(text.toUtf8());
    currentPath = path;
    hasUnsavedModify = false;
}

void MainWindow::on_save_triggered(){
    if (currentPath.isEmpty()){  //zgh 2024/12/17 下午6:48: 刚打开记事本，就写了一些，此时currentPath是空的
        on_saveAs_triggered();
    } else{
        QFile file(currentPath);
        if (!file.open(QFile::WriteOnly)){
            qWarning()<< "file save failed";
            return;
        }
        QString text = textEdit->toPlainText();
        file.write(text.toUtf8());
    }
    hasUnsavedModify = false;
}

void MainWindow::on_autoNewLine_triggered(bool checked) {
    if (checked){
        textEdit->setLineWrapMode(QTextEdit::LineWrapMode::WidgetWidth);
    } else{
        textEdit->setLineWrapMode(QTextEdit::LineWrapMode::NoWrap);
    }
    QSettings settings("zgh","003notePad");
    settings.setValue("enableAutoNewLine",checked);
}

void MainWindow::closeEvent(QCloseEvent *closeEvent) {
    if (hasUnsavedModify){
        auto stdBtn = QMessageBox::question(this,"notepad","您有未保存的修改，是否保存？",QMessageBox::StandardButton::Save | QMessageBox::StandardButton::Discard | QMessageBox::StandardButton::Cancel);
        switch (stdBtn) {
            case QMessageBox::StandardButton::Save:
                on_save_triggered();
                break;
            case QMessageBox::StandardButton::Discard:
                break;
            case QMessageBox::StandardButton::Cancel:
                closeEvent->ignore();
                return;
            default:
                break;
        }
    }
    QMainWindow::closeEvent(closeEvent);
}
