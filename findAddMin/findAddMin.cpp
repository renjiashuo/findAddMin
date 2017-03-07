#include <iostream>
#include <vector>
#include <cstdarg>
#include <algorithm>
#include <map>

using namespace std;

class findAddMin
{
private:
	double youhuiquan;		// �Ż�ȯ���
	double minSum;		// ��Ʒ�۸������Сֵ
	map<double, vector<string> > goods;	// ��Ʒ�۸񼯺�
	vector<double> combination;			// һ�����
	map<vector<double>, int> combinations;	// ���е����
public:
	// ���캯���������Ż�ȯ���
	findAddMin(double youhuiquan)
	{
		this->youhuiquan = youhuiquan;
	}
	// ����һ����Ʒ�۸�
	void add(double good,string str)
	{
		if (goods.find(good) == goods.end())
		{
			vector<string> strs;
			strs.push_back(str);
			goods.insert(make_pair(good, strs));
		}
		else
		{
			goods[good].push_back(str);
		}
	}
	// ����һЩ��Ʒ�۸񣬵�һ������Ϊһ�������ӵ���Ʒ����������Ĳ���Ϊ��Щ��Ʒ�ļ۸�
	void add(int good, ...)
	{
		va_list ap;
		va_start(ap, good);
		for (int i = 0; i < good; ++i)
		{
			double temp = va_arg(ap, double);
			if (goods.find(temp) == goods.end())
			{
				vector<string> strs;
				goods.insert(make_pair(temp, strs));
			}
		}
	}
	// �ҳ���Ʒ��ϼ۸�����Ż�ȯ����Сֵ
	void findMin(double sum)
	{
		for (map<double, vector<string> >::iterator iter = goods.begin(); iter != goods.end(); iter++)
		{
			double good = iter->first;
			if (sum + good > youhuiquan + 0.001)
			{
				if (sum + good < minSum)
				{
					minSum = sum + good;
				}
			}
			else
			{
				findMin(sum + good);
			}
		}
	}
	// ����Щ��Ʒ�ļ۸�ֱ����
	bool printEvery(double sum,double partMinSum, bool value)
	{
		//if (value)
		//	return value;
		for (map<double, vector<string> >::iterator iter = goods.begin(); iter != goods.end(); iter++)
		{
			if (value)
				return value;
			double good = iter->first;
			vector<string> names = iter->second;
			if (sum + good < partMinSum + 0.1)
			{
				if (sum + good == partMinSum)
				{
					combination.push_back(good);
					//cout << "����һ��" << good << "Ԫ��";
					//for (int i = 0; i < names.size(); i++)
					//{
					//	cout << "��" << names[i].c_str() << "��";
					//	if (i != names.size() - 1)
					//		cout << "/";
					//}
					//cout << endl;
					partMinSum = sum;
					if (partMinSum < 0.001)
					{
						value = true;
						//cout << "�ܻ���" << minSum << "Ԫ" << endl;
						//sort(combination.begin(), combination.end());
						//if (combinations.find(combination) == combinations.end())
						//	value = true;
						//else
						//	combination.pop_back();
					}
					else
					{
						value = printEvery(0, partMinSum, value);
						if (value)
							return value;
					}
				}
				else
				{
					value = printEvery(sum + good, partMinSum, value);
					//if (value)
					//	return value;
				}
			}
			//if (iter == --goods.end() && combination.size() != 0)
			//	combination.pop_back();
		}
	}
	// �㷨��ں���
	void letsFind()
	{
		combination.clear();
		combinations.clear();
		minSum = youhuiquan * 10;
		findMin(0);
		int combinationsMount = combinations.size();

		// ����������
		//while (true)
		//{
		//	printEvery(0, minSum, false);
		//	sort(combination.begin(), combination.end());
		//	if (combinations.find(combination) == combinations.end())
		//		combinations.insert(make_pair(combination, combinations.size()+1));
		//	combination.clear();
		//	if (combinations.size() == combinationsMount)
		//		break;
		//	else
		//		combinationsMount++;
		//}

		// ����������
		printEvery(0, minSum, false);
		sort(combination.begin(), combination.end());
		combinations.insert(make_pair(combination, combinations.size() + 1));
		for (map<vector<double>, int>::iterator iter = combinations.begin(); iter != combinations.end(); iter++)
		{
			vector<double> com = iter->first;
			double sum = 0;
			for (int i = 0; i < com.size(); i++)
			{
				cout << com[i] << endl;
				sum += com[i];
			}
			cout << "sum = " << sum << endl;
		}
	}
};

int main()
{
	findAddMin example(50);
	//example.add(20, 13.9, 15.9, 19.9, 13.9, 23.25, 17.25, 28.24, 15.81, 25.62, 19.49, 23.49, 29.87, 21.31, 32.24, 22.24, 26.81, 33.68, 24.25, 28.18, 34.37);
	//example.add(21, 15.9, 22.23, 27.19, 18.5, 23.83, 29.98, 20.17, 24.57, 33.05, 24.92, 31.44, 37.73, 22.82, 27.49, 34.94, 26.03, 31.37, 39.41, 28.37, 32.98, 40.21);
	//example.add(19, 119.9, 19.9, 22.95, 27.18, 28.29, 32.39, 34.63, 19.9, 30.86, 28.08, 32.03, 27.71, 31.56, 29.76, 33.61, 32.14, 35.99, 34.3, 38.22);
	//example.add(45.0,"");

	example.add(11, 13.9, 15.9, 18.8, 19.9, 26.0, 28.0, 29.0, 39.0, 46.0, 49.0, 56.0);

	//example.add(4, 24.0, 27.0, 23.0, 28.0);
	example.letsFind();

	return 0;
}