#include <iostream>
#include <QDebug>

int main(int argc, char* argv[])
{
    std::cout << "hello Plugin Host~" << std::endl;
    qDebug() << "hello qDebug";
    return 0;
}
