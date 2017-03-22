#include "paintselection.h"
#include <QImage>
#include <QPainter>
#include <QtWidgets> 


#define PHOTO_WIDTH  840
#define PHOTO_HEIGHT 540
#define BAR_HEIGHT 10

#define BRUSH_SIZE 16

PaintSelection::PaintSelection(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setFixedSize(900, 600);
	fore_cursor_ = QCursor(QPixmap(":/PaintSelection/Resources/Images/cursor-fore.png").scaled(QSize(BRUSH_SIZE, BRUSH_SIZE)));
	back_cursor_ = QCursor(QPixmap(":/PaintSelection/Resources/Images/cursor-back.png").scaled(QSize(BRUSH_SIZE, BRUSH_SIZE)));
	select_map_ = NULL;
	photo_rect_ = QRectF(0, 0, 0, 0);
}

PaintSelection::~PaintSelection()
{

}

// Slot functions
void PaintSelection::OpenImage(){
	//m_pixmap = QPixmap::fromImage(image);
	// Open file
	QString fileName = QFileDialog::getOpenFileName(this, tr("Read Image"), ".", tr("Images(*.bmp *.png *.jpg)"));

	// Load file
	if (!fileName.isEmpty())
	{
		image_mat_ = cv::imread(fileName.toLatin1().data());
		cvtColor(image_mat_, image_mat_, CV_BGR2RGB);
		if (select_map_ != NULL)
		{
			delete select_map_;
		}
		photoSizeTransform(image_mat_.cols, image_mat_.rows);
		select_map_ = new QPixmap(photo_rect_.width(), photo_rect_.height());    //���pixmap������������׼�����Ƶ��ռ������
		select_map_->fill(Qt::transparent);     //������ͼƬ�ı�����͸��
	}
	update();
}

// Event functions
void PaintSelection::paintEvent(QPaintEvent * event){
	QPainter painter(this);

	// background
	QPixmap image_back = QPixmap(PHOTO_WIDTH, PHOTO_HEIGHT);
	image_back.fill(Qt::darkCyan);
	painter.drawPixmap(0, (height() - PHOTO_HEIGHT) / 2 + BAR_HEIGHT, image_back);
	// Draw image
	if (!image_mat_.empty())
	{
		QImage image_show = QImage((unsigned char *)(image_mat_.data), image_mat_.cols, image_mat_.rows, image_mat_.step, QImage::Format_RGB888);
		painter.drawImage(photo_rect_, image_show);
	}
	if (select_map_ != NULL)
	{
		painter.drawPixmap(photo_rect_.topLeft(), (*select_map_));
	}
}
void PaintSelection::mousePressEvent(QMouseEvent *e){
	QPoint cur_p = e->pos();
	if (photo_rect_.contains(cur_p))
	{
		start_pos_ = cur_p;
		if (e->button() == Qt::LeftButton)
		{
			triggerCursor(CURSOR_FORE);
		}
		if (e->button() == Qt::RightButton)
		{
			triggerCursor(CURSOR_BACK);
		}
	}
}
void PaintSelection::mouseMoveEvent(QMouseEvent *e)
{
	QPoint cur_p = e->pos();
	if (cur_cursor_ == CURSOR_FORE || CURSOR_BACK)
	{
		//���ȵõ��滭�Ĺ���
		QPainter painter(this);

		//���úû��ʵķ��
		QPen pen;
		pen.setStyle(Qt::SolidLine);    //���û��ʵķ��
		pen.setWidth(BRUSH_SIZE);   //���û��ʵĿ��
		if (cur_cursor_ == CURSOR_FORE)
		{
			pen.setColor(QColor(0,0,255,127));
		}
		else{
			pen.setColor(QColor(255,0,0,127));
		}
		pen.setCapStyle(Qt::RoundCap);
		pen.setJoinStyle(Qt::RoundJoin);

		painter.begin(select_map_);      //������ͼƬ�ϻ�ͼ
		painter.setPen(pen);   //�����úõĻ��ʸ���ͼ����
		painter.drawLine(start_pos_ - photo_rect_.topLeft(), e->pos() - photo_rect_.topLeft());    //��һ��ֱ�ߣ�����㵽����
		painter.end();   //�����滭,�������begin��Ӧ�����ǽ�����ͼƬ�ϵĻ滭
		start_pos_ = e->pos();      //�����������������һ��һ���µĿ�ʼ�������Ϳ��Ի��������

		this->update();   //���¿ռ�Ļ��棬��ε�update���ý��ֻ����һ��paintEvent�¼�
	}
}
void PaintSelection::mouseReleaseEvent(QMouseEvent *e){
	triggerCursor(CURSOR_DEFAULT);
}

void PaintSelection::triggerCursor(CURSOR_STATUS c_in){
	cur_cursor_ = c_in;
	switch (c_in)
	{
	case PaintSelection::CURSOR_DEFAULT:
		setCursor(Qt::ArrowCursor);
		break;
	case PaintSelection::CURSOR_FORE:
		setCursor(fore_cursor_);
		break;
	case PaintSelection::CURSOR_BACK:
		setCursor(back_cursor_);
		break;
	default:
		setCursor(Qt::ArrowCursor);
		break;
	}
}
// image operators
void PaintSelection::photoSizeTransform(int its_width, int its_height){
	QSizeF its_size(its_width, its_height);
	double sizeRatio = (double)its_height / (double)its_width;

	// ��֤�ȱ������ţ�1.����������ı����ţ�2.����������һ�߱��޶��߳���С����Ҫ�仯
	if (sizeRatio > (double)PHOTO_HEIGHT / (double)PHOTO_WIDTH)
	{
		if (its_height > PHOTO_HEIGHT)
		{
			its_size.setWidth(PHOTO_HEIGHT / sizeRatio);
			its_size.setHeight(PHOTO_HEIGHT);
		}
		else
		{
			its_size.setWidth(its_width);
			its_size.setHeight(its_height);
		}
	}
	else{
		if (its_width > PHOTO_WIDTH)
		{
			its_size.setWidth(PHOTO_WIDTH);
			its_size.setHeight(PHOTO_WIDTH * sizeRatio);
		}
		else
		{
			its_size.setWidth(its_width);
			its_size.setHeight(its_height);
		}
	}

	// ����ͼ��λ�ô�С;λ�ã����¿հ���ȣ����Ҽ����ȣ�ͼƬλ���趨���������м�
	photo_rect_.setTopLeft(QPointF((PHOTO_WIDTH - its_size.width()) / 2, (height() - its_size.height()) / 2 + BAR_HEIGHT));
	photo_rect_.setSize(its_size);
}