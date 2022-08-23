#pragma once

class Day13 {
public:

	struct point {
		int x, y;

		point(int _x, int _y) {
			x = _x;
			y = _y;
		}

		friend bool operator==(const point& a, const point& b) {
			if (a.x == b.x && a.y == b.y) {
				return true;
			}
			else {
				return false;
			}
		}
	};

	struct pointHasher
	{
		size_t operator()(const point& Input) const
		{
			return std::hash<int>{}(Input.x) ^ (std::hash<int>{}(Input.y) + 0xbeef);
		}
	};

	struct fold {
		std::string type;
		int location;

		fold(std::string t, int l) {
			type = t;
			location = l;
		}
	};

	void Solve();
private:

	void CalculatePoints();
};