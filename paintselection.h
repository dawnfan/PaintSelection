#ifndef PAINTSELECTION_H
#define PAINTSELECTION_H

#include <QtWidgets/QMainWindow>
#include "ui_paintselection.h"
#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\highgui\highgui.hpp>

class PaintSelection : public QMainWindow
{
	Q_OBJECT

public:
	PaintSelection(QWidget *parent = 0);
	~PaintSelection();

public slots:
	void OpenImage();
protected:
	//events callback
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void paintEvent(QPaintEvent * event);
private:
	enum CURSOR_STATUS
	{
		CURSOR_DEFAULT,
		CURSOR_FORE,
		CURSOR_BACK
	};
	Ui::PaintSelectionClass ui;
	QCursor fore_cursor_;
	QCursor back_cursor_;
	CURSOR_STATUS cur_cursor_;

	QPixmap*	 select_map_;
	cv::Mat		 image_mat_;
	cv::Mat		 image_mat_after_;
	QPointF		 start_pos_;

	QRectF photo_rect_;
	void triggerCursor(CURSOR_STATUS c_in);
	void photoSizeTransform(int its_width, int its_height);
};

#endif // PAINTSELECTION_H
