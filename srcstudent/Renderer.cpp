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
                buffer->DrawFilledTriangle(renderable.points2D.data[drawable->faces.data[i].index1],
                                        renderable.points2D.data[drawable->faces.data[i].index2],
                                        renderable.points2D.data[drawable->faces.data[i].index3],
                                        drawable->faceColors.data[i],
                                        drawable->faceColors.data[i],
                                        drawable->faceColors.data[i]);
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
	// compléter ici
}

void Renderer::DrawLambert()
{
	// compléter ici
}
void Renderer::DrawGouraud()
{
	// compléter ici
}
void Renderer::DrawPhong()
{
	// compléter ici
}
