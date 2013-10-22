
#define ORDER 3
#define GENESIZE 9
#define ZERO_TO_ONE 1

class CayleyTable
{
	int gene[GENESIZE];

public:
	CayleyTable(int* permutations)
    {
		//if permutations are legal, store them
		for (int i = 0 ; i < GENESIZE ; ++i)
        {
			gene[i] = permutations[i];
		}
	}
	~CayleyTable(){};

	/**
	 * Returns the value of a sudoku table at x,y
	 */
	 int getbyIndexXY(int x, int y){
         int yPos = (y % ORDER) * ORDER + y / ORDER;
         int returnval = ((gene[x] + gene[yPos]) % GENESIZE);
         return returnval == 0 ? 9 : returnval; //0->9
	 }
    
	 int getbyIndex(int i){
	 	return getbyIndexXY(i / GENESIZE, i % GENESIZE);
	 }

};