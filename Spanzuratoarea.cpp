#include<iostream>
#include<vector>
#include<string>
#include<set>


int Spanzuratoarea(std::string stringDat)
{
	unsigned int size = stringDat.size();
	std::string rez(size,'_');
	std::set<char> litere;
	for (auto i : stringDat)
	{
		litere.insert(i);
	}
	int fails = 6;
	int succes = 0;
	while (fails)
	{
		std::cout << rez << std::endl;
		char x;
		std::cout << "Introduce-ti un caracter: ";
		std::cin >> x;
		if (litere.count(x) != true)
		{
			fails--;
			std::cout << "Caracter gresit.Mai aveti " << fails << " incercari" << std::endl;;
		}
		else {
			size_t pos=stringDat.find(x);
			while (pos != std::string::npos)
			{
				rez[pos] = stringDat[pos];
				stringDat[pos] = '`';
				pos = stringDat.find(x);
				succes++;
			}
		}
		if (succes == stringDat.size())
		{
			std::cout << "Felicitari,ati castigat";
			return 0;
		}
	}
	std::cout << "Din pacate ati pierdut";
	return 0;

}




int main()
{
	Spanzuratoarea("ancora");
	return 0;
}