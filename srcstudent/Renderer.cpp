#include <Renderer.h>
#include <Panel3D.h>
#include <Engine.h>

void Renderer::DrawFilaire()
{
    /* numbre de faces à dessiner */
    int nbr_face = drawable->faces.size;
    for(int i = 0; i < nbr_face; i++){
        Face nowFace = drawable->faces.data[i];
        if(drawable->colorOnFace){
            /* dessiner les petits triangles avec face color*/
            /* dessiner ligne entre index1 et index2 */
            buffer->DrawLine(renderable.points2D.data[nowFace.index1],
                                            renderable.points2D.data[nowFace.index2],
                                            drawable->faceColors.data[i],
                                            drawable->faceColors.data[i]);
            /* dessiner ligne entre index2 et index3 */
            buffer->DrawLine(renderable.points2D.data[nowFace.index2],
                                            renderable.points2D.data[nowFace.index3],
                                            drawable->faceColors.data[i],
                                            drawable->faceColors.data[i]);
            /* dessiner ligne entre index1 et index3 */
            buffer->DrawLine(renderable.points2D.data[nowFace.index1],
                                            renderable.points2D.data[nowFace.index3],
                                            drawable->faceColors.data[i],
                                            drawable->faceColors.data[i]);
        }else{
            /* dessiner les petits triangles avec point color*/
            /* dessiner ligne entre index1 et index2 */
            buffer->DrawLine(renderable.points2D.data[nowFace.index1],
                                            renderable.points2D.data[nowFace.index2],
                                            drawable->pointColors.data[nowFace.index1],
                                            drawable->pointColors.data[nowFace.index2]);
            /* dessiner ligne entre index2 et index3 */
            buffer->DrawLine(renderable.points2D.data[nowFace.index2],
                                            renderable.points2D.data[nowFace.index3],
                                            drawable->pointColors.data[nowFace.index2],
                                            drawable->pointColors.data[nowFace.index3]);
            /* dessiner ligne entre index1 et index3 */
            buffer->DrawLine(renderable.points2D.data[nowFace.index1],
                                            renderable.points2D.data[nowFace.index3],
                                            drawable->pointColors.data[nowFace.index1],
                                            drawable->pointColors.data[nowFace.index3]);

        }

    }
}

void Renderer::DrawFilaireCache()
{
    int nbr_face = drawable->faces.size;
    for(int i = 0; i < nbr_face; i++){
        Face nowFace = drawable->faces.data[i];
        /* dessiner les petits triangles qui est visibles */
        if(effectiveDrawable->faceVisibles.data[i]){
            if(drawable->colorOnFace){
                /* dessiner les petits triangles avec face color*/
                /* dessiner ligne entre index1 et index2 */
                buffer->DrawLine(renderable.points2D.data[nowFace.index1],
                                            renderable.points2D.data[nowFace.index2],
                                            drawable->faceColors.data[i],
                                            drawable->faceColors.data[i]);
                /* dessiner ligne entre index2 et index3 */
                buffer->DrawLine(renderable.points2D.data[nowFace.index2],
                                            renderable.points2D.data[nowFace.index3],
                                            drawable->faceColors.data[i],
                                            drawable->faceColors.data[i]);
                /* dessiner ligne entre index1 et index3 */
                buffer->DrawLine(renderable.points2D.data[nowFace.index1],
                                            renderable.points2D.data[nowFace.index3],
                                            drawable->faceColors.data[i],
                                            drawable->faceColors.data[i]);
            }else{
                /* dessiner les petits triangles avec point color*/
                /* dessiner ligne entre index1 et index2 */
                buffer->DrawLine(renderable.points2D.data[nowFace.index1],
                                            renderable.points2D.data[nowFace.index2],
                                            drawable->pointColors.data[nowFace.index1],
                                            drawable->pointColors.data[nowFace.index2]);
                /* dessiner ligne entre index2 et index3 */
                buffer->DrawLine(renderable.points2D.data[nowFace.index2],
                                            renderable.points2D.data[nowFace.index3],
                                            drawable->pointColors.data[nowFace.index2],
                                            drawable->pointColors.data[nowFace.index3]);
                /* dessiner ligne entre index1 et index3 */
                buffer->DrawLine(renderable.points2D.data[nowFace.index1],
                                            renderable.points2D.data[nowFace.index3],
                                            drawable->pointColors.data[nowFace.index1],
                                            drawable->pointColors.data[nowFace.index3]);
            }
        }
    }
}

