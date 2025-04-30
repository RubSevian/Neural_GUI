#pragma once
#include <QBrush>
#include <QColor>
#include <QMouseEvent>
#include <QPainter>
#include <QPen>
#include <QRadialGradient>
#include <QRect>
#include <QSize>
#include <QWidget>

class PainWidget : public QWidget
{
	Q_OBJECT

public:

	explicit PainWidget(QWidget* parent = nullptr);
	QVector<double> getPixelData()
	  const; //получим нормализованные пиксели + сделаем функцию константной
			 //чтобы она не изменяла состояние обьекта PaintWidget
	void clear(); // Очистка рисунка

signals:
	void imageUpdate(); // Сигнал который создается при обновлении рисунка

protected:

	void paintEvent(QPaintEvent* event) override; // Переопределение события отрисовки
	void mousePressEvent(
	  QMouseEvent* eventMouse) override; // Переопределение события нажатия кнопки мыши
	void mouseMoveEvent(QMouseEvent* eventMouse) override; // Переопределение события движения мыши

private:

	QImage	 image;
	QPoint	 lastPoint;
	QPainter painter;
	QColor	 brushColor;
	QPen	 pen;
	int		 brushSize;
};
