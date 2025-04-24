#pragma once

#include <QDebug>
#include <QObject>
#include <QRandomGenerator>
#include <QVector>

class NeuralNetwork : public QObject // Наследуем класс
{
	Q_OBJECT

public:

	// inputNum-число входных слоев
	// int hiddenNum - число скрытых слоев
	// int outputNum - число выходных слоев

	NeuralNetwork(int inputNum, int hiddenNum, int outputNum);

private:

	int m_inputSize;  //Кол-во входных нейронов
	int m_hiddenSize; //Кол-во скрытых нейронов
	int m_outputSize; //Кол-во выходных нейронов

	QVector<double> m_inputNeurons; // тут будет массив входных нейронов
	QVector<double> m_hiddenNeurons; // тут будет массив скрытых нейронов
	QVector<double> m_outputNeurons; // тут будет массив выходных нейронов

	//Создаем двумерный массив для хранения весов(одновременно относятся к двум слоям)

	QVector<QVector<double>> m_inputHiddenWeight; // веса между входным и скрытым слоем
	QVector<QVector<double>> m_hiddenOutputWeight; //веса мехжду скрытым и выходным слоем

	//Смещение (bias)

	QVector<double> m_hiddenBiases; //Смещение скрытых нерйонов
	QVector<double> m_outputBiases; //Смещение выходных нейронов

	//Функция Активации

	double ReLU(double x);

	QRandomGenerator random;

	//Функция прямого распространения

	void feedForward(QVector<double> input);
};
