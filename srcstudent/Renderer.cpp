#include <Renderer.h>
#include <Panel3D.h>
#include <Engine.h>

void Renderer::DrawFilaire()
{
    /* numbre de faces à dessiner */
    int nbr_face = drawable->faces.size;
    for(int i = 0; i < nbr_face; i++){
        if(drawable->colorOnFace){
            /* dessiner les petits triangles avec face color*/
            /* dessiner ligne entre index1 et index2 */
            buffer->DrawLine(renderable.points2D.data[drawable->faces.data[i].index1],
                                            renderable.points2D.data[drawable->faces.data[i].index2],
                                            drawable->faceColors.data[i],
                                            drawable->faceColors.data[i]);
            /* dessiner ligne entre index2 et index3 */
            buffer->DrawLine(renderable.points2D.data[drawable->faces.data[i].index2],
                                            renderable.points2D.data[drawable->faces.data[i].index3],
                                            drawable->faceColors.data[i],
                                            drawable->faceColors.data[i]);
            /* dessiner ligne entre index1 et index3 */
            buffer->DrawLine(renderable.points2D.data[drawable->faces.data[i].index1],
                                            renderable.points2D.data[drawable->faces.data[i].index3],
                                            drawable->faceColors.data[i],
                                            drawable->faceColors.data[i]);
        }else{
            /* dessiner les petits triangles avec point color*/
            /* dessiner ligne entre index1 et index2 */
            buffer->DrawLine(renderable.points2D.data[drawable->faces.data[i].index1],
                                            renderable.points2D.data[drawable->faces.data[i].index2],
                                            drawable->pointColors.data[drawable->faces.data[i].index1],
                                            drawable->pointColors.data[drawable->faces.data[i].index2]);
            /* dessiner ligne entre index2 et index3 */
            buffer->DrawLine(renderable.points2D.data[drawable->faces.data[i].index2],
                                            renderable.points2D.data[drawable->faces.data[i].index3],
                                            drawable->pointColors.data[drawable->faces.data[i].index2],
                                            drawable->pointColors.data[drawable->faces.data[i].index3]);
            /* dessiner ligne entre index1 et index3 */
            buffer->DrawLine(renderable.points2D.data[drawable->faces.data[i].index1],
                                            renderable.points2D.data[drawable->faces.data[i].index3],
                                            drawable->pointColors.data[drawable->faces.data[i].index1],
                                            drawable->pointColors.data[drawable->faces.data[i].index3]);

        }

    }
}

void Renderer::DrawFilaireCache()
{
    int nbr_face = drawable->faces.size;
    for(int i = 0; i < nbr_face; i++){
        /* dessiner les petits triangles qui est visibles */
        if(effectiveDrawable->faceVisibles.data[i]){
            if(drawable->colorOnFace){
                /* dessiner les petits triangles avec face color*/
                /* dessiner ligne entre index1 et index2 */
                buffer->DrawLine(renderable.points2D.data[drawable->faces.data[i].index1],
                                            renderable.points2D.data[drawable->faces.data[i].index2],
                                            drawable->faceColors.data[i],
                                            drawable->faceColors.data[i]);
                /* dessiner ligne entre index2 et index3 */
                buffer->DrawLine(renderable.points2D.data[drawable->faces.data[i].index2],
                                                renderable.points2D.data[drawable->faces.data[i].index3],
                                                drawable->faceColors.data[i],
                                                drawable->faceColors.data[i]);
                /* dessiner ligne entre index1 et index3 */
                buffer->DrawLine(renderable.points2D.data[drawable->faces.data[i].index1],
                                                renderable.points2D.data[drawable->faces.data[i].index3],
                                                drawable->faceColors.data[i],
                                                drawable->faceColors.data[i]);
            }else{
                /* dessiner les petits triangles avec point color*/
                /* dessiner ligne entre index1 et index2 */
                buffer->DrawLine(renderable.points2D.data[drawable->faces.data[i].index1],
                                                renderable.points2D.data[drawable->faces.data[i].index2],
                                                drawable->pointColors.data[drawable->faces.data[i].index1],
                                                drawable->pointColors.data[drawable->faces.data[i].index2]);
                /* dessiner ligne entre index2 et index3 */
                buffer->DrawLine(renderable.points2D.data[drawable->faces.data[i].index2],
                                                renderable.points2D.data[drawable->faces.data[i].index3],
                                                drawable->pointColors.data[drawable->faces.data[i].index2],
                                                drawable->pointColors.data[drawable->faces.data[i].index3]);
                /* dessiner ligne entre index1 et index3 */
                buffer->DrawLine(renderable.points2D.data[drawable->faces.data[i].index1],
                                                renderable.points2D.data[drawable->faces.data[i].index3],
                                                drawable->pointColors.data[drawable->faces.data[i].index1],
                                                drawable->pointColors.data[drawable->faces.data[i].index3]);
            }
        }
    }
}

void Renderer::DrawFacePleine()
{
    int nbr_face = drawable->faces.size;
    for(int i = 0; i < nbr_face; i++){

        /* dessiner les petits triangles qui est visibles */
        if(effectiveDrawable->faceVisibles.data[i]){
            /* dessiner les petits triangles avec face color */
            if(drawable->colorOnFace){

                Color color = drawable->faceColors.data[i];
                buffer->DrawFilledTriangle(renderable.points2D.data[drawable->faces.data[i].index1],
                                        renderable.points2D.data[drawable->faces.data[i].index2],
                                        renderable.points2D.data[drawable->faces.data[i].index3],
                                        color, color, color);
            }else{
                /* dessiner les petits triangles avec point color */
                buffer->DrawFilledTriangle(renderable.points2D.data[drawable->faces.data[i].index1],
                                        renderable.points2D.data[drawable->faces.data[i].index2],
                                        renderable.points2D.data[drawable->faces.data[i].index3],
                                        drawable->pointColors.data[drawable->faces.data[i].index1],
                                        drawable->pointColors.data[drawable->faces.data[i].index2],
                                        drawable->pointColors.data[drawable->faces.data[i].index3]);
            }
        }
    }
}

