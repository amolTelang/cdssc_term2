#include<stdio.h>
#include<string.h>
#include<ctype.h>
struct Rules
//structure containing grammar, first, follow,symbols and corresponding rules of each non terminal
{
char acGrammar[10]; //character array to hold the rule of variable
char acFirst[10]; //character array to hold the First set of variable
char acFollow[10]; //character array to hold the Follow set of variable
char actable[10][10]; //character array to hold the entries in parsing table of variable
char symbol[10];
int iSymCount;
}VAR[10];

int iGrmCount,istrCount;
int itemp,itemp2,itemp3=0;
int l,p,q,x,y,z,i,j,k;
int istktop,iinptop,imtchtop=-1;
char var,actemp[5];
char inputstr[25],acstk_stack[20],acstk_input[20],acstk_matched[20];


void ComputeFirst(char ); //Function to compute first set
void ComputeFollow(char ); //Function to compute follow set
int StringParser(); //Function to parse the given input string
int CheckError(char ,char ); //Function to check error
void strreverse(char [],char []); //Function to reverse a string
void displayStacks(); //Function to display stacks
void main()
{
int iRetValue;
printf("Enter the number of rules: "); //Reading the number of rules in grammar
scanf("%d",&iGrmCount);
printf("Enter the Grammar: \n");
//Reading the grammar
for(i=0;i<iGrmCount;i++)
scanf("%s",VAR[i].acGrammar);
printf("\n");
printf("Grammar given: \n");
//Displaying grammar
for(i=0;i<iGrmCount;i++)
printf("%s\n",VAR[i].acGrammar);
for(i=0;i<iGrmCount;i++)
//Computing first set
{
itemp=i;
j=0;
ComputeFirst(VAR[i].acGrammar[0]);
}
for(i=0;i<iGrmCount;i++)
{
if(VAR[i].acGrammar[0]==VAR[i+1].acGrammar[0])
strcat(VAR[i].acFirst,VAR[i+1].acFirst);
}
printf("\nFirst Set:\n");
for(i=0;i<iGrmCount;i++)
//Displaying first set
{
if(VAR[i].acGrammar[0]==VAR[i-1].acGrammar[0])

continue;
else
{
printf("%c: ",VAR[i].acGrammar[0]);
for(j=0;j<strlen(VAR[i].acFirst);j++)
printf("%c ",VAR[i].acFirst[j]);
}
printf("\n");
}
printf("\n");
p=0;
VAR[0].acFollow[p]='$';
//inserting $ in follow set of first variable of grammar
for(i=0;i<iGrmCount;i++)
//Computing follow set
{
if(VAR[i].acGrammar[0]==VAR[i-1].acGrammar[0])
continue;
ComputeFollow(VAR[i].acGrammar[0]);
}
printf("\n\nFollow Set:\n\n");
for(i=0;i<iGrmCount;i++)
//Displaying follow set
{
if(VAR[i].acGrammar[0]==VAR[i-1].acGrammar[0])
continue;
else

{
printf("%c: ",VAR[i].acGrammar[0]);
for(j=0;j<strlen(VAR[i].acFollow);j++)
printf("%c ",VAR[i].acFollow[j]);
}
printf("\n");
}
printf("\n\nPredictive Parsing table:\n\n");
//Computing and displaying predictive parsing table
for(i=0;i<iGrmCount;i++)
{
VAR[i].iSymCount=0;
x=0;
if(VAR[i].acGrammar[0]!=VAR[i-1].acGrammar[0])
{
printf("\n\nNon terminal: %c ",VAR[i].acGrammar[0]);
printf("\nInput Symbols Rules\n");
}
if(!(isupper(VAR[i].acGrammar[3])) && VAR[i].acGrammar[3]!='e')
//if first symbol in grammar is a terminal, not epsilon
{
p=0;
q=0;
VAR[i].actable[p][q]=VAR[i].acGrammar[3];
printf("%c ",VAR[i].actable[p][q]);

VAR[i].symbol[x++]=VAR[i].actable[p][q];
q++;
for(j=0;j<strlen(VAR[i].acGrammar);j++)
{
VAR[i].actable[p][q]=VAR[i].acGrammar[j];
printf("%c",VAR[i].actable[p][q]);
q++;
}
printf("\n");
VAR[i].iSymCount++;
}
else
{
p=0;
for(j=0;j<strlen(VAR[i].acFirst);j++)
{
if(VAR[i].acFirst[j]=='e')
//if first symbol in grammar is epsilon

{
for(k=0;k<strlen(VAR[i-1].acFollow);k++)
{
q=0;
VAR[i].actable[p][q]=VAR[i-1].acFollow[k];
printf("%c  ",VAR[i].actable[p][q]);
VAR[i].symbol[x++]=VAR[i].actable[p][q];
q++;

for(l=0;l<strlen(VAR[i].acGrammar);l++)
{
VAR[i].actable[p][q]=VAR[i].acGrammar[l];
printf("%c",VAR[i].actable[p][q]);
q++;
}
printf("\n");
p++;
VAR[i].iSymCount++;
}
}
else
//if first symbol in grammar is a variable
{
q=0;
VAR[i].actable[p][q]=VAR[i].acFirst[j];
printf("%c  ",VAR[i].actable[p][q]);
VAR[i].symbol[x++]=VAR[i].actable[p][q];
q++;
for(k=0;k<strlen(VAR[i].acGrammar);k++)
{
VAR[i].actable[p][q]=VAR[i].acGrammar[k];
printf("%c",VAR[i].actable[p][q]);
q++;
}
printf("\n");

p++;
VAR[i].iSymCount++;
}
}
}
}
printf("\n\n");
printf("Enter the number of strings to be parsed: "); //Reading the number of strings to be parsed
scanf("%d",&istrCount);
for(x=0;x<istrCount;x++)
{
istktop=-1;
iinptop=-1;
printf("\nEnter the string to be parsed: ");

//Reading the input string to be parsed
scanf("%s",inputstr);
itemp=0;
for(y=0;y<strlen(inputstr);y++)
{
if(inputstr[y]!='i' && inputstr[y]!='+' && inputstr[y]!='*' && inputstr[y]!='('
&& inputstr[y]!=')')
{
printf("\nString is not accepted by the given grammar\nSymbols allowed in the input string: i + * ( ) \n");
itemp=1;

break;
}
}
if(itemp==1)
continue;
strcat(inputstr,"$");
for(i=strlen(inputstr)-1;i>=0;i--)
//pushing the input string into Input stack
acstk_input[++iinptop]=inputstr[i];
acstk_stack[++istktop]='$';
//pushing $ and first variable into stack
acstk_stack[++istktop]=VAR[0].acGrammar[0];
iRetValue=StringParser();
//Calling function to parse tree
if(iRetValue==1)
printf("\nString is not accepted by the given grammar\n");
else
printf("\nString is accepted by the given grammar\n");
printf("\n\n");
}
}

