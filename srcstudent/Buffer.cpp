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
            double poidsA = 1.0 - p1.Distance(tmp)/p1.Distance(p2);
            double poidsB = 1.0 - poidsA;
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
            double poidsA = 1.0 - p1.Distance(tmp)/p1.Distance(p2);
            double poidsB = 1.0 - poidsA;
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
            Coord2D pointL, pointR;
            pointL.x = scanLineComputer.left.data[py];
            pointL.y = py;

            pointR.x = scanLineComputer.right.data[py];
            pointR.y = py;

            /* définir 2 colors et caluler l'interpolation linéaire entre eux */
            Color colorL, colorR;
            colorL = c1 * scanLineComputer.leftweight.data[py].data[0] +
                    c2 * scanLineComputer.leftweight.data[py].data[1] +
                    c3 * scanLineComputer.leftweight.data[py].data[2];
            colorR = c1 * scanLineComputer.rightweight.data[py].data[0] +
                    c2 * scanLineComputer.rightweight.data[py].data[1] +
                    c3 * scanLineComputer.rightweight.data[py].data[2];
            /* dessiner chaque lignes dans le triangles */
            DrawLine(pointL, pointR, colorL, colorR);
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

    Color colorL, colorR;
    Coord3D posiL, posiR, normalL, normalR;
    Color colorLight, colorPoint;
    Coord2D tmp2D; // point cruuent à dessiner
    /* pour chaque ligne, on calcule des color, position et normal */
    for( int py = scanLineComputer.ymin; py <= scanLineComputer.ymax; py++ )
    {
        /* les point a gauche et à droit sur la ligne à scanner */
        Coord2D pointL(scanLineComputer.left.data[py], py);
        Coord2D pointR(scanLineComputer.right.data[py], py);
        /* calculer les variables avec les poids */
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

        /* dessiner le sommet du triqngle */
        if( scanLineComputer.left.data[py] == scanLineComputer.right.data[py])
		{
		    /* la ligne a un seule point, on utilise la ponit à gauche */
		    tmp2D.x = scanLineComputer.left.data[py];
			tmp2D.y = py;
			colorLight = pointLight.GetColor(posiL, normalL);
			SetPoint(tmp2D, (ambientLight.ambientColor + colorLight) * colorL);
		}else{
            /* dessiner tous les points sur la ligne courante */
            for(int px = scanLineComputer.left.data[py]; px <= scanLineComputer.right.data[py]; px++)
            {
                /* calculer les poids du point en ligne */
                tmp2D.x = px;
                tmp2D.y = py;

                double poidsA = 1.0 - pointL.Distance(tmp2D)/pointL.Distance(pointR);
                double poidsB = 1.0 - poidsA;
                /* calculer la couleur avec les poids*/
                Coord3D tmp3D = posiL * poidsA + posiR * poidsB;
                Coord3D tmpNormal = normalL * poidsA + normalR * poidsB;

                colorLight = pointLight.GetColor(tmp3D, tmpNormal);
                colorPoint = colorL * poidsA + colorR * poidsB;
                /* dessiner tous les points */
                SetPoint(tmp2D, (ambientLight.ambientColor + colorLight) * colorPoint);
            }
		}
    }
}