void Renderer::DrawLambert()
{
    int nbr_face = drawable->faces.size;
    for(int i = 0; i < nbr_face; i++){

        /* dessiner les petits triangles qui est visibles */
        if(effectiveDrawable->faceVisibles.data[i]){
            /* dessiner les petits triangles avec face color */
            if(drawable->colorOnFace){
                Color color1 = pointLight.GetColor(effectiveDrawable->points.data[drawable->faces.data[i].index1],
                                                            effectiveDrawable->faceNormals.data[i])
                                                            * drawable->faceColors.data[i];
                Color color2 = pointLight.GetColor(effectiveDrawable->points.data[drawable->faces.data[i].index2],
                                                            effectiveDrawable->faceNormals.data[i])
                                                            * drawable->faceColors.data[i];
                Color color3 = pointLight.GetColor(effectiveDrawable->points.data[drawable->faces.data[i].index2],
                                                            effectiveDrawable->faceNormals.data[i])
                                                            * drawable->faceColors.data[i];
                buffer->DrawFilledTriangle(renderable.points2D.data[drawable->faces.data[i].index1],
                                        renderable.points2D.data[drawable->faces.data[i].index2],
                                        renderable.points2D.data[drawable->faces.data[i].index3],
                                        color1, color2, color3);
            }else{
                /* dessiner les petits triangles avec point color */
                Color color1 = pointLight.GetColor(effectiveDrawable->points.data[drawable->faces.data[i].index1],
                                                     effectiveDrawable->faceNormals.data[i])
                                                     * drawable->pointColors.data[drawable->faces.data[i].index1];
                Color color2 = pointLight.GetColor(effectiveDrawable->points.data[drawable->faces.data[i].index2],
                                                    effectiveDrawable->faceNormals.data[i])
                                                    * drawable->pointColors.data[drawable->faces.data[i].index2];
                Color color3 = pointLight.GetColor(effectiveDrawable->points.data[drawable->faces.data[i].index3],
                                                    effectiveDrawable->faceNormals.data[i])
                                                    * drawable->pointColors.data[drawable->faces.data[i].index3];
                buffer->DrawFilledTriangle(renderable.points2D.data[drawable->faces.data[i].index1],
                                        renderable.points2D.data[drawable->faces.data[i].index2],
                                        renderable.points2D.data[drawable->faces.data[i].index3],
                                        color1, color2, color3);
            }
        }
    }
}

void Renderer::DrawGouraud()
{
    int nbr_face = drawable->faces.size;
    for(int i = 0; i < nbr_face; i++){

        /* dessiner les petits triangles qui est visibles */
        if(effectiveDrawable->faceVisibles.data[i]){
            /* dessiner les petits triangles avec face color */
            if(drawable->colorOnFace){
                Color color1 = pointLight.GetColor(effectiveDrawable->points.data[drawable->faces.data[i].index1],
                                                    effectiveDrawable->pointNormals.data[drawable->faces.data[i].index1])
                                                    * drawable->faceColors.data[i];
                Color color2 = pointLight.GetColor(effectiveDrawable->points.data[drawable->faces.data[i].index2],
                                                    effectiveDrawable->pointNormals.data[drawable->faces.data[i].index2])
                                                    * drawable->faceColors.data[i];
                Color color3 = pointLight.GetColor(effectiveDrawable->points.data[drawable->faces.data[i].index3],
                                                    effectiveDrawable->pointNormals.data[drawable->faces.data[i].index3])
                                                    * drawable->faceColors.data[i];
                buffer->DrawFilledTriangle(renderable.points2D.data[drawable->faces.data[i].index1],
                                        renderable.points2D.data[drawable->faces.data[i].index2],
                                        renderable.points2D.data[drawable->faces.data[i].index3],
                                        color1, color2, color3);
            }else{
                /* dessiner les petits triangles avec point color */
                Color color1 = pointLight.GetColor(effectiveDrawable->points.data[drawable->faces.data[i].index1],
                                                            effectiveDrawable->pointNormals.data[drawable->faces.data[i].index1])
                                                            * drawable->pointColors.data[drawable->faces.data[i].index1];
                Color color2 = pointLight.GetColor(effectiveDrawable->points.data[drawable->faces.data[i].index2],
                                                            effectiveDrawable->pointNormals.data[drawable->faces.data[i].index2])
                                                            * drawable->pointColors.data[drawable->faces.data[i].index2];
                Color color3 = pointLight.GetColor(effectiveDrawable->points.data[drawable->faces.data[i].index3],
                                                            effectiveDrawable->pointNormals.data[drawable->faces.data[i].index3])
                                                            * drawable->pointColors.data[drawable->faces.data[i].index3];
                buffer->DrawFilledTriangle(renderable.points2D.data[drawable->faces.data[i].index1],
                                        renderable.points2D.data[drawable->faces.data[i].index2],
                                        renderable.points2D.data[drawable->faces.data[i].index3],
                                        color1, color2, color3);
            }
        }
    }
}
void Renderer::DrawPhong()
{
	// compléter ici
}
