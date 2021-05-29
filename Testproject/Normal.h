
#include "Bubble.h"
#include <string>
class Normal :
	public Bubble
{
private:
	std::string color;
public:
	Normal(int x, int y , std::string c);

	std::string getstr();
};
