#include <iostream>
#include <string>
#include <algorithm>

using namespace std;
string permutation(string temp);
int find_max(string temp);
int find_swap(string temp, string front_max, string max);
void main()
{
	string *input_string;
	string *temp;
	int number;

	cout<<"---------------input----------------"<<endl;
	cin>>number;

	input_string = new string[number];
	temp = new string[number];
	
	for(int i=0;i<number;i++)
	{
		cin>>input_string[i];
	}
	cout<<"---------------output----------------"<<endl;
	for(int i=0;i<number;i++)
	{
		temp[i] = permutation(input_string[i]);
		if(temp[i] == input_string[i])
			cout<<"no answer"<<endl;
		else
		cout<<temp[i]<<endl;
	}
}

string permutation(string input_string)
{
	int index_max, index_first, index_last;
	string str_left, str_max, str_right;
	string output_string;
	string temp_left, temp_right;
	string temp;
	index_max = find_max(input_string);
	index_last = input_string.size()-1;
	index_first = 0;

	
	if(input_string.size() >3 && input_string[input_string.size()-2]<input_string[input_string.size()-1])
	{
		swap(input_string[input_string.size()-2],input_string[input_string.size()-1]);
		
		return input_string;

	}


	if(input_string.size() == 0 || input_string.size() == 1) // string사이즈가 0 혹은 1일때
		return input_string;
	else if(input_string.size() == 2) // string 사이즈가 2일때
	{
		if(input_string[0] < input_string[1]) //첫번째 원소보다 두번째원소가 더클때
			swap(input_string[0],input_string[1]); //자리를 바꿈
		return input_string; 
	}

	str_left = input_string.substr(index_first,index_max);
	str_max = input_string[index_max];
	str_right = input_string.substr(index_max+1);

	if(index_max == index_first)
	{
		str_right = permutation(str_right);
		output_string = str_max + str_right;
	}
	else if(index_max == index_last)
	{
		if(str_left[index_max-1]!=str_max[0])
		{
			swap(str_left[index_max-1],str_max[0]);
			output_string = str_left+str_max;
		}
		else
		{
			
			for(int a=index_max ; a>=0 ; a--)
			{
				if(input_string[a] != input_string[index_max])
				{
					swap(input_string[a],input_string[index_max]);
					index_max = a;
					str_left = input_string.substr(index_first,index_max);
					str_max = input_string[index_max];
					str_right = input_string.substr(index_max+1);
					reverse(str_right.begin(), str_right.end());
					break;
				}
			}
			output_string = str_left+str_max+str_right;
		}
	}
	else
	{
		
		temp = permutation(str_right);
		if(temp != str_right)
		{
			str_right = temp;
			output_string = str_left+str_max+str_right;
		}
		else if(temp == str_right)
		{
			int check=0;
			int swap_index = find_swap(str_right, str_left,str_max);
			if( swap_index == -1)
				swap(str_left[index_max-1],str_max[0]);
			else
				swap(str_left[index_max-1],str_right[swap_index]);
			if(str_right[0]<str_max[0])
			{
				temp = str_max + str_right;
				reverse(temp.begin(),temp.end());
				output_string = str_left + temp;
				check = 1;
			}
			
			if(check == 0)
			{
				
				for(int i = 0 ; i<str_right.size() ; i++)
				{
					if(str_right[i] > str_max[0] && str_right[i+1] <= str_max[0])
					{
						
						temp_left=str_right.substr(0,i+1);
						temp_right=str_max+str_right.substr(i+1);
						str_right = temp_left+temp_right;
						reverse(str_right.begin(),str_right.end());
						break;
					}
				}
				output_string = str_left + str_right;
			}
		}	
	}
	return output_string;
	
}
int find_max(string temp)
{
	int pre=0, now=0;
	for(int i=0; i<temp.size() ;i++)
	{
		now = i;
		if(temp.at(pre) <= temp.at(now))
			pre = now;
	}
	return pre;
}
int find_swap(string temp, string front_max, string max)
{
	int pre=-1, now;
	
	for(int i=0; i<temp.size() ;i++)
	{
		
		if(temp[i] > front_max[0] && temp[i] < max[0])
		{
			now = i;
			if(i==0)
				pre = now;
			else if(temp.at(pre) > temp.at(now))
				pre = now;
		}
	}
	return pre;
}