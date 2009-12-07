/***************************************************************************
 *   Copyright (C) 2009 by Volodymyr Shevchyk                              *
 *   volder@users.sourceforge.net                                          *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


#include <QtGui>
#include <QTextStream>
#include <QPainterPath>
#include <QPoint>
#include <math.h>
#include <QDebug>
#include <QShortcut>


#include "graphics.h"

graphics::graphics(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
        this->setWindowTitle("GraphicCore");
	setObjectName("graphics");

        width = 640;
        height = 480;

	curentColor = 0;
	textSize = 12;
	textFont = "Arial";
	textDirection = 0;
	lineThickness = 1;
	lineStyle = 0;

        textDirection = 0;

	pix = QPixmap(width, height);
        pixBG = QPixmap(width, height);
        pixBG.fill(Qt::white);
        pix.fill(Qt::transparent);
        pix.alphaChannel();



	resize(width, height);

        rsi = new ReadStdIn(this);
        new QShortcut(Qt::Key_Return, this, SLOT(close()));
	connect(rsi, SIGNAL(commandAppeared(QString)), this, SLOT(processCommand(QString)));
        rsi->start();

}

graphics::~graphics()
{
}

void graphics::processCommand(QString  command)
{
	if(getMethodName(command) == "initgraph")
	{
		index = command.indexOf("(",0);
		indexOfSimbol = command.indexOf(",", index);
		numberOf = indexOfSimbol - index;
		width = command.mid(index+1, numberOf-1).toInt(0,10);
		
		index = indexOfSimbol;
		indexOfSimbol = command.indexOf(")", index+1);
		numberOf = indexOfSimbol - index;
		height = command.mid(index+1, numberOf-1).toInt(0,10);

		createPixmap(width, height);
                creatBGPixmap(width, height);
                update();
	}
	QPainterPath myPath;
	
	p.begin(&pix);
	pen.setWidth(lineThickness);
	switch(curentColor)
		{
			case 0: pen.setColor(Qt::black); 
					p.setPen(pen); 				update();break;
			case 1: pen.setColor(Qt::darkBlue); 
					p.setPen(pen);				update();break;
			case 2: pen.setColor(Qt::darkGreen); 
					p.setPen(pen);				update();break;
			case 3: pen.setColor(Qt::darkCyan); 
					p.setPen(pen);				update();break;
			case 4: pen.setColor(Qt::darkRed);
					p.setPen(pen);				update();break;
			case 5: pen.setColor(QColor(139, 0, 139)); 
					p.setPen(pen);				update();break;
			case 6: pen.setColor(QColor(165, 42, 42));
					p.setPen(pen);			 	update();break;
			case 7: pen.setColor(Qt::gray);
					p.setPen(pen);	 			update();break;
			case 8: pen.setColor(Qt::darkGray); 
					p.setPen(pen);				update();break;
			case 9: pen.setColor(Qt::blue); 
					p.setPen(pen);				update();break;
			case 10:pen.setColor(Qt::green); 
					p.setPen(pen);				update();break;
			case 11:pen.setColor(Qt::cyan);
					p.setPen(pen);	 			update();break;
			case 12:pen.setColor(Qt::red);
					p.setPen(pen);	 			update();break;
			case 13:pen.setColor(QColor(255, 0, 255));
					p.setPen(pen);				update();break;
			case 14:pen.setColor(Qt::yellow);
					p.setPen(pen);	 			update();break;
			case 15:pen.setColor(Qt::white);
					p.setPen(pen);	 			update();break;
		}
	switch(lineStyle)
	{
			case 0: pen.setStyle(Qt::SolidLine); 
					p.setPen(pen); 				update();break;
			case 1: pen.setStyle(Qt::DotLine); 
					p.setPen(pen);				update();break;
			case 2: pen.setStyle(Qt::DashDotLine); 
					p.setPen(pen);				update();break;
			case 3: pen.setStyle(Qt::DashLine); 
					p.setPen(pen);				update();break;
			case 4: pen.setStyle(Qt::CustomDashLine);
					p.setPen(pen);				update();break;
	}
	if(getMethodName(command) == "arc")
	{
		index = command.indexOf("(",0);
		indexOfSimbol = command.indexOf(",", index);
		numberOf = indexOfSimbol - index;
                x1 = command.mid(index+1, numberOf-1).toInt(0,10);

		index = indexOfSimbol;
		indexOfSimbol = command.indexOf(",", index+1);
		numberOf = indexOfSimbol - index;
                y1 = command.mid(index+1, numberOf-1).toInt(0,10);

		index = indexOfSimbol;
		indexOfSimbol = command.indexOf(",", index+1);
		numberOf = indexOfSimbol - index;
		stAngle = command.mid(index+1, numberOf-1).toInt(0,10) / 2;

		index = indexOfSimbol;
		indexOfSimbol = command.indexOf(",", index+1);
		numberOf = indexOfSimbol - index;
		endAngle = command.mid(index+1, numberOf-1).toInt(0,10);

		index = indexOfSimbol;
		indexOfSimbol = command.indexOf(")", index+1);
		numberOf = indexOfSimbol - index;
		r = command.mid(index+1, numberOf-1).toInt(0,10);

                p.drawArc(x1-r, y1-r, 2*r, 2*r, stAngle, endAngle);
                update();
	}
	if (getMethodName(command) == "bar")
	{
		index = command.indexOf("(",0);
		indexOfSimbol = command.indexOf(",", index);
		numberOf = indexOfSimbol - index;
		x = command.mid(index+1, numberOf-1).toInt(0,10);
		
		index = indexOfSimbol;
		indexOfSimbol = command.indexOf(",", index+1);
		numberOf = indexOfSimbol - index;
		y = command.mid(index+1, numberOf-1).toInt(0,10);
		
		index = indexOfSimbol;
		indexOfSimbol = command.indexOf(",", index+1);
		numberOf = indexOfSimbol - index;
		x1 = command.mid(index+1, numberOf-1).toInt(0,10);
	
		index = indexOfSimbol;
		indexOfSimbol = command.indexOf(")", index+1);
		numberOf = indexOfSimbol - index;
		y1 = command.mid(index+1, numberOf-1).toInt(0,10);

                p.drawRect(x, y, x1-x, y1-y);
		update();
	}
        if (getMethodName(command) == "bar3d")
	{
		index = command.indexOf("(",0);
		indexOfSimbol = command.indexOf(",", index);
		numberOf = indexOfSimbol - index;
		x = command.mid(index+1, numberOf-1).toInt(0,10);
		
		index = indexOfSimbol;
		indexOfSimbol = command.indexOf(",", index+1);
		numberOf = indexOfSimbol - index;
		y = command.mid(index+1, numberOf-1).toInt(0,10);
		
		index = indexOfSimbol;
		indexOfSimbol = command.indexOf(",", index+1);
		numberOf = indexOfSimbol - index;
		x1 = command.mid(index+1, numberOf-1).toInt(0,10);

		index = indexOfSimbol;
		indexOfSimbol = command.indexOf(",", index+1);
		numberOf = indexOfSimbol - index;
		y1 = command.mid(index+1, numberOf-1).toInt(0,10);

		index = indexOfSimbol;
		indexOfSimbol = command.indexOf(",", index+1);
		numberOf = indexOfSimbol - index;
		z = command.mid(index+1, numberOf-1).toInt(0,10);	

		index = indexOfSimbol;
		indexOfSimbol = command.indexOf(")", index+1);
		numberOf = indexOfSimbol - index;
		methodText = command.mid(index+1, numberOf-1);
	
		p.drawRect(x, y, x1-x, y1-y);
		if(methodText == "true")
		{
			int a, c;
			c = z;
                        a = (int) fabs(c / sqrt(2)); //Modified to avoid warning: passing `double' for converting 1 of `int abs(int)'
 			p.drawLine(x, y, x+a, y-a); 
			p.drawLine(x+a, y-a, x1+a, y-a);
			p.drawLine(x1+a, y-a, x1+a, y1-a);
			p.drawLine(x1, y, x1+a, y-a);
			p.drawLine(x1, y1, x1+a, y1-a);
		}
		update();
	}
	if(getMethodName(command) == "circle")
	{
		index = command.indexOf("(",0);
		indexOfSimbol = command.indexOf(",", index);
		numberOf = indexOfSimbol - index;
                x1 = command.mid(index+1, numberOf-1).toInt(0,10);
		
		index = indexOfSimbol;
		indexOfSimbol = command.indexOf(",", index+1);
		numberOf = indexOfSimbol - index;
                y1 = command.mid(index+1, numberOf-1).toInt(0,10);

		index = indexOfSimbol;
		indexOfSimbol = command.indexOf(")", index+1);
		numberOf = indexOfSimbol - index;
		r = command.mid(index+1, numberOf-1).toInt(0,10);

                p.drawEllipse(x1-r, y1-r, 2*r, 2*r);
		update();
	}
        if(getMethodName(command) == "cleardevice")
	{
                pix.fill(Qt::transparent);
	}
        if(getMethodName(command) == "closegraph")
        {
            //rsi->readKomand = false;
        }
        if(getMethodName(command) == "drawfunc")
        {
            qDebug() << command;
        }
	if(getMethodName(command) == "drawpoly")
	{
/*		int pX, pY;
		if(step == 1)
		{

			index = command.indexOf("(",0);
			indexOfSimbol = command.indexOf(",", index+1);
			numberOf = indexOfSimbol - index;
			x1 = command.mid(index+1, numberOf-1).toInt(0,10);

			index = indexOfSimbol;
			indexOfSimbol = command.indexOf(")", index+1);
			numberOf = indexOfSimbol - index;
			y1 = command.mid(index+1, numberOf-1).toInt(0,10);
			
			pX = x1;
			pY = y1;
			myPath.moveTo(x1, y1);
			ui.label->setText(command);
		}
		index = command.indexOf("(",0);
		indexOfSimbol = command.indexOf(",", index+1);
		numberOf = indexOfSimbol - index;
		x = command.mid(index+1, numberOf-1).toInt(0,10);

		index = indexOfSimbol;
		indexOfSimbol = command.indexOf(")", index+1);
		numberOf = indexOfSimbol - index;
		y = command.mid(index+1, numberOf-1).toInt(0,10);

		
        polygon[step - 1] = QPointF(x, y);
		myPath.moveTo(pX, pY);
		myPath.lineTo(x, y);
	
		pX = x;
		pY = y;
		step += 1;	

		if(step > numOfPoints)
		{
			myPath.addPolygon(polygon);
			ui.label->setText(command);
			p.drawPath(myPath);
			update();
		}
*/	}
	if(getMethodName(command) == "ellipse")
	{
		index = command.indexOf("(",0);
		indexOfSimbol = command.indexOf(",", index);
		numberOf = indexOfSimbol - index;
		x = command.mid(index+1, numberOf-1).toInt(0,10);
		
		index = indexOfSimbol;
		indexOfSimbol = command.indexOf(",", index+1);
		numberOf = indexOfSimbol - index;
		y = command.mid(index+1, numberOf-1).toInt(0,10);

		index = indexOfSimbol;
		indexOfSimbol = command.indexOf(",", index+1);
		numberOf = indexOfSimbol - index;
		x1 = command.mid(index+1, numberOf-1).toInt(0,10);

		index = indexOfSimbol;
		indexOfSimbol = command.indexOf(")", index+1);
		numberOf = indexOfSimbol - index;
		y1 = command.mid(index+1, numberOf-1).toInt(0,10);

		p.drawEllipse(x-x1, y-y1, 2*x1, 2*y1);
		update();
	}
	if(getMethodName(command) == "fillellipse")
	{
		index = command.indexOf("(",0);
		indexOfSimbol = command.indexOf(",", index);
		numberOf = indexOfSimbol - index;
		x = command.mid(index+1, numberOf-1).toInt(0,10);
		
		index = indexOfSimbol;
		indexOfSimbol = command.indexOf(",", index+1);
		numberOf = indexOfSimbol - index;
		y = command.mid(index+1, numberOf-1).toInt(0,10);

		index = indexOfSimbol;
		indexOfSimbol = command.indexOf(",", index+1);
		numberOf = indexOfSimbol - index;
		x1 = command.mid(index+1, numberOf-1).toInt(0,10);

		index = indexOfSimbol;
		indexOfSimbol = command.indexOf(")", index+1);
		numberOf = indexOfSimbol - index;
		y1 = command.mid(index+1, numberOf-1).toInt(0,10);

		myPath.addEllipse(x-x1, y-y1, 2*x1, 2*y1);
		p.drawPath(myPath);
		update();
	}
	if(getMethodName(command) == "line")
	{
		index = command.indexOf("(",0);
		indexOfSimbol = command.indexOf(",", index);
		numberOf = indexOfSimbol - index;
		x = command.mid(index+1, numberOf-1).toInt(0,10);
		
		index = indexOfSimbol;
		indexOfSimbol = command.indexOf(",", index+1);
		numberOf = indexOfSimbol - index;
		y = command.mid(index+1, numberOf-1).toInt(0,10);

		index = indexOfSimbol;
		indexOfSimbol = command.indexOf(",", index+1);
		numberOf = indexOfSimbol - index;
		x1 = command.mid(index+1, numberOf-1).toInt(0,10);
	
		index = indexOfSimbol;
		indexOfSimbol = command.indexOf(")", index+1);
		numberOf = indexOfSimbol - index;
		y1 = command.mid(index+1, numberOf-1).toInt(0,10);

		p.drawLine(x, y, x1,y1);
		update();
	}
        if(getMethodName(command) == "lineto")
        {
                index = command.indexOf("(",0);
                indexOfSimbol = command.indexOf(",", index);
                numberOf = indexOfSimbol - index;
                x = command.mid(index+1, numberOf-1).toInt(0,10);

                index = indexOfSimbol;
                indexOfSimbol = command.indexOf(")", index+1);
                numberOf = indexOfSimbol - index;
                y = command.mid(index+1, numberOf-1).toInt(0,10);

                p.drawLine(x1, y1, x, y);
                update();
                x1 = x;
                y1 = y;
        }
         if(getMethodName(command) == "moveto")
        {
                index = command.indexOf("(",0);
                indexOfSimbol = command.indexOf(",", index);
                numberOf = indexOfSimbol - index;
                x1 = command.mid(index+1, numberOf-1).toInt(0,10);

                index = indexOfSimbol;
                indexOfSimbol = command.indexOf(")", index+1);
                numberOf = indexOfSimbol - index;
                y1 = command.mid(index+1, numberOf-1).toInt(0,10);
        }
        if (getMethodName(command) == "outtext")
	{
		index = command.indexOf("\"", 0);
		indexOfSimbol = command.indexOf("\"", index+ 1);
		numberOf = indexOfSimbol - index;
		methodText = command.mid(index+1, numberOf-1);

                p.drawText(x1, x1, methodText);
		update();
	}
        if (getMethodName(command) == "outtextxy")
	{
		QString oneSimbol;
 		p.setFont(QFont(textFont, textSize));

		index = command.indexOf("(",0);
		indexOfSimbol = command.indexOf(",", index);
		numberOf = indexOfSimbol - index;
                x1 = command.mid(index+1, numberOf-1).toInt(0,10);
		
		index = indexOfSimbol;
		indexOfSimbol = command.indexOf(",", index+1);
		numberOf = indexOfSimbol - index;
                y1 = command.mid(index+1, numberOf-1).toInt(0,10);

		index = command.indexOf("\"", 0);
		indexOfSimbol = command.indexOf("\"", index+ 1);
		numberOf = indexOfSimbol - index;
		methodText = command.mid(index+1, numberOf-1);

		switch(textDirection)
		{
                        case 0: p.drawText(x1, y1, methodText); break;
			case 1:
				for(int i = 0; i <= methodText.length(); i++)
				{
					oneSimbol = methodText.mid(i, 1);
                                        p.drawText(x1, y1, oneSimbol);
					y += textSize;
				}
                }
		update();
	}
	if(getMethodName(command) == "pieslice")
	{
		index = command.indexOf("(",0);
		indexOfSimbol = command.indexOf(",", index);
		numberOf = indexOfSimbol - index;
                x1 = command.mid(index+1, numberOf-1).toInt(0,10);

		index = indexOfSimbol;
		indexOfSimbol = command.indexOf(",", index+1);
		numberOf = indexOfSimbol - index;
                y1 = command.mid(index+1, numberOf-1).toInt(0,10);

		index = indexOfSimbol;
		indexOfSimbol = command.indexOf(",", index+1);
		numberOf = indexOfSimbol - index;
		stAngle = command.mid(index+1, numberOf-1).toInt(0,10) / 2;

		index = indexOfSimbol;
		indexOfSimbol = command.indexOf(",", index+1);
		numberOf = indexOfSimbol - index;
		endAngle = command.mid(index+1, numberOf-1).toInt(0,10);

		index = indexOfSimbol;
		indexOfSimbol = command.indexOf(")", index+1);
		numberOf = indexOfSimbol - index;
		r = command.mid(index+1, numberOf-1).toInt(0,10);

                p.drawPie(x1-r, y1-r, 2*r, 2*r, stAngle, endAngle);
                update();
	}
        if(getMethodName(command) == "putpixel")
	{
		index = command.indexOf("(",0);
		indexOfSimbol = command.indexOf(",", index);
		numberOf = indexOfSimbol - index;
                x1 = command.mid(index+1, numberOf-1).toInt(0,10);
		
		index = indexOfSimbol;
		indexOfSimbol = command.indexOf(")", index);
		numberOf = indexOfSimbol - index;
                y1 = command.mid(index+1, numberOf-1).toInt(0,10);

                p.drawPoint(x1, y1);
                update();
	}
        if (getMethodName(command) == "setbkcolor")
        {
                index = command.indexOf("(", 0);
                indexOfSimbol = command.indexOf(")", index+ 1);
                numberOf = indexOfSimbol - index;
                curentBGColor = command.mid(index+1, numberOf-1).toInt(0,10);

                setCurentBGColor(curentBGColor);
                update();
        }
        if (getMethodName(command) == "setcolor")
	{
		index = command.indexOf("(", 0);
		indexOfSimbol = command.indexOf(")", index+ 1);
		numberOf = indexOfSimbol - index;
		curentColor = command.mid(index+1, numberOf-1).toInt(0,10);
	}
        if (getMethodName(command) == "setlinestyle")
	{
		index = command.indexOf("(",0);
		indexOfSimbol = command.indexOf(",", index);
		numberOf = indexOfSimbol - index;
		lineStyle = command.mid(index+1, numberOf-1).toInt(0,10);

		index = indexOfSimbol;
		indexOfSimbol = command.indexOf(")", index+1);
		numberOf = indexOfSimbol - index;
		lineThickness= command.mid(index+1, numberOf-1).toInt(0,10);
	}
        if (getMethodName(command) == "settextstyle")
	{
		index = command.indexOf("(",0);
		indexOfSimbol = command.indexOf(",", index);
		numberOf = indexOfSimbol - index;
		textFont = command.mid(index+1, numberOf-1);

		index = indexOfSimbol;
		indexOfSimbol = command.indexOf(",", index+1);
		numberOf = indexOfSimbol - index;
		textDirection = command.mid(index+1, numberOf-1).toInt(0,10);

		index = indexOfSimbol;
		indexOfSimbol = command.indexOf(")", index);
		numberOf = indexOfSimbol - index;
		textSize = command.mid(index+1, numberOf-1).toInt(0,10);
	}
	p.end();
        update();
}

