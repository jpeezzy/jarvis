
#include <iostream>
#include <QApplication>
#include <QtMultimedia>
#include <QtMultimediaWidgets>
#include <QMovie>
#include <QLabel>
#include <QHBoxLayout>
int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	QWindow window; 
	window.resize(1000,1000);
/*	QMediaPlayer *player = new QMediaPlayer;

	QMediaPlaylist *playlist = new QMediaPlaylist(player);
	playlist->addMedia(QUrl::fromLocalFile(QFileInfo("/home/masa/jarvis/src/space.mp4").absoluteFilePath()));
	//player->setMedia(QUrl::fromLocalFile(QFileInfo("/home/masa/jarvis/src/animation/space.mp4").absoluteFilePath()));
	//playlist->addMedia(QUrl("http://example.com/myclip2.mp4"));
	playlist->setPlaybackMode(QMediaPlaylist::Loop);
	QVideoWidget* videoWidget = new QVideoWidget;
	player->setVideoOutput(videoWidget);
	player->setPlaylist(playlist);
	videoWidget->showFullScreen();
	playlist->setCurrentIndex(1);
	player->play(); 
	//window.show(); */
	QMovie *movie = new QMovie("space.gif");
	QLabel *processLabel = new QLabel(parent);
	processLabel->setMovie(movie);
	movie->start();
	    QHBoxLayout *layout = new QHBoxLayout();
			    layout->addWidget(processLabel);
//	QMovie* m_pMovie = new QMovie("space.mp4");
	//window.show();
	//processLabel->setText("asdfasdfasefasefasef:");
	// tell the painter to draw on the QImage
	// // you probably want the to draw the text to the rect of the image
	processLabel->setTextFormat(Qt::RichText);
	QLabel* test = new QLabel("Hello WOlrd!");
	processLabel->show();
	return app.exec();
}
