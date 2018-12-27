//============================================================================
// Name        : Conversion.cpp
// Author      : SOHAIL
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "conversion.h"
#include "Stack.h"
#include "StackLinkedList.cpp"
using namespace std;

void Conversion::input()
{
	int c=1,s=0,n1=0,n2=0,i=0,b=2;
	while(c==1)
	{
		c=0;
	cout<<"\nEnter Expression in Infix Form ";
	cin.getline(infix,20);
	while(infix[i]!='\0')                         //validation for Taking Infix Expression
	{
		if(isOperand(infix[i])==1)
			n1++;
		else if(isOperator(infix[i])==1)
			n2++;
		else if(infix[i]=='('||infix[i]==')')
			b++;
		else
			s++;
		i++;
	}
	if(n1!=n2+1 || s>0 || 0!=(b%2))
	{
		c++;
		s=n1=n2=i=0;
		b=2;
		cout<<"\nOperantor must be one less than number of operand and Space not Allowed ";
		cout<<"\nOr Make sure braces are closed";
		cout<<"\nRe-Enter";
	}
	}

}

int Conversion::isOperand(char in)//to check character is operand or not
{

 if((in>='a' && in<='z') || (in>='A' && in<='Z') || (in>='0' && in<='9'))
	 return 1;         //return 1 if operand
 else
	 return 0;        //return 0 if not operand
}

int Conversion::isOperator(char in)
{
	if(in=='+' || in=='-' || in=='*' || in=='/' || in=='^' || in=='$')
		return 1;       //return 1 if character is operator
	else
		return 0;       //return 0 if not operator
}
int Conversion:: precedence(char in)//return precedence of operator
{
	if( in=='(' || in==')')
					return 0 ;
	else if ( in == '$' || in=='^')
			return 3 ;
	else if ( in == '*' || in == '/' || in == '%' )
			return 2 ;
		else
			if ( in == '+' || in == '-' )
				return 1 ;

	return 0;
}

bool Conversion::isRightAsso(char op)
{                                         //return true  if if operator is right associative other vice false
	if(op == '^' ||op=='$') return 1;   //if false means is left associative
		return 0;
}

int Conversion::pow(int op1,int op2)//return result of exponent operator
{
	int i,r;
	r=op1;
	for(i=1;i<op2;i++)
	{
		r=r*op1;
	}
 return r;
}

void Conversion::convertInfixToPostfix()//to convert infix to post fix form
{
     int i=0,p=0,j=0;
     char x,y,z;
     cout<<"\nInfix"<<"\t\t\t\tStack"<<"\t\t\tPostfix";
     cout<<"\n"<<infix<<"\t\t\t\tNULL"<<"\t\t\tNULL"<<"";
     int l;
     l=strlen(infix);

     while(infix[i]!='\0') //scan from left to right
     {
    	 x=infix[i];

    	 if(isOperand(x)==1)  //check character is operand if true insert to postfix string
    	 {
    		 postfix[p++]=x;
    	 }
    	 else if(x=='(')         //if character is '(' push on stack
    		{SOC.push(x);}
    	 else if(x==')')//if ')' pop from stack and insert to post fix exp until '(' comes
    	 {
    		 y=SOC.pop();

    		 while(y!='(')
    		 {
                 postfix[p++]=y;
                 y=SOC.pop();
    		 }
    	 }
    	 else if(isOperator(infix[i])==1) //check for operator
    	 {

    		 z=SOC.TopData();   //take stack data as Z

    		 if(SOC.isempty()==1)  //if stack empty directly push on stack
    		 {
               SOC.push(x);
    		 }
    		 else if(z=='(' || precedence(x)>precedence(z))// if z is equal to '(' or precendence of x is greater than z
    		 {
    			 SOC.push(x);   // then x push on stack
    		 }
    		 else
    		 {
    			 if(precedence(x)<precedence(z))
    			 {
    				 while(precedence(x)<precedence(z))//until precedence is less of x
    			 {
    				 z=SOC.pop();    //first pop from stack and insert on post fix string
    				 postfix[p++]=z;
    				 z=SOC.TopData();  //get top data of stack
    				 }
    				SOC.push(x);
    		     }
    			 else if(precedence(x)==precedence(z)) //if precedence is equal check for associativity
    			 {
                   if(isRightAsso(x)==0) //check for Associativity
                   {
                	   z=SOC.pop();        //if left pop and then push
                	   postfix[p++]=z;
                	   SOC.push(x);
                   }
                   else
                	   {
                	   SOC.push(x);   //if right
                	   }
    			 }
    		 }
    	 }
          i++;
    	 cout<<"\n";
    	 if(i==l)
    	   cout<<"NULL";
    	 for(j=i;j<l;j++)
    	 cout<<infix[j];
    	 cout<<"\t\t\t\t";
    	 SOC.display();
    	 cout<<"\t\t\t";
    	 for(j=0;j<p;j++)
    	 cout<<postfix[j]<<"";


        //

     }
     while(!SOC.isempty())        //inserting remaining stack elements to postfix array
          {
         	 x=SOC.pop();
            postfix[p++]=x;
            	 cout<<"\nNULL";
            	 cout<<"\t\t\t\t";
            	 SOC.display();
            	 cout<<"\t\t\t";
                for(j=0;j<p;j++)
            	 cout<<postfix[j];
          }
          postfix[p]='\0';
          cout<<"\nYour Final Post Fix Form Expression is : "<<postfix;
}

