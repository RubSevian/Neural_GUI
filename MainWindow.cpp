#include "MainWindow.hpp"

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
{
	Net = new NeuralNetwork(784, 100, 10); // Нейросеть

	// Настройка интерфеса

	mainWindowWidget = new QWidget(this);
	setCentralWidget(mainWindowWidget);
	mainWindowGridLayout = new QGridLayout();
	mainWindowWidget->setLayout(mainWindowGridLayout); //вставляем выравнивающий слой

	//Первая группа виджетов (верхняя)

	resaultLabelNet = new QLabel("hi");				// Родительский класс this
	resaultLabelNet->setAlignment(Qt::AlignCenter); // выравнивание по центру
	resaultLabelNet->setFont(QFont("Time NewRoman", 14, QFont::Bold)); // Установка шрифта

	group1H = new QHBoxLayout(); // горизонтальное выравнивание
	for (int i = 0; i < output_num; ++i)
	{
		labelsGroup1[i] = new QLabel(QString::number(i));
		labelsGroup1[i]->setAlignment(Qt::AlignCenter); // выравнивание по центру цифры
		group1H->addWidget(labelsGroup1[i]); //Засовываем в наш виджет числа от 1 до 10
	}
	group1V = new QVBoxLayout(); //Добавляем вертикальный слой
	group1V->addWidget(resaultLabelNet);
	group1V->addLayout(group1H); // Добавляем выравнивание в вертикальный слой
	// group1V->addLayout(group1V); // Добавляем выравнивание в вертикальный слой
	groupBox1 = new QGroupBox();
	groupBox1->setLayout(group1V);
	mainWindowGridLayout->addWidget(groupBox1, 0, 0);

	// Вторая группа виджетов(нижняя)
	group2H = new QHBoxLayout(); // горизонтальное выравнивание
	for (int i = 0; i < output_num; ++i)
	{
		progressBar[i] = new QProgressBar();
		progressBar[i]->setRange(0, 100); // Диапазон значений
		progressBar[i]->setOrientation(Qt::Vertical); // Изменяем ориентацию на вертикальную
		labelsGroup2[i] = new QLabel(QString::number(i));
		labelsGroup2[i]->setAlignment(Qt::AlignCenter);
		group2V = new QVBoxLayout(); // кол- во вертик слоев по кол-ву выравнимаемых обьектов
		group2V->addWidget(progressBar[i]);
		group2V->addWidget(labelsGroup2[i]); // подписи
		group2H->addLayout(group2V);		 // выравнивание по горизонтали
	}
	groupBox2 = new QGroupBox();
	groupBox2->setLayout(group2H);
	mainWindowGridLayout->addWidget(groupBox2, 1, 0); // 0 and 1 так как хоти разместить пониже

	// 3-я группа виджетов.Виджет рисование

	paintWidget		= new PainWidget();
	group3V			= new QVBoxLayout();
	cleanPushButton = new QPushButton("Очистить");
	group3V->addWidget(paintWidget);
	group3V->addWidget(cleanPushButton);
	groupBox3 = new QGroupBox();
	groupBox3->setLayout(group3V);
	mainWindowGridLayout->addWidget(groupBox3, 2, 0);
}

MainWindow::~MainWindow()
{
	delete Net;
}
