#include "pch.h"
#include "CppUnitTest.h"
#include "..\..\OOP_1\program.h"
#include "..\..\OOP_1\program.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace type_plants;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		// Тест функции заполнения контейнера "container_Fill"
		TEST_METHOD(Test_Container_Fill_Empty)
		{
			ifstream ifst("In_Empty.txt");	// Пустой входной файл
			container c;
			c.container_Fill(ifst);
			ifst.close();

			Assert::AreEqual(c.size, 0);
			c.container_Clear();
		}
		
		// Тест функции container_Fill()
		TEST_METHOD(Test_Container_Fill_4_elem)
		{
			ifstream ifst("In_4_elem.txt"); // Входной файл, содержащий 4 элемента
			container c;
			c.container_Fill(ifst);
			ifst.close();

			ifstream input_file("In_4_elem.txt");
			int count_string = 0;
			while (input_file.ignore(numeric_limits<streamsize>::max(), '\n'))
			{
				if (!input_file.eof())
					count_string++;
			}
			count_string = count_string + 1;

			input_file.close();

			Assert::AreEqual(c.size, count_string / 4);
			c.container_Clear();
		}
		
		// Тест функции container_Clear()
		TEST_METHOD(Test_container_Clear_Empty)
		{
			ifstream ifst("In_Empty.txt"); // Пустой входной файл
			container c;
			c.container_Fill(ifst);
			c.container_Clear();
			ifst.close();

			Assert::AreEqual(c.size, 0);
		}

		// Тест функции container_Clear()
		TEST_METHOD(Test_container_Clear_4_elem)
		{
			ifstream ifst("In_4_elem.txt"); // Входной файл, содержащий 4 элемента
			container c;
			c.container_Fill(ifst);
			c.container_Clear();
			ifst.close();

			Assert::AreEqual(c.size, 0);
		}

		int Compare(ifstream& ifst_1, ifstream& ifst_2)
		{
			char c1, c2;
			int pos = -1;
			while (ifst_1.get(c1) && ifst_2.get(c2))
			{
				pos++;
				if (c1 != c2)
				{
					return pos;
				}
			}
			return -1;
		}

		// Тест функции container_Output()
		TEST_METHOD(Test_container_Output_4_elem)
		{
			ifstream ifst("In_4_elem.txt"); // Входной файл, содержащий 4 элемента
			ofstream ofst("Out_4_elem.txt");
			container c;
			c.container_Fill(ifst);
			c.container_Clear();
			ifst.close();
			ofst.close();

			ifstream pattern("Pattern_Out_4_elem.txt");
			ifstream current("Out_4_elem.txt");
			int res = Compare(current, pattern);
			pattern.close();
			current.close();

			Assert::AreEqual(res + 1, 0);
		}
		
		// Проверка поведения при наличии пустых строк между растениями
		TEST_METHOD(Test_input_Plants_empty_lines)
		{
			ifstream ifst("In_Plants_empty_lines.txt"); //В файле 6 растений с пустыми строками между ними
			ofstream ofst("Out_Plants_empty_lines.txt");
			container c;
			c.container_Fill(ifst);
			c.container_Output(ofst);
			ifst.close();
			ofst.close();

			Assert::AreEqual(c.size, 6);
			c.container_Clear();
		}
		
		
		// Если поля во входном файле сдвинуты
		TEST_METHOD(Test_input_Plants_shift)
		{
			ifstream ifst("In_Plants_shift.txt"); // В файле 1 растение со сдвинутыми полями
			ofstream ofst("Out_Plants_shift.txt");
			container c;
			c.container_Fill(ifst);
			c.container_Output(ofst);
			ifst.close();
			ofst.close();

			Assert::AreEqual(c.size, 1);
			c.container_Clear();
		}

		// Тест функции sort()
		TEST_METHOD(Test_sort_4_elem)
		{
			ifstream ifst("In_4_elem.txt"); // Входной файл, содержащий 4 элемента
			ofstream ofst("Out_sort_4_elem.txt");
			container c;
			c.container_Fill(ifst);
			c.sort();
			c.container_Output(ofst);
			ifst.close();
			ofst.close();

			ifstream input_file("In_4_elem.txt");
			int count_string = 0;
			while (input_file.ignore(numeric_limits<streamsize>::max(), '\n'))
			{
				if (!input_file.eof())
					count_string++;
			}
			count_string = count_string + 1;

			input_file.close();

			Assert::AreEqual(c.size, count_string / 4);
			c.container_Clear();
		}

		// Тест функции sort()
		TEST_METHOD(Test_sort_1_elem)
		{
			ifstream ifst("In_1_elem.txt"); // Входной файл, содержащий 1 элемент
			ofstream ofst("Out_sort_1_elem.txt");
			container c;
			c.container_Fill(ifst);
			c.sort();
			c.container_Output(ofst);
			ifst.close();
			ofst.close();

			Assert::AreEqual(c.size, 1);
			c.container_Clear();
		}

		// Тест функции sort() 
		TEST_METHOD(Test_sort_2_elem)
		{
			ifstream ifst("In_2_elem.txt"); // Входной файл, содержащий 2 элемента
			ofstream ofst("Out_sort_2_elem.txt");
			container c;
			c.container_Fill(ifst);
			c.sort();
			c.container_Output(ofst);
			ifst.close();
			ofst.close();

			Assert::AreEqual(c.size, 2);
			c.container_Clear();
		}
		
		// Проверка функции number_consonants() в случае отсутсвия согласных букв в названии растения
		TEST_METHOD(Test_number_consonants_0)
		{
			ifstream ifst("In_number_consonants_0.txt"); // В названии растения нет согласных букв
			ofstream ofst("Out_number_consonants_0.txt");
			container c;
			c.container_Fill(ifst);
			c.container_Output(ofst);
			c.container_Clear();
			ifst.close();
			ofst.close();

			ifstream input_file("Out_number_consonants_0.txt");
			string s;
			while (input_file.peek() != EOF)
			{
				getline(input_file, s);
			}
			input_file.close();
			s = s[s.length() - 2];

			Assert::AreEqual(atoi(s.c_str()), 0);
		}

		// Проверка функции number_consonants() в случае одной согласной буквы в названии растения
		TEST_METHOD(Test_number_consonants_1)
		{
			ifstream ifst("In_number_consonants_1.txt"); // В названии растения 1 согласная буква
			ofstream ofst("Out_number_consonants_1.txt");
			container c;
			c.container_Fill(ifst);
			c.container_Output(ofst);
			c.container_Clear();
			ifst.close();
			ofst.close();

			ifstream input_file("Out_number_consonants_1.txt");
			string s;
			while (input_file.peek() != EOF)
			{
				getline(input_file, s);
			}
			input_file.close();
			s = s[s.length() - 2];

			Assert::AreEqual(atoi(s.c_str()), 1);
		}

		// Проверка функции number_consonants() в случае четырех согласных букв в названии растения
		TEST_METHOD(Test_number_consonants_4)
		{
			ifstream ifst("In_number_consonants_4.txt"); // В названии растения 4 согласных буквы
			ofstream ofst("Out_number_consonants_4.txt");
			container c;
			c.container_Fill(ifst);
			c.container_Output(ofst);
			c.container_Clear();
			ifst.close();
			ofst.close();

			ifstream input_file("Out_number_consonants_4.txt");
			string s;
			while (input_file.peek() != EOF)
			{
				getline(input_file, s);
			}
			input_file.close();
			s = s[s.length() - 2];

			Assert::AreEqual(atoi(s.c_str()), 4);
		}
		
		// Тест функции Output_only_tree() для пустого контейнера
		TEST_METHOD(Test_Output_only_tree_Empty)
		{
			ifstream ifst("In_Empty.txt"); // Пустой входной файл
			ofstream ofst("Out_only_tree_Empty.txt");
			container c;
			c.container_Fill(ifst);
			c.Output_only_tree(ofst);
			c.container_Clear();
			ifst.close();
			ofst.close();

			ifstream input_file("Out_only_tree_Empty.txt");

			int count_string = 0;
			while (input_file.ignore(numeric_limits<streamsize>::max(), '\n'))
			{
				if (!input_file.eof())
					count_string++;
			}
			count_string = count_string + 1;

			input_file.close();

			Assert::AreEqual((count_string - 1) / 4, 0);
		}


		// Тест функции Output_only_tree() без деревьев в контейнере
		TEST_METHOD(Test_Output_only_tree_Without_tree)
		{
			ifstream ifst("In_Without_tree.txt"); // Входной файл, содержащий 2 элемента
			ofstream ofst("Out_only_tree_Without_tree.txt");
			container c;
			c.container_Fill(ifst);
			c.Output_only_tree(ofst);
			c.container_Clear();
			ifst.close();
			ofst.close();

			ifstream input_file("Out_only_tree_Without_tree.txt");
			int count_string = 0;
			while (input_file.ignore(numeric_limits<streamsize>::max(), '\n'))
			{
				if (!input_file.eof())
					count_string++;
			}
			count_string = count_string + 1;

			input_file.close();

			Assert::AreEqual((count_string - 2) / 4, 0);
		}
	};
}