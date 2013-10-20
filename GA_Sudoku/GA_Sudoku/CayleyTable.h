#define ORDER 3

class CayleyTable
{
	int cayleyTablePermutation[ORDER * ORDER];

public:
	CayleyTable(int* permutations){
		//if permutations are legal, store them
		for (int i = 0 ; i < ORDER * ORDER ; ++i){
			cayleyTablePermutation[i] = permutations[i];
		}
	}
	~CayleyTable();

	/* data */

	

	/**
	 * Returns the value of a sudoku table at x,y
	 */
	int getbyIndexXY(int x, int y){
		return cayleyTablePermutation[x] + cayleyTablePermutation[(y % ORDER) * ORDER + y / ORDER] % (ORDER * ORDER);
	}
	int getbyIndex(int i){
		return getbyIndexXY(i%9, i/9);
	}

	void getFromInput(int *inputBoard){

	}

	float fitnessFunction(){}

	void crossoverFunction(){}

	void mutationFunction(){}
};