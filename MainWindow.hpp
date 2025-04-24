#pragma once

#include <NeuralNetwork.hpp>
#include <QMainWindow>

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:

	MainWindow(QWidget* parent = nullptr);
	~MainWindow();

private:

	NeuralNetwork* Net;
};
