#include <iostream>
#include <fstream>
#define INFILE "INPUT.TXT"
#define OUTFILE "OUTPUT.TXT"


unsigned long long power_of_2(unsigned long long exponent)
{
	if (exponent < sizeof(unsigned long long) * CHAR_BIT)
		return 1 << exponent;
	else
		return 0;
};


unsigned long long parse(const std::string input)
{
	unsigned long long result, power;
	long long cycle;


	result = 0;
	power = 1;
	for (cycle = input.size() - 1; cycle > -1; cycle--)
	{
		if (input[cycle] == '1')
			result += power;

		power *= 2;
	};


	return result;
};


unsigned int weight(unsigned long long vector)
{
	unsigned int result;


	result = 0;
	while (vector > 0)
	{
		if (vector % 2)
			result++;

		vector /= 2;
	};


	return result;
}


void move(unsigned long long& temporary, unsigned long long& position)
{
	temporary /= 2;

	position++;
};


unsigned long long* calculate_amount(const unsigned long long vector[], const unsigned long long N, const unsigned long long K)
{
	const unsigned long long limit = power_of_2(K);
	unsigned long long* result = new unsigned long long[N + 1], value, temporary, position, cycle;


	result[0] = 1;
	for (cycle = 1; cycle <= N; cycle++)
		result[cycle] = 0;

	for (cycle = 1; cycle < limit; cycle++)
	{
		temporary = cycle;
		
		position = 0;

		while (!(temporary % 2) && temporary)
			move(temporary, position);

		 value = vector[position];

		 move(temporary, position);

		 while (temporary)
		 {
			 while(!(temporary % 2))
				 move(temporary, position);

			 value ^= vector[position];

			 move(temporary, position);
		 };

		 std::cout << value << std::endl;

		 result[weight(value)]++;
	};


	return result;
};


int main()
{
	unsigned long long N, K, limit, cycle, *vector, *amount;
	std::string input;
	std::ifstream input_file;
	std::ofstream output_file;


	try
	{
		input_file.open("INPUT.TXT");

		input_file >> N;

		limit = power_of_2(N);

		if (limit)
		{
			vector = new unsigned long long[limit];
			if (!vector)
				throw std::runtime_error("Cannot allocate memory for storage of vectors.");

			K = 0;
			while (!input_file.eof() && (K < limit))
			{
				input_file >> input;

				vector[K] = parse(input);

				K++;
			};

			input_file.close();

			amount = calculate_amount(vector, N, K);

			output_file.open("OUTPUT.TXT");

			for (cycle = 0; cycle <= N; cycle++)
				output_file << cycle << "\t" << amount[cycle] << std::endl;

			output_file.close();

			delete[] vector;
			delete[] amount;
		}
		else
			throw std::runtime_error("Cannot allocate memory for exponentiation.");
	}
	catch (std::exception error)
	{
		std::cout << error.what() << std::endl;

		return 1;
	};


	return 0;
}