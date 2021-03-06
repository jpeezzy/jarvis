#include "simplemenu.h"
#include <QMenu>
#include <QMenuBar>
#include <QFile>
#include <QWidget>
#include <QGridLayout>
#include <QFont>
SimpleMenu::SimpleMenu(QWidget *parent)
	: QMainWindow(parent) //QVideoWidget(parent) 
{
	//this parts sets up animated background 
/*	player = new QMediaPlayer;
	playlist = new QMediaPlaylist(player);
	playlist->addMedia(QUrl::fromLocalFile(QFileInfo("/home/masa/jarvis/src/space.mp4").absoluteFilePath()));
	playlist->setPlaybackMode(QMediaPlaylist::Loop);
	videoWidget = new QVideoWidget;
	player->setVideoOutput(videoWidget);
	player->setPlaylist(playlist);
	videoWidget->showFullScreen();
	playlist->setCurrentIndex(1);
//	player->play(); */
	//
	//thread that controls the backend;

	jarvisThread = std::thread(&commands::intro, &jarvis);

	//jarvis.detatch();
	QAction *quit = new QAction("&Quit", this); //Qaction
	
	//text is QLabel pointer that prints a string to screen
	text = new QLabel("Hello World!", this);
	text->setAlignment(Qt::AlignCenter);
	text->setWordWrap(true);

//	text->show();
//	text->activateWindow();
//	text->raise();
//	text->setAttribute(Qt::WA_TranslucentBackground);
	//text->setStyleSheet("background:transparent;");

	//makes text font bigger 
	QFont font = text->font();
	font.setPointSize(60);
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
	textBox->setMaxLength(30);
	textBox->show();
	textBox->activateWindow();
//	textbox->setAttribute(Qt::WA_TranslucentBackground);
//	textbox->setStyleSheet("background:transparent;");

//This sets the layout where text is showed on top of the input text box;  
	QGridLayout *layout = new QGridLayout;
//	layout-> addWidget(videoWidget);
	layout->addWidget(text);
	layout->addWidget(textBox,1,0);
//	videoWidget->stackUnder(text);
//	text->raise();
//	textBox->raise();

	QWidget *window = new QWidget();
	window->setLayout(layout);	
	this->setCentralWidget(window);
	
//	layout->addWidget(text);
//this adds file button on top of application;
	QMenu *file;
	file = menuBar() -> addMenu("&File"); //Qmenuobject
	file->addAction(quit);//adds the option "quit under file menu" 
	
	connect(quit, &QAction::triggered, qApp, QApplication::quit);//when quit is slelected, app closes
//	connect(quit, &QAction::triggered, qApp, [this]{;});
	//this connects text box with the enter key, hopefully sending the message to the main program.
	//we do this by using connect, and using a functor(object that can be used () like a function
	
	//this connect sends the text from the text box into a std::string that can be send to the backend
	connect(textBox, &QLineEdit::returnPressed, text, [this]{text->setText(textBox->text());});
	connect(textBox, &QLineEdit::returnPressed, textBox, [this]{commandToString(textBox->text());});

	connect(textBox, &QLineEdit::returnPressed, textBox, &QLineEdit::clear);
	connect(textBox, &QLineEdit::returnPressed, textBox, [this]{backEnd();});

}

std::string SimpleMenu::getText()
{
	return textCommand; 
}

void SimpleMenu::commandToString(QString qText)
{
	//textCommand = qText.toStdString();
	textCommand = qText.toUtf8().constData();
	//std::cout << "WORD THAT IS PRINTED IS " << textCommand << std::endl;
	/*This also sends textcommand to the backend  */
	//jarvisThread= std::thread(&SimpleMenu::backEnd, this);
}

void SimpleMenu::backEnd()
{
	jarvis.storeQuestion(textCommand);
}