void ComputeFirst(char ch)
{
if(!(isupper(VAR[itemp].acGrammar[3])))

//if grammar contains a terminal as its first symbol
{
VAR[i].acFirst[j++]=VAR[itemp].acGrammar[3];
return;
}
else

//if grammar contains a variable as its first symbol
{
for(k=i+1;k<iGrmCount;k++)
{
var=VAR[itemp].acGrammar[3];
if(VAR[k].acGrammar[0]==var)
{
itemp=k;
ComputeFirst(VAR[k].acGrammar[0]);
if(VAR[k+1].acGrammar[0]==var)
{
itemp=k+1;
ComputeFirst(VAR[k+1].acGrammar[0]);

//recursively calling ComputeFirst to compute first set
if(VAR[k+1].acGrammar[3]=='e')
{
itemp2++;
ComputeFirst(VAR[i].acGrammar[itemp2]);
}
}
}
}
}
}


void ComputeFollow(char ch)
{
int iepsilon=0,iVarFound;
if(i==0)
//for first variable in grammar start inserting follow set from 1, $ is in follow set
p=1;
else

//for other variables in grammar start inserting follow set from 0
p=0;


for(j=0;j<iGrmCount;j++)
{
iVarFound=0;
if(VAR[j].acGrammar[0]!=VAR[i].acGrammar[0])
{
for(k=3;k<strlen(VAR[j].acGrammar);k++)
{
if(VAR[j].acGrammar[k]==ch)
//if any grammar containing the current sent variable in its production rule, VarFound=1
{
iVarFound=1;
break;
}
}
if(iVarFound==1)

//if Variable is found check for its next symbol in the grammar
{
if(!isupper(VAR[j].acGrammar[k+1]) &&
VAR[j].acGrammar[k+1]!='\0')
//if next symbol is a terminal
VAR[i].acFollow[p]=VAR[j].acGrammar[k+1];
else if(VAR[j].acGrammar[k+1]=='\0')

//if next symbol is null, i.e variable is at the end of production
{
for(x=0;x<strlen(VAR[j].acFollow);x++)
VAR[i].acFollow[p++]=VAR[j].acFollow[x];
}

else if(isupper(VAR[j].acGrammar[k+1]))

//if next symbol is a variable
{
for(x=0;x<iGrmCount;x++)
{
if(VAR[x].acGrammar[0]==VAR[j].acGrammar[k+1])
break;
}
for(y=0;y<strlen(VAR[x].acFirst);y++)
{
if(VAR[x].acFirst[y]!='e')
VAR[i].acFollow[p++]=VAR[x].acFirst[y];
else
{
iepsilon=1;
break;
}
}
if(iepsilon==1)
{
for(z=0;z<strlen(VAR[x].acFollow);z++)
VAR[i].acFollow[p++]=VAR[j].acFollow[z];
}
}
break;
}
}
}
}


