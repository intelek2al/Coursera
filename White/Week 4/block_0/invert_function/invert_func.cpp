#include <iostream>
#include <vector>

using namespace std;

// struct Image {
//   double quality;
//   double freshness;
//   double rating;
// };

// struct Params {
//   double a;
//   double b;
//   double c;
// };

class FunctionPart {
	public:
		FunctionPart(char c, double params) {
			oper = c;
			val = params;
		}
		double Apply(double params) const {
			return (oper == '+') ? params + val : params - val;
		}
		void Invert() {
			oper = (oper == '+') ? '-' : '+';
		}
	private:
		double val;
		char oper;
};

class Function {
	public:
		void AddPart(char c, double params) {
			part.push_back({c, params});
		}
		double Apply(double params) const {
			for (const FunctionPart& p : part) {
				params = p.Apply(params);
			}
			return params;
		}
		void Invert() {
			for (FunctionPart& p : part) {
				p.Invert();
			}
			reverse(begin(part), end(part));
		}
	private:
		vector<FunctionPart> part;
};

// Function MakeWeightFunction(const Params& params,
//                             const Image& image) {
//   Function function;
//   function.AddPart('-', image.freshness * params.a + params.b);
//   function.AddPart('+', image.rating * params.c);
//   return function;
// }

// double ComputeImageWeight(const Params& params, const Image& image) {
//   Function function = MakeWeightFunction(params, image);
//   return function.Apply(image.quality);
// }

// double ComputeQualityByWeight(const Params& params,
//                               const Image& image,
//                               double weight) {
//   Function function = MakeWeightFunction(params, image);
//   function.Invert();
//   return function.Apply(weight);
// }

// int main() {
//   Image image = {10, 2, 6};
//   Params params = {4, 2, 6};
//   cout << ComputeImageWeight(params, image) << endl;
//   cout << ComputeQualityByWeight(params, image, 46) << endl;
//   return 0;
// }
