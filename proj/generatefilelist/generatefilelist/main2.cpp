#include "stdafx.h"
using namespace std;

#include<time.h>
#include<stdlib.h>
#include<stdio.h>

vector<wstring> vctLastName{ L"赵", L"钱", L"孙", L"李", L"周", L"吴", L"郑", L"王",
L"冯", L"陈", L"楮", L"卫", L"蒋", L"沈", L"韩", L"杨",
L"朱", L"秦", L"尤", L"许", L"何", L"吕", L"施", L"张",
L"孔", L"曹", L"严", L"华", L"金", L"魏", L"陶", L"姜",
L"戚", L"谢", L"邹", L"喻", L"柏", L"水", L"窦", L"章",
L"云", L"苏", L"潘", L"葛", L"奚", L"范", L"彭", L"郎",
L"鲁", L"韦", L"昌", L"马", L"苗", L"凤", L"花", L"方",
L"俞", L"任", L"袁", L"柳", L"酆", L"鲍", L"史", L"唐",
L"费", L"廉", L"岑", L"薛", L"雷", L"贺", L"倪", L"汤",
L"滕", L"殷", L"罗", L"毕", L"郝", L"邬", L"安", L"常",
L"乐", L"于", L"时", L"傅", L"皮", L"卞", L"齐", L"康",
L"伍", L"余", L"元", L"卜", L"顾", L"孟", L"平", L"黄",
L"和", L"穆", L"萧", L"尹", L"姚", L"邵", L"湛", L"汪",
L"祁", L"毛", L"禹", L"狄", L"米", L"贝", L"明", L"臧",
L"计", L"伏", L"成", L"戴", L"谈", L"宋", L"茅", L"庞",
L"熊", L"纪", L"舒", L"屈", L"项", L"祝", L"董", L"梁",
L"杜", L"阮", L"蓝", L"闽", L"席", L"季", L"麻", L"强",
L"贾", L"路", L"娄", L"危", L"江", L"童", L"颜", L"郭",
L"梅", L"盛", L"林", L"刁", L"锺", L"徐", L"丘", L"骆",
L"高", L"夏", L"蔡", L"田", L"樊", L"胡", L"凌", L"霍",
L"虞", L"万", L"支", L"柯", L"昝", L"管", L"卢", L"莫",
L"经", L"房", L"裘", L"缪", L"干", L"解", L"应", L"宗",
L"丁", L"宣", L"贲", L"邓", L"郁", L"单", L"杭", L"洪",
L"包", L"诸", L"左", L"石", L"崔", L"吉", L"钮", L"龚",
L"程", L"嵇", L"邢", L"滑", L"裴", L"陆", L"荣", L"翁",
L"荀", L"羊", L"於", L"惠", L"甄", L"麹", L"家", L"封",
L"芮", L"羿", L"储", L"靳", L"汲", L"邴", L"糜", L"松",
L"井", L"段", L"富", L"巫", L"乌", L"焦", L"巴", L"弓",
L"牧", L"隗", L"山", L"谷", L"车", L"侯", L"宓", L"蓬",
L"全", L"郗", L"班", L"仰", L"秋", L"仲", L"伊", L"宫",
L"宁", L"仇", L"栾", L"暴", L"甘", L"斜", L"厉", L"戎",
L"祖", L"武", L"符", L"刘", L"景", L"詹", L"束", L"龙",
L"叶", L"幸", L"司", L"韶", L"郜", L"黎", L"蓟", L"薄",
L"印", L"宿", L"白", L"怀", L"蒲", L"邰", L"从", L"鄂",
L"索", L"咸", L"籍", L"赖", L"卓", L"蔺", L"屠", L"蒙",
L"池", L"乔", L"阴", L"鬱", L"胥", L"能", L"苍", L"双",
L"闻", L"莘", L"党", L"翟", L"谭", L"贡", L"劳", L"逄",
L"姬", L"申", L"扶", L"堵", L"冉", L"宰", L"郦", L"雍",
L"郤", L"璩", L"桑", L"桂", L"濮", L"牛", L"寿", L"通",
L"边", L"扈", L"燕", L"冀", L"郏", L"浦", L"尚", L"农",
L"温", L"别", L"庄", L"晏", L"柴", L"瞿", L"阎", L"充",
L"慕", L"连", L"茹", L"习", L"宦", L"艾", L"鱼", L"容",
L"向", L"古", L"易", L"慎", L"戈", L"廖", L"庾", L"终",
L"暨", L"居", L"衡", L"步", L"都", L"耿", L"满", L"弘",
L"匡", L"国", L"文", L"寇", L"广", L"禄", L"阙", L"东",
L"欧", L"殳", L"沃", L"利", L"蔚", L"越", L"夔", L"隆",
L"师", L"巩", L"厍", L"聂", L"晁", L"勾", L"敖", L"融",
L"冷", L"訾", L"辛", L"阚", L"那", L"简", L"饶", L"空",
L"曾", L"毋", L"沙", L"乜", L"养", L"鞠", L"须", L"丰",
L"巢", L"关", L"蒯", L"相", L"查", L"后", L"荆", L"红",
L"游", L"竺", L"权", L"逑", L"盖", L"益", L"桓", L"公",
L"万俟", L"司马", L"上官", L"欧阳",
L"夏侯", L"诸葛", L"闻人", L"东方",
L"赫连", L"皇甫", L"尉迟", L"公羊",
L"澹台", L"公冶", L"宗政", L"濮阳",
L"淳于", L"单于", L"太叔", L"申屠",
L"公孙", L"仲孙", L"轩辕", L"令狐",
L"锺离", L"宇文", L"长孙", L"慕容",
L"鲜于", L"闾丘", L"司徒", L"司空",
L"丌官", L"司寇", L"仉", L"督", L"子车",
L"颛孙", L"端木", L"巫马", L"公西",
L"漆雕", L"乐正", L"壤驷", L"公良",
L"拓拔", L"夹谷", L"宰父", L"谷梁",
L"晋", L"楚", L"阎", L"法", L"汝", L"鄢", L"涂", L"钦",
L"段干", L"百里", L"东郭", L"南门",
L"呼延", L"归", L"海", L"羊舌", L"微生",
L"岳", L"帅", L"缑", L"亢", L"况", L"後", L"有", L"琴",
L"梁丘", L"左丘", L"东门", L"西门",
L"商", L"牟", L"佘", L"佴", L"伯", L"赏", L"南宫",
L"墨", L"哈", L"谯", L"笪", L"年", L"爱", L"阳", L"佟" };