void graphics::paintEvent(QPaintEvent * /*event*/ )
{
        QPainter painter(this );
        painter.drawPixmap(0, 0, pixBG);
        painter.drawPixmap( 0 , 0 , pix);
}

void graphics::createPixmap(int width, int height)
{
	resize(width, height);
	pix = QPixmap(width, height);
        pix.fill(Qt::transparent);
}

void graphics::creatBGPixmap(int width, int height)
{
        resize(width, height);
        pixBG = QPixmap(width, height);
        pixBG.fill(Qt::white);
}
QString graphics::getMethodName(QString command)
{
	QString methodName;
	index = command.indexOf("(",0);
	methodName = command.left(index);
	return methodName;
}
void graphics::setCurentBGColor(int curentBGColor)
{

                switch(curentBGColor)
                {
                        case 0: pixBG.fill(Qt::black); 				update();break;
                        case 1: pixBG.fill(Qt::darkBlue);                       update();break;
                        case 2: pixBG.fill(Qt::darkGreen);                      update();break;
                        case 3: pixBG.fill(Qt::darkCyan);       		update();break;
                        case 4: pixBG.fill(Qt::darkRed);			update();break;
                        case 5: pixBG.fill(QColor(139, 0, 139));        	update();break;
                        case 6: pixBG.fill(QColor(165, 42, 42));	 	update();break;
                        case 7: pixBG.fill(Qt::gray);	 			update();break;
                        case 8: pixBG.fill(Qt::darkGray);			update();break;
                        case 9: pixBG.fill(Qt::blue);    			update();break;
                        case 10:pixBG.fill(Qt::green);  			update();break;
                        case 11:pixBG.fill(Qt::cyan);   			update();break;
                        case 12:pixBG.fill(Qt::red); 	 			update();break;
                        case 13:pixBG.fill(QColor(255, 0, 255));        	update();break;
                        case 14:pixBG.fill(Qt::yellow);	 			update();break;
                        case 15:pixBG.fill(Qt::white);   			update();break;
                }
}
