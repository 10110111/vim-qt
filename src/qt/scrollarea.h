#ifndef VIM_GUI_QT_SCROLLAREA
#define VIM_GUI_QT_SCROLLAREA

#include <QWidget>
#include <QGridLayout>

class VimScrollBar;

class ScrollBarHolder : public QWidget
{
	Q_OBJECT
public:
	ScrollBarHolder(QWidget* parent = nullptr)
		: QWidget(parent)
	{
	}
	void grab(VimScrollBar*);
private slots:
	void onChildVisibilityChanged();
};

class ScrollArea: public QWidget
{
	Q_OBJECT
public:
	ScrollArea(QWidget *parent=0);
	void setWidget(QWidget *widget);
    void addScrollbarLeft(VimScrollBar* scrollbar);
    void addScrollbarRight(VimScrollBar* scrollbar);
    void addScrollbarBottom(VimScrollBar* scrollbar);

private:
	QWidget *m_widget;
	ScrollBarHolder *m_leftScrollBarHolder, *m_rightScrollBarHolder, *m_bottomScrollBarHolder;
	QGridLayout *m_layout;

};

#endif
