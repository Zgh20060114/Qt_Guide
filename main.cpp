#include <QApplication>
#include "mainWindow.h"

//zgh 2024/12/16 上午9:03: Qt::XXXX的命名空间是存枚举的
//zgh 2024/12/16 上午9:04: Qt里面设置set，读取直接
//zgh 2024/12/17 上午8:46: Qt反射机制需用到Q_OBJECT宏，但是这个宏要求分离声明和定义




int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();
    return QApplication::exec();
}
