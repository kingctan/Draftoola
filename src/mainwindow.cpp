#include "mainwindow.h"
#include "ui_mainwindow.h"


#include "item/itembase.h"
#include "item/itemrect.h"
#include "item/itemoval.h"
#include "item/itemtext.h"
#include "item/itemgroup.h"
#include "item/itemstruct.h"
#include "item/stroke.h"
#include "item/shadow.h"
#include "item/exportlevel.h"
#include "designer/handleframe.h"
#include "manager/stylefactory.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
    QApplication::setStyle(new StyleFactory( QApplication::style()->objectName()));

	ui->setupUi(this);

    showMaximized();

    // inizialize widgets
    setupWorkspace();
    setupToolbar();


    // connect widgets
    connectSlots();


    // TODO: delete function for release
    tmpSetup();

}

MainWindow::~MainWindow()
{
	delete ui;

}

void MainWindow::setupWorkspace()
{
    QScrollArea * scrollProp = new QScrollArea();

    m_properties = new ItemProperties(scrollProp);
    m_outliner = new Outliner();

    m_canvas = new CanvasView();
    this->setCentralWidget(m_canvas);

    m_outlinerDock = new QDockWidget(tr("Outliner"));
    m_outlinerDock->setWidget(m_outliner);
    m_outlinerDock->setAllowedAreas(Qt::DockWidgetArea::RightDockWidgetArea | Qt::DockWidgetArea::LeftDockWidgetArea);
    this->addDockWidget(Qt::LeftDockWidgetArea, m_outlinerDock);


    m_propertiesDock = new QDockWidget("Properties");
    m_propertiesDock->setWidget(scrollProp);
    m_propertiesDock->setAllowedAreas(Qt::DockWidgetArea::RightDockWidgetArea | Qt::DockWidgetArea::LeftDockWidgetArea);
    m_propertiesDock->setSizePolicy(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::MinimumExpanding);
//    m_propertiesDock->setFixedWidth(300);
    this->addDockWidget(Qt::RightDockWidgetArea, m_propertiesDock);
}

void MainWindow::setupToolbar()
{

//    ui->mainToolBar->setFloatable(false);
//    ui->mainToolBar->setMovable(false);
//    ui->mainToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    m_toolArtboard = new QToolButton();
    m_toolArtboard->setIcon( QIcon(":/icons/dark/tools/presentation.svg") );
    m_toolArtboard->setText(tr("Artboard"));
    ui->mainToolBar->addWidget(m_toolArtboard);

    m_toolRectangle = new QToolButton();
    m_toolRectangle->setIcon( QIcon(":/icons/dark/tools/rectangle.svg") );
    m_toolRectangle->setText(tr("Rectangle"));
    ui->mainToolBar->addWidget(m_toolRectangle);

    m_toolOval = new QToolButton();
    m_toolOval->setIcon( QIcon(":/icons/dark/tools/ellipse.svg") );
    m_toolOval->setText(tr("Oval"));
    ui->mainToolBar->addWidget(m_toolOval);

    m_toolLine = new QToolButton();
    m_toolLine->setIcon( QIcon(":/icons/dark/tools/line.svg") );
    m_toolLine->setText(tr("Line"));
    ui->mainToolBar->addWidget(m_toolLine);

    m_toolTriangle = new QToolButton();
    m_toolTriangle->setIcon( QIcon(":/icons/dark/tools/triangle.svg") );
    m_toolTriangle->setText(tr("Triangle"));
    ui->mainToolBar->addWidget(m_toolTriangle);

    m_toolStar = new QToolButton();
    m_toolStar->setIcon( QIcon(":/icons/dark/tools/star.svg") );
    m_toolStar->setText(tr("Star"));
    ui->mainToolBar->addWidget(m_toolStar);

    m_toolPolygon = new QToolButton();
    m_toolPolygon->setIcon( QIcon(":/icons/dark/tools/pentagon.svg") );
    m_toolPolygon->setText(tr("Polygon"));
    ui->mainToolBar->addWidget(m_toolPolygon);

    m_toolPath = new QToolButton();
    m_toolPath->setIcon( QIcon(":/icons/dark/tools/fountain-pen-tip.svg") );
    m_toolPath->setText(tr("Vector"));
    ui->mainToolBar->addWidget(m_toolPath);

    m_toolText = new QToolButton();
    m_toolText->setIcon( QIcon(":/icons/dark/tools/format-textbox.svg") );
    m_toolText->setText(tr("Text"));
    ui->mainToolBar->addWidget(m_toolText);

    m_toolImage = new QToolButton();
    m_toolImage->setIcon( QIcon(":/icons/dark/tools/image.svg") );
    m_toolImage->setText(tr("Image"));
    ui->mainToolBar->addWidget(m_toolImage);



}

void MainWindow::connectSlots()
{
    connect(m_canvas->handleFrame(), &HandleFrame::sendActiveItems, this, &MainWindow::setActiveItems);
    connect(m_canvas, &CanvasView::itemsChanged, m_outliner, &Outliner::updateList);
    connect(m_properties, &ItemProperties::itemsChanged, m_canvas->handleFrame(), &HandleFrame::frameToSelection);

    // signal to signal connection
    connect(m_properties, &ItemProperties::exportItem, [this](AbstractItemBase *item){
        emit m_scene->exportItem(item);
    });
}

