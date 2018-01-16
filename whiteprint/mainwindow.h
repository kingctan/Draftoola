#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDockWidget>

#include "designer/tool_itemproperties.h"
#include "designer/tool_outliner.h"
#include "designer/canvas.h"
//#include "designer/canvasframe.h"
#include "item/itembase.h"
#include "item/artboard.h"
#include "designer/wascene.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    Outliner * m_outliner;
    ItemProperties * m_properties;
	Canvas * m_canvas;
	WAScene * m_scene;

    QDockWidget * m_outlinerDock;
    QDockWidget * m_propertiesDock;


public slots:
	void setActiveItem(QGraphicsItem *item);

};

#endif // MAINWINDOW_H
