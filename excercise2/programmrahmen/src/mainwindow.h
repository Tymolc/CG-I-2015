#pragma once

//
// Qt
//
#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

    //[-------------------------------------------------------]
    //[ Public functions                                      ]
    //[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param parent
		*    Parent widget (can be NULL)
		*  @param flags
		*    QT flags
		*/
        MainWindow(QWidget *parent = NULL, QFlag flags = 0);

		/**
		*  @brief
		*    Destructor
		*/
    	~MainWindow();
  private:

};
