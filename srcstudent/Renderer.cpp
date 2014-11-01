#include <Renderer.h>
#include <Panel3D.h>
#include <Engine.h>

void Renderer::DrawFilaire()
{
    /* numbre de point à dessiner */
    int size_point = renderable.points2D.size;
    for(int i = 0; i < size_point - 1; i++){
        buffer->DrawLine(renderable.points2D.data[i],
                                        renderable.points2D.data[i+1], pointLight.diffuseColor, ambientLight.ambientColor);
    }
    buffer->DrawLine(renderable.points2D.data[0],
                                        renderable.points2D.data[size_point - 1], pointLight.diffuseColor, ambientLight.ambientColor);
}
void Renderer::DrawFilaireCache()
{
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
