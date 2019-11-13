typedef struct{
	float coef;
	int expn;
}term,ElemType

typedef LinkList polynomial;

void CreatPolyn(polynomail&P,int m);

void DestroyPolyn(polynomail&P);

void PrintPolyn(polynomial P);

void PolynLength(polynomail P);

void AddPolyn(polynomail &Pa,polynomail &Pb);

void SubtractPolyn(polynomail &Pa, polynomail &Pb);

void Multiply