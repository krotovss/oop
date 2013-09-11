#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

class Range
{
private:
	int left;
	int right;

public:
	Range(int from = 0, int to = 0)
	{
		left = from;
		right = to;
	}

	bool isIntersect(const Range& r) const
	{
		return !(left > r.right || right < r.left);
	}

	bool isValid() const
	{
		return !(left == 0 && right == 0);
	}

	bool operator<(const Range& r)
	{
		return left < r.left;
	}

	Range getIntersection(const Range& r) const
	{
		if (!isIntersect(r))
			return Range(0, 0);
		
		return Range(std::max(left, r.left), std::min(right, r.right));
	}

	Range getUnion(const Range& r) const
	{
		if (!isIntersect(r)) 
			return Range(0, 0);

		return Range(std::min(left, r.left), std::max(right, r.right));
	}

	int getLength() const
	{
		return right - left;
	}

	int printValues() const
	{
		cout << left << " " << right << endl;

		return 0;
	}
};

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int n;
	cin >> n;
	vector<Range> v;
	v.resize(n);

	for (int i = 0; i < n; ++i)
	{
		int x;
		int y;
		cin >> x >> y;

		v[i] = Range(x, y);
	}

	std::sort(v.begin(), v.end());

	Range current = v[0];
	int max = current.getLength();
	for (int i = 1; i < n; ++i)
	{
		if (current.isIntersect(v[i]))
			current = current.getUnion(v[i]);
		else
			current = v[i];

		if (current.getLength() > max)
			max = current.getLength();
	}

	cout << max << endl;

	return 0;
}