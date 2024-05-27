#include <iostream>

using namespace std;

class Polynom {
public:
	float a;
	int n;
	Polynom* next;

	Polynom() { //конструктор
		a = 1.0;
		n = 2;
		next = NULL;
	}

	Polynom(float o ) {
		a = o;
		n = 3;
		next = NULL;
	}

	Polynom(int c ) {
		n = c;
		a = 1.3;
		next = NULL;
	}

	Polynom(int e , float s = 1.2 ) {
		a = s;
		n = e;
		next = NULL;
	}

	void print_polynom() {
		cout << a << "x^" << n;
	}

	void print_all() {
		Polynom* i = this;
		i->print_polynom();
		while (i->next != NULL) {
			i = i->next;
			cout << "+";
			i->print_polynom();
		}
	}

	Polynom operator + (Polynom& y) {
		Polynom res;
		if (n == y.n) {
			res.a = a + y.a;
			res.n = n;
		}
		else {
			res.a = a;
			res.n = n;
			res.next = new Polynom(y.a, y.n);
		}
		
		return res;
	}

	Polynom operator - (Polynom& z) {
		Polynom res;
		if (n == z.n) {
			res.a = a - z.a;
			res.n = n;
		}
		else {
			res.a = a;
			res.n = n;
			res.next = new Polynom(z.a, -z.n);
		}
		
		return res;
	}

	float getA() const {
		return a;
	}

	void setA(float newA) {
		a = newA;
	}

	int getN() const {
		return n;
	}

	void setN(int newN) {
		n = newN;
	}

	void konets(float a, float n) {
		Polynom* newPolynom = new Polynom(a, n);
		Polynom* temp = this;

		while (temp->next != NULL) {
			temp = temp->next;
		}

		temp->next = newPolynom;
	}

	void sortirovka() {
		bool swapped;
		Polynom* ptr1;
		Polynom* lptr = nullptr;

		if (this == nullptr)
			return;

		do {
			swapped = false;
			ptr1 = this;

			while (ptr1->next != lptr) {
				if (ptr1->n < ptr1->next->n) {
					swap(ptr1->a, ptr1->next->a);
					swap(ptr1->n, ptr1->next->n);
					swapped = true;
				}
				ptr1 = ptr1->next;
			}
			lptr = ptr1;
		} while (swapped);
	}
};

int main() {
	setlocale(LC_ALL, "Russian");
	Polynom A;
	A.a = 3.5;
	Polynom B;
	B.n = 4; 
	B.a = 3.6; 
	A.next = &B;

	B.print_all();
	cout << endl;
	cout << "Непонятный полином В!" << endl << endl;

	Polynom C = A + B;
	C.print_all();

	cout << endl << endl;

	Polynom D = A - B;
	D.print_all();

	cout << endl << endl;

	cout << "Значение А: " << A.getA() << endl;
	A.setA(5.3);
	cout << "Новое значение А: " << A.getA() << endl;

	cout << "Значение В: " << B.getA() << endl;
	B.setA(6.5);
	cout << "Новое значение В: " << B.getA() << endl;

	// Элемент в конец списка A
	A.konets(10, 50.11);

	cout << endl;
	cout << "Печать полинома после добавления нового элемента:" << endl;
	A.print_all();
	
	cout << endl << endl;

	A.sortirovka();
	cout << "Печать полинома после сортировки по убыванию степени:" << endl;
	A.print_all();
	cout << endl;

	return 0;
}