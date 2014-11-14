
#include <ScanLineComputer.h>
#include <Buffer.h>
#include <FastMath.h>
#include <limits.h>



void ScanLineComputer::AddEdge(const Coord2D p1, const Coord2D p2,
															 const int index1, const int index2)
{
	// compléter ici : calculer les points de la bordure et appeler AddPoint
	// on utitlise la méthode de Bresenheim pour calculer les points du
	// segment [p1,p2] et on les ajoute via la méthode AddPoint
    int X, Y, LongX, LongY, Critere, Const1, Const2, IncX, IncY, cpt;
    X = p1.x;
    Y = p1.y;
    LongX = p2.x - X;
    LongY = p2.y - Y;
    if(LongX >= 0){
        IncX = 1;
    }else{
        IncX = -1;
        LongX = -LongX;
    }
	if(LongY >= 0){
        IncY = 1;
	}else{
        IncY = -1;
        LongY = -LongY;
	}
	if(LongY < LongX){
        Const1 = 2 * (LongY - LongX);
        Const2 = 2 * LongY;
        Critere = Const2 - LongX;
        for(cpt = 1; cpt <= LongX; cpt++){
            /* dessiner les pixels dans la zone de dessin */
            if(Y < height && X < width && X > 0 && Y > 0){
                /* 0<X<width et 0<Y<height */
                AddPoint(X, Y, p1, p2, index1, index2);
            }else if(X < width && X > 0 && Y > 0){
                /* Y>height, donc on met height-1 sur Y */
                AddPoint(X, height - 1, p1, p2, index1, index2);
            }else if(Y < height && X > 0 && Y > 0){
                /* X>width, donc on met width-1 sur X */
                AddPoint(width - 1, Y, p1, p2, index1, index2);
            }else if(Y < height && X < width && X > 0){
                /* Y<0, on met 1 sur Y */
                AddPoint(X, 1, p1, p2, index1, index2);
            }else if(Y < height && X < width && Y > 0){
                /* X<0, on met 1 sur X */
                AddPoint(1, Y, p1, p2, index1, index2);
            }
            if(Critere > 0){
                Y += IncY;
                Critere += Const1;
            }else{
                Critere += Const2;
            }
            X += IncX;
        }
	}else{
        Const1 = 2 * (LongX - LongY);
        Const2 = 2 * LongX;
        Critere = Const2 - LongY;
        for(cpt = 1; cpt <= LongY; cpt++){
            /* dessiner les pixels dans la zone de dessin */
            if(Y < height && X < width && X > 0 && Y > 0){
                /* 0<X<width et 0<Y<height */
                AddPoint(X, Y, p1, p2, index1, index2);
            }else if(X < width && X > 0 && Y > 0){
                /* Y>height, donc on met height-1 sur Y */
                AddPoint(X, height - 1, p1, p2, index1, index2);
            }else if(Y < height && X > 0 && Y > 0){
                /* X>width, donc on met width-1 sur X */
                AddPoint(width - 1, Y, p1, p2, index1, index2);
            }else if(Y < height && X < width && X > 0){
                /* Y<0, on met 1 sur Y */
                AddPoint(X, 1, p1, p2, index1, index2);
            }else if(Y < height && X < width && Y > 0){
                /* X<0, on met 1 sur X */
                AddPoint(1, Y, p1, p2, index1, index2);
            }
            if(Critere > 0){
                X += IncX;
                Critere += Const1;
            }else{
                Critere += Const2;
            }
            Y += IncY;
        }
	}

}


