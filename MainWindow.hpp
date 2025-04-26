#pragma once

#include "PainWidget.hpp"

#include <NeuralNetwork.hpp>
#include <QGridLayout>
#include <QGroupBox>   // обьеденям в группы виджеты
#include <QHBoxLayout> // выравнивание по горизонтали
#include <QLabel>	   // текст в окне
#include <QMainWindow>
#include <QProgressBar>
#include <QPushButton>
#include <QVBoxLayout> // выравнивание по вертикали

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:

	MainWindow(QWidget* parent = nullptr);
	~MainWindow();

private:

	NeuralNetwork* Net;

	//Массив чисел
	static const int output_num = 10;
	QLabel*			 labelsGroup1[output_num];
	QLabel*			 labelsGroup2[output_num];
	QProgressBar*	 progressBar[output_num];

	//Интерфейс
	QWidget*	 mainWindowWidget; //главный виджет окна
	QLabel*		 resaultLabelNet;  // Решение нейросети
	QGroupBox*	 groupBox1;		   // Первая группа виджетов(верхняя)
	QGroupBox*	 groupBox2;		   // Вторая группа виджетов(нижняя)
	QGroupBox*	 groupBox3;		   // Третья группа виджетов
	PainWidget*	 paintWidget;	   // Виджет Рисование
	QPushButton* cleanPushButton;  //кнопка удаление(очистить)

	// Размещение виджета
	QGridLayout* mainWindowGridLayout;
	QHBoxLayout* group1H;
	QVBoxLayout* group1V;
	QHBoxLayout* group2H;
	QVBoxLayout* group2V;
	QVBoxLayout* group3V;
};