void Conversion::convertInfixToPrefix() //function to convert in prefix form
{
	 int i=0,p=0,j;
	     char x,y,z;

	     i=strlen(infix);
	     i--;
	     cout<<"\nInfix"<<"\t\t\t\tStack"<<"\t\t\tTemp_PreFix";
	     cout<<"\n"<<infix<<"\t\t\t\tNULL"<<"\t\t\tNULL"<<"";
	     while(i!=-1)       //scanning from Right To Left
	     {
	    	 x=infix[i];

	    	 if(isOperand(x)==1)  //check for operand
	    	 {
	    		 temp[p++]=x;

	    	 }
	    	 else if(x==')')
	    		SOC.push(x);
	    	 else if(x=='(')
	    	 {
	    		 y=SOC.pop();
	    		 while(y!=')')
	    		 {
	                 temp[p++]=y;

	                 y=SOC.pop();
	    		 }
	    	 }
	    	 else if(isOperator(infix[i])==1) //check for operator
	    	 {

	    		 z=SOC.TopData();
	    		 if(SOC.isempty()==1)
	    		 {
	               SOC.push(x);

	    		 }
	    		 else if(z==')'||precedence(x)>precedence(z))
	    		 {
	    			 SOC.push(x);
	    		 }
	    		 else
	    		 {
	    			 if(precedence(x)<precedence(z)) //if precedence of infix current scan element is less than stack top element
	    			 {
	    				 while(precedence(x)<precedence(z)&& precedence(z)!=0)
	    				 {
	    				 z=SOC.pop();
                                           //pop all elements  until precedence is less or empty stack
	    				 temp[p++]=z;

	    				 z=SOC.TopData();
	    				 }
	    				 SOC.push(x); //then push scanned element
	    		      }
	    			 else
	    			 {
	                   if(isRightAsso(x)==1) //check for associativity
	                   {
	                	   z=SOC.pop();  //if Right pop then push
	                	   temp[p++]=z;
	                	   SOC.push(x);
	                   }
	                   else
	                	   {
	                	   SOC.push(x); //if left
	                	   }
	    			 }
	    		 }
	    	 }
	    	/* cout<<"\nStack at Conversion";   //display stack status
	    	    SOC.display(0);
	    	    cout<<"\nTemporary  Prefix expression During Conversion : "<<prefix<<"\n";
*/
	    	 i--;

	    	 cout<<"\n";
	    	    	 if(i<0)
	    	    	   cout<<"NULL";
	    	    	 for(j=0;j<=i;j++)
	    	    	 cout<<infix[j];
	    	    	 cout<<"\t\t\t\t";
	    	    	 SOC.display();
	    	    	 cout<<"\t\t\t";
	    	    	 for(j=0;j<p;j++)
	    	    	 cout<<temp[j]<<"";
	     }
	     while(!SOC.isempty()) //reverse temp string to get Final Prefix Expreesion
	          {
	         	 x=SOC.pop();
	        temp[p++]=x;
	        cout<<"\nNULL";
	                    	 cout<<"\t\t\t\t";
	                    	 SOC.display();
	                    	 cout<<"\t\t\t";
	                    	 for(j=0;j<p;j++)
	                    	 cout<<temp[j];
	          }
	          temp[p]='\0';
                     i=0;
	          	    int n = strlen(temp);
	          	    n--;
	          	    for(int y = n; y >= 0; y--)
	          	    {
	          	  prefix[i] = temp[y];
	          	    i++;
	          	    }
	          	    prefix[i]='\0';
	          	    cout<<"\nAfter Reversing temporary prefix expression..";
	          	    cout<<"\nYour Final Prefix Form of Expression is : "<<prefix;
}