void Renderer::DrawFacePleine()
{
    int nbr_face = effectiveDrawable->sortedVisibleFaces.size;
    for(int i = 0; i < nbr_face; i++){
        /* index de face */
        int index = effectiveDrawable->sortedVisibleFaces.data[i].index;
        Face nowFace = drawable->faces.data[index];
        /* dessiner les petits triangles avec face color */
        if(drawable->colorOnFace){

            Color color = drawable->faceColors.data[index];
            buffer->DrawFilledTriangle(renderable.points2D.data[nowFace.index1],
                                    renderable.points2D.data[nowFace.index2],
                                    renderable.points2D.data[nowFace.index3],
                                    color, color, color);
        }else{
            /* dessiner les petits triangles avec point color */
            buffer->DrawFilledTriangle(renderable.points2D.data[nowFace.index1],
                                    renderable.points2D.data[nowFace.index2],
                                    renderable.points2D.data[nowFace.index3],
                                    drawable->pointColors.data[nowFace.index1],
                                    drawable->pointColors.data[nowFace.index2],
                                    drawable->pointColors.data[nowFace.index3]);
        }
    }
}

/* Idem DrawFacePleine sauf que l'on considère maintenant le modèle d'illumination simple */
void Renderer::DrawLambert()
{
    int nbr_face = effectiveDrawable->sortedVisibleFaces.size;
    for(int i = 0; i < nbr_face; i++){
        /* index de face */
        int index = effectiveDrawable->sortedVisibleFaces.data[i].index;
        Face nowFace = drawable->faces.data[index];
        /* dessiner les petits triangles avec face color */
        if(drawable->colorOnFace){
            Color color1 = pointLight.GetColor(effectiveDrawable->points.data[nowFace.index1],
                                                effectiveDrawable->faceNormals.data[index])
                                                * drawable->faceColors.data[index];
            Color color2 = pointLight.GetColor(effectiveDrawable->points.data[nowFace.index2],
                                                effectiveDrawable->faceNormals.data[index])
                                                * drawable->faceColors.data[index];
            Color color3 = pointLight.GetColor(effectiveDrawable->points.data[nowFace.index2],
                                                effectiveDrawable->faceNormals.data[index])
                                                * drawable->faceColors.data[index];
            buffer->DrawFilledTriangle(renderable.points2D.data[nowFace.index1],
                                    renderable.points2D.data[nowFace.index2],
                                    renderable.points2D.data[nowFace.index3],
                                    color1, color2, color3);
        }else{
            /* dessiner les petits triangles avec point color */
            Color color1 = pointLight.GetColor(effectiveDrawable->points.data[nowFace.index1],
                                                effectiveDrawable->faceNormals.data[index])
                                                * drawable->pointColors.data[nowFace.index1];
            Color color2 = pointLight.GetColor(effectiveDrawable->points.data[nowFace.index2],
                                                effectiveDrawable->faceNormals.data[index])
                                                * drawable->pointColors.data[nowFace.index2];
            Color color3 = pointLight.GetColor(effectiveDrawable->points.data[nowFace.index3],
                                                effectiveDrawable->faceNormals.data[index])
                                                * drawable->pointColors.data[nowFace.index3];
            buffer->DrawFilledTriangle(renderable.points2D.data[nowFace.index1],
                                    renderable.points2D.data[nowFace.index2],
                                    renderable.points2D.data[nowFace.index3],
                                    color1, color2, color3);
        }
    }
}