void MainWindow::tmpSetup()
{
    // Gradients
    QLinearGradient gradient(0,0,50,50);
    gradient.setColorAt(0, Qt::white);
    gradient.setColorAt(1, Qt::darkBlue);

    // Strokes
    Stroke strokeR("TestEllipseStroke", QBrush(QColor(128,208,23, 128)),3, StrokePosition::Inner);
    Stroke stroke("TestEllipseStroke", QBrush(gradient),4, StrokePosition::Outer);
    stroke.setCapStyle(Qt::PenCapStyle::RoundCap);
    stroke.setStyle(Qt::PenStyle::DotLine);
    Stroke stroke3("TestEllipseStroke", QBrush(QColor(128,208,23)),2, StrokePosition::Center);

    // Shadows
    Shadow shadow = Shadow("Shadow", QColor(0,0,0,100), 0, QPointF(0,0),0);
    Shadow shadow2 = Shadow("Shadow2", QColor(255,0,0), 10, QPointF(0,0), 2);
    Shadow shadow3 = Shadow("Shadow3", QColor(0,0,0,255), 1, QPointF(0,0),0);

    // Fills - Image
    QImage fillImage("sun.jpg");

    Fills fill("rect",fillImage);
    fill.setBlendMode(QPainter::CompositionMode_SourceOver);
//    fill.setFillMode(FillMode::Stretch);

    Fills fill2("oval", QColor(255,0,0,128));
//    fill2.setStyle(Qt::Dense7Pattern);
//    fill2.setFillType(FillType::Pattern);

    Fills fill3("black", QColor());

    //Export Levels
    ExportLevel expLevel(0, 1);
    ExportLevel expLevel2(1, 2);
    ExportLevel expLevel3(2, 3);


    // Artboard
    Artboard *artboard = new Artboard("Artboard1");
    artboard->addExportLevel(expLevel);
    artboard->addExportLevel(expLevel2);
    //	artboard->setPos(20,20);
    m_canvas->addItem(artboard, 0, 0);
//    m_outliner->addNode(artboard);

    // Object Ovals
    ItemOval *oval = new ItemOval(60,80);
    oval->setName("Oval1");
    oval->addFills(fill2);
//    oval->setRotation(45);
    oval->addStroke(stroke);
//    oval->addShadow(shadow);
    oval->addShadow(shadow2);
//    oval->addShadow(shadow3);
    oval->addExportLevel(expLevel);
    oval->addExportLevel(expLevel2);
    oval->addExportLevel(expLevel3);
    m_canvas->addItem(oval, 50,120);

    // Object Rects
    ItemRect *rect = new ItemRect(60,100);
//    rect->setTransform(QTransform().rotate(70, Qt::YAxis));
    rect->setName("Rect1");
    rect->setRadius(5,0,15,20);
//    rect->setRotation(45);
    rect->addStroke(strokeR);
    //	rect->addStroke(stroke);
    rect->addShadow(shadow);
    rect->addShadow(shadow2);
    rect->addInnerShadow(shadow3);
    rect->addFills(fill);
    m_canvas->addItem(rect, 10,10);

    ItemRect * rect2 = new ItemRect(10,10);
//	rect2->setRadius(0,0,15,0);
    rect2->setRotation(0);
    rect2->addFills(fill3);
    m_canvas->addItem(rect2, 30,10, oval);


    // Object Text
    ItemText *text = new ItemText("Hello World<br>second line");
    m_canvas->addItem(text, 100, 10);

    // Artboard
    Artboard *artboard2 = new Artboard("Artboard2");
    artboard2->addExportLevel(expLevel);
    //	artboard->setPos(20,20);
    m_canvas->addItem(artboard2, 400, 0);


    // Object Ovals
    ItemOval *oval2 = new ItemOval(60,60);
    oval2->setName("Oval2");
    oval2->addFills(fill2);
    m_canvas->addItem(oval2, 50,120, artboard2);


//	stroke.setStrokePosition(StrokePosition::Outer);
//	ItemOval * ovalG = new ItemOval(50,50);
//	ovalG->addFills(Fills("oval", QColor(Qt::green)));
//	ovalG->addStroke(stroke);
//	ovalG->setParentItem(rect);


//        ItemRect * rectG = new ItemRect(50,60);
//        rectG->addFills(Fills("rect", QColor(Qt::blue)));
//        m_canvas->addItem(rectG, 60,0);

//        stroke.setStrokePosition(StrokePosition::Outer);
//        ItemOval * ovalG = new ItemOval(50,50);
//        ovalG->addFills(Fills("oval", QColor(Qt::green)));
//        ovalG->addStroke(stroke);
//        m_canvas->addItem(ovalG, 0,0);

//    	ItemGroup * group = new ItemGroup();
//    	group->addToGroup(rectG);
//    	group->addToGroup(ovalG);
//    	m_canvas->addItem(group, 20,280);
}

/***************************************************
 *
 * Slots
 *
 ***************************************************/

void MainWindow::setActiveItems(QList<AbstractItemBase *> items)
{
    m_properties->setActiveItems(items);
}
