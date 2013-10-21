#define ORDER 3
#define GENESIZE 9
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
		return cayleyTablePermutation[x] + cayleyTablePermutation[(y % ORDER) * ORDER + y / ORDER] % (GENESIZE);
	}
	int getbyIndex(int i){
		return getbyIndexXY(i%GENESIZE, i/GENESIZE);
	}

	void getFromInput(int *inputBoard){

	}

	float fitnessFunction(){

		//Count repititions in the smapled seciton, raise by 2^-n.
	}

	void crossoverFunction(){

		//TODO: Figure out how to sample;

		int gene1[GENESIZE]; //get it from somewhere
		int gene2[GENESIZE]; //get it from somewhere

		int newGene[GENESIZE];

		for (int i = 0; i < GENESIZE; ++i)
		{
			newGene[gene2[i]] = gene1[i]; //Permute 1 by 2 
		}

		//TODO: Now generate the new sudoku board from getByIndexXY.
	}

	void mutationFunction(){
	//TODO add noise, swap columns

	}
};