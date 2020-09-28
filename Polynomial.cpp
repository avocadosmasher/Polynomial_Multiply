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
	terms = 0 ; // 0이 아닌 항의 수
	termArray = new Term[capacity] ;  // 크기 4 로 배열 생성
}

Polynomial::~Polynomial(void)
{
}

Polynomial Polynomial::Add(Polynomial b)
// a(x)(*this의 값)와 b(x)를 더한 결과를 반환한다.
{
  Polynomial c; 
  int aPos = 0, bPos = 0 ;

  while ((aPos < terms) && (bPos < b.terms)) 
    if(termArray[aPos].exp == b.termArray[bPos].exp) { // 현재 가르키는 다항식a와 b의 지수가 같을때
        float t = termArray[aPos].coef + b.termArray[bPos].coef;
        if (t) c.NewTerm(t, termArray[aPos].exp);
        aPos++; bPos++;
	}
	else if (termArray[aPos].exp < b.termArray[bPos].exp) { // 현재 가르키는 다항식 a의 계수가 b의 계수보다 작을때.
        c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
        bPos++;
	}
	else { // 현재 가르키는 다항식 a의 계수가 b의 계수보다 클때
        c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
        aPos++;
    } 

  // A(x)(*this)의 나머지 항들을 추가한다.
  for (; aPos < terms; aPos++)
    c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);

  // B(x)의 나머지 항들을 추가한다.
  for (; bPos < b.terms; bPos++)
    c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
 
  return c;
} // Add의 끝


void Polynomial::NewTerm(const float theCoeff, const int theExp)
// 새로운 항을 termArray 끝에 첨가한다.
{
    if (terms == capacity) 
    {//termArray의 크기를 두 배로 확장
          capacity *= 2; 
          Term *temp = new Term [capacity];           // 새로운 배열
		  for(int i=0; i<terms ; i++) 
			  temp[i] = termArray[i] ;
          delete [ ] termArray;                       // 그전 메모리를 반환
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
      // 마지막 항을 출력
      cout << termArray[i].coef << " x^" << termArray[i].exp << "\n" ;
   }
   else
	  cout << " No terms " << endl;

}

Polynomial Polynomial::Multiply(Polynomial b)
{
    Polynomial c; // 결과로 반환될 다항식.
    int aPos = 0, bPos = 0; // aPos, bPos를 통해 tempArray의 인덱스를 가르킨다.

    // 순서가 b 다항식의 항 하나씩 a 다항식의 모든 항들과 곱셈을 진행하고 그 결과를 temp에 임시로 받아서 c와 덧셈을 한다.
    // 그렇게 b 다항식의 마지막 항까지 진행을 해 c를 반환하는 형태.
    while (aPos < terms) // a 다항식이 끝날때까지 진행.
    {
        Polynomial temp; // 임시로 다항식을 저장해 놓음.
        while (bPos < b.terms) // 현재 aPos가 가르키는 a의 항과 b의 항들의 곱셈결과를 temp에 저장하려구 함.
        {
            float t_coef = 0;// temp의 계수가 저장될 예정.
            int t_exp = 0; // temp의 지수 저장될 예정.
            t_coef = termArray[aPos].coef * b.termArray[bPos].coef; // 계수끼리는 곱셈을 진행 후 저장.
            t_exp = termArray[aPos].exp + b.termArray[bPos].exp; // 지수끼리는 곱셈시 서로 덧셈이 진행됨. 그 결과를 저장.
            temp.NewTerm(t_coef, t_exp); // 그냥 위의 코드들을 여기에 때려넣을수도 있었지만... 보기에 이쁘지 않으므로 이와같이 처리함.
            bPos++; // bPos를 다음으로.
        }
        c = c.Add(temp); // 결과를 c와 더한 후 c에 저장.
        aPos++; // aPos의 전진.
        bPos = 0; // bPos를 초기화.
    }
    // 현재 c에는 곱셈을 마친 결과가 저장되어 있음.
    return c; // 결과 반환.
}
