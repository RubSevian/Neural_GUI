#include "PainWidget.hpp"

PainWidget::PainWidget(QWidget* parent)
	: QWidget{parent}
{
	setFixedSize(280, 280); //окно виджета размером 280*280
	image =
	  QImage(28,
			 28,
			 QImage::Format_RGB32); // Создаем изображение 28x28, формат RGB32 (32 бита на пиксель)
	clear();				// Очищаем изображение (фон)
	brushColor = Qt::green; // Устанавливаем цвет кисти по умолчанию (белый)
	brushSize = 3; // Устанавливаем размер кисти по умолчанию (3 пикселя)
}

// Получение данных пикселей в виде вектора doubles (нормализованные значения)
QVector<double> PainWidget::getPixelData() const
{
	QVector<double> pixelData(28 * 28);
	// int				index = 0;
	for (int y = 0; y < 28; ++y)
	{
		for (int x = 0; x < 28; ++x)
		{
			QColor color	 = image.pixelColor(x, y);
			double grayscale = (0.299 * color.red() + 0.587 * color.green() + 0.114 * color.blue())
							 / 255.0; // вычислим оттенки серого
			pixelData[y * 28 + x] = grayscale; // cохраняем нормализованное значение в векторе
		}
	}
	return pixelData; // возвращаем вектор с данными пикселей
}

void PainWidget::clear()
{
	image.fill(Qt::white);
	update();
}

// Переопределяем событие отрисовка (для перерисовки виджета)
void PainWidget::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);

	painter.drawImage(QRect(0, 0, 280, 280),
					  image); // рисование изображения на виджете, масштабируя его
}

void PainWidget::mousePressEvent(QMouseEvent* eventMouse)
{
	lastPoint =
	  eventMouse->pos() / 10; // запоминаем начальную точку (делим на 10 для масштабирования)
}

// Обработчик движения мыши (вызывается, когда мышь перемещается с зажатой кнопкой)
void PainWidget::mouseMoveEvent(QMouseEvent* eventMouse)
{
	QPainter imagePainter(&image);

	// Сделаем возможным создание плавных линий

	QRadialGradient gradient(eventMouse->pos() / 10, brushSize / 2);
	gradient.setColorAt(0, brushColor); // центр градиента - цвет кисти
	gradient.setColorAt(1, Qt::transparent); // края градиента - прозрачные (полностью)

	QPen pen(QBrush(gradient),
			 brushSize,
			 Qt::SolidLine,
			 Qt::RoundCap,
			 Qt::RoundJoin); // создаем перо для рисования

	imagePainter.setPen(pen); // устанавливаем перо для imagePainter

	imagePainter.drawLine(
	  lastPoint,
	  eventMouse->pos()
		/ 10); // рисуем линию между последней и текущей позициями мыши (с масштабированием)
	lastPoint = eventMouse->pos() / 10; // Обновляем последнюю позицию
	update();			// Вызываем перерисовку виджета (paintEvent)
	emit imageUpdate(); // Отправляем сигнал о том, что изображение было обновлено
}
