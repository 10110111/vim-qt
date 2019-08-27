#include "vimscrollbar.moc"

VimScrollBar::VimScrollBar(scrollbar_T *sbar, Qt::Orientation o, QWidget *parent)
:QScrollBar(o, parent), sb(sbar)
{
	connect(this, SIGNAL(valueChanged(int)),
			this, SLOT(draggingFinished()));
}

void VimScrollBar::dragging()
{
	if (sb == NULL) {
		return;
	}

	gui_drag_scrollbar(sb, this->value(), 1);
}

void VimScrollBar::draggingFinished()
{
	if (sb == NULL) {
		return;
	}

	gui_drag_scrollbar(sb, this->value(), 0);
}

void VimScrollBar::setGeometry(int pos, int len)
{
	if (orientation() == Qt::Vertical) {
		move(0, pos-1);
		resize(sizeHint().width(), len);
	} else {
		move(pos, 0);
		resize(len, sizeHint().height());
	}
}

void VimScrollBar::setVisible(bool show)
{
	bool visible = isVisible();
	QScrollBar::setVisible(show);

	const auto holder = parentWidget();
	if (show) {
		holder->show();
		if (orientation() == Qt::Vertical) {
			holder->setFixedWidth(sizeHint().width());
		} else {
			holder->setFixedHeight(sizeHint().height());
		}
	}

	if ( visible != show ) {
		emit visibilityChanged(show);
	}
}
