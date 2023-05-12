#include<iostream>

class Quad {
public:
	Quad(const int x, const int y, const int high, const int lenght);
	~Quad() {};
	Quad(const Quad& other);
	Quad& operator=(const Quad& other);

	void scale(const int alpha); //if (alpha == 1) {invalid_argument}
	//void union(Quad first, Quad second);
	//void intersect();

private:
	int x_ = 0;
	int y_ = 0;
	int high_;
	int len_;
	int xc_;
	int yc_;
};

int main() {
	Quad q(0, 0, 2, 3);
}

Quad::Quad(const int x, const int y, const int high, const int len) {
	//                                       | //x, y   //x1, y1 -> x
	//                                     y v //x2,y2  //x3, y3
	x_ = x;
	y_ = y;
	high_ = high;
	len_ = len;
	xc_ = (x + len_) / 2;
	yc_ = (y + high_) / 2;
	int x1 = x_ + len_;
	int y1 = y_;
	int x2 = x_;
	int y2 = y_ + high_;
	int x3 = x_ + len_;
	int y3 = y_ + high_;
}

/*void Quad::scale(const int alpha) {
	int x1 = x_ + len_;
	int y1 = y_;
	int x2 = x_;
	int y2 = y_ + high_;
	int x3 = x_ + len_;
	int y3 = y_ + high_;
}*/


//пересечение intersect
//объединение union - это прямоугольник, который объединяет
//масштабирование scale