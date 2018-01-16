#include <QDebug>
#include "wagroup.h"
#include "waoval.h"
#include "warect.h"
#include "watext.h"

WAGroup::WAGroup(QGraphicsItem *parent) : QGraphicsItemGroup(parent)
{
	this->setFlags(QGraphicsItem::ItemIsSelectable |
				   QGraphicsItem::ItemIsFocusable |
				   QGraphicsItem::ItemClipsChildrenToShape |
				   QGraphicsItem::ItemContainsChildrenInShape |
				   QGraphicsItem::ItemSendsScenePositionChanges |
				   QGraphicsItem::ItemSendsGeometryChanges
				   );
	this->setAcceptHoverEvents(true);
}

QRectF WAGroup::rect() const
{

			QRectF selectionBoundingRect;
			QList<QGraphicsItem *> selectedItems = childItems();
			foreach(QGraphicsItem *current, selectedItems) {

				WARect * warect = dynamic_cast<WARect*>(current);
				WAOval * waoval = dynamic_cast<WAOval*>(current);
				WAText * watext = dynamic_cast<WAText*>(current);
				WAGroup * wagroup = dynamic_cast<WAGroup*>(current);

				if(watext){
					selectionBoundingRect = selectionBoundingRect.united(QRectF(watext->scenePos().x(), watext->scenePos().y(), watext->rect().width(), watext->rect().height()));
				}
				if(warect){
					selectionBoundingRect = selectionBoundingRect.united(QRectF(warect->scenePos().x(), warect->scenePos().y(), warect->rect().width(), warect->rect().height()));
				}
				if(waoval){
					selectionBoundingRect = selectionBoundingRect.united(QRectF(waoval->scenePos().x(), waoval->scenePos().y(), waoval->rect().width(), waoval->rect().height()));
				}
				if(wagroup){
					selectionBoundingRect = selectionBoundingRect.united(QRectF(wagroup->scenePos().x(), wagroup->scenePos().y(), wagroup->rect().width(), wagroup->rect().height()));
				}

			}

			return selectionBoundingRect;
}

void WAGroup::setRect(QRectF rect)
{

}
