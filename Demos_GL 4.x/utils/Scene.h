#ifndef SCENE_H
#define SCENE_H

class Scene
{
public:
	Scene() { }

	/**
	Load textures, initialize shaders, etc.
	*/
	virtual void init() = 0;

	/**
	This is called prior to every frame.  Use this
	to update your animation.
	*/
	virtual void update(double t) = 0;

	/**
	Draw your scene.
	*/
	virtual void render() = 0;

	/**
	Called when screen is resized
	*/
	virtual void resize(int, int) = 0;
protected:

};

#endif // SCENE_H