int StringParser()
{
char cstktop,cinptop;
cstktop=acstk_stack[istktop];
cinptop=acstk_input[iinptop];
printf("\n");
displayStacks();
while(cstktop!='$')
{
printf("\n");
cstktop=acstk_stack[istktop];
cinptop=acstk_input[iinptop];

if(cstktop==cinptop)

//if stack top is same as input top match the input symbol
{
acstk_matched[++imtchtop]=cinptop;

//push the matched input symbol into matched stack
printf("Action: Match %c\n",cinptop);
istktop--; //poping from stack
iinptop--; //popping from input stack
//displayStacks();

//calling function to display stacks
}
else if(!(isupper(cstktop)) && cstktop!='e')
//if stack top symbol is a terminal then report error, input string is not accepted
return 1;
else if(CheckError(cstktop,cinptop))
//if there is no entry in parsing table for stack top and input top report error,
return 1;
//input string is not accepted
else
{
for(i=0;i<iGrmCount;i++)
{
if(VAR[i].acGrammar[0]==cstktop)
{
if(itemp3==1 && VAR[i].acGrammar[0]==VAR[i+1].acGrammar[0])
i=i+1;
break;
}
}

for(k=0;k<VAR[i].iSymCount;k++)
//getting the production corresponding to non terminal on top of stack and
{
//terminal on top of input stack
if(VAR[i].actable[k][0]==cinptop)
{
printf("Action: Output production ");
for(l=1;l<strlen(VAR[i].actable[k]);l++)
printf("%c",VAR[i].actable[k][l]);
break;
}
}
printf("\n");
istktop--;
//Popping the stack
if(VAR[i].actable[k][l-1]!='e')
{
strreverse(actemp,VAR[i].actable[k]);
//Pushing into stack
for(l=0;actemp[l]!='>';l++)
acstk_stack[++istktop]=actemp[l];
}
//displayStacks();
}
cstktop=acstk_stack[istktop];
if(cstktop=='$')
	return 0;
}
}

int CheckError(char cstktop,char cinptop)
{
int ErrorFound;
ErrorFound=1;
itemp3=0;
for(i=0;i<iGrmCount;i++)
{
if(VAR[i].acGrammar[0]==cstktop)
break;
}
itemp2=i;
for(j=0;j<strlen(VAR[i].symbol);j++)
{
if(itemp3!=1)
i=itemp2;
if(VAR[i].symbol[j]==cinptop)
//if there is an entry in parsing table corresponding to current stack top and input top.
{
//then no error is found
ErrorFound=0;
break;
}
if(ErrorFound==1)
{
if(VAR[i].acGrammar[0]==VAR[i+1].acGrammar[0])
{ i=i+1;
if(VAR[i].symbol[j]==cinptop)
{
ErrorFound=0;
itemp3=1;
break;
}
}
}
}
return ErrorFound;
}


void displayStacks()
{
printf("Stack: ");
for(i=0;i<=istktop;i++)
//Displaying stack
printf("%c",acstk_stack[i]);
printf("\n");
printf("Input: ");
for(i=0;i<=iinptop;i++)
//Displaying input stack
printf("%c",acstk_input[i]);
printf("\n");
printf("Matched: ");
//Displaying matched stack
for(i=0;i<=imtchtop;i++)
printf("%c",acstk_matched[i]);
printf("\n");
}


void strreverse(char dest[5],char src[5])

{
int x,y=0;
for(x=strlen(src)-1;x>0;x--,y++)
dest[y]=src[x];
}
