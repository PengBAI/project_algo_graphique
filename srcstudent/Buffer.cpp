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
            /* Les points intermédiaires correspondent à une
            interpolation linéaire entre ces deux couleurs.*/
            double poidsA = 1 - p1.Distance(tmp)/p1.Distance(p2);
            double poidsB = 1 - poidsA;
            /* set point tmp */
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
            /* Les points intermédiaires correspondent à une
            interpolation linéaire entre ces deux couleurs.*/
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
    /* Dessin des contours */
    DrawLine(p1, p2, c1, c2);
    DrawLine(p2, p3, c2, c3);
    DrawLine(p3, p1, c3, c1);
    /* draw triangle y entre ymin et ymax */
    for(int py = scanLineComputer.ymin; py <= scanLineComputer.ymax; py++ ){
            /* définir 2 points de ligne pointL et ponitR à gauche et à droite*/
            Coord2D pointL, ponitR;
            pointL.x = scanLineComputer.left.data[py];
            pointL.y = py;

            ponitR.x = scanLineComputer.right.data[py];
            ponitR.y = py;
            /* définir 2 colors et caluler l'interpolation linéaire entre eux */
            Color colorL, colorR;
            colorL = c1 * scanLineComputer.leftweight.data[py].data[0] +
                    c2 * scanLineComputer.leftweight.data[py].data[1] +
                    c3 * scanLineComputer.leftweight.data[py].data[2];
            colorR = c1 * scanLineComputer.rightweight.data[py].data[0] +
                    c2 * scanLineComputer.rightweight.data[py].data[1] +
                    c3 * scanLineComputer.rightweight.data[py].data[2];
            /* dessiner chaque lignes dans le triangles */
            DrawLine(pointL, ponitR, colorL, colorR);
    }

}

void Buffer::DrawPhongTriangle(const Coord2D p1, const Coord2D p2,
		const Coord2D p3, const Color c1, const Color c2, const Color c3,
		const Coord3D posi1, const Coord3D posi2, const Coord3D posi3,
		const Coord3D normal1, const Coord3D normal2, const Coord3D normal3,
		const AmbientLight & ambientLight, const PointLight & pointLight)
{
    /* Initialise les structures de données du scanline */
    scanLineComputer.Init();
    /* calculer les limites "scanline" du triangle et pour calculer les poids des trois */
    scanLineComputer.Compute(p1, p2, p3);
    /* dessiner les trois points */
    SetPoint(p1, c1);
    SetPoint(p2, c2);
    SetPoint(p3, c3);

    Color colorL, colorR;
    Coord3D current3D, posiL, posiR, normalL, normalR;
    /* pour chaque ligne, on calcule des color, position et normal */
    for( int py = scanLineComputer.ymin; py <= scanLineComputer.ymax; py++ )
    {
        Coord2D pointL(scanLineComputer.left.data[py], py);
        Coord2D pointR(scanLineComputer.right.data[py], py);

        colorL = c1 * scanLineComputer.leftweight.data[py].data[0] +
                        c2 * scanLineComputer.leftweight.data[py].data[1] +
                        c3 * scanLineComputer.leftweight.data[py].data[2];

        colorR = c1 * scanLineComputer.rightweight.data[py].data[0] +
                        c2 * scanLineComputer.rightweight.data[py].data[1] +
                        c3 * scanLineComputer.rightweight.data[py].data[2];

        posiL = posi1 * scanLineComputer.leftweight.data[py].data[0] +
                        posi2 * scanLineComputer.leftweight.data[py].data[1] +
                        posi3 * scanLineComputer.leftweight.data[py].data[2];

        posiR = posi1 * scanLineComputer.rightweight.data[py].data[0] +
                        posi2 * scanLineComputer.rightweight.data[py].data[1] +
                        posi3 * scanLineComputer.rightweight.data[py].data[2];

        normalL = normal1 * scanLineComputer.leftweight.data[py].data[0] +
                        normal2 * scanLineComputer.leftweight.data[py].data[1] +
                        normal3 * scanLineComputer.leftweight.data[py].data[2];

        normalR = normal1 * scanLineComputer.rightweight.data[py].data[0] +
                        normal2 * scanLineComputer.rightweight.data[py].data[1] +
                        normal3 * scanLineComputer.rightweight.data[py].data[2];

        /* dessiner tous les points sur la ligne courante */
		for(int px = scanLineComputer.left.data[py]; px <= scanLineComputer.right.data[py]; px++)
		{
		    Coord2D tmp2D(px, py);
            double poidsA = 1 - pointL.Distance(tmp2D)/pointL.Distance(pointR);
            double poidsB = 1 - poidsA;

		    Coord3D tmp3D = posiL * poidsA + posiR * poidsB;
		    Coord3D tmpNormal = normalL * poidsA + normalR * poidsB;

		    Color colorDiffuse = pointLight.GetColor(tmp3D, tmpNormal);
		    Color colorPoint = colorL * poidsA + colorR * poidsB;

		    SetPoint(tmp2D, (ambientLight.ambientColor + colorDiffuse) * colorPoint);
		}
    }
}

