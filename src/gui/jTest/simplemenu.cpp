#include "simplemenu.h"
#include <QMenu>
#include <QMenuBar>
#include <QFile>
#include <QWidget>
#include <QGridLayout>
#include <QFont>
SimpleMenu::SimpleMenu(QWidget *parent)
	: QMainWindow(parent) 
{
	QAction *quit = new QAction("&Quit", this); //Qaction
	
	//text is QLabel pointer that prints a string to screen
	text = new QLabel("Hello World!", this);
	text->setAlignment(Qt::AlignCenter);

	//makes text font bigger 
	QFont font = text->font();
	font.setPointSize(72);
	font.setBold(true);
	text->setFont(font);

	//Sets up a style sheet similar to css for dynamic parameters (color of background)
	QFile qFile("stylesheet.css");
	qFile.open(QFile::ReadOnly);
	QString StyleSheet = QLatin1String(qFile.readAll());
	qApp->setStyleSheet(StyleSheet);
//documentation on style sheets here http://doc.qt.io/qt-4.8/stylesheet-reference.html

	//this shows the text box for inputting commands; 
	textBox = new QLineEdit;
	textBox->setPlaceholderText("input commands here");
	
//This sets the layout where text is showed on top of the input text box;  
	QGridLayout *layout = new QGridLayout; 
	layout->addWidget(text);
	layout->addWidget(textBox,1,0);
	QWidget *window = new QWidget();
	window->setLayout(layout);	
	this->setCentralWidget(window);
	
	//this adds file button on top of application;
	QMenu *file;
	file = menuBar() -> addMenu("&File"); //Qmenuobject
	file->addAction(quit);//adds the option "quit under file menu" 

	connect(quit, &QAction::triggered, qApp, QApplication::quit);//when quit is slelected, app closes

	//this connects text box with the enter key, hopefully sending the message to the main program.
	//we do this by using connect, and using a functor(object that can be used () like a function
	connect(textBox, &QLineEdit::returnPressed, text, [this]{text->setText(textBox->text());});
}

