#include <Renderer.h>
#include <Panel3D.h>
#include <Engine.h>

void Renderer::DrawFilaire()
{
    /* numbre de faces à dessiner */
    int nbr_face = drawable->faces.size;
    for(int i = 0; i < nbr_face; i++){
        /* dessiner les petits triangles */
        /* dessiner ligne entre index1 et index2 */
        buffer->DrawLine(renderable.points2D.data[drawable->faces.data[i].index1],
                                        renderable.points2D.data[drawable->faces.data[i].index2], pointLight.diffuseColor, ambientLight.ambientColor);
        /* dessiner ligne entre index2 et index3 */
        buffer->DrawLine(renderable.points2D.data[drawable->faces.data[i].index2],
                                        renderable.points2D.data[drawable->faces.data[i].index3], pointLight.diffuseColor, ambientLight.ambientColor);
        /* dessiner ligne entre index1 et index3 */
        buffer->DrawLine(renderable.points2D.data[drawable->faces.data[i].index1],
                                        renderable.points2D.data[drawable->faces.data[i].index3], pointLight.diffuseColor, ambientLight.ambientColor);

    }
}

void Renderer::DrawFilaireCache()
{
    int nbr_face = drawable->faces.size;
    for(int i = 0; i < nbr_face; i++){
        /* dessiner les petits triangles qui est visibles */
        if(effectiveDrawable->faceVisibles.data[i]){
            /* dessiner ligne entre index1 et index2 */
            buffer->DrawLine(renderable.points2D.data[drawable->faces.data[i].index1],
                                            renderable.points2D.data[drawable->faces.data[i].index2], pointLight.diffuseColor, ambientLight.ambientColor);
            /* dessiner ligne entre index2 et index3 */
            buffer->DrawLine(renderable.points2D.data[drawable->faces.data[i].index2],
                                            renderable.points2D.data[drawable->faces.data[i].index3], pointLight.diffuseColor, ambientLight.ambientColor);
            /* dessiner ligne entre index1 et index3 */
            buffer->DrawLine(renderable.points2D.data[drawable->faces.data[i].index1],
                                            renderable.points2D.data[drawable->faces.data[i].index3], pointLight.diffuseColor, ambientLight.ambientColor);
        }
    }

	// compléter ici

}
void Renderer::DrawFacePleine()
{
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
