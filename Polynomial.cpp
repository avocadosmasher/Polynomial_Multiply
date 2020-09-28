#include "StdAfx.h"
#include "Polynomial.h"
#include "Term.h"

#include <iostream>
using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
Polynomial::Polynomial(void)
{
    capacity = 4;
	terms = 0 ; // 0�� �ƴ� ���� ��
	termArray = new Term[capacity] ;  // ũ�� 4 �� �迭 ����
}

Polynomial::~Polynomial(void)
{
}

Polynomial Polynomial::Add(Polynomial b)
// a(x)(*this�� ��)�� b(x)�� ���� ����� ��ȯ�Ѵ�.
{
  Polynomial c; 
  int aPos = 0, bPos = 0 ;

  while ((aPos < terms) && (bPos < b.terms)) 
    if(termArray[aPos].exp == b.termArray[bPos].exp) { // ���� ����Ű�� ���׽�a�� b�� ������ ������
        float t = termArray[aPos].coef + b.termArray[bPos].coef;
        if (t) c.NewTerm(t, termArray[aPos].exp);
        aPos++; bPos++;
	}
	else if (termArray[aPos].exp < b.termArray[bPos].exp) { // ���� ����Ű�� ���׽� a�� ����� b�� ������� ������.
        c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
        bPos++;
	}
	else { // ���� ����Ű�� ���׽� a�� ����� b�� ������� Ŭ��
        c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
        aPos++;
    } 

  // A(x)(*this)�� ������ �׵��� �߰��Ѵ�.
  for (; aPos < terms; aPos++)
    c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);

  // B(x)�� ������ �׵��� �߰��Ѵ�.
  for (; bPos < b.terms; bPos++)
    c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
 
  return c;
} // Add�� ��


void Polynomial::NewTerm(const float theCoeff, const int theExp)
// ���ο� ���� termArray ���� ÷���Ѵ�.
{
    if (terms == capacity) 
    {//termArray�� ũ�⸦ �� ��� Ȯ��
          capacity *= 2; 
          Term *temp = new Term [capacity];           // ���ο� �迭
		  for(int i=0; i<terms ; i++) 
			  temp[i] = termArray[i] ;
          delete [ ] termArray;                       // ���� �޸𸮸� ��ȯ
          termArray = temp;
	} 
    termArray[terms].coef = theCoeff;
    termArray[terms++].exp = theExp;
}


void Polynomial::Print()
{
   int i ;

   if (terms) {
      for (i = 0 ; i < terms-1 ; i++)
	      cout << termArray[i].coef << " x^" << termArray[i].exp << " + " ;
      // ������ ���� ���
      cout << termArray[i].coef << " x^" << termArray[i].exp << "\n" ;
   }
   else
	  cout << " No terms " << endl;

}

Polynomial Polynomial::Multiply(Polynomial b)
{
    Polynomial c; // ����� ��ȯ�� ���׽�.
    int aPos = 0, bPos = 0; // aPos, bPos�� ���� tempArray�� �ε����� ����Ų��.

    // ������ b ���׽��� �� �ϳ��� a ���׽��� ��� �׵�� ������ �����ϰ� �� ����� temp�� �ӽ÷� �޾Ƽ� c�� ������ �Ѵ�.
    // �׷��� b ���׽��� ������ �ױ��� ������ �� c�� ��ȯ�ϴ� ����.
    while (aPos < terms) // a ���׽��� ���������� ����.
    {
        Polynomial temp; // �ӽ÷� ���׽��� ������ ����.
        while (bPos < b.terms) // ���� aPos�� ����Ű�� a�� �װ� b�� �׵��� ��������� temp�� �����Ϸ��� ��.
        {
            float t_coef = 0;// temp�� ����� ����� ����.
            int t_exp = 0; // temp�� ���� ����� ����.
            t_coef = termArray[aPos].coef * b.termArray[bPos].coef; // ��������� ������ ���� �� ����.
            t_exp = termArray[aPos].exp + b.termArray[bPos].exp; // ���������� ������ ���� ������ �����. �� ����� ����.
            temp.NewTerm(t_coef, t_exp); // �׳� ���� �ڵ���� ���⿡ ������������ �־�����... ���⿡ �̻��� �����Ƿ� �̿Ͱ��� ó����.
            bPos++; // bPos�� ��������.
        }
        c = c.Add(temp); // ����� c�� ���� �� c�� ����.
        aPos++; // aPos�� ����.
        bPos = 0; // bPos�� �ʱ�ȭ.
    }
    // ���� c���� ������ ��ģ ����� ����Ǿ� ����.
    return c; // ��� ��ȯ.
}
