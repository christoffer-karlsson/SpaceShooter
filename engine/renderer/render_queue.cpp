#include "render_queue.h"

std::vector<std::unique_ptr<renderable_object>> render_queue::RenderQueue;

render_queue::render_queue() { }

void render_queue::PushToQueue(renderable_object *Object)
{
	RenderQueue.emplace_back(Object);
}

void render_queue::ExecuteQueue()
{
	// NOTE: Sort the render queue by z-coordinates. Go through the queue, 
	// and draw all objects to screen. Clear the queue after.
	std::sort(RenderQueue.begin(), RenderQueue.end(), z_sort());
	std::for_each(RenderQueue.begin(), RenderQueue.end(), call_renderer());
	RenderQueue.clear();
}

void call_renderer::operator()(std::unique_ptr<renderable_object>& Object)
{
	Render.DrawBitmap(Object.get());
}