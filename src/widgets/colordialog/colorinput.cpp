/*************************************************************************************

   Draftoola - UI and UX prototyping tool for designing static and animated layouts.

   Copyright (C) 2020 Martin Reininger <nitramr>

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License along
   with this program; if not, write to the Free Software Foundation, Inc.,
   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

**************************************************************************************/

#include "colorinput.h"
#include "ui_colorinput.h"
#include <QDebug>

#include <utilities.h>

ColorInput::ColorInput(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ColorInput)
{
    ui->setupUi(this);

    //   ui->txtHex->setInputMask( "#Hhhhhh" );

    connectSlots();
}

ColorInput::~ColorInput()
{
    delete ui;
}

void ColorInput::connectSlots()
{
    connect(ui->sbRed, QOverload<int>::of(&QSpinBox::valueChanged), this, &ColorInput::updateColor);
    connect(ui->sbGreen, QOverload<int>::of(&QSpinBox::valueChanged), this, &ColorInput::updateColor);
    connect(ui->sbBlue, QOverload<int>::of(&QSpinBox::valueChanged), this, &ColorInput::updateColor);
    connect(ui->sbAlpha, QOverload<int>::of(&QSpinBox::valueChanged), this, &ColorInput::updateAlpha);
    connect(ui->txtHex, &QLineEdit::returnPressed, this, &ColorInput::updateColor);
}

void ColorInput::disconnectSlots()
{
    disconnect(ui->sbRed, QOverload<int>::of(&QSpinBox::valueChanged), this, &ColorInput::updateColor);
    disconnect(ui->sbGreen, QOverload<int>::of(&QSpinBox::valueChanged), this, &ColorInput::updateColor);
    disconnect(ui->sbBlue, QOverload<int>::of(&QSpinBox::valueChanged), this, &ColorInput::updateColor);
    disconnect(ui->sbAlpha, QOverload<int>::of(&QSpinBox::valueChanged), this, &ColorInput::updateAlpha);
    disconnect(ui->txtHex, &QLineEdit::returnPressed, this, &ColorInput::updateColor);
}

void ColorInput::setColor(const Color color, int alpha)
{
    disconnectSlots();

    m_color = color;
    m_alpha = alpha;
    ui->txtHex->setText( color.name(QColor::NameFormat::HexRgb) );
    ui->sbRed->setValue( color.red() );
    ui->sbGreen->setValue( color.green() );
    ui->sbBlue->setValue( color.blue() );
    ui->sbAlpha->setValue( m_alpha ); // we have to round the value because of qreal conversion

    connectSlots();
}


/*!
 * \brief Update color that changed by input
 */
void ColorInput::updateColor()
{
    QLineEdit *hexEdit = dynamic_cast<QLineEdit*>(sender());

    if(hexEdit){
        m_color.setNamedColor( ui->txtHex->text() );
    }else{
        m_color.setRgb(ui->sbRed->value(), ui->sbGreen->value(), ui->sbBlue->value() );
    }

    setColor( m_color, m_alpha);

    emit colorChanged( m_color);
}

void ColorInput::updateAlpha()
{
    setColor( m_color, ui->sbAlpha->value());

    emit alphaChanged( m_alpha);
}
