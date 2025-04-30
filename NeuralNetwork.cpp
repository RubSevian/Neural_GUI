#include "NeuralNetwork.hpp"

NeuralNetwork::NeuralNetwork(int inputNum, int hiddenNum, int outputNum)
{
	m_inputSize	 = inputNum;
	m_hiddenSize = hiddenNum;
	m_outputSize = outputNum;

	//Устанавливаем размер вектора весов с помощью resize
	m_hiddenNeurons.resize(m_hiddenSize);
	m_outputNeurons.resize(m_outputSize);
	// m_hiddenBiases.resize(m_inputSize);
	// Заполнение весов между входным и скрытым слоями
	m_inputHiddenWeight.resize(m_inputSize);
	for (int i = 0; i < m_inputSize; ++i)
	{
		m_inputHiddenWeight[i].resize(m_hiddenSize);
		for (int j = 0; j < m_hiddenSize; ++j)
			m_inputHiddenWeight[i][j] =
			  0.005 * (random.generateDouble() * 2 - 1); // Чтобы были отрицательные числа
	}
	// Заполенение весов между скрытым и выходным слоями
	m_hiddenOutputWeight.resize(m_hiddenSize);
	for (int i = 0; i < m_hiddenSize; ++i)
	{
		m_hiddenOutputWeight[i].resize(m_outputSize);
		for (int j = 0; j < m_outputSize; ++j)
			m_hiddenOutputWeight[i][j] =
			  0.005 * (random.generateDouble() * 2 - 1); // Чтобы были отрицательные числа
	}

	//Заполнение смещений скрытого слоя
	m_hiddenBiases.resize(m_hiddenSize);
	for (int i = 0; i < m_hiddenSize; ++i)
		m_hiddenBiases[i] = 0.005 * (random.generateDouble() * 2 - 1);

	//Заполнение смещений выходного слоя
	m_outputBiases.resize(m_outputSize);
	for (int i = 0; i < m_outputSize; ++i)
	{
		m_outputBiases[i] = 0.005 * (random.generateDouble() * 2 - 1);
		qDebug() << m_outputBiases[i];
	}
}

double NeuralNetwork::LReLU(double x)
{
	if (x > 0)
		return x;
	else
		return x * a_lrelu;
}

double NeuralNetwork::lreluDerivate(double x)
{
	if (x > 0)
		return 0;
	else
		return a_lrelu;
}

void NeuralNetwork::feedForward(QVector<double> input)
{
	//Рассчет значений скрытых нейронов
	for (int i = 0; i < m_hiddenSize; ++i)
	{
		double activation = m_hiddenBiases[i]; // взвешенная сумма
		for (int j = 0; j < m_inputSize; ++j)
			activation += input[j] * m_inputHiddenWeight[i][j];
		m_hiddenNeurons[i] = LReLU(activation);
	}

	//Рассчет значений выходных нейронов
	for (int i = 0; i < m_hiddenSize; ++i)
	{
		double activation = m_outputBiases[i]; // взвешенная сумма
		for (int j = 0; j < m_hiddenSize; ++j)
			activation += input[j] * m_hiddenOutputWeight[i][j];
		m_outputNeurons[i] = LReLU(activation);
	}
}

void NeuralNetwork::backPropagation(QVector<double> output)
{
	double learningRate = 0.1;
	outputError.resize(m_outputSize);
	hiddenError.resize(m_hiddenSize);
	// Ошибка выходного слоя
	for (int i = 0; i < m_outputSize; ++i)
		outputError[i] = (output[i] - m_outputNeurons[i]) * LReLU(m_outputNeurons[i]);

	// Ошибка скрытого слоя
	for (int i = 0; i < m_hiddenSize; ++i)
	{
		double error = 0;
		for (int j = 0; j < m_outputSize; ++j)
			error += outputError[j] * m_hiddenOutputWeight[i][j];
		hiddenError[i] = error * LReLU(m_hiddenNeurons[i]);
	}
	//Обновление весов и смещений между скрытым и входным слоями

	for (int i = 0; i < m_hiddenSize; ++i)
		for (int j = 0; j < m_outputSize; ++j)
			m_hiddenOutputWeight[i][j] += learningRate * outputError[j] * m_hiddenNeurons[i];
	for (int i = 0; i < m_outputSize; ++i)
		m_outputBiases[i] += learningRate * outputError[i];
	//Обновление весов и смещений между входным и скрытым слоями
	for (int i = 0; i < m_inputSize; ++i)
		for (int j = 0; j < m_hiddenSize; ++j)
			m_inputHiddenWeight[i][j] += learningRate * hiddenError[j] * m_inputNeurons[i];
	for (int i = 0; i < m_hiddenSize; ++i)
		m_hiddenBiases[i] += learningRate * hiddenError[i];
}
