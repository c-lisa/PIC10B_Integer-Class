/** @file hw1.cpp
    @author [Lisa Chiang]
    @date [1/17/2017]

[This program uses a class called Integer and other functions to convert integers inputted
by the user into binary bits. This conversion allows the user to input large numbers that 
can be manipulated without the constrainst of size. In addition to switching between integers
and bits, the program also allows the user to do basic arithmetic manipulations such as addition
and multiplication to the integers via bits.]

*/
#include <iostream>
#include <vector> 

/**@class Integer
   @brief Class to convert and manipulate unsigned integers and vectors of bits.

   This class allows the user to maniuplate unsigned integers and vectors that contain 
   bits stored as boolean variables. There are functions that allow the user to convert 
   from one to another and also manipulate both types of variables using arithmetic 
   functions. 
*/
class Integer {
public:
	//Constructors
	Integer();
	Integer(unsigned int a);

	//Mutators
	void print_as_bits(); //uses testnumberbits and inttoboolbit 
		int testnumberbits(unsigned int number); //takes number and gives number of bits
		void inttoboolbit(unsigned int number, std::vector<bool> &bits); //uses testnumberbits to convert numbers into boolean bits
	void plus_equals(const Integer& rhs); //adds current value to rhs (a = a + b)
	void times_equals(const Integer& rhs); //multiplies current value to rhs (b * 2)
	unsigned int backtoint(std::vector<int> &binaryint); //converts vectors with binary bits into unsigned integer 

	//Accessors
	unsigned int getx() const; //accesses x for Integers
	void print_as_int() const; //prints the result as an integer

private:
	std::vector<bool> bit; 
	unsigned int x; 
};

//Function declarations
Integer plus(Integer lhs, const Integer& rhs); //adds any two Intgers
Integer multiply(Integer lhs, const Integer& rhs); //multiplies any two Integers

int main() {
	unsigned int uint_value;

	std::cout << "Please input an integer a: ";
	std::cin >> uint_value;
	Integer a = uint_value; //Create Integer type with input value

	std::cout << "The base-2 representation of a is: ";
	a.print_as_bits();
	std::cout << std::endl;

	std::cout << "Please input an integer b: ";
	std::cin >> uint_value;
	Integer b = uint_value; //Create Integer type with input value 

	std::cout << "The base-2 representation of b is: ";
	b.print_as_bits();
	std::cout << std::endl;

	Integer c = plus(a, b); //a+b
	Integer d = multiply(a, b); //a*b
	
	std::cout << "a + b = "; c.print_as_int(); std::cout << " = ";
	c.print_as_bits(); std::cout << std::endl;
	std::cout << "a * b = "; d.print_as_int(); std::cout << " = ";
	d.print_as_bits(); std::cout << std::endl;

	a.plus_equals(b);
	std::cout << "After a += b, a = "; a.print_as_int(); std::cout << std::endl; 
		
	Integer two = 2;
	b.times_equals(two);
	std::cout << "After b *= 2, b= "; b.print_as_int(); std::cout << std::endl;

	return 0;
}

//Integers::Constructors
/**@brief Default Constructor

   Creates a 0 vector by setting private variable x to 0. 

   @param No parameters.
   @return Does not return anything. 
*/
Integer::Integer()
{
	x = 0;
}
/**@brief Constructor

Sets private variable x to a.

@param a is the value that x is set to. 
@return Does not return anything.
*/
Integer::Integer(unsigned int a)
{
	x = a;
}

