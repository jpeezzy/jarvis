#include "simplemenu.h"
#include <QFile>
int main(int argc, char* argv[])
{
	QApplication app(argc,argv);

	SimpleMenu window;
	//window.resize(250,150);

	window.setWindowTitle("jarvis?");
	window.setWindowIcon(QIcon("test.png"));
	window.setToolTip("Testing toooltip");
	window.showFullScreen(); //launches application full screen 
	//window.show();
	return app.exec();
}

