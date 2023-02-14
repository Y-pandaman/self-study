#include "smallwidget.h"
#include <QHBoxLayout>
#include <QSlider>
#include <QSpinBox>

SmallWidget::SmallWidget(QWidget *parent) : QWidget(parent) {
  QSpinBox *spin = new QSpinBox(this);
  QSlider *slider =
      new QSlider(Qt::Horizontal, this); // Qt::Horizontal 水平滑条

  // 把控件添加到布局中
  // 第一种写法
  QHBoxLayout *hLayout = new QHBoxLayout(this);
  hLayout->addWidget(spin);
  hLayout->addWidget(slider);

  // 第二种写法
  //    QHBoxLayout *hLayout = new QHBoxLayout;
  //    hLayout->addWidget(spin);
  //    hLayout->addWidget(slider);
  //    setLayout(hLayout);

  // 微调改变滑块
  connect(spin, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
          slider, &QSlider::setValue);

  //滑块改变微调
  connect(slider, &QSlider::valueChanged, spin, &QSpinBox::setValue);
}
