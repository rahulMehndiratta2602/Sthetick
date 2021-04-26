//Sthetick
//G61
//Kartikey Papnai 2018A7PS0228H
//Rahul Mehendiratta 2017A7PS1479H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
// Returns 'true' if the character is a DELIMITER.
int lineNo = 1;
struct Err
{
	char str[100];
	int lineNo;
	struct Err *next;
};
struct Err *head;
void InsertError(char *str, int lineNo)
{
	struct Err *temp = (struct Err *)malloc(sizeof(struct Err));
	strcpy(temp->str, str);

	temp->lineNo = lineNo;
	temp->next = NULL;
	if (head == NULL)
		head = temp;
	else
	{
		struct Err *counter = head;
		while (counter->next != NULL)
			counter = counter->next;
		counter->next = temp;
	}
}
bool isDelimiter(char ch)
{
	if (ch == ' ' || ch == '\n' || ch == '+' || ch == '-' || ch == '*' || ch == '@' || //@ is for comments
		ch == '/' || ch == ',' || ch == ';' || ch == '>' ||
		ch == '<' || ch == '=' || ch == '(' || ch == ')' ||
		ch == '[' || ch == ']' || ch == '{' || ch == '}' || ch == '"' || ch == '!' || ch == '&' || ch == '|' || ch == '%')
		return (true);
	return (false);
}
// Returns 'true' if the character is a bracket.
bool isBracket(char ch)
{
	if (ch == '{' || ch == '}' || ch == '(' || ch == ')' || ch == '[' || ch == ']')
		return true;
	return false;
}
bool isAssignmentOperator(char ch)
{
	if (ch == '=')
		return true;
	return false;
}
bool isLessGreaterOperator(char ch)
{
	if (ch == '<' || ch == '>')
		return true;
	return false;
}
bool isRelationalOperator(char *str)
{
	if (!strcmp(str, "==") || !strcmp(str, "!=") || !strcmp(str, ">=") || !strcmp(str, "<="))
		return true;
	return false;
}
bool isLogicalOperator(char ch)
{
	if (ch == '!' || ch == '&' || ch == '|')
		return true;
	return false;
}
// Returns 'true' if the character is an OPERATOR.
bool isArithmeticOperator(char ch)
{
	if (ch == '+' || ch == '-' || ch == '*' ||
		ch == '/' || ch == '%')
		return (true);
	return (false);
}

// Returns 'true' if the string is a VALID IDENTIFIER.
bool validIdentifier(char *str)
{
	int valid = 0;
	if (isalpha(str[0]) || (str[0] == '_') || str[0] == '$')
	{
		if (strlen(str) == 1)
			return true;
		int i = 1;
		while (i < strlen(str))
		{
			if (isalpha(str[i]) || (str[i] == '_') || str[i] == '$' || isdigit(str[i]))
				valid = 1;
			else
			{
				valid = 0;
				break;
			}
			i++;
		}
	}
	return (valid == 1);
}

// Returns 'true' if the string is a KEYWORD.
bool isKeyword(char *str)
{
	if (!strcmp(str, "if") || !strcmp(str, "else") ||
		!strcmp(str, "while") || !strcmp(str, "do") ||
		!strcmp(str, "break") ||
		!strcmp(str, "continue") || !strcmp(str, "int") || !strcmp(str, "double") || !strcmp(str, "float") || !strcmp(str, "return") || !strcmp(str, "char") || !strcmp(str, "case") || !strcmp(str, "char") || !strcmp(str, "sizeof") || !strcmp(str, "long") || !strcmp(str, "short") || !strcmp(str, "typedef") || !strcmp(str, "switch") || !strcmp(str, "unsigned") || !strcmp(str, "void") || !strcmp(str, "static") || !strcmp(str, "struct") || !strcmp(str, "goto"))
		return (true);
	return (false);
}
// Returns 'true' if the string is an INTEGER.
bool isInteger(char *str)
{
	int i, len = strlen(str);

	if (len == 0)
		return (false);
	for (i = 0; i < len; i++)
	{
		if (str[i] != '0' && str[i] != '1' && str[i] != '2' && str[i] != '3' && str[i] != '4' && str[i] != '5' && str[i] != '6' && str[i] != '7' && str[i] != '8' && str[i] != '9' || (str[i] == '-' && i > 0))
			return (false);
	}
	return (true);
}

// Returns 'true' if the string is a REAL NUMBER.
bool isRealNumber(char *str)
{
	int i, len = strlen(str);
	bool hasDecimal = false;

	if (len == 0)
		return (false);
	for (i = 0; i < len; i++)
	{
		if (str[i] != '0' && str[i] != '1' && str[i] != '2' && str[i] != '3' && str[i] != '4' && str[i] != '5' && str[i] != '6' && str[i] != '7' && str[i] != '8' && str[i] != '9' && str[i] != '.' ||
			(str[i] == '-' && i > 0))
			return (false);
		if (str[i] == '.')
			hasDecimal = true;
	}
	return (hasDecimal);
}

// Extracts the SUBSTRING.
char *subString(char *str, int left, int right)
{
	int i;
	char *subStr = (char *)malloc(
		sizeof(char) * (right - left + 2));

	for (i = left; i <= right; i++)
		subStr[i - left] = str[i];
	subStr[right - left + 1] = '\0';
	return (subStr);
}

