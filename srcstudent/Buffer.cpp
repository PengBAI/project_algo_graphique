#include <Buffer.h>
#include <FastMath.h>

/* l'algorithme de tracé de ligne de Bresenham */
void Buffer::DrawLine(const Coord2D p1, const Coord2D p2, const Color c1,
		const Color c2)
{
    int X, Y, LongX, LongY, Critere, Const1, Const2, IncX, IncY, cpt;
    Coord2D tmp;
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
            tmp.x = X;
            tmp.y = Y;
            /* Les points intermédiaires correspondent à une interpolation linéaire entre ces deux couleurs.*/
            double poidsA = 1 - p1.Distance(tmp)/p1.Distance(p2);
            double poidsB = 1 - poidsA;
            SetPoint(tmp, c1 * poidsA + c2 * poidsB);
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
            tmp.x = X;
            tmp.y = Y;
            /* Les points intermédiaires correspondent à une interpolation linéaire entre ces deux couleurs.*/
            double poidsA = 1 - p1.Distance(tmp)/p1.Distance(p2);
            double poidsB = 1 - poidsA;
            SetPoint(tmp, c1 * poidsA + c2 * poidsB);
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

void Buffer::DrawFilledTriangle(const Coord2D p1, const Coord2D p2,
		const Coord2D p3, const Color c1, const Color c2, const Color c3)
{
    /* Initialise les structures de données du scanline */
    scanLineComputer.Init();
    /* calculer les limites "scanline" du triangle et pour calculer les poids des trois */
    scanLineComputer.Compute(p1, p2, p3);
    /* draw triangle */
    for(int pGauche = 0; pGauche < scanLineComputer.left.size; pGauche++ ){
        for(int pDroit = 0; pDroit < scanLineComputer.right.size; pDroit++){

            Coord2D pp1, pp2;
            pp1.x = scanLineComputer.leftweight.data[scanLineComputer.left.data[pGauche]].data[0]*p1.x +
                    scanLineComputer.leftweight.data[scanLineComputer.left.data[pGauche]].data[1]*p2.x +
                    scanLineComputer.leftweight.data[scanLineComputer.left.data[pGauche]].data[2]*p3.x;

            pp1.y = scanLineComputer.leftweight.data[scanLineComputer.left.data[pGauche]].data[0]*p1.y +
                    scanLineComputer.leftweight.data[scanLineComputer.left.data[pGauche]].data[1]*p2.y +
                    scanLineComputer.leftweight.data[scanLineComputer.left.data[pGauche]].data[2]*p3.y;

            pp1.x = scanLineComputer.rightweight.data[scanLineComputer.right.data[pDroit]].data[0]*p1.x +
                    scanLineComputer.rightweight.data[scanLineComputer.right.data[pDroit]].data[1]*p2.x +
                    scanLineComputer.rightweight.data[scanLineComputer.right.data[pDroit]].data[2]*p3.x;

            pp2.y = scanLineComputer.rightweight.data[scanLineComputer.right.data[pDroit]].data[0]*p1.y +
                    scanLineComputer.rightweight.data[scanLineComputer.right.data[pDroit]].data[1]*p2.y +
                    scanLineComputer.rightweight.data[scanLineComputer.right.data[pDroit]].data[2]*p3.y;

            DrawLine(pp1, pp2,
                           c1*scanLineComputer.leftweight.data[scanLineComputer.left.data[pGauche]].data[0] +
                           c2*scanLineComputer.leftweight.data[scanLineComputer.left.data[pGauche]].data[1] +
                           c3*scanLineComputer.leftweight.data[scanLineComputer.left.data[pGauche]].data[2],
                           c1*scanLineComputer.rightweight.data[scanLineComputer.right.data[pDroit]].data[0] +
                           c2*scanLineComputer.rightweight.data[scanLineComputer.right.data[pDroit]].data[1] +
                           c3*scanLineComputer.rightweight.data[scanLineComputer.right.data[pDroit]].data[2]);
        }
    }

}

void Buffer::DrawPhongTriangle(const Coord2D p1, const Coord2D p2,
		const Coord2D p3, const Color c1, const Color c2, const Color c3,
		const Coord3D posi1, const Coord3D posi2, const Coord3D posi3,
		const Coord3D normal1, const Coord3D normal2, const Coord3D normal3,
		const AmbientLight & ambientLight, const PointLight & pointLight)
{
	// compléter ici
}

