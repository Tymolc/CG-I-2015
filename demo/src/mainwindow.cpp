#include "mainwindow.h"

#include <QHBoxLayout>
#include <QListWidget>
#include <QStackedWidget>

#include "example.h"

MainWindow::MainWindow(QWidget *parent, QFlag flags)
    : QMainWindow(parent, flags)
{
    setWindowTitle("3D Computergrafik I - SS2015 - Programmrahmen");

    QWidget * container = new QWidget;

    container->setMinimumSize(1024, 768);

    QHBoxLayout * layout = new QHBoxLayout;

    QListWidget * list = new QListWidget;

    list->setMaximumWidth(200);

    list->addItem("Bild 1");
    list->addItem("Bild 2");

    QStackedWidget * stack = new QStackedWidget;

    Example * example1 = new Example("image1.png");
    Example * example2 = new Example("image2.jpg");

    stack->addWidget(example1);
    stack->addWidget(example2);

    connect(list, SIGNAL(currentRowChanged(int)), stack,
            SLOT(setCurrentIndex(int)));

    layout->addWidget(list);
    layout->addWidget(stack);

    container->setLayout(layout);

    setCentralWidget(container);
}