void Conversion::evaluatePost() //to evaluate post fix exp.
{

	int i=0,j,l;
	char x;                         //declaration of variables need for calculation
	int value,result=0,op1,op2;
	l=strlen(postfix);
	cout<<"\nPostFix"<<"\t\t"<<"Stack";
	cout<<"\n"<<postfix<<"\t\t"<<"NULL";
     while(postfix[i]!='\0')   //scan from left to right
     {
    	 x=postfix[i];
    	 if(isOperand(x)==1)  //if operand take its value
    	 {
    		 cout<<"\nEnter value of "<<x;
    		 cin>>value;
    		 SOI.push(value);
    	 }
    	 else if(isOperator(x)==1)//if operator pop two operands and perform operation as per operator
    		                       //and again push result back to stack
		{
    		 op1=SOI.pop();
    		 op2=SOI.pop();
           switch(x)
           {
           case '+':
        	       result=op2+op1;
        	       SOI.push(result);
        	   break;
           case '-':
        	        result=op2-op1;
        	        SOI.push(result);
        	   break;
           case '*':
        	   result=op2*op1;
        	   SOI.push(result);
        	   break;
           case '/':
        	   result=op2/op1;
        	   SOI.push(result);
        	   break;
           case '^':
                  result=pow(op2,op1);

                  SOI.push(result);
        	   break;
           }

		}

          i++;
          cout<<"\nPostFix"<<"\t\t"<<"Stack\n";
          for(j=i;j<l;j++)
          {
        	  cout<<postfix[j];
          }
          cout<<"\t\t";
          cout<<"||";
          SOI.display();
          cout<<"||";
     }
     result=SOI.pop();  //pop result from stack and show
     cout<<"\nPost Result : "<<result;
}
void Conversion::evaluatePre() //to evaluate prefix exp.
{


	int i=0,j;
		char x;
		int value,result=0,op1,op2;
		 i=strlen(prefix);
		 i--;
		 cout<<"\nPreFix"<<"\t\t"<<"Stack";
		 	cout<<"\n"<<prefix<<"\t\t"<<"NULL";
	     while(i!=-1)  //scan from right to left
	     {
	    	 x=prefix[i];

	    	 if(isOperand(x)==1)  //if operand take its value
	    	 {
	    		 cout<<"\nEnter value of "<<x;
	    		 cin>>value;
	    		 SOI.push(value);
	    	 }
	    	 else if(isOperator(x)==1) //if operator pop two operands and perform operation as per operator
                                       //and again push result back to stack
			{

	    		 op1=SOI.pop();
	    		 op2=SOI.pop();
	           switch(x)
	           {
	           case '+':
	        	       result=op1+op2;
	        	       SOI.push(result);
	        	   break;
	           case '-':
	        	        result=op1-op2;
	        	        SOI.push(result);
	        	   break;
	           case '*':
	        	   result=op1*op2;
	        	   SOI.push(result);
	        	   break;
	           case '/':
	        	   result=op1/op2;
	        	   SOI.push(result);
	        	   break;
	           case '^':
	                             result=pow(op1,op2);
	                             SOI.push(result);
	                   	   break;
	           }
			}


	          i--;
	          cout<<"\nPostFix"<<"\t\t"<<"Stack\n";
	                   for(j=0;j<=i;j++)
	                   {
	                 	  cout<<prefix[j];
	                   }
	                   cout<<"\t\t";
	                   cout<<"||";
	                   SOI.display();
	                   cout<<"||";
	     }
	     result=SOI.pop(); //final result is in stack pop and show
	    cout<<"\nPrefix Result : "<<result;
}

int main() {

	Conversion C;
	int c=0;
	C.input();
	while(c!=6)
	{
		 //Display all function that program can perform
	cout<<"\n\n1.Enter Infix Expression \n2.Convert Given Infix To Postfix Form \n3.Convert Given Infix To Prefix Form ";
	cout<<"\n4.Evaluate Postfix expression \n5.Evaluate Prefix Expression \n6.exit ";
	cin>>c;
	switch(c)
	{
	case 1:
		C.input();  //to take infix expression from user
		break;
	case 2:

		C.convertInfixToPostfix(); //function call to convert infix exp to postfix exp
		break;
	case 3:
		C.convertInfixToPrefix();//function call to convert infix exp to prefix exp
		break;
	case 4:
		C.convertInfixToPostfix(); //functions for evaluation of postfix exp
		C.evaluatePost();
		break;
	case 5:
		C.convertInfixToPrefix();//functions call for evaluation of prefix exp
		C.evaluatePre();
		break;
	case 6:
		return 0;
		break;
	default: cout<<"\n Incorrect Choice Re-Enter";
	}
	}
	return 0;
}
