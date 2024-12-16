#include <QApplication>
#include <QMainWindow>
#include <QDebug>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit> //zgh 2024/12/15 下午9:23: 一行
#include <QIntValidator>

//zgh 2024/12/15 下午4:24: qt中一切类的基类QObject-> 派生出子类比如QWidget -> QLabel QMainWindow QPushButton QComboBox（各种窗体子类）
//zgh 2024/12/15 下午5:43: Qlayout派生出-> QBoxLayout ->QVBoxLayout,QHBoxLayout
//zgh 2024/12/15 下午5:44:             -> QGridLayout

class Label : public QLabel{
public:
    explicit Label(QWidget *parent = nullptr): QLabel(parent){  //zgh 2024/12/15 下午5:26: explicit必须用(),显式转换，不能用=，隐式转换
        setAlignment(Qt::AlignCenter);
        setStyleSheet("QLabel { background-color: #333333; color: yellow; font-size: 60px;}");
    }
};

QLineEdit *lineEdit;
QLineEdit *lineEdit1;
QLineEdit *lineEditResult;

void calcPlus(){
    auto result = lineEdit->text().toDouble()+lineEdit1->text().toDouble();
    qDebug()<< "Confirm: "<< result;
    lineEditResult->setText(QString::number(result));
}


int main(int argc, char *argv[]) { //zgh 2024/12/15 下午1:53: 命令行参数
    QApplication a(argc, argv); //zgh 2024/12/15 下午1:54: QApplication全局单例,一个进程只能构建一个

    QMainWindow window; //zgh 2024/12/15 下午3:13: 创建回调
//    qDebug()<<"Hidden?: "<<window.isHidden();
    window.setWindowTitle("nihao");
//    window.setFixedSize(200,200);
    window.setGeometry(1440,1080,400,400);

    QWidget *centralwidgt = new QWidget;
    window.setCentralWidget(centralwidgt);
    QHBoxLayout *qvBoxLayout = new QHBoxLayout;
    centralwidgt->setLayout(qvBoxLayout);



    Label *label1 = new Label; //zgh 2024/12/15 下午4:20: 自动delete  //zgh 2024/12/15 下午4:52:在堆上动态创建
    //zgh 2024/12/15 下午4:52: QLabel label; 在栈上创建，自动销毁
    label1->setText("标签1");
//    qvBoxLayout->addWidget(label1);

    Label *label2 = new Label;
    label2->setText("标签2");
//    qvBoxLayout->addWidget(label2);

    QPushButton *button = new QPushButton;
    button->setText("确认");
    qvBoxLayout->addWidget(button);
    //zgh 2024/12/15 下午9:06:               信号                                       槽  这就是Qt的信号与槽，类似于回调？
    window.connect(button,&QPushButton::clicked,&window,&calcPlus);  //zgh 2024/12/15 下午9:22: 第五个参数：例如Qt::AutoConnection，信号与槽的连接方式

    QPushButton *button1 = new QPushButton;
    button1->setText("取消");
    qvBoxLayout->addWidget(button1);
    window.connect(button1,&QPushButton::clicked,&window,[&window]{  //zgh 2024/12/15 下午9:11:为什么[&window]一定要指定对象呢
        qDebug()<< "Cancel";
    });

    lineEdit = new QLineEdit;
    lineEdit->setText("0");
//    QIntValidator *intValidator = new QIntValidator;
    lineEdit->setValidator(new QDoubleValidator);
    qvBoxLayout->addWidget(lineEdit);

    lineEdit1 = new QLineEdit;
    lineEdit1->setText("0");
    lineEdit1->setValidator(new QDoubleValidator);
    qvBoxLayout->addWidget(lineEdit1);

    lineEditResult = new QLineEdit;
    lineEditResult->setText("0");
    lineEditResult->setValidator(new QDoubleValidator);
    qvBoxLayout->addWidget(lineEditResult);

    window.show();

//    qDebug()<<"Hidden?: "<<window.isHidden();
//    QString string="1 2 3你 4\n\r\t";
//    qDebug()<<string;
//    QStringList stringList=string.split(u'你');
//    qDebug()<<stringList;

    return a.exec(); //zgh 2024/12/15 下午2:43: Qt的事件循环，不断循环，监听事件，没有输入会长时间等待,阻塞；监听到事件了处理相应的事件回调
}

void fun(){
    QApplication::instance(); //zgh 2024/12/15 下午2:32: instance()获取之前创建的QApplication
}

