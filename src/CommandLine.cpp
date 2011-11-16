#include <QtGui>
#include "CommandLine.h"

CommandLine::CommandLine(QWidget* parent)
{
	setStyleSheet("border-style: none;"
				  "background-color: black;"
				  "font-family: \"Monospace\";"
				  "color: white;"
				 );
	connect(this, SIGNAL(returnPressed()), this, SLOT(executeCommand()));
}

void CommandLine::executeCommand()
{
	QString command = text();
	QRegExp open(":open (.*)");
	QRegExp newTab(":tabnew (.*)");
	QRegExp protocol_checker("\\b(http://|https://)\\b");
	QString url;

	int protocol_index = protocol_checker.indexIn(command);
	if (open.exactMatch(command))
	{
		url = open.cap(1);
        if (protocol_index == -1)
			url = "http://" + url;
		emit(openUrlRequested(url));
	}

	if (newTab.exactMatch(command))
	{
		url = newTab.cap(1);
        if (protocol_index == -1)
			url = "http://" + url;
		emit(newTabRequested(url));
	}
	emit(clear());
}
