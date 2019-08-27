#include "scrollarea.moc"
#include "vimscrollbar.h"

#include <QWidget>
#include <QGridLayout>

void ScrollBarHolder::grab(VimScrollBar* scrollbar)
{
	if (scrollbar->parent() == this) {
		return;
	}
	scrollbar->setParent(this);
	connect(scrollbar, SIGNAL(visibilityChanged(bool)), this, SLOT(onChildVisibilityChanged()));
}

void ScrollBarHolder::onChildVisibilityChanged()
{
	for (const auto sibling : findChildren<VimScrollBar*>()) {
		if (sibling->isVisible()) {
			return;
		}
	}

	hide();
}

enum
{
    LEFT_SCROLLBAR_COLUMN=0,
    CENTRAL_WIDGET_COLUMN,
    RIGHT_SCROLLBAR_COLUMN,

    CENTRAL_WIDGET_ROW=0,
    BOTTOM_SCROLLBAR_ROW=1,
};

ScrollArea::ScrollArea(QWidget *parent)
:QWidget(parent), m_widget(NULL)
, m_leftScrollBarHolder  (new ScrollBarHolder(this))
, m_rightScrollBarHolder (new ScrollBarHolder(this))
, m_bottomScrollBarHolder(new ScrollBarHolder(this))
{
	setAutoFillBackground(true);
	m_layout = new QGridLayout(this);
	m_layout->setSpacing(0);
	m_layout->setContentsMargins(0,0,0,0);
	m_layout->setAlignment(Qt::AlignTop | Qt::AlignHCenter);

    m_layout->addWidget(m_leftScrollBarHolder  , CENTRAL_WIDGET_ROW  , LEFT_SCROLLBAR_COLUMN, 2, 1);
    m_layout->addWidget(m_rightScrollBarHolder , CENTRAL_WIDGET_ROW  , RIGHT_SCROLLBAR_COLUMN,2, 1);
    m_layout->addWidget(m_bottomScrollBarHolder, BOTTOM_SCROLLBAR_ROW, CENTRAL_WIDGET_COLUMN);
}

void ScrollArea::setWidget(QWidget *w)
{
	if ( w == m_widget || !w ) {
		return;
	}

	m_widget = w;
	m_layout->addWidget(m_widget, 0, CENTRAL_WIDGET_COLUMN);
}

void ScrollArea::addScrollbarLeft(VimScrollBar* scrollbar)
{
    m_leftScrollBarHolder->grab(scrollbar);
}

void ScrollArea::addScrollbarRight(VimScrollBar* scrollbar)
{
    m_rightScrollBarHolder->grab(scrollbar);
}

void ScrollArea::addScrollbarBottom(VimScrollBar* scrollbar)
{
    m_bottomScrollBarHolder->grab(scrollbar);
}
