

#include <bits/stdc++.h> 
using namespace std; 

 
struct Node { 
	float coeff; 
	int pow; 
	struct Node* next; 
}; 


void create_node(float x, int y, 
				struct Node** temp) 
{ 
	struct Node *r, *z; 
	z = *temp; 

	 
	if (z == NULL) { 

		r = (struct Node*)malloc( 
			sizeof(struct Node)); 

	
		r->coeff = x; 
		r->pow = y; 
		*temp = r; 
		r->next = (struct Node*)malloc( 
			sizeof(struct Node)); 
		r = r->next; 
		r->next = NULL; 
	} 

	
	else { 
		r->coeff = x; 
		r->pow = y; 
		r->next = (struct Node*)malloc( 
			sizeof(struct Node)); 
		r = r->next; 
		r->next = NULL; 
	} 
} 

 
void store_quotient(float mul_c, int diff, 
					struct Node* quo) 
{ 
	 
	while (quo->next != NULL) { 
		quo = quo->next; 
	} 

	
	quo->pow = diff; 
	quo->coeff = mul_c; 
	quo->next = (struct Node*)malloc( 
		sizeof(struct Node)); 
	quo = quo->next; 
	quo->next = NULL; 
} 


void formNewPoly(int diff, float mul_c, 
				struct Node* poly) 
{ 
	
	while (poly->next != NULL) { 
		poly->pow += diff; 
		poly->coeff *= mul_c; 
		poly = poly->next; 
	} 
} 


void copyList(struct Node* r, 
			struct Node** copy) 
{ 
	
	while (r != NULL) { 

		struct Node* z 
			= (struct Node*)malloc( 
				sizeof(struct Node)); 

		
		z->coeff = r->coeff; 
		z->pow = r->pow; 
		z->next = NULL; 

		struct Node* dis = *copy; 
		if (dis == NULL) { 
			*copy = z; 
		} 
		else { 
			while (dis->next != NULL) { 
				dis = dis->next; 
			} 
			dis->next = z; 
		} 
		r = r->next; 
	} 
} 

void polySub(struct Node* poly1, 
			struct Node* poly2, 
			struct Node* poly) 
{ 

	while (poly1->next && poly2->next) { 


		if (poly1->pow > poly2->pow) { 

			poly->pow = poly1->pow; 
			poly->coeff = poly1->coeff; 
			poly1 = poly1->next; 
			poly->next 
				= (struct Node*)malloc( 
					sizeof(struct Node)); 
			poly = poly->next; 
			poly->next = NULL; 
		} 

		
		else if (poly1->pow < poly2->pow) { 

			poly->pow = poly2->pow; 
			poly->coeff = -1 * poly2->coeff; 
			poly2 = poly2->next; 
			poly->next 
				= (struct Node*)malloc( 
					sizeof(struct Node)); 
			poly = poly->next; 
			poly->next = NULL; 
		} 

		else { 

			if ((poly1->coeff 
				- poly2->coeff) 
				!= 0) { 

				poly->pow = poly1->pow; 
				poly->coeff = (poly1->coeff 
							- poly2->coeff); 

				poly->next = (struct Node*)malloc( 
					sizeof(struct Node)); 
				poly = poly->next; 
				poly->next = NULL; 
			} 

		
			poly1 = poly1->next; 
			poly2 = poly2->next; 
		} 
	} 

	while (poly1->next || poly2->next) { 

		
		if (poly1->next) { 
			poly->pow = poly1->pow; 
			poly->coeff = poly1->coeff; 
			poly1 = poly1->next; 
		} 

		if (poly2->next) { 
			poly->pow = poly2->pow; 
			poly->coeff = -1 * poly2->coeff; 
			poly2 = poly2->next; 
		} 

		poly->next 
			= (struct Node*)malloc( 
				sizeof(struct Node)); 
		poly = poly->next; 
		poly->next = NULL; 
	} 
} 

void show(struct Node* node) 
{ 
	int count = 0; 
	while (node->next != NULL 
		&& node->coeff != 0) { 

		if (count == 0) 
			cout << node->coeff; 

		
		else
			cout << abs(node->coeff); 
		count++; 

		if (node->pow != 0) 
			cout << "x^" << node->pow; 
		node = node->next; 

		if (node->next != NULL) 

			
			if (node->coeff > 0) 
				cout << " + "; 
			else
				cout << " - "; 
	} 

	cout << "\n"; 
} 

void divide_poly(struct Node* poly1, 
				struct Node* poly2) 
{ 
	
	struct Node *rem = NULL, *quo = NULL; 

	quo = (struct Node*)malloc( 
		sizeof(struct Node)); 
	quo->next = NULL; 

	struct Node *q = NULL, *r = NULL; 

	
	copyList(poly1, &q); 

	
	copyList(poly2, &r); 

	
	while (q != NULL 
		&& (q->pow >= poly2->pow)) { 

		
		int diff = q->pow - poly2->pow; 

		float mul_c = (q->coeff 
					/ poly2->coeff); 

		
		store_quotient(mul_c, diff, 
					quo); 

		struct Node* q2 = NULL; 

		
		copyList(r, &q2); 
	
		formNewPoly(diff, mul_c, q2); 

		struct Node* store = NULL; 
		store = (struct Node*)malloc( 
			sizeof(struct Node)); 

		polySub(q, q2, store); 

	
		q = store; 
		free(q2); 
	} 
	
	cout << "Quotient: "; 
	show(quo); 
 
	cout << "Remainder: "; 
	rem = q; 
	show(rem); 
} 

int main() 
{ 
	struct Node* poly1 = NULL; 
	struct Node *poly2 = NULL, *poly = NULL; 


	create_node(5.0, 2, &poly1); 
	create_node(4.0, 1, &poly1); 
	create_node(2.0, 0, &poly1); 
	create_node(5.0, 1, &poly2); 
	create_node(5.0, 0, &poly2); 
	
	divide_poly(poly1, poly2); 

	return 0; 
} 
