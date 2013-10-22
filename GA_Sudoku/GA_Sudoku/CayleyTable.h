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

	/**
	 * Returns the value of a sudoku table at x,y
	 */
	 int getbyIndexXY(int x, int y){
	 	return cayleyTablePermutation[x] + cayleyTablePermutation[(y % ORDER) * ORDER + y / ORDER] % (GENESIZE);
	 }
	 int getbyIndex(int i){
	 	return getbyIndexXY(i%GENESIZE, i/GENESIZE);
	 }
	};


	static float fitnessFunc(const int* iBoard, const size_t& iTileCount){

		//Count repititions in the smapled seciton, raise by 2^-n.
	}

	static void crossoverFunc(const int* iBoardA, const int* iBoardB, int* oBoard, const size_t& iTileCount){

		//TODO: Create a function and figure out how to sample;
		int *geneA = sampleBoard(*iBoardA, GENESIZE);
		int *geneB = sampleBoard(*iBoardB, GENESIZE);

		int newGene[GENESIZE];

		for (int i = 0; i < GENESIZE; ++i)
		{
			newGene[gene2[i]] = gene1[i]; //Permute 1 by 2 
		}

		CayleyTable t = CayleyTable(newGene);

		for (int i = 0; i < iTileCount; ++i)
		{
			oBoard[i] = newGene.getbyIndex(i);
		}
		//TODO: Now generate the new sudoku board from getByIndexXY.
	}

	static void mutateFunc(int* ioBoard, const size_t& iTileCount, const float& iMutationRate){
	

	//TODO add noise, swap columns

	}
