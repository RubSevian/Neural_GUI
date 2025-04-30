#pragma once

#include <QWidget>

class SecondWindow : public QObject
{
	Q_OBJECT

public:

	explicit SecondWindow(QObject* parent = nullptr);
signals:
};