std::wstring RandomName()
{
	static int addl = 0;
	addl++;
	wstring name;

	srand((int)time(0) + addl);
	
	int j = 1 + (int)((float)vctLastName.size()*rand() / (RAND_MAX + 1.0));

	name += vctLastName[j];
	wcout << j << endl;

	for (size_t i = 0; i < 2; i++)
	{
		wchar_t chChinese{ 0 };
		do
		{
			wchar_t x1 = 0x4e + (int)((float)(0x9f - 0x4e)*rand() / (RAND_MAX + 1.0));
			wchar_t x2 = 0x00 + (int)((float)(0xff - 0x00)*rand() / (RAND_MAX + 1.0));
			chChinese |= x1;
			chChinese <<= 8;
			chChinese |= x2;
		} while (chChinese > 0x9fa5 || chChinese < 0x4e00);

		name += chChinese;
	}
	
	return name;
};
/*
int main()
{
	locale &loc = locale::global(locale(locale(), "", LC_CTYPE));
	wcout << RandomName() << endl;
	wcout << RandomName() << endl;
	wcout << RandomName() << endl;
	wcout << RandomName() << endl;
	wcout << RandomName() << endl;
	wcout << RandomName() << endl;
	wcout << RandomName() << endl;
	wcout << RandomName() << endl;
	wcout << RandomName() << endl;
	wcout << RandomName() << endl;
	wstring name;
	wcin >> name;
	return 0;
	}*/