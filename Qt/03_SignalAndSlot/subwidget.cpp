#include "subwidget.h"

SubWidget::SubWidget(QWidget *parent) : QWidget(parent) {
  this->setWindowTitle("窗口2");
  button.setParent(this);
  button.setText("切换到窗口1");
  button.move(50, 50); // 按钮位置

  connect(&button, &QPushButton::clicked, this, &SubWidget::sendSlot);

  resize(400, 300); // 窗体大小
}

void SubWidget::sendSlot() {
  emit mySignal();
  emit mySignal(10, "窗口2");
}
