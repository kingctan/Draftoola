#include "shadow.h"
#include <QDebug>

/***************************************************
 *
 * Constructor
 *
 ***************************************************/

Shadow::Shadow() : Shadow(QString::null){}

Shadow::Shadow(QString name, QColor color, qreal radius, QPointF offset, qreal spread) : AbstractItemProperty(name)
{
    m_color = color;
    m_radius = radius;
    m_offset = offset;
    m_spread = spread;
}

Shadow::Shadow(const Shadow &other) : AbstractItemProperty(other)
{   
    m_color = other.m_color;
    m_radius = other.m_radius;
    m_offset = other.m_offset;
    m_spread = other.m_spread;

}


/***************************************************
 *
 * Properties
 *
 ***************************************************/


void Shadow::setColor(QColor color)
{
    m_color = color;
}

QColor Shadow::color() const
{
    return m_color;
}

void Shadow::setRadius(qreal radius)
{
    m_radius = radius;
}

qreal Shadow::radius() const
{
    return m_radius;
}

void Shadow::setOffset(QPointF offset)
{
    m_offset = offset;
}

void Shadow::setOffset(qreal x, qreal y)
{
    setOffset(QPointF(x,y));
}

QPointF Shadow::offset() const
{
    return m_offset;
}

void Shadow::setSpread(qreal spread)
{
    m_spread = spread;
}

qreal Shadow::spread() const
{
    return m_spread;
}

void Shadow::fromObject(AbstractItemProperty object)
{
    m_id = object.m_id;
    m_isOn = object.m_isOn;
    m_blendMode = object.m_blendMode;
    m_name = object.m_name;
}


/***************************************************
 *
 * Operator
 *
 ***************************************************/

bool Shadow::operator==(const Shadow &other) const
{
    if(this == &other) return true;

    return m_color == other.m_color &&
            m_radius == other.m_radius &&
            m_offset == other.m_offset &&
            m_spread == other.m_spread &&
            AbstractItemProperty::operator==(other);;
}

QDebug operator<<(QDebug dbg, const Shadow &obj)
{
    const AbstractItemProperty &aip = obj;

    dbg << "Shadow(" <<
           aip <<
           obj.color() <<
           obj.radius() <<
           obj.offset() <<
           obj.spread() <<
           ")";
    return dbg.maybeSpace();
}

QDataStream &operator<<(QDataStream &out, const Shadow &obj)
{
    const AbstractItemProperty &aip = obj;

    out << aip
        << obj.color()
        << obj.radius()
        << obj.offset()
        << obj.spread();

    return out;
}

QDataStream &operator>>(QDataStream &in, Shadow &obj)
{
    QColor m_color;
    qreal m_radius;
    QPointF m_offset;
    qreal m_spread;
    AbstractItemProperty m_aip;

    in >> m_aip >> m_color >> m_radius >> m_offset >> m_spread;

    obj.fromObject(m_aip);
    obj.setColor(m_color);
    obj.setRadius(m_radius);
    obj.setOffset(m_offset);
    obj.setSpread(m_spread);

    return in;
}