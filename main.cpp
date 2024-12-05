#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cmath>

bool parseFile(const std::string& path, std::vector<int>& va, std::vector<int>& vb)
{
	std::ifstream file(path);
	
	if (!file.is_open())
	{
		std::cout << "Failed to open file" << std::endl;
		return false;
	}
	
	std::string line;

	while (std::getline(file, line))
	{
		std::istringstream iss(line);
		int l = 0;
		int r = 0;

		if (iss >> l >> r)
		{
			va.emplace_back(l);
			vb.emplace_back(r);
		}
	}

	file.close();

	return true;
}

int sumDistances(std::vector<int>& va, std::vector<int>& vb)
{
	int total = 0;

	for (size_t i = 0; i < va.size(); i++)
	{
		total += abs(va[i] - vb[i]);
	}

	return total;
}

int sumSimilarities(std::vector<int>& va, std::vector<int>& vb)
{
	int total = 0;
	int aCount = 1;

	size_t bIndex = 0;

	for (size_t aIndex = 0; aIndex < va.size(); aIndex++)
	{
		if (aIndex < va.size() - 1 && va[aIndex] == va[aIndex + 1])
		{
			aCount++;
		}
		else
		{
			int bCount = 0;
		
			for (; bIndex < vb.size(); bIndex++)
			{
				if (vb[bIndex] == va[aIndex])
				{
					bCount++;
				}
				else if (vb[bIndex] > va[aIndex])
				{
					total += va[aIndex] * aCount * bCount;
					break;
				}
			}

			aCount = 1;
		}
	}

	return total;
}

void day_01(const std::string& input)
{
	std::vector<int> lList;
	std::vector<int> rList;

	if (!parseFile(input, lList, rList))
	{
		std::cerr << "Day 1: Failed to parse file." << std::endl;
		return;
	}
	else
	{
		std::cout << "Day 1" << std::endl;
	}

	std::sort(lList.begin(), lList.end());
	std::sort(rList.begin(), rList.end());

	std::cout << "\tDistance: " << sumDistances(lList, rList) << std::endl;
	std::cout << "\tSimilarity: " << sumSimilarities(lList, rList) << std::endl;
}

int main(int argc, char* argv[])
{
	day_01("01/input.txt");

	return 0;
}