void Renderer::DrawGouraud()
{
    int nbr_face = effectiveDrawable->sortedVisibleFaces.size;
    for(int i = 0; i < nbr_face; i++){
        /* index de face */
        int index = effectiveDrawable->sortedVisibleFaces.data[i].index;
        Face nowFace = drawable->faces.data[index];
        /* dessiner les petits triangles avec face color */
        if(drawable->colorOnFace){
            Color color1 = pointLight.GetColor(effectiveDrawable->points.data[nowFace.index1],
                                                effectiveDrawable->pointNormals.data[nowFace.index1])
                                                * drawable->faceColors.data[index];
            Color color2 = pointLight.GetColor(effectiveDrawable->points.data[nowFace.index2],
                                                effectiveDrawable->pointNormals.data[nowFace.index2])
                                                * drawable->faceColors.data[index];
            Color color3 = pointLight.GetColor(effectiveDrawable->points.data[nowFace.index3],
                                                effectiveDrawable->pointNormals.data[nowFace.index3])
                                                * drawable->faceColors.data[index];
            buffer->DrawFilledTriangle(renderable.points2D.data[nowFace.index1],
                                    renderable.points2D.data[nowFace.index2],
                                    renderable.points2D.data[nowFace.index3],
                                    color1, color2, color3);
        }else{
            /* dessiner les petits triangles avec point color */
            Color color1 = pointLight.GetColor(effectiveDrawable->points.data[nowFace.index1],
                                                effectiveDrawable->pointNormals.data[nowFace.index1])
                                                * drawable->pointColors.data[nowFace.index1];
            Color color2 = pointLight.GetColor(effectiveDrawable->points.data[nowFace.index2],
                                                effectiveDrawable->pointNormals.data[nowFace.index2])
                                                * drawable->pointColors.data[nowFace.index2];
            Color color3 = pointLight.GetColor(effectiveDrawable->points.data[nowFace.index3],
                                                effectiveDrawable->pointNormals.data[nowFace.index3])
                                                * drawable->pointColors.data[nowFace.index3];
            buffer->DrawFilledTriangle(renderable.points2D.data[nowFace.index1],
                                    renderable.points2D.data[nowFace.index2],
                                    renderable.points2D.data[nowFace.index3],
                                    color1, color2, color3);
        }
    }
}

void Renderer::DrawPhong()
{
    int nbr_face = effectiveDrawable->sortedVisibleFaces.size;
    for( int i = 0; i < nbr_face; i++ )
    {
        int index = effectiveDrawable->sortedVisibleFaces.data[i].index;
        Face nowFace = drawable->faces.data[index];

        /* les points à dessiner */
        Coord3D posi1 = effectiveDrawable->points.data[nowFace.index1];
        Coord3D posi2 = effectiveDrawable->points.data[nowFace.index2];
        Coord3D posi3 = effectiveDrawable->points.data[nowFace.index3];

        if( drawable->colorOnFace )
        {
            /* coleur de face */
            Color color = drawable->faceColors.data[index];
            buffer->DrawPhongTriangle(
                                    renderable.points2D.data[nowFace.index1],
                                    renderable.points2D.data[nowFace.index2],
                                    renderable.points2D.data[nowFace.index3],
                                    color, color, color,
                                    posi1, posi2, posi3,
                                    effectiveDrawable->pointNormals.data[nowFace.index1],
                                    effectiveDrawable->pointNormals.data[nowFace.index2],
                                    effectiveDrawable->pointNormals.data[nowFace.index3],
                                    ambientLight, pointLight);
        }
        else
        {
            buffer->DrawPhongTriangle(
                                    renderable.points2D.data[nowFace.index1],
                                    renderable.points2D.data[nowFace.index2],
                                    renderable.points2D.data[nowFace.index3],
                                    drawable->pointColors.data[nowFace.index1],
                                    drawable->pointColors.data[nowFace.index2],
                                    drawable->pointColors.data[nowFace.index3],
                                    posi1, posi2, posi3,
                                    effectiveDrawable->pointNormals.data[nowFace.index1],
                                    effectiveDrawable->pointNormals.data[nowFace.index2],
                                    effectiveDrawable->pointNormals.data[nowFace.index3],
                                    ambientLight, pointLight);
        }
    }
}
