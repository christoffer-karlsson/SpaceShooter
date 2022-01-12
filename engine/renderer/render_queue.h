#pragma once

#include "render_mkrenderable.h"
#include "render_base.h"
#include <vector>
#include <memory>

/**
*	All objects that should be rendered in the current frame, are pushed to the render queue. The object must first be
*	converted via the render_mkrenderable class.
*/
class render_queue
{
	private:
	static std::vector<std::unique_ptr<renderable_object>> RenderQueue;		//<! Queue with renderable objects, that will be rendered to buffer.

	public:
	void PushToQueue(renderable_object *Object);							//<! Push renderable object to the queue.
	void ExecuteQueue();													//<! Iterate the queue. The queue will first be sorted by the Z positions and then the renderer will be called for all objects. Queue will then be cleared.

	public:
	render_queue();
};

/**
*	Predicate to call the renderer for all the renderable objects in the queue.
*/
class call_renderer
{
	private:
	render_base Render;

	public:
	void operator()(std::unique_ptr<renderable_object> &Object);
};