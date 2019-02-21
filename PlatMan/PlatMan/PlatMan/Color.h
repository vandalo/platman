struct Color {
	int r;
	int g;
	int b;
	int a;
	Color() { r = 0; g = 0; b = 0; a = 0; }
	Color(int red, int green, int blue, int alpha) {
		r = red, g = green, b = blue, a = alpha;
	}
};