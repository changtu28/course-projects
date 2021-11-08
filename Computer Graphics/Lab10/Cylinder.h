#ifndef CYLINDER_H
#define CYLINDER_H

class Cylinder
{
private:
    unsigned int vaoID;
	static const float TWOPI;
	int nelms;  //Total number of elements

public:
    Cylinder(float radius, float height, int nslices, int nstacks);
    void render() const;
};

#endif //TORUS_H
