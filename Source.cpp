#include<iostream>
#include<cmath>
#include<vector>

//tells you how many bit spaces this number will take, for pushing into vector
int testnumberbits(int number)
{
	int bitnumber;
	int b = 0;

	//make sure number is not zero 
	if (number != 0)
	{
		for (int a = 0; a < number; a++)
		{
			//keeping running until pow(2,a) is just less than given number
			if (pow(2, a) < number || pow(2, a) == number)
			{
				b++;
				bitnumber = b;
			}
		}
	}
	//if zero allocate 1 bit space
	else if (number == 0)
	{
		bitnumber = 1;
	}

	return bitnumber;
}

//printing out vector
void print_as_bits(int number, std::vector<bool> bit)
{
	for (int i = 0; i < number; i++) //number = 4
	{
		if (!bit[i])
		{
			std::cout << "0";
		}
		else if (bit[i])
		{
			std::cout << "1";
		}
	}
}

//converting into bits 
void bitconversion(int number, std::vector<bool> bit)
{
	int a = testnumberbits(number); //4 
	int x = number;  //12 

	while (x > 0) //while x is greater than 0; while 4 > 0 YES
	{
		if (pow(2, (a - 1)) <= x) //if 2^3 aka 8 < 12 YES; if 2^2 aka 4 <=4 YES 
		{
			bit.push_back(true); //v[0] = true aka 1; v[1] = true aka 1
			x -= pow(2, (a - 1)); //12-8 = 4; 4-4 = 0; 
			a--; //a = 3; a = 2 
		}
		else
		{
			bit.push_back(false); 
			a--; 
		}
	}

	if (a > 0) //a = 2 
	{
		for (int i = 0; i < a; i++)
		{
			bit.push_back(false); //when i = 0 v[2] = false aka 0; when i = 1 v[3] = false aka 0 then END 
		}
	}

	print_as_bits(testnumberbits(number), bit);
}

int main()
{
	int number;
	std::vector <bool> bit; 

	std::cout << "Input a number: ";
	std::cin >> number;
	std::cout << std::endl;
	std::cout << "It has: "; 
	std::cout << testnumberbits(number);
	std::cout << " numbers of bits";
	std::cout << std::endl;
	std::cout << "It looks like this in binary form: "; 
	bitconversion(number, bit); 
	std::cout << std::endl; 
	std::cout << std::endl;
	std::cout << std::endl;

	return 0;
}