//Integers::Mutators
/**@brief Prints result as binary bits.

Uses functions testnumberbits and intotoboolbit to convert
integers into binary bits (0 or 1) and outputs them in the 
following format: (#,#,#,...#)_2. 

@param No parameters.
@return Does not return anything.
*/
void Integer::print_as_bits()
{
	//Formatting
	std::cout << "(";
	//Tests for number of bits that will be used
	int size = testnumberbits(x);
	//Converts the private variable x into a vector of boolean variables
	inttoboolbit(x, bit);
	//Converts boolean variables to binary numbers
	for (int i = 0; i < size; i++)
	{
		//If false, output 0
		if (!bit[i])
		{
			std::cout << "0";
		}
		//If true, output 1
		else if (bit[i])
		{
			std::cout << "1";
		}
	}
	//Formatting
	std::cout << ")_2";
}
/**@brief Testing Number of Bits

Performs basic arithmetic using powers of 2 in order to calculate how many
bits a given number will require. This is used to create an ending condition
for for loops in other functions as well as initializing and resizing vectors.

@param number is the integer that will be used to calculate the number of bits needed.
@return Returns an integer that is the number of bits.
*/
int Integer::testnumberbits(unsigned int number)
{
	//Counter for number of bits that will be returned
	int bitnumber = 0;

	//Making sure the given number is not 0 
	if (number != 0)
	{
		//Keep running for loop until pow(2,a) is just less than given number
		for (int a = 0; a < number; a++)
		{
			if (pow(2, a) < number || pow(2, a) == number)
			{
				bitnumber++;
			}
		}
	}
	//If the number is equal to 0, allocate one more bit space
	else if (number == 0)
	{
		bitnumber = 1;
	}

	return bitnumber;
}
/**@brief Converting integers into boolean values in vector.

Uses testnumberbits function to convert integers into boolean values. These
boolean values are pushed into the vector linked to the private variable.

@param number is the number that will be converted into boolean values.
@param bits is the vector that contains the boolean values.
@return Does not return anything.
*/
void Integer::inttoboolbit(unsigned int number, std::vector<bool> &bits)
{
	//Resizes variable in case values already exist in vector, thus skewing summation and multiplication. 
	bit.resize(0);

	//Creating dummy variables to prevent private variables from being changed. 
	int a = testnumberbits(number); //size
	int b = number; //number given

					//Enter loop if the number (b) given is greater than 0. 
	while (b > 0)
	{
		//If the pow(2,numberbits) is less than or equal to the given number, continue here. 
		if (pow(2, (a - 1)) <= b)
		{
			//Push back true. 
			bits.push_back(true);
			//Subtract power of 0 from given number (b). 
			b -= pow(2, (a - 1));
			//Decrease number of bits left to give values to. 
			a--;
		}
		//If pow(2,numberbits) is not less than or equal to given number, continue here.
		else
		{
			//Push back false. 
			bits.push_back(false);
			//Decrease number of bits left to give values to. 
			a--;
		}
	}
	//If the number of bits left is still greater than 0
	if (a > 0)
	{
		//For every bit left, push back false. 
		for (int i = 0; i < a; i++)
		{
			bits.push_back(false);
		}
	}
}

/**@brief Plus_Equals Void Function

Uses getx() function to access values of implicit variable (lhs) and given 
variable (rhs). The implicit variable is added to the given variable (rhs) to 
redefine the value of the implicit variable. lhs = lhs + rhs

@param rhs is the variable being added to the implicit variable. 
@return Does not return anything.
*/
void Integer::plus_equals(const Integer& rhs)
{
	/* The getx() function 	is used to access the private variables. Then 
	the plus function converts these unsigned integers to vectors of bools and 
	then vectors of binary integers. After these binary integers are added, the sum 
	is returned. This is what x is equal to. */
	x = (plus(getx(), rhs.getx())).getx();
	//The integer sum is converted into boolean bits in the bit vector
	inttoboolbit(x, bit);
}
/**@brief Times_Equals Void Function

Uses getx() function to access values of implicit variable (lhs) and given
variable (rhs). The implicit variable is multiplied to the given variable (rhs) to
redefine the value of the implicit variable. lhs = lhs * rhs

@param rhs is the variable being multiplied to the implicit variable.
@return Does not return anything.
*/
void Integer::times_equals(const Integer& rhs)
{
	/* The getx() function 	is used to access the private variables. Then
	the multiply function converts these unsigned integers to vectors of bools and
	then vectors of binary integers. After these binary integers are multiplied, the sum
	is returned. This is what x is equal to. */
	x = (multiply(getx(), rhs.getx())).getx();
	//The integer sum is converted into boolean bits in the bit vector
	inttoboolbit(x, bit);
}

/**@brief Converts binary integers to unsigned integers

Performs calculations on a vector of binary integers (0 or 1) and converts sum of 
calcutions into an unsigned integer. 

@param binaryint is a vector of binary integers that will be converted into an unsigned integer.
@return Returns an unsigned integer that is equal to value of the binary integers.
*/
unsigned int backtoint(std::vector<int> &binaryint)
{
	//Creates dummy variable for size of integer - 1
	int a = binaryint.size() - 1; 
	//Initializes sum to 0
	int sum = 0;
	//Runs for loop from vector[size] to vector[0]
	for (int i = a; i >= 0; i--) 
	{
		if (binaryint[i] == 1)
		{
			//sum = sum + pow(2,(size-currentiteration)
			sum += pow(2, (a - i));
		}
	}
	return sum;
}