void tokenize(char *str)
{
	bool invalid = false;
	head = NULL;
	FILE *ptr = fopen("output2.txt", "w");
	int left = 0, right = 0;
	int len = strlen(str);
	// fprintf(ptr,"%s",str);

	while (right <= len && left <= right)
	{
		if (isDelimiter(str[right]) == false)
			right++;

		if (isDelimiter(str[right]) == true && left == right)
		{
			if (str[right] == '\n')
				lineNo++;
			if (str[right] == '@')
			{
				while (right <= len && str[right] != '\n')
					right++;
				lineNo++;
			}
			if (isBracket(str[right]) == true)
				fprintf(ptr, "'%c' is a BRACKET on lineno %d\n", str[right], lineNo);
			else if (isArithmeticOperator(str[right]) == true)
				fprintf(ptr, "'%c' is an ARITHMETIC OPERATOR on lineno %d\n", str[right], lineNo);
			else if (isAssignmentOperator(str[right]) == true)
			{
				//handling == case
				char *subStr = subString(str, right, right + 1);
				if (isRelationalOperator(subStr))
				{
					fprintf(ptr, "'%s' is a RELATIONAL OPERATOR on lineno %d\n", subStr, lineNo);
					right++;
					left = right;
				}
				else
					fprintf(ptr, "'%c' is an ASSIGNMENT_OPERATOR on lineno %d\n", str[right], lineNo);
			}
			else if (str[right] == '!')
			{
				//handling != case
				char *subStr = subString(str, right, right + 1);
				if (isRelationalOperator(subStr))
				{
					fprintf(ptr, "'%s' is a RELATIONAL OPERATOR on lineno %d\n", subStr, lineNo);
					right++;
					left = right;
				}
				else
					fprintf(ptr, "'%c' is a LOGICAL OPERATOR on lineno %d\n", str[right], lineNo);
			}
			else if (isLessGreaterOperator(str[right]))
			{
				//handling <=,>= case
				char *subStr = subString(str, right, right + 1);
				if (isRelationalOperator(subStr))
				{
					fprintf(ptr, "'%s' is a RELATIONAL OPERATOR on lineno %d\n", subStr, lineNo);
					right++;
					left = right;
				}
				else
				{
					fprintf(ptr, "'%c' is a RELATIONAL OPERATOR on lineno %d\n", str[right], lineNo);
				}
			}
			right++;
			left = right;
		}
		else if (isDelimiter(str[right]) == true && left != right || (right == len && left != right))
		{
			char *subStr = subString(str, left, right - 1);

			if (isKeyword(subStr) == true)
				fprintf(ptr, "'%s' is a KEYWORD on lineno %d\n", subStr, lineNo);

			else if (isInteger(subStr) == true)
				fprintf(ptr, "'%s' is an INTEGER on lineno %d\n", subStr, lineNo);

			else if (isRealNumber(subStr) == true)
				fprintf(ptr, "'%s' is a REAL NUMBER on lineno %d\n", subStr, lineNo);

			else if (validIdentifier(subStr) == true && isDelimiter(str[right - 1]) == false)
				fprintf(ptr, "'%s' is an IDENTIFIER on lineno %d\n", subStr, lineNo);

			else if (validIdentifier(subStr) == false && isDelimiter(str[right - 1]) == false)
			{
				// FILE * ptr2 = freopen(NULL,"w",ptr);
				// fprintf(ptr2,"'%s' IS NOT A VALID IDENTIFIER on lineno %d\n", subStr,lineNo);
				invalid = true;
				fprintf(ptr, "'%s' is error on lineno %d\n", subStr, lineNo);
				InsertError(subStr, lineNo);
			}
			left = right;
		}
	}
	if (invalid == true)
	{
		FILE *ptr2 = freopen(NULL, "w", ptr);
		struct Err *temp = head;
		while (temp != NULL)
		{
			if (strlen(temp->str) == 1)
				fprintf(ptr2, "Lexical Error in line No %d.'%c' is not a valid symbol\n", temp->lineNo, temp->str[0]);
			else
				fprintf(ptr2, "Lexical Error in line No %d.'%s' is not a valid identifier\n", temp->lineNo, temp->str);
			temp = temp->next;
		}
	}
	fclose(ptr);
	return;
}
char *inputString(FILE *fp, size_t size)
{
	//The size is extended by the input with the value of the provisional
	char *str;
	int ch;
	size_t len = 0;
	str = realloc(NULL, sizeof(*str) * size); //size is start size
	if (!str)
		return str;
	while (EOF != (ch = fgetc(fp)))
	{
		str[len++] = ch;
		if (len == size)
		{
			str = realloc(str, sizeof(*str) * (size += 16));
			if (!str)
				return str;
		}
	}
	str[len++] = '\0';

	return realloc(str, sizeof(*str) * len);
}

int main(void)
{
	char *m;
	m = inputString(fopen("C:\Users\mandy\OneDrive\Desktop\Sthetick\Sthetick\Lexical Analyser\testcases\testcase4.txt", "r"), 100000);
	// printf("%s\n", m);
	tokenize(m);
	free(m);
	return 0;
}
