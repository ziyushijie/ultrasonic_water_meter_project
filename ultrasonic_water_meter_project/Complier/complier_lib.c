#include "complier_lib.h"

//===每个月的天数,默认是12个月，这样正好对应数组的1到12，故数组大小是13字节
const uint8_t g_month_days_table[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能:把16进制转换为BCD格式
//////输入参数:
//////输出参数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t hex_to_bcd(uint8_t hex)
{
	uint8_t _return = 0;
	_return = (hex % 10 + (hex / 10) * 16);
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 把ASCII字符转换为16进制
//////输入参数:
//////输出参数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t ascii_to_hex(uint8_t hex)
{
	if ((hex >= 0x30) && (hex <= 0x39))
	{
		hex -= 0x30;
	}
	else if ((hex >= 0x41) && (hex <= 0x46)) // Capital
	{
		hex -= 0x37;
	}
	else if ((hex >= 0x61) && (hex <= 0x66)) //littlecase
	{
		hex -= 0x57;
	}
	else
	{
		hex = 0xff;
	} 
	return hex;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 把16进制转换为ASCII字符
//////输入参数:
//////输出参数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t hex_to_ascii(uint8_t hex)
{
	if (hex == 0)
	{
		hex += 0x30;
	}
	else if (hex <= 9)
	{
		hex += 0x30;
	}
	else if ((hex >= 10) && (hex <= 15))//Capital
	{
		hex += 0x37;
	}
	else
	{
		hex = 0xFF;
	}
	return hex;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能:把BCD格式转换为10进制
//////输入参数:
//////输出参数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t bcd_to_dec(uint8_t bcd)
{
	uint8_t _return = (bcd >> 4);
	_return = (_return * 10 + (bcd & 0x0F));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能:把10进制转换为BCD格式
//////输入参数:
//////输出参数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t dec_to_bcd(uint8_t dec)
{
	uint8_t _return = (dec / 10);
	_return = ((_return << 4) + ((dec % 10) & 0x0F));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能:
//////输入参数:
//////输出参数:
//////说		明:求解一个数据m的n次方
//////////////////////////////////////////////////////////////////////////////
uint64_t my_pow(uint16_t m, uint16_t n)
{
	uint64_t r = 0;
	uint64_t base = m;
	while (n > 0)
	{
		if ((n & 0x01) == 1)
		{
			r *= base;
		}
		base *= base;
		n >>= 1;
	}
	return base;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 冒泡升序排列数据
//////输入参数:
//////输出参数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t asc_sort_byte(uint8_t *buffer, uint16_t length)
{
	uint16_t i = 0;
	uint16_t j = 0;
	uint16_t k = length - 1;
	uint16_t m = 0;
	uint8_t flag;
	uint8_t tmp;

	//---用k来保存新的判断条件
	for (i = 0; i < k; i++)
	{
		//---flag初始化为0
		flag = 0;
		m = 0;

		//---每排序一趟，则至少有一个元素已经有序，用 j<length-i-1 可以缩小排序范围
		for (j = 0; j < (length - 1 - i); j++)
		{
			//---当前面的元素大于后面的元素时，交换位置
			if (buffer[j] > buffer[j + 1])
			{
				tmp = buffer[j];
				buffer[j] = buffer[j + 1];
				buffer[j + 1] = tmp;

				//---若程序进入if语句,则必然会发生交换，当发生交换时把flag置成 1
				flag = 1;

				//---记住最后一次交换的位置
				m = j;
			}
		}

		//---判断,如果flag=0，说明上一趟排序没有发生交换，数列已经有序，break
		if (flag == 0)
		{
			break;
		}

		//---将新的长度赋值给k
		k = m;
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能:升序排列数组
//////输入参数:
//////输出参数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t asc_sort_word(uint16_t *buffer, uint16_t length)
{
	uint16_t i = 0;
	uint16_t j = 0;
	uint16_t k = length - 1;
	//uint16_t m = 0;
	uint8_t flag;
	uint16_t tmp;

	//---用k来保存新的判断条件
	for (i = 0; i < k; i++)
	{
		//---flag初始化为0
		flag = 0;
		//假设当前趟的第一个数为最值, 记在m中
		//m = i;

		//---每排序一趟，则至少有一个元素已经有序，用 j<length-i-1 可以缩小排序范围
		for (j = 0; j < (length - 1 - i); j++)
		{
			//---当前面的元素大于后面的元素时，交换位置
			if (buffer[j] > buffer[j + 1])
			{
				tmp = buffer[j];
				buffer[j] = buffer[j + 1];
				buffer[j + 1] = tmp;

				//---若程序进入if语句,则必然会发生交换，当发生交换时把flag置成 1
				flag = 1;

				//---记住最后一次交换的位置
				//m = j;
			}
		}

		//---判断,如果flag=0，说明上一趟排序没有发生交换，数列已经有序，break
		if (flag == 0)
		{
			break;
		}

		//---将新的长度赋值给k
		//k = m;
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能:升序排列数组
//////输入参数:
//////输出参数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t asc_sort_double_word(uint32_t* buffer, uint16_t length)
{
	uint16_t i = 0;
	uint16_t j = 0;
	uint16_t k = length - 1;
	//uint16_t m = 0;
	uint8_t flag;
	uint32_t tmp;

	//---用k来保存新的判断条件
	for (i = 0; i < k; i++)
	{
		//---flag初始化为0
		flag = 0;
		//假设当前趟的第一个数为最值, 记在m中
		//m = i;

		//---每排序一趟，则至少有一个元素已经有序，用 j<length-i-1 可以缩小排序范围
		for (j = 0; j < (length - 1 - i); j++)
		{
			//---当前面的元素大于后面的元素时，交换位置
			if (buffer[j] > buffer[j + 1])
			{
				tmp = buffer[j];
				buffer[j] = buffer[j + 1];
				buffer[j + 1] = tmp;

				//---若程序进入if语句,则必然会发生交换，当发生交换时把flag置成 1
				flag = 1;

				//---记住最后一次交换的位置
				//m = j;
			}
		}

		//---判断,如果flag=0，说明上一趟排序没有发生交换，数列已经有序，break
		if (flag == 0)
		{
			break;
		}

		//---将新的长度赋值给k
		//k = m;
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 升序排列浮点数数组
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t asc_sort_float(float* buffer, uint16_t length)
{
	uint16_t i = 0;
	uint16_t j = 0;
	uint16_t k = length - 1;
	//uint16_t m = 0;
	uint8_t flag;
	float tmp;

	//---用k来保存新的判断条件
	for (i = 0; i < k; i++)
	{
		//---flag初始化为0
		flag = 0;
		//假设当前趟的第一个数为最值, 记在m中
		//m = i;

		//---每排序一趟，则至少有一个元素已经有序，用 j<length-i-1 可以缩小排序范围
		for (j = 0; j < (length - 1 - i); j++)
		{
			//---当前面的元素大于后面的元素时，交换位置
			if (buffer[j] > buffer[j + 1])
			{
				tmp = buffer[j];
				buffer[j] = buffer[j + 1];
				buffer[j + 1] = tmp;

				//---若程序进入if语句,则必然会发生交换，当发生交换时把flag置成 1
				flag = 1;

				//---记住最后一次交换的位置
				//m = j;
			}
		}

		//---判断,如果flag=0，说明上一趟排序没有发生交换，数列已经有序，break
		if (flag == 0)
		{
			break;
		}

		//---将新的长度赋值给k
		//k = m;
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 冒泡降序排列数据
//////输入参数:
//////输出参数:
//////说		明:现在发现降序有问题，需要后续调试
//////////////////////////////////////////////////////////////////////////////
uint8_t desc_sort_byte(uint8_t *buffer, uint16_t length)
{
	uint16_t i = 0;
	uint16_t j = 0;
	uint16_t k = length - 1;
	uint16_t m = 0;
	uint8_t flag;
	uint8_t tmp;

	//---用k来保存新的判断条件
	for (i = 0; i < k; i++)
	{
		//---flag初始化为0
		flag = 0;
		m = 0;

		//---每排序一趟，则至少有一个元素已经有序，用 j<length-i-1 可以缩小排序范围
		for (j = 0; j < (length - 1 - i); j++)
		{
			//---当前面的元素大于后面的元素时，交换位置
			if (buffer[j] < buffer[j + 1])
			{
				tmp = buffer[j + 1];
				buffer[j + 1] = buffer[j];
				buffer[j] = tmp;

				//---若程序进入if语句,则必然会发生交换，当发生交换时把flag置成 1
				flag = 1;

				//---记住最后一次交换的位置
				m = j;
			}
		}

		//---判断,如果flag=0，说明上一趟排序没有发生交换，数列已经有序，break
		if (flag == 0)
		{
			break;
		}

		//---将新的长度赋值给k
		k = m;
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 冒泡降序排列数据
//////输入参数:
//////输出参数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t desc_sort_word(uint16_t *buffer, uint16_t length)
{
	uint16_t i = 0;
	uint16_t j = 0;
	uint16_t k = length - 1;
	uint16_t tmp;

	//---用k来保存新的判断条件
	for (i = 0; i < k; i++)
	{
		for (j = 0; j < (k - i); j++)
		{
			//---当前面的元素大于后面的元素时，交换位置
			if (buffer[j] < buffer[j + 1])
			{
				tmp = buffer[j + 1];
				buffer[j + 1] = buffer[j];
				buffer[j] = tmp;
			}
		}
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t desc_sort_float(float *buffer, uint16_t length)
{
	uint16_t i = 0;
	uint16_t j = 0;
	uint16_t k = length - 1;
	float tmp;

	//---用k来保存新的判断条件
	for (i = 0; i < k; i++)
	{
		for (j = 0; j < (k - i); j++)
		{
			//---当前面的元素大于后面的元素时，交换位置
			if (buffer[j] < buffer[j + 1])
			{
				tmp = buffer[j + 1];
				buffer[j + 1] = buffer[j];
				buffer[j] = tmp;
			}
		}
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能:从指定位置开始计算平均值
//////输入参数:
//////输出参数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint16_t calc_avg_word_from_index(uint16_t *buffer, uint16_t length, uint16_t index)
{
	double sum = 0;
	uint16_t i = 0;
	for (i = index; i < length; i++)
	{
		sum += buffer[i];
	}
	return (uint16_t)(sum / (length - index));
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能:计算平均值
//////输入参数:
//////输出参数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint16_t calc_avg_word(uint16_t *buffer, uint16_t length)
{
	double sum = 0;
	uint16_t i = 0;
	for (i = 0; i < length; i++)
	{
		sum += buffer[i];
	}
	return (uint16_t)(sum / length);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能:从指定位置开始计算平均值
//////输入参数:
//////输出参数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t calc_avg_byte_from_index(uint8_t *buffer, uint16_t length, uint16_t index)
{
	double sum = 0;
	uint16_t i = 0;
	for (i = index; i < length; i++)
	{
		sum += buffer[i];
	}
	return (uint8_t)(sum / (length - index));
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能:计算平均值
//////输入参数:
//////输出参数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint16_t calc_avg_byte(uint8_t *buffer, uint16_t length)
{
	double sum = 0;
	uint16_t i = 0;
	for (i = 0; i < length; i++)
	{
		sum += buffer[i];
	}
	return (uint8_t)(sum / length);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 计算浮点数平均值
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
float calc_avg_float(float*buffer, uint16_t length)
{
	double sum = 0;
	uint16_t i = 0;
	for (i = 0; i < length; i++)
	{
		sum += buffer[i];
	}
	return (float)(sum / length);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能:从指定位置开始计算平均值
//////输入参数:
//////输出参数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint32_t calc_avg_double_word_from_index(uint32_t* buffer, uint16_t length, uint16_t index)
{
	double sum = 0;
	uint16_t i = 0;
	for (i = index; i < length; i++)
	{
		sum += buffer[i];
	}
	return (uint32_t)(sum / (length - index));
}

///////////////////////////////////////////////////////////////////////////////
//////函	   数:
//////功	   能:数组比较
//////输入参数:
//////输出参数: 0---相等；1---不相等
//////说	   明:
//////////////////////////////////////////////////////////////////////////////
uint8_t compare_byte_to_byte(uint8_t *p1, uint8_t *p2, uint16_t length)
{
	uint16_t i = 0;
	for (i = 0; i < length; i++)
	{
		if (p1[i] != p2[i])
		{
			return 1;
		}
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//////函	   数:
//////功	   能:从指定位置进行两个数组的比较
//////输入参数:
//////输出参数: 0---相等；1---不相等
//////说	   明: 指定比较数据的起始位置
//////////////////////////////////////////////////////////////////////////////
uint8_t compare_byte_to_byte_from_index(uint8_t *p1, uint8_t *p2, uint16_t index, uint16_t length)
{
	uint16_t i = 0;
	for (i = index; i < length; i++)
	{
		if (p1[i] != p2[i])
		{
			return 1;
		}
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//////函	   数:
//////功	   能:数组比较
//////输入参数:
//////输出参数: 0---相等；1---不相等
//////说	   明:
//////////////////////////////////////////////////////////////////////////////
uint8_t compare_word_to_word(uint16_t *p1, uint16_t *p2, uint16_t length)
{
	uint16_t i = 0;
	for (i = 0; i < length; i++)
	{
		if (p1[i] != p2[i])
		{
			return 1;
		}
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//////函	   数:
//////功	   能:从指定位置进行两个数组的比较
//////输入参数:
//////输出参数: 0---相等；1---不相等
//////说	   明: 指定比较数据的起始位置
//////////////////////////////////////////////////////////////////////////////
uint8_t compare_word_to_word_from_index(uint16_t *p1, uint16_t *p2, uint16_t index, uint16_t length)
{
	uint16_t i = 0;
	for (i = index; i < length; i++)
	{
		if (p1[i] != p2[i])
		{
			return 1;
		}
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//////函	   数:
//////功	   能:比较数组中的内容是不是都是指定的数据
//////输入参数:
//////输出参数: 0---相等；1---不相等
//////说	   明:
//////////////////////////////////////////////////////////////////////////////
uint8_t compare_byte(uint8_t* p1, uint8_t buffer, uint16_t length)
{
	uint16_t i = 0;
	for (i = 0; i < length; i++)
	{
		if (p1[i] !=buffer)
		{
			return 1;
		}
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//////函	   数:
//////功	   能:比较数组中的内容是不是都是指定的数据
//////输入参数:
//////输出参数: 0---相等；1---不相等
//////说	   明:
//////////////////////////////////////////////////////////////////////////////
uint8_t compare_word(uint16_t* p1, uint16_t buffer, uint16_t length)
{
	uint16_t i = 0;
	for (i = 0; i < length; i++)
	{
		if (p1[i] != buffer)
		{
			return 1;
		}
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t compare_double_word(uint32_t* p1, uint32_t buffer, uint16_t length)
{
	uint16_t i = 0;
	for (i = 0; i < length; i++)
	{
		if (p1[i] != buffer)
		{
			return 1;
		}
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能:转置数据
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t invert_uint8(uint8_t* buffer)
{
	uint8_t i;
	uint8_t temp = 0;
	//---检验数据是否为空
	if (buffer!=NULL)
	{
		for (i = 0; i < 8; i++)
		{
			if (buffer[0] & (1 << i))
			{
				temp |= 1 << (7 - i);
			}
		}
	}
	return temp;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：高低bit的交换
//////输入参	数：
//////输出参	数：
//////说		明：
//////////////////////////////////////////////////////////////////////////////
uint8_t  swap_bit_uint8(uint8_t val)
{
	val = (val << 4) | (val >> 4);
	val = ((val << 2) & 0xcc) | ((val >> 2) & 0x33);
	val = ((val << 1) & 0xaa) | ((val >> 1) & 0x55);
	return val;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能:转置数据
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint16_t invert_uint16(uint16_t* buffer)
{
	uint8_t i;
	uint16_t temp = 0;
	//---检验数据是否为空
	if (buffer != NULL)
	{
		for (i = 0; i < 16; i++)
		{
			if (buffer[0] & (1 << i))
			{
				temp |= 1 << (15 - i);
			}
		}
	}
	return temp;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能:数据比较
//////输入参	数:
//////输出参	数:0---相等，1---不相等
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t my_str_cmp(uint8_t* src, uint8_t* des, uint16_t length)
{
	uint16_t strIndex = 0;
	for (strIndex=0;strIndex<length;strIndex++)
	{
		if (src[strIndex]!=des[strIndex])
		{
			break;
		}
	}
	return ((strIndex == length) ? 0 : 1);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能:
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t my_str_cmp_index(uint8_t* src, uint8_t* des, uint16_t length,uint16_t *p_index)
{
	uint16_t str_index = 0;
	*p_index = 0;
	for (str_index = 0; str_index < length; str_index++)
	{
		if (src[str_index] != des[str_index])
		{
			*p_index=str_index;
			break;
		}
	}
	return ((str_index == length) ? 0 : 1);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能:ascii编码转换成utf8格式
//////输入参	数:isLowCase---0:转换成大写字母，1:转换成小写字母
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t ascii_to_utf8_byte(uint8_t ascii,uint8_t is_low_case)
{
	if (ascii <= 9)
	{
		ascii += '0';
	}
	else
	{
		ascii = (ascii - 10) + ((is_low_case != 0) ? ('a') : ('A'));
	}
	return ascii;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：将ascii编码转的数据换成utf8编码的数据
//////输入参	数：length,ascii数组的大小;
//////			is_low_case---0:转换成大写字母,1:转换成小写字母
//////输出参	数：无
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void ascii_to_utf8_array(uint8_t* ascii, uint8_t* utf8, uint16_t length, uint8_t is_low_case)
{
	uint16_t ascii_index = 0;
	for (ascii_index=0;ascii_index<length;ascii_index++)
	{
		(*utf8++) = ascii_to_utf8_byte((ascii[ascii_index] >> 4) & 0x0F, is_low_case);
		(*utf8++) = ascii_to_utf8_byte((ascii[ascii_index] >> 0) & 0x0F, is_low_case);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能:
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
char* my_itoa(int val, char* s, uint16_t*length, int radix)
{
	char zm[37] = "0123456789abcdefghijklmnopqrstuvwxyz";
	char aa[100] = { 0 };

	int sum = val;
	char* cp = s;
	int i = 0;
	int j=0;
	//---增加了对错误的检测
	if (radix < 2 || radix>36)
	{
		return s;
	}

	if (val < 0)
	{
		return s;
	}

	while (sum > 0)
	{
		aa[i++] = zm[sum % radix];
		sum /= radix;
	}

	for (j = i - 1; j >= 0; j--)
	{
		*cp++ = aa[j];
		//---地址偏移
		(*length)++;
	}
	*cp = '\0';
	return cp;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参	数：
//////输出参	数：
//////说		明：主要是结局strstr的局限性，遇到'\0'结束
//////////////////////////////////////////////////////////////////////////////
char* my_str_n_str(const char* src, const char* des, uint32_t length)
{
	uint32_t str_index = 0;
	const char* bp;
	const char* sp;
	//---字符串不能为空
	if ((src!=NULL)&&(des!=NULL))
	{
		//---遍历src字符串
		for (str_index  = 0;  str_index < length; str_index++)
		{
			//---用来遍历子串
			bp =(char*) &src[str_index];
			sp = des;
			do 
			{
				//---到了des的结束位置，返回src位置
				if (!*sp)
				{
					return (char*)&src[str_index];
				}
			} 
			while (*bp++==*sp++);
			//---喂狗
			WDT_RESET();
		}
	}
	return NULL;
}


///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 根据年月日计算是星期几（使用基姆拉尔森计算公式）
//////输入参数:
//////输出参数: 1---星期一；2---星期二；3---星期三；4---星期四；5---星期五；6---星期六；7---星期天；0---错误
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t calc_rtc_week(RTC_TimeType* RTCx)
{
	//---年
	int temp_y = RTCx->msg_years;
	//---月
	int temp_m = RTCx->msg_month;
	//---日
	int temp_d = RTCx->msg_day;
	//---星期
	int temp_w = -1;
	uint8_t _return = 0;
	////////////////////////////////////////////////////////////////////////////////////////////////
	////基姆拉尔森计算公式:
	////W= (d+2*m+3*(m+1)/5+y+y/4-y/100+y/400) mod 7
	////在公式中d表示日期中的日数，m表示月份数，y表示年数。
	////注意:在公式中有个与其他公式不同的地方:
	////把一月和二月看成是上一年的十三月和十四月，例:如果是2004-1-10则换算成:2003-13-10来代入公式计算
	////////////////////////////////////////////////////////////////////////////////////////////////
	if (1 == temp_m || 2 == temp_m)
	{
		temp_m += 12;
		temp_y--;
	}
	//---获取信息想你想
	temp_w = (temp_d + 1 + 2 * temp_m + 3 * (temp_m + 1) / 5 + temp_y + temp_y / 4 - temp_y / 100 + temp_y / 400) % 7;
	//---解析星期几
	switch (temp_w)
	{
		//---星期天
		case 0:
		{
			_return = 7;
			break;
		}
		//---星期一
		case 1:
		{
			_return = 1;
			break;
		}
		//---星期二
		case 2:
		{
			_return = 2;
			break;
		}
		//---星期三
		case 3:
		{
			_return = 3;
			break;
		}
		//---星期四
		case 4:
		{
			_return = 4;
			break;
		}
		//---星期五
		case 5:
		{
			_return = 5;
			break;
		}
		//---星期六
		case 6:
		{
			_return = 6;
			break;
		}
		//---星期天
		case 7:
		{
			_return = 7;
			break;
		}
		//---异常
		default:
		{
			_return = 0;
			break;
		}
	}
	return _return;
}


///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 根据年月日计算当前时间是一年的中第几天
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint16_t calc_rtc_year_day(RTC_TimeType* RTCx)
{
	uint16_t _return = 0;
	switch (RTCx->msg_month)
	{
		case 1: 
		{
			_return = 0;
			break;
		}
		case 2: 
		{
			_return = 31;
			break;
		}
		case 3: 
		{
			_return = 59;
			break;
		}
		case 4: 
		{
			_return = 90; 
			break;
		}
		case 5:
		{
			_return = 120; 
			break;
		}
		case 6:
		{
			_return = 151; 
			break;
		}
		case 7:
		{
			_return = 181; 
			break;
		}
		case 8:
		{
			_return = 212; 
			break;
		}
		case 9:
		{
			_return = 243;
			break;
		}
		case 10:
		{
			_return = 273;
			break;
		}
		case 11:
		{
			_return = 304;
			break; 
		}
		case 12:
		{
			_return = 334;
			break; 
		}
	}
	_return += RTCx->msg_day;
	//---校验是不是闰年
	if (((RTCx->msg_year % 4) == 0) && 
		((RTCx->msg_year % 100) != 0) || 
		((RTCx->msg_year % 400) == 0) && 
		(RTCx->msg_month > 2))
	{
		_return++;
	}
	return _return;
}