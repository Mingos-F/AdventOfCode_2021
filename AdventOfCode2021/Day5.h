#pragma once

class Day5 {
public:
	void Solve();
private:
	struct Point
	{
		int x, y;

		bool operator==(const Point& Other) const
		{
			return x == Other.x && y == Other.y;
		}

		friend std::istream& operator>>(std::istream& s, Point& p)
		{
			if (!s)
				return s;

			if (!(s >> p.x))
				return s;

			char delim = 0;
			s >> delim;
			if (delim != ',')
			{
				s.setstate(std::ios_base::badbit);
				return s;
			}

			s >> p.y;

			return s;
		}
	};

	struct PointHasher
	{
		size_t operator()(const Point& Input) const
		{
			return std::hash<int>{}(Input.x) ^ (std::hash<int>{}(Input.y) + 0xbeef);
		}
	};

	struct Line
	{
		Point start, end;

		bool is_horizontal() const { return start.x == end.x; }
		bool is_vertical() const { return start.y == end.y; }

		friend std::istream& operator>>(std::istream& s, Line& line)
		{
			if (!s)
				return s;

			if (!(s >> line.start))
				return s;

			char delim1 = 0, delim2 = 0;
			s >> delim1 >> delim2;
			if (delim1 != '-' || delim2 != '>')
			{
				s.setstate(std::ios_base::badbit);
				return s;
			}

			s >> line.end;

			if (line.start.y > line.end.y)
			{
				std::swap(line.start.x, line.end.x);
				std::swap(line.start.y, line.end.y);
			}
			if (line.start.x > line.end.x)
			{
				std::swap(line.start.x, line.end.x);
				std::swap(line.start.y, line.end.y);
			}

			return s;
		}

		friend std::ostream& operator<<(std::ostream& o, Line& line) {
			o << line.start.x << "," << line.start.y << " -> " << line.end.x << "," << line.end.y << std::endl;
			return o;
		}
	};

	void FindPoints(bool flag);
};