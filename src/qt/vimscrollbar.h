#ifndef __GUI_QT_VIMSCROLLBAR__
#define __GUI_QT_VIMSCROLLBAR__

#include "qvimshell.h"

#include <QScrollBar>

class VimScrollBar: public QScrollBar
{
	Q_OBJECT
public:
	VimScrollBar(scrollbar_T *, Qt::Orientation, QWidget *parent=0);
	int length();

	void setVisible(bool);
	void setGeometry(int pos, int len);
signals:
	void visibilityChanged(bool);

protected slots:
	void dragging();
	void draggingFinished();

private:
	scrollbar_T *sb;
};

#endif