//Integers::Accessors
/**@brief Accessor for x

Accesses unsigned integer x for Integer class.

@param There are no parameters.
@return Returns private variable x.
*/
unsigned int Integer::getx() const
{
	return x;
}
/**@brief Printing the Integer 

Prints private variable x (unsigned integer)

@param No parameters.
@return Does not return anything.
*/
void Integer::print_as_int() const
{
	std::cout << x;
}

//Non-Integer-class Functions
/**@brief Adding Integers

Converts Integers into boolean values and stores values in vectors. Vectors are 
adjusted so that they contain the same number of bits. Boolean values are then 
converted into binary numbers (0 or 1). Binary numbers are stored in another vector
and are added to form a final vector, which is reversed and converted back to an 
Integer and returned. 

@param lhs is one of the Integers that will be added.
@param rhs is the other Integer that will be added. 
@return Returns an Integer that is the sum of lhs and rhs. 
*/
Integer plus(Integer lhs, const Integer& rhs)
{
	//Converting the two Integers into boolean values and storing them in vectors
	std::vector<bool>lhsvector;
	lhs.inttoboolbit(lhs.getx(), lhsvector);
	Integer rhs2 = rhs; //creating copy of rhs since it cannot be changed
	std::vector<bool>rhsvector;
	rhs2.inttoboolbit(rhs2.getx(), rhsvector);

	//Creating dummy variables for the sizes of the vectors
	int a = lhs.testnumberbits(lhs.getx());
	int b = rhs2.testnumberbits(rhs2.getx());

	//Adjusting sizes of vectors to be equal 
	//If size of lhs vector is bigger
	if (a > b)
	{
		//Add zeroes in front of rhs vector
		int addzeroes = a - b; 
		for (int i = 0; i < addzeroes; i++)
		{
			rhsvector.insert(rhsvector.begin(), 0);

		}
	}
	//If size of rhs vector is bigger
	else
	{
		//Add zeroes in front of lhs vector
		int addzeroes = b - a;
		for (int i = 0; i < addzeroes; i++)
		{
			lhsvector.insert(lhsvector.begin(), 0);
		}
	}

	//Creating vectors with binary code (0 or 1)
	std::vector<int>lhsbinary;
	std::vector<int>rhsbinary;

	//Changing rhsvector and lhsvector into binaries
	for (int i = 0; i < lhsvector.size(); i++) //number = 4
	{
		//If false, pushback 0
		if (!lhsvector[i])
		{
			lhsbinary.push_back(0);
		}
		//If truee, pushback 1
		else if (lhsvector[i])
		{
			lhsbinary.push_back(1);
		}
	}
	for (int i = 0; i < rhsvector.size(); i++) //number = 4
	{
		//If false, pushback 0
		if (!rhsvector[i])
		{
			rhsbinary.push_back(0);
		}
		//If truee, pushback 1
		else if (rhsvector[i])
		{
			rhsbinary.push_back(1);
		}
	}

	//Creating carryover vector
	std::vector<int>carryover((lhsvector.size() + 1));
	//Filling carryover with zeroes to initialize
	for (int i = 0; i < carryover.size(); i++)
	{
		carryover[i] = 0;
	}
	
	//Creating vector that will be sum of lhsbinary, rhsbinary, carryover
	std::vector<int>sumof3; 

	//Adding the three vectors (lhsbinary, rhsbinary, carryover)
	for (int i = (lhsbinary.size() - 1); i >= 0; i--)
	{
		//Temporary sum of three vectors at iteration i
		int sum = lhsbinary[i] + rhsbinary[i] + carryover[i + 1];
		//If not last iteration of loop
		if (i != 0)
		{
			if (sum == 0)
			{
				sumof3.push_back(0);
			}
			else if (sum == 1)
			{
				sumof3.push_back(1);
			}
			else if (sum == 2)
			{
				sumof3.push_back(0);
				carryover[i] = 1; //carryover one before because carryover has one extra space
			}
			else if (sum == 3)
			{
				sumof3.push_back(1);
				carryover[i] = 1;  //carryover one before because carryover has one extra space
			}
		}
		//If last iteration of loop, have to take into account extra carryover
		else if (i == 0)
		{
			if (sum == 0)
			{
				sumof3.push_back(0);
			}
			else if (sum == 1)
			{
				sumof3.push_back(1);
			}
			else if (sum == 2)
			{
				sumof3.push_back(0);
				sumof3.push_back(1);
			}
			else if (sum == 3)
			{
				sumof3.push_back(1);
				sumof3.push_back(1);
			}
		}
	}

	//Reverse order of sumof3 vector and copy to final
	std::vector<int>final;
	for (int i = (sumof3.size() - 1); i >= 0; i--)
	{
		final.push_back(sumof3[i]);
	}

	//convert back to unsigned integer
	return backtoint(final);
}
/**@brief Multiplying Integers

Converts Integers into boolean values and stores values in vectors. Vectors are
adjusted so that they contain the same number of bits. Boolean values are then
converted into binary numbers (0 or 1). Binary numbers are stored in another vector
and are multiplied to form a final vector, which is reversed and converted back to an
Integer and returned.

@param lhs is one of the Integers that will be multiplied.
@param rhs is the other Integer that will be multiplied.
@return Returns an Integer that is the product of lhs and rhs.
*/
Integer multiply(Integer lhs, const Integer& rhs)
{
	//Converting the two Integers into boolean values and storing them in vectors
	std::vector<bool>lhsvector;
	lhs.inttoboolbit(lhs.getx(), lhsvector);
	Integer rhs2 = rhs; //creating copy of rhs since it cannot be changed
	std::vector<bool>rhsvector;
	rhs2.inttoboolbit(rhs2.getx(), rhsvector);

	//Creating dummy variables for the sizes of the vectors
	int a = lhs.testnumberbits(lhs.getx());
	int b = rhs2.testnumberbits(rhs2.getx());

	//Adjusting sizes of vectors to be equal 
	//If size of lhs vector is bigger
	if (a > b)
	{
		//Add zeroes in front of rhs vector
		int addzeroes = a - b;
		for (int i = 0; i < addzeroes; i++)
		{
			rhsvector.insert(rhsvector.begin(), 0);

		}
	}
	//If size of rhs vector is bigger
	else
	{
		//Add zeroes in front of lhs vector
		int addzeroes = b - a;
		for (int i = 0; i < addzeroes; i++)
		{
			lhsvector.insert(lhsvector.begin(), 0);
		}
	}

	//Creating vectors with binary code (0 or 1)
	std::vector<int>lhsbinary;
	std::vector<int>rhsbinary;

	//Changing rhsvector and lhsvector into binaries
	for (int i = 0; i < lhsvector.size(); i++) //number = 4
	{
		//If false, pushback 0
		if (!lhsvector[i])
		{
			lhsbinary.push_back(0);
		}
		//If truee, pushback 1
		else if (lhsvector[i])
		{
			lhsbinary.push_back(1);
		}
	}
	for (int i = 0; i < rhsvector.size(); i++) //number = 4
	{
		//If false, pushback 0
		if (!rhsvector[i])
		{
			rhsbinary.push_back(0);
		}
		//If truee, pushback 1
		else if (rhsvector[i])
		{
			rhsbinary.push_back(1);
		}
	}
	
	//Creating variable for size of vectors
	int size = lhsvector.size() - 1;
	//Creating variable for sum of lines of products
	unsigned int sum = 0;
	//Counter for how many lines of multiplication done
	int counter = 0;

	for (int j = size; j >= 0; j--)
	{
		//Temporary vector that can have products pushed into it
		std::vector<int>temp;
		//If value of number is equal to 1
		if (rhsvector[j] == 1)
		{
			//Pushback the entire other number (because 1*that number = that number)
			for (int i = 0; i <= size; i++)
			{
				temp.push_back(lhsvector[i]);
			}
			//If the counter is not 0, then push back zeroes to account for line of addition
			for (int k = 0; k < counter; k++)
			{
				temp.push_back(0);
			}
		}
		//Sum = sum + conversion of temp vector into integer
		sum += backtoint(temp);
		//Increase counter to indicate line of addition
		counter++;
	}

	return sum;
}
