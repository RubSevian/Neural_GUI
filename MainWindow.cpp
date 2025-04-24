#include "MainWindow.hpp"

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
{
	Net = new NeuralNetwork(784, 100, 10);
}

MainWindow::~MainWindow() {